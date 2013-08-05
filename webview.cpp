#include "webview.h"

AWebView::AWebView(DownLoad *download, QWidget *parent)
    : m_downLoad(download)
    , QWebView(parent)
{
    //Network proxy settings, enabled flash plugins
    QNetworkProxyFactory::setUseSystemConfiguration(true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, true);

    //Add Cache
    m_ndCache = new QNetworkDiskCache(this);
    cacheLocation = QDesktopServices::storageLocation(QDesktopServices::CacheLocation);
    m_ndCache->setCacheDirectory(cacheLocation);
    page()->networkAccessManager()->setCache(m_ndCache);

    //WebView signal and slot
    connect(this, SIGNAL(loadProgress(int)), SLOT(viewProgress(int)));
    connect(this, SIGNAL(loadFinished(bool)), SLOT(viewFinished(bool)));

    //The local slot function signal associated with webkit
    connect(page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),
            this, SLOT(addJavaScriptObject()));

    //Related downloads, here set aside
    connect(m_downLoad, SIGNAL(on_clicked(QString)), this, SLOT(on_linkClicked(QString)));

    //The two link opens the page
    page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    connect(page(), SIGNAL(linkClicked(QUrl)), this, SLOT(on_linkPage(QUrl)));

    load(QUrl("http://www.83133.com/"));
    //load(QUrl("http://www.999.com/tool"));
}

void AWebView::viewProgress(int p)
{
    emit showMsg(p, title());
}

void AWebView::viewFinished(bool b)
{
    emit hideMsg(b);
    //Control page, so that picture rotation
    QString code = "$('img').each( function () { $(this).css('-webkit-transition', '-webkit-transform 2s'); $(this).css('-webkit-transform', 'rotate(360deg)') } ); undefined";
    page()->mainFrame()->evaluateJavaScript(code);
}

//Page context menu
void AWebView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(pageAction(QWebPage::Back));
    menu.addAction(pageAction(QWebPage::Forward));
    menu.addAction(pageAction(QWebPage::Reload));
    menu.exec(mapToGlobal(event->pos()));
    return;
}

void AWebView::addJavaScriptObject()
{
    //JS object name download access through an object m downLoad
	page()->mainFrame()->addToJavaScriptWindowObject("download", m_downLoad);
}

void AWebView::on_linkClicked(QString url)
{
    //After leaving open the preview of
    load(QUrl(url));
}

void AWebView::on_linkPage(QUrl url)
{
    qDebug() << url;
    load(url);
}
