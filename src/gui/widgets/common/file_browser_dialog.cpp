#include "file_browser_dialog.h"
#include <QHeaderView>
#include <QDialogButtonBox>
#include <QApplication>
#include <QDir>

FileBrowserDialog::FileBrowserDialog(Mode mode, QWidget *parent)
    : QDialog(parent), m_model(new QFileSystemModel(this)), m_view(new QTreeView(this)), m_pathEdit(new QLineEdit(this)), m_mode(mode)
{
    setWindowTitle(mode == SelectFile ? "Select File" : "Select Directory");
    resize(700, 400);

    m_model->setRootPath(QDir::rootPath());
    m_model->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files);

    m_view->setModel(m_model);
    m_view->setRootIndex(m_model->index(QDir::homePath()));
    m_view->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    m_view->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(m_view->selectionModel(), &QItemSelectionModel::currentChanged, this, &FileBrowserDialog::onSelectionChanged);

    QLabel *hint = new QLabel(tr("Select a %1 from the filesystem").arg(mode == SelectFile ? "file" : "directory"), this);

    QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttons, &QDialogButtonBox::accepted, this, &FileBrowserDialog::onAccept);
    connect(buttons, &QDialogButtonBox::rejected, this, &FileBrowserDialog::reject);

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(hint);
    topLayout->addStretch();
    topLayout->addWidget(m_pathEdit);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(m_view);
    mainLayout->addWidget(buttons);

    // initialize selection to home
    m_pathEdit->setText(QDir::homePath());
    m_selectedPath = QDir::homePath();
}

void FileBrowserDialog::onSelectionChanged(const QModelIndex &index)
{
    QString path = m_model->filePath(index);
    m_pathEdit->setText(path);
    m_selectedPath = path;
}

void FileBrowserDialog::onAccept()
{
    if (m_mode == SelectDirectory) {
        QFileInfo info(m_selectedPath);
        if (!info.exists() || !info.isDir()) {
            // select directory requirement
            return;
        }
    } else {
        QFileInfo info(m_selectedPath);
        if (!info.exists() || !info.isFile()) {
            // require file
            return;
        }
    }
    accept();
}
