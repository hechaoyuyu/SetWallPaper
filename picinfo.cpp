#include "picinfo.h"

PicInfo::PicInfo()
{

}

PicInfo::PicInfo(const QUrl &url, const QString &filename)
{
    URL = url;
    FileName = filename;
}

bool PicInfo::operator ==(const PicInfo& rhs)
{
    return URL == rhs.URL;
}

QDataStream& operator >>(QDataStream& ds, PicInfo& pic)
{
    ds >> pic.URL >> pic.FileName;
    return ds;
}

QDataStream& operator <<(QDataStream& ds, const PicInfo& pic)
{
    ds << pic.URL << pic.FileName;
    return ds;
}

