#include "download.h"

DownLoad::DownLoad(QObject *parent) :
    QObject(parent)
{
    m_cmd = new QProcess(this);
    m_cmd->setEnvironment(QProcess::systemEnvironment());
    m_accessManager = new QNetworkAccessManager(this);
    connect(m_accessManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(httpFinished(QNetworkReply*)));
    //Path
    m_path = m_settings.value("path").toString();
    if(m_path.isEmpty())
    {
        m_path = QDesktopServices::storageLocation(QDesktopServices::PicturesLocation) + QDir::separator();
        m_settings.setValue("path", m_path);
    }

    m_pixmap = new QPixmap;
    //Get resolution
    screenW = qApp->desktop()->width();
    screenH = qApp->desktop()->height();
    //Pic Cache
    m_picHistory = new PicHistory;
}

void DownLoad::downloadPic(QString url)
{
    //Start download
    qDebug() << url;
    if(m_picHistory->exist(QUrl(url)))
    {
        qDebug() << tr("Pictures downloaded");
        m_picName = m_picHistory->get(QUrl(url));
        //m_pixmap->load(m_picName);
        setWallpaper(m_picName);
    }
    else
        m_accessManager->get(QNetworkRequest(url));

    //Reserve signal, send to AWebView
    //emit on_clicked(url);
}

void DownLoad::httpFinished(QNetworkReply *reply)
{
    QUrl url = reply->url();
    QFileInfo info(url.path());
    QString fileName(info.fileName());
    if (fileName.isEmpty())
    {
        qDebug() << tr("Picture no exist");
        return;
    }

    m_picName = m_path + fileName;
#ifdef Q_WS_WIN32
    //XP only with bmp
    if(QSysInfo::windowsVersion() == QSysInfo::WV_XP)
    {
        m_picName = m_path + info.baseName() + ".bmp";
    }
#endif


    if(reply->error() == QNetworkReply::NoError)
    {
        m_pixmap->loadFromData(reply->readAll());
        m_pixmap->save(m_picName);
        //Scaled picture
        QPixmap l_pixmap = m_pixmap->scaled(screenW, screenH);
        l_pixmap.save(m_picName);

        m_picHistory->addPicture(url, m_picName);
        qDebug() << tr("Picture save as: %1").arg(m_picName);
        //!!!finished() after
        setWallpaper(m_picName);
    }
    else
    {
        qDebug() << reply->errorString();
    }
}

void DownLoad::on_prev()
{
    qDebug() << tr("Prev wallpaper");
    QString prev = m_picHistory->prev();
    if(!prev.isEmpty())
    {
        m_picName = prev;
        qDebug() << m_picName;
        //m_pixmap->load(m_picName);
        setWallpaper(m_picName);
    }
}

void DownLoad::on_next()
{
    qDebug() << tr("Next wallpaper");
    QString next = m_picHistory->next();
    if(!next.isEmpty())
    {
        m_picName = next;
        qDebug() << m_picName;
        //m_pixmap->load(m_picName);
        setWallpaper(m_picName);
    }
}

void DownLoad::on_rand()
{
    qDebug() << tr("Rand wallpaper");
    QString rand = m_picHistory->rand();
    if(!rand.isEmpty())
    {
        m_picName = rand;
        qDebug() << m_picName;
        //m_pixmap(m_picName);
        setWallpaper(m_picName);
    }
}

void DownLoad::setWallpaper(QString picname)
{
    qDebug() << picname;
#ifdef Q_OS_LINUX
    //gnome
    m_cmd->start(QString("gconftool-2 --type=string --set /desktop/gnome/background/picture_filename %1").arg(picname));
    m_cmd->waitForFinished();
    //gnomeshell
    m_cmd->start(QString("gsettings set org.gnome.desktop.background picture-uri \"file://%1\"").arg(picname));
    m_cmd->waitForFinished();
    //mate
    m_cmd->start(QString("mateconftool-2 --type=string --set /desktop/gnome/background/picture_filename %1").arg(picname));
    m_cmd->waitForFinished();
    //xfce
    m_cmd->start(QString("xfconf-query -c xfce4-desktop -p /backdrop/screen0/monitor0/image-path -s %1").arg(picname));
    m_cmd->waitForFinished();

    qDebug() << tr("Wallpaper settings successful");
    //emit kde_wallpaper(picname);
#endif

#ifdef Q_OS_MACX
    m_cmd->start(QString("defaults write com.apple.desktop Background '{default = {ImageFilePath =\"" + picname + "\"; }; }"));
    m_cmd->waitForFinished();
    m_cmd->start(QString("killAll Dock"));
    m_cmd->waitForFinished();
#endif

#ifdef Q_OS_WIN32
    QByteArray bg = picname.toLatin1();
    bool ok = SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, (void*)bg.data(),SPIF_UPDATEINIFILE | SPIF_SENDWININICHANGE);
    if(ok)
    {
        qDebug() << tr("Wallpaper settings successful");
    }
#endif
}
