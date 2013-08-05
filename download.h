#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QtGui>
#include <QDebug>
#include <QObject>
#include <QPixmap>
#include <QSettings>
#include <QtNetwork>
#include <QDesktopServices>

#ifdef Q_WS_WIN32
#include <windows.h>
#endif

#include "pichistory.h"

class DownLoad : public QObject
{
    Q_OBJECT
public:
    explicit DownLoad(QObject *parent = 0);

signals:
    //Reserve signal
    //Send to AWebView
    void on_clicked(QString);

public slots:
    void on_prev();
    void on_next();
    void on_rand();
    //JS QObject
    void downloadPic(QString);
    //Http download
    void httpFinished(QNetworkReply*);

private:
    void setWallpaper(QString);

private:
    QProcess *m_cmd;
    QPixmap *m_pixmap;
    QSettings m_settings;
    int screenW, screenH;
    PicHistory *m_picHistory;
    QString m_path, m_picName;
    QNetworkAccessManager *m_accessManager;
};

#endif // DOWNLOAD_H
