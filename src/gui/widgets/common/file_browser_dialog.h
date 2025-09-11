#ifndef GUI_WIDGETS_COMMON_FILE_BROWSER_DIALOG_H
#define GUI_WIDGETS_COMMON_FILE_BROWSER_DIALOG_H

#include <QDialog>
#include <QFileSystemModel>
#include <QTreeView>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

class FileBrowserDialog : public QDialog {
    Q_OBJECT
public:
    enum Mode { SelectFile, SelectDirectory };

    explicit FileBrowserDialog(Mode mode = SelectFile, QWidget *parent = nullptr);
    ~FileBrowserDialog() override = default;

    QString selectedPath() const { return m_selectedPath; }

    // Convenience static function
    static QString getPath(Mode mode, QWidget *parent = nullptr) {
        FileBrowserDialog dlg(mode, parent);
        if (dlg.exec() == QDialog::Accepted) return dlg.selectedPath();
        return QString();
    }

private slots:
    void onAccept();
    void onSelectionChanged(const QModelIndex &index);

private:
    QFileSystemModel *m_model;
    QTreeView *m_view;
    QLineEdit *m_pathEdit;
    Mode m_mode;
    QString m_selectedPath;
};

#endif // GUI_WIDGETS_COMMON_FILE_BROWSER_DIALOG_H
