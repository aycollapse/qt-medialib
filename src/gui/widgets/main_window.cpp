// mainwindow.cpp
#include <QShortcut>
#include <QKeySequence>
#include <QWidgetAction>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QPushButton>
#include <QLabel>
#include <QToolBar>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QDebug>
#include <QPlainTextEdit>
#include <QSlider>
#include <QSpinBox>
#include <QComboBox>
#include <QFormLayout>
#include <QFile>
#include <QFileInfo>
#include <QDir>

#include "main_window.h"
#include "../../core/models/book.h"
#include "../../core/models/movie.h"
#include "../../core/models/videogame.h"
#include "../../core/models/manager.h"
#include "../visitors/media_details_visitor.h"
#include "common/file_browser_dialog.h"
#include "common/help_dialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
}

MainWindow::~MainWindow()
{
    clearDetailsView(); 
}

void MainWindow::setupUI()
{
    this->setObjectName("MainWindow");
    QMenuBar *menuBar = new QMenuBar(this);

    QAction *homeAction = new QAction(QIcon(":/icons/home.png"), "", this);
    homeAction->setToolTip("Home");
    homeAction->setIconVisibleInMenu(true);
    connect(homeAction, &QAction::triggered, this, &MainWindow::onHomeClicked);
    menuBar->addAction(homeAction);

    QMenu *optionsMenu = new QMenu(this);
    optionsMenu->setIcon(QIcon(":/icons/settings.png"));
    optionsMenu->setToolTipsVisible(true);
    optionsMenu->setToolTip("Options");
    QAction *exportAction = new QAction( "Export", this);
    QAction *importAction = new QAction( "Import", this);
    connect(exportAction, &QAction::triggered, this, &MainWindow::onExportClicked);
    connect(importAction, &QAction::triggered, this, &MainWindow::onImportClicked);
    optionsMenu->addAction(exportAction);
    optionsMenu->addAction(importAction);
    menuBar->addMenu(optionsMenu);

    QAction *helpAction = new QAction(QIcon(":/icons/help.png"), "", this);
    helpAction->setToolTip("Help");
    helpAction->setIconVisibleInMenu(true);
    connect(helpAction, &QAction::triggered, this, &MainWindow::onHelpClicked);
    menuBar->addAction(helpAction);


    searchBar = new SearchBar(this);
    connect(searchBar, &SearchBar::filterChanged, this, &MainWindow::applyFilter);


    addMediaButton = new QToolButton(this);
    addMediaButton->setText("Add Media");
    addMediaButton->setIcon(QIcon(":/icons/add.png")); 
    addMediaButton->setPopupMode(QToolButton::InstantPopup);
    setupAddMenu();


    QWidget *searchContainer = new QWidget(this);
    searchContainer->setObjectName("SearchContainer");
    QHBoxLayout *searchLayout = new QHBoxLayout(searchContainer);
    searchLayout->setContentsMargins(0,0,0,0);
    searchLayout->addWidget(addMediaButton);
    searchLayout->addStretch(); 
    searchLayout->addWidget(searchBar);

    menuBar->setCornerWidget(searchContainer, Qt::TopRightCorner);
    setMenuBar(menuBar);

    stackedWidget = new QStackedWidget(this);
    

    homeView = new QWidget(this);
    homeView->setObjectName("HomeView");
    QVBoxLayout *homeLayout = new QVBoxLayout(homeView);
    QWidget *flowContainer = new QWidget(homeView);
    flowLayout = new FlowLayout(flowContainer, 10, 10, 10);
    flowContainer->setLayout(flowLayout);
    flowContainer->setObjectName("FlowContainer");

    QScrollArea *scrollArea = new QScrollArea(homeView);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(flowContainer);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    homeLayout->addWidget(scrollArea);

    stackedWidget->addWidget(homeView);
    setCentralWidget(stackedWidget);

    QFile styleFile("src/gui/style/theme.qss");
    if (!styleFile.exists()) {
        styleFile.setFileName(QStringLiteral(":/gui/style/theme.qss"));
    }
    if (styleFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString stylesheet = QString::fromUtf8(styleFile.readAll());
        this->setStyleSheet(stylesheet);
        styleFile.close();
    }

    detailsView = nullptr;

    updateHomeView();
    
    resize(1000, 600);
    

    this->setFocus();


    // Ctrl+Q -> Quit
    auto quitShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Q), this);
    connect(quitShortcut, &QShortcut::activated, this, &QWidget::close);

    // Ctrl+E -> Export
    auto exportShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_E), this);
    connect(exportShortcut, &QShortcut::activated, this, &MainWindow::onExportClicked);

    // Ctrl+I -> Import
    auto importShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_I), this);
    connect(importShortcut, &QShortcut::activated, this, &MainWindow::onImportClicked);

    // Ctrl+F -> Search
    auto searchShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_F), this);
    connect(searchShortcut, &QShortcut::activated, this, [this]() 
    {
        searchBar->getSearchInput()->setFocus();
        searchBar->getSearchInput()->selectAll();
    });

    // Enter/Esc -> Exit search
    auto enterShortcut = new QShortcut(QKeySequence(Qt::Key_Return), searchBar);
    auto escapeShortcut = new QShortcut(QKeySequence(Qt::Key_Escape), searchBar);
    connect(enterShortcut, &QShortcut::activated, this, [this]() {
        this->setFocus();
    });
    connect(escapeShortcut, &QShortcut::activated, this, [this]() {
        this->setFocus();
    });
}

void MainWindow::setupAddMenu()
{
    auto *menu = new QMenu(this);
    QStringList mediaTypes = {"Book", "Movie", "VideoGame"};
    
    for (const QString &type : mediaTypes) {
        QAction *action = menu->addAction(type);
        connect(action, &QAction::triggered, this, [this, type]() {
            onCreateNewMedia(type);
        });
    }

    addMediaButton->setMenu(menu);
}

void MainWindow::applyFilter(const MediaFilter::FilterSettings& settings)
{
    auto& mediaVector = Manager::getInstance().getMediaVector();
    
    for (size_t i = 0; i < mediaVector.size() && i < mediaCards.size(); ++i) {
        bool visible = MediaFilter::matchesFilter(mediaVector[i].get(), settings);
        mediaCards[i]->setVisible(visible);
    }
}

void MainWindow::updateHomeView()
{
    mediaCards.clear();
    QLayoutItem *item;
    while ((item = flowLayout->takeAt(0)) != nullptr) {
        if (QWidget *widget = item->widget()) {
            delete widget;
        }
        delete item;
    }

    auto& mediaVector = Manager::getInstance().getMediaVector();
    
    for (const auto& media : mediaVector) {
        if (!media) continue;

        MediaCardVisitor visitor;
        media->accept(visitor);
        QWidget *card = visitor.getWidget();
        
        AbstractMedia* mediaPtr = media.get();
        
        if (QPushButton *imageButton = card->findChild<QPushButton*>("imageButton")) {
            connect(imageButton, &QPushButton::clicked, this, [this, mediaPtr]() {
                onMediaItemClicked(mediaPtr);
            });
        }

        flowLayout->addWidget(card);
        mediaCards.push_back(card);
    }

    applyFilter(searchBar->getCurrentFilter());
}

void MainWindow::showDetailsView(AbstractMedia* media)
{
    currentMedia = media;

    if (detailsView) {
        stackedWidget->removeWidget(detailsView);
        delete detailsView;
    }

    detailsView = new QWidget(this);
    detailsView->setObjectName("DetailsView");
    QVBoxLayout *layout = new QVBoxLayout(detailsView);

    QString titleText;
    if (media) {
        if (dynamic_cast<Book*>(media)) {
            titleText = "Edit Book";
        } else if (dynamic_cast<Movie*>(media)) {
            titleText = "Edit Movie";
        } else if (dynamic_cast<Videogame*>(media)) {
            titleText = "Edit Video Game";
        }
    } else {
        titleText = QString("New %1").arg(selectedMediaType);
    }
    
    QLabel* titleLabel = new QLabel(titleText, detailsView);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    layout->addWidget(titleLabel);

    MediaDetailsVisitor visitor;
    if (media) {
        media->accept(visitor);
    } else {
        if (selectedMediaType == "Book") {
            Book emptyBook;
            visitor.visit(emptyBook);
        } else if (selectedMediaType == "Movie") {
            Movie emptyMovie;
            visitor.visit(emptyMovie);
        } else if (selectedMediaType == "VideoGame") {
            Videogame emptyGame;
            visitor.visit(emptyGame);
        }
    }
    
    QWidget* formWidget = visitor.getWidget();
    formWidget->setObjectName("detailsForm");  
    layout->addWidget(formWidget);

    QLineEdit* bannerEdit = formWidget->findChild<QLineEdit*>("bannerPath");
    if (bannerEdit) {
        QWidget* pickerContainer = new QWidget(detailsView);
        QHBoxLayout* pickerLayout = new QHBoxLayout(pickerContainer);
        pickerLayout->setContentsMargins(0,0,0,0);
        pickerLayout->addStretch();
        QPushButton* pickButton = new QPushButton("Choose Banner", pickerContainer);
        pickButton->setIcon(QIcon(":/icons/addpath.png"));
        pickerLayout->addWidget(pickButton);
        layout->addWidget(pickerContainer);

        connect(pickButton, &QPushButton::clicked, this, [this, bannerEdit]() {
            QString path = FileBrowserDialog::getPath(FileBrowserDialog::SelectFile, this);
            if (path.isEmpty()) return;

            QString destPath = path;
            QString dataFolder = Manager::getInstance().getDefaultData();
            QDir imagesDir(QDir(dataFolder).filePath("images"));
            if (!imagesDir.exists()) {
                QDir().mkpath(imagesDir.absolutePath());
            }

            QFileInfo srcInfo(path);
            QString baseName = srcInfo.fileName();
            QString candidate = imagesDir.filePath(baseName);

            if (QFile::exists(candidate)) {
                QString base = srcInfo.completeBaseName();
                QString suf = srcInfo.suffix();
                int i = 1;
                QString tryName;
                do {
                    if (suf.isEmpty()) tryName = QString("%1_%2").arg(base).arg(i);
                    else tryName = QString("%1_%2.%3").arg(base).arg(i).arg(suf);
                    candidate = imagesDir.filePath(tryName);
                    ++i;
                } while (QFile::exists(candidate) && i < 1000);
            }

            bool copied = false;
            if (!QFile::exists(candidate)) {
                copied = QFile::copy(path, candidate);
            }

            if (copied) destPath = candidate;

            bannerEdit->setText(destPath);
         });
    }

    QWidget* buttonContainer = new QWidget(detailsView);
    QHBoxLayout* buttonLayout = new QHBoxLayout(buttonContainer);
    buttonLayout->setContentsMargins(0, 0, 0, 0);

    buttonLayout->addStretch();

    QPushButton *backButton = new QPushButton("Back", buttonContainer);
    backButton->setIcon(QIcon(":/icons/back.png"));
    connect(backButton, &QPushButton::clicked, this, &MainWindow::onBackToHomeClicked);
    buttonLayout->addWidget(backButton);

    QPushButton *saveButton = new QPushButton("Save", buttonContainer);
    saveButton->setIcon(QIcon(":/icons/save.png"));
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::onSaveMediaClicked);
    buttonLayout->addWidget(saveButton);

    if (media) {
        QPushButton *deleteButton = new QPushButton("Delete", buttonContainer);
        deleteButton->setStyleSheet("QPushButton { color: red; }");
        connect(deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteMediaClicked);
        buttonLayout->addWidget(deleteButton);
    }

    layout->addWidget(buttonContainer);

    stackedWidget->addWidget(detailsView);
    stackedWidget->setCurrentWidget(detailsView);
}

void MainWindow::clearDetailsView()
{
    if (detailsView) {
        stackedWidget->removeWidget(detailsView);
        detailsView->deleteLater(); 
        detailsView = nullptr;
    }
    stackedWidget->setCurrentWidget(homeView);
}

void MainWindow::onHomeClicked()
{
    clearDetailsView();
    updateHomeView();
}

void MainWindow::onExportClicked() {
    QString path = FileBrowserDialog::getPath(FileBrowserDialog::SelectDirectory, this);
    if (path.isEmpty()) return;

    bool ok = Manager::getInstance().exportData(path);
    if (!ok) {
        qWarning() << "Export failed to" << path;
    } else {
        qDebug() << "Exported to" << path;
    }
}

void MainWindow::onImportClicked() {

    QString path = FileBrowserDialog::getPath(FileBrowserDialog::SelectDirectory, this);
    if (path.isEmpty()) return;

    bool ok = Manager::getInstance().importData(path);
    if (!ok) {
        qWarning() << "Import failed from" << path;
    } else {
        qDebug() << "Imported from" << path;
        updateHomeView();
    }
}

void MainWindow::onHelpClicked() {
    HelpDialog dlg(this);
    dlg.exec();
}

void MainWindow::onMediaItemClicked(AbstractMedia* media)
{
    showDetailsView(media);
}

void MainWindow::onCreateNewMedia(const QString& mediaType)
{
    selectedMediaType = mediaType; 
    showDetailsView(nullptr); 
}

void MainWindow::onBackToHomeClicked()
{
    clearDetailsView();
}

void MainWindow::onSaveMediaClicked()
{
    qDebug() << "Save button clicked";
    
    QWidget* formWidget = detailsView->findChild<QWidget*>("detailsForm");
    if (!formWidget) {
        qDebug() << "Error: no details form found";
        return;
    }

    QMap<QString, QString> formData;

    QList<QLineEdit*> lineEdits = formWidget->findChildren<QLineEdit*>();
    for (QLineEdit* edit : lineEdits) {
        QString key = edit->objectName();
        if (key.isEmpty()) continue;
        formData[key] = edit->text();
        qDebug() << "LineEdit field:" << key << "=" << edit->text();
    }
    QList<QDateEdit*> dateEdits = formWidget->findChildren<QDateEdit*>();
    for (QDateEdit* edit : dateEdits) {
        QString key = edit->objectName();
        if (key.isEmpty()) continue;
        formData[key] = edit->date().toString("yyyy-MM-dd");
        qDebug() << "Date field:" << key << "=" << formData[key];
    }

    QSpinBox* hoursSpin = formWidget->findChild<QSpinBox*>("durationHours");
    QSpinBox* minutesSpin = formWidget->findChild<QSpinBox*>("durationMinutes");
    if (hoursSpin || minutesSpin) {
        int h = hoursSpin ? hoursSpin->value() : 0;
        int m = minutesSpin ? minutesSpin->value() : 0;
        QTime t(h, m, 0);
        formData["duration"] = t.toString("hh:mm:ss");
        formData["durationHours"] = QString::number(h);
        formData["durationMinutes"] = QString::number(m);
        qDebug() << "Duration captured from spinboxes:" << formData["duration"] << "(h=" << h << ", m=" << m << ")";
    } else {
        QList<QTimeEdit*> timeEdits = formWidget->findChildren<QTimeEdit*>();
        for (QTimeEdit* edit : timeEdits) {
            QString key = edit->objectName();
            if (key.isEmpty()) continue;
            formData[key] = edit->time().toString("hh:mm:ss");
            qDebug() << "Time field:" << key << "=" << formData[key];
        }
    }

    QList<QPlainTextEdit*> plainEdits = formWidget->findChildren<QPlainTextEdit*>();
    for (QPlainTextEdit* edit : plainEdits) {
        QString key = edit->objectName();
        if (key.isEmpty()) continue;
        formData[key] = edit->toPlainText();
        qDebug() << "PlainText field:" << key << "=" << formData[key];
    }

    // Collect combobox values (e.g., videogame mode)
    QList<QComboBox*> comboBoxes = formWidget->findChildren<QComboBox*>();
    for (QComboBox* cb : comboBoxes) {
        QString key = cb->objectName();
        if (key.isEmpty()) continue;
        formData[key] = cb->currentText();
        qDebug() << "ComboBox field:" << key << "=" << formData[key];
    }

    if (!formData.contains("rating")) {
        QList<QSlider*> sliders = formWidget->findChildren<QSlider*>();
        for (QSlider* slider : sliders) {
            if (slider->objectName().isEmpty() || slider->objectName() == "ratingSlider") {
                float realValue = slider->value() / 2.0f;
                formData["rating"] = QString::number(realValue, 'f', 1);
                qDebug() << "Captured rating from slider=" << realValue;
                break;
            }
        }
    }

    if (currentMedia) {
        if (dynamic_cast<Book*>(currentMedia)) formData["type"] = "book";
        else if (dynamic_cast<Movie*>(currentMedia)) formData["type"] = "movie";
        else if (dynamic_cast<Videogame*>(currentMedia)) formData["type"] = "videogame";
        qDebug() << "Editing existing media of type:" << formData["type"];
    } else {
        formData["type"] = selectedMediaType.toLower();
        qDebug() << "Creating new media of type:" << formData["type"];
    }

    QUuid id = currentMedia ? currentMedia->getId() : QUuid();
    qDebug() << "Emitting saveMediaRequested with id:" << (id.isNull() ? "(new)" : id.toString());
    emit saveMediaRequested(id, formData);

    clearDetailsView();
    updateHomeView();
}

void MainWindow::onDeleteMediaClicked()
{
    if (!currentMedia) return;

    qDebug() << "Delete clicked for media with ID:" << currentMedia->getId();
    emit deleteMediaRequested(currentMedia->getId());
    clearDetailsView();
    updateHomeView();
}
