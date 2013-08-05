#ifndef CONTENT_H
#define CONTENT_H

#include <QMenu>
#include <QDebug>
#include <QWidget>
#include <QWebView>
#include <QWebPage>
#include <QWebFrame>
#include <QtNetwork>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QDesktopServices>
#include "download.h"
//#include "kdewallpaper.h"

class AWebView : public QWebView
{
    Q_OBJECT
public:
    AWebView(DownLoad *download, QWidget *parent = 0);

protected:
    void contextMenuEvent(QContextMenuEvent *event);

signals:
    void hideMsg(bool);
    void showMsg(int, QString);


private slots:
    //WebView signal and slot
    void viewProgress(int);
    void viewFinished(bool);

    //The two link opens the page
    void on_linkPage(QUrl);
    //Open picture
    void on_linkClicked(QString);
    //Will be exposed to the Qt WebKit QObject function
    void addJavaScriptObject();

private:
    //Use local cache
    QString cacheLocation;
    QNetworkDiskCache *m_ndCache;
    //QObject object exposed to the local webkit and js
    DownLoad *m_downLoad;
    //KdeWallpaper *m_kdeWallpaper;
};

#endif // CONTENT_H
