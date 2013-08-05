#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QFrame(parent)
    , m_pressMouse(false)
{
    //Init windows
    initWindow();

    m_downLoad = new DownLoad(this);
    m_titleBar = new TitleBar(this);
    m_webView = new AWebView(m_downLoad, this);
    m_statuBar = new StatuBar(this);
    m_setPaper = new SetPaper(this);

    connect(m_webView, SIGNAL(hideMsg(bool)),
            m_statuBar, SLOT(hideMsgBar(bool)));
    connect(m_webView, SIGNAL(showMsg(int,QString)),
            m_statuBar, SLOT(showMsgBar(int,QString)));

    m_Layout = new QVBoxLayout(this);
    m_Layout->addWidget(m_titleBar);
    m_Layout->addWidget(m_webView);
    m_Layout->addWidget(m_statuBar);

    m_Layout->setMargin(0);
    m_Layout->setSpacing(0);

    //Create systemtray
    createActions();
}

void MainWindow::initWindow()
{
    //Set title and icons
    setWindowTitle(tr("Change WallPaper"));
    //setWindowIcon(QIcon(":/icons/title"));

    setAttribute(Qt::WA_DeleteOnClose);

    //Set style
    setFrameShape(Panel);
    setFrameShadow(QFrame::Raised);

    //Track mouse
    setMouseTracking(true);

    //Off system default title
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint | Qt::WindowSystemMenuHint);

    //Background translucent
    //setWindowOpacity(1);
    //setAttribute(Qt::WA_TranslucentBackground);

    //Fill background
    //setStyleSheet("QFrame {background-image:url(:/icons/back);border:1px solid black;}");

    //Set window size
    setSizeWindow();
}

void MainWindow::setSizeWindow()
{
    //Systemic resolution
    int w = qApp->desktop()->width();
    int h = qApp->desktop()->height();
    //Set windows min and max
    setMinimumSize(900, 500);
    setMaximumSize(w, h);
    //Center show
    move((w - 900)/2, (h - 500)/2);
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    //Linear gradient
    QLinearGradient objLinear(rect().topLeft(), rect().bottomRight());
    objLinear.setColorAt(0,Qt::red);
    objLinear.setColorAt(0.2,Qt::cyan);
    objLinear.setColorAt(0.4,Qt::yellow);
    objLinear.setColorAt(0.5,Qt::green);
    objLinear.setColorAt(0.6,Qt::gray);
    objLinear.setColorAt(0.8,Qt::blue);
    objLinear.setColorAt(1,Qt::magenta);
    painter.fillRect(rect(), objLinear);
//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing);
//    QLinearGradient linearGradient(rect().topLeft(), rect().bottomRight());
//    //从点（100，150）开始到点（300，150）结束，确定一条直线
//    linearGradient.setColorAt(0,Qt::red);
//    linearGradient.setColorAt(0.2,Qt::black);
//    linearGradient.setColorAt(0.4,Qt::yellow);
//    linearGradient.setColorAt(0.6,Qt::white);
//    linearGradient.setColorAt(0.8,Qt::green);
//    linearGradient.setColorAt(1,Qt::blue);
//    //将直线开始点设为0，终点设为1，然后分段设置颜色
//    painter.fillRect(rect(), linearGradient);
//    //绘制矩形，线性渐变线正好在矩形的水平中心线上
}

//!!22

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    m_oldPos = event->pos();
    m_pressMouse = (event->button() == Qt::LeftButton);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();

    if(m_pressMouse)
    {
        int dx = x - m_oldPos.x();
        int dy = y - m_oldPos.y();

        QRect g = geometry();

        if(left)
            g.setLeft(g.left() + dx);
        if(right)
            g.setRight(g.right() + dx);
        if(bottom)
            g.setBottom(g.bottom() + dy);
        setGeometry(g);

        m_oldPos = QPoint(!left ? event->x() : m_oldPos.x(), event->y());
    }
    else if(!isMaximized())
    {
        QRect r = rect();
        left = qAbs(x - r.left()) <= 5;
        right = qAbs(x - r.right()) <= 5;
        bottom = qAbs(y - r.bottom()) <= 5;
        bool hor = (left | right) && (y >= 24); //fix title

        if(hor && bottom)
        {
            if(left)
                setCursor(Qt::SizeBDiagCursor);
            else
                setCursor(Qt::SizeFDiagCursor);
        }
        else if(hor)
        {
            //!!11
            setCursor(Qt::SizeHorCursor);
        }
        else if(bottom)
        {
            setCursor(Qt::SizeVerCursor);
        }
        else
        {
            setCursor(Qt::ArrowCursor);
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_pressMouse = false;
        setCursor(Qt::ArrowCursor);
        left = right = bottom = false;
    }
}

void MainWindow::createActions()
{
    QMenu *menu = new QMenu;
    menu->addAction(QIcon(":/icons/prev"), tr("Prev"), m_downLoad, SLOT(on_prev()));
    menu->addAction(QIcon(":/icons/next"), tr("Next"), m_downLoad, SLOT(on_next()));
    menu->addAction(QIcon(":/icons/settings"), tr("Settings"), m_setPaper, SLOT(on_settings()));
    menu->addSeparator();
    menu->addAction(QIcon(":/icons/exit"), tr("Exit"), qApp, SLOT(quit()));

    m_systemTray = new QSystemTrayIcon(this);
    m_systemTray->setIcon(QIcon(":/icons/logo"));
    m_systemTray->setToolTip(tr("Change WallPaper"));
    m_systemTray->setContextMenu(menu);
    m_systemTray->show();
    connect(m_systemTray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason activationReason)
{
    switch(activationReason)
    {
    case QSystemTrayIcon::Unknown:
        break;
    case QSystemTrayIcon::Context: //right click
        break;
    case QSystemTrayIcon::DoubleClick:
        break;
    case QSystemTrayIcon::Trigger: //left click
        if (isVisible())
            hide();
        else
        {
            show();
            setWindowState(this->windowState() & (~Qt::WindowMinimized | Qt::WindowActive));
            setFocus();
            activateWindow();
        }
        break;
    case QSystemTrayIcon::MiddleClick:
        m_systemTray->showMessage(tr("Change WallPaper"), tr("Welcome to use wallpaper set up software"), QSystemTrayIcon::Information, 10000);
        break;
    }
}

void MainWindow::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::WindowStateChange)
    {
        if(isMinimized())
        {
            hide();
        }
        else
        {
            show();
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(isVisible())
    {
        hide();
        event->ignore();
    }
}

MainWindow::~MainWindow()
{
    delete m_downLoad;
    delete m_titleBar;
    delete m_webView;
    delete m_statuBar;
}
