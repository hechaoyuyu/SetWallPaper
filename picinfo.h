#ifndef PICINFO_H
#define PICINFO_H

#include <QUrl>
class PicInfo
{
public:
    QUrl URL;
    QString FileName;

    PicInfo();
    PicInfo(const QUrl &, const QString &);
    bool operator ==(const PicInfo &);
    friend QDataStream& operator >>(QDataStream&, PicInfo&);
    friend QDataStream& operator <<(QDataStream&, const PicInfo&);
};

#endif // PICINFO_H
