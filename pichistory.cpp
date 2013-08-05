#include "pichistory.h"

PicHistory::PicHistory()
{
    QString l_path = QDesktopServices::storageLocation(QDesktopServices::PicturesLocation) + QDir::separator();
    m_historyFile = l_path + "Thumbs.db";
    m_picInfo = NULL;
    load();
    current = m_picInfo->count() - 1;
}

void PicHistory::load()
{
    QFile file(m_historyFile);
    if(!file.exists())
    {
        file.open(QFile::WriteOnly);
        file.close();
    }
    if(file.open(QFile::ReadOnly))
    {
        QDataStream in(&file);
        if(m_picInfo == NULL)
            m_picInfo = new QList<PicInfo>();
        else
            m_picInfo->clear();
        in >> *m_picInfo;
        file.close();
    }
}

QString PicHistory::prev()
{
    if(m_picInfo->count() == 0)
        return QString();
    current--;
    if(current < 0)
        current = m_picInfo->count() - 1;
    return m_picInfo->at(current).FileName;
}

QString PicHistory::next()
{
    if(m_picInfo->count() == 0)
        return QString();
    current++;
    if(current >= m_picInfo->count())
        current = 0;
    return m_picInfo->at(current).FileName;
}

QString PicHistory::rand()
{
    current = qrand() % m_picInfo->count();
    return m_picInfo->at(current).FileName;
}

QString PicHistory::get(QUrl url)
{
    return m_picInfo->at(m_picInfo->indexOf(PicInfo(url, ""))).FileName;
}

void PicHistory::save()
{
    QFile file(m_historyFile);
    if(file.open(QFile::WriteOnly))
    {
        QDataStream out(&file);
        out << *m_picInfo;
        file.close();
    }
}

bool PicHistory::exist(QUrl url)
{
    return m_picInfo->contains(PicInfo(url, ""));
}

void PicHistory::delPicture(QUrl &url)
{
    int del = m_picInfo->indexOf(PicInfo(url, ""));
    m_picInfo->removeAt(del);
    if(del == current)
    {
        current = m_picInfo->count() - 1;
    }
    save();
}

void PicHistory::addPicture(QUrl &url, QString &filename)
{
    m_picInfo->append(PicInfo(url, filename));
    current = m_picInfo->count() - 1;
    save();
}
