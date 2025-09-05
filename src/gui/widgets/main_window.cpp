// mainwindow.cpp

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

#include "main_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QMenuBar *menuBar = new QMenuBar(this);

    QAction *homeAction = new QAction("Home", this);
    connect(homeAction, &QAction::triggered, this, &MainWindow::onHomeClicked);
    menuBar->addAction(homeAction);

    QMenu *optionsMenu = new QMenu("Options", this);
    QAction *exportAction = new QAction("Export", this);
    QAction *importAction = new QAction("Import", this);
    connect(exportAction, &QAction::triggered, this, &MainWindow::onExportClicked);
    connect(importAction, &QAction::triggered, this, &MainWindow::onImportClicked);
    optionsMenu->addAction(exportAction);
    optionsMenu->addAction(importAction);
    menuBar->addMenu(optionsMenu);

    QAction *helpAction = new QAction("Help", this);
    connect(helpAction, &QAction::triggered, this, &MainWindow::onHelpClicked);
    menuBar->addAction(helpAction);

    searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText("Search...");
    connect(searchBar, &QLineEdit::textChanged, this, &MainWindow::onSearchTextChanged);

    QWidget *searchContainer = new QWidget(this);
    QHBoxLayout *searchLayout = new QHBoxLayout(searchContainer);
    searchLayout->setContentsMargins(0,0,0,0);
    searchLayout->addWidget(searchBar);

    menuBar->setCornerWidget(searchContainer, Qt::TopRightCorner);


    setMenuBar(menuBar);
    centralWidgetContainer = new QWidget(this);
    flowLayout = new FlowLayout(centralWidgetContainer, 10, 10, 10);

    // placehlder
    for (int i = 0; i < 20; ++i) {
        QPushButton *card = new QPushButton(QString("Item %1").arg(i+1));
        card->setFixedSize(150, 200);
        flowLayout->addWidget(card);
    }

    centralWidgetContainer->setLayout(flowLayout);

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(centralWidgetContainer);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); 

    setCentralWidget(scrollArea);
    resize(1000, 600);
}

void MainWindow::onHomeClicked() {
    qDebug() << "Home clicked";
}

void MainWindow::onExportClicked() {
    qDebug() << "Export clicked";
}

void MainWindow::onImportClicked() {
    qDebug() << "Import clicked";
}

void MainWindow::onHelpClicked() {
    qDebug() << "Help clicked";
}

void MainWindow::onSearchTextChanged(const QString &text) {
    qDebug() << "Search:" << text;
}
