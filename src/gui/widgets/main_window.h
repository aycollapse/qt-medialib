#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QLineEdit>
#include "common/flow_layout.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void onHomeClicked();
    void onExportClicked();
    void onImportClicked();
    void onHelpClicked();
    void onSearchTextChanged(const QString &text);

private:
    QWidget *centralWidgetContainer;
    FlowLayout *flowLayout;
    QLineEdit *searchBar;
};

#endif // MAIN_WINDOW_H