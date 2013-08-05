#ifndef PICHISTORY_H
#define PICHISTORY_H

#include <QUrl>
#include <QDir>
#include <QFile>
#include <QDesktopServices>
#include "picinfo.h"

class PicHistory
{
public:
    PicHistory();
    void load();

public:
    QString prev();
    QString next();
    QString rand();
    QString get(QUrl);

public:
    void save();
    bool exist(QUrl);
    void delPicture(QUrl &);
    void addPicture(QUrl &, QString &);

private:
    int current;
    QString m_historyFile;
    QList<PicInfo> *m_picInfo;
};
#endif // PICHISTORY_H
