#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QStackedWidget>
#include <QToolButton>
#include <QMenu>
#include <QActionGroup>
#include <QPushButton>
#include "common/flow_layout.h"
#include "search_bar.h"
#include "../../core/models/abstract_media.h"
#include "../../core/search/media_filter.h"
#include "../visitors/media_card_visitor.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

signals:
    void saveMediaRequested(const QUuid &id, const QMap<QString, QString> &data);
    void deleteMediaRequested(const QUuid &id);

private slots:
    void onHomeClicked();
    void onExportClicked();
    void onImportClicked();
    void onHelpClicked();
    void onMediaItemClicked(AbstractMedia* media);
    void onCreateNewMedia(const QString& mediaType);
    void onBackToHomeClicked();
    void onSaveMediaClicked();
    void onDeleteMediaClicked();

private:
    void setupUI();
    void setupAddMenu();
    void updateHomeView();
    void showDetailsView(AbstractMedia* media = nullptr);
    void clearDetailsView();
    void applyFilter(const MediaFilter::FilterSettings& settings);

private:
    QStackedWidget *stackedWidget;
    QWidget *homeView;
    QWidget *detailsView;
    FlowLayout *flowLayout;
    SearchBar *searchBar;
    QToolButton *addMediaButton;
    AbstractMedia* currentMedia;
    QString selectedMediaType;  // Track type when creating new media
    std::vector<QWidget*> mediaCards; // Store media cards for filtering
};

#endif // MAIN_WINDOW_H