#include "setpaper.h"

SetPaper::SetPaper(QWidget *parent)
    : QFrame(parent, Qt::Dialog|Qt::FramelessWindowHint)
{ 
    //Set style
    setFrameShape(StyledPanel);
    setFrameShadow(QFrame::Raised);
    resize(350, 150);

    //Create title
    createTitle();

    //Create options
    createOptions();

    //Create button
    createButtons();

    //Create layout
    createLayout();
}

void SetPaper::createButtons()
{
    QHBoxLayout *l_buttonLayout = new QHBoxLayout;
    m_okButton = new QPushButton;
}

void SetPaper::createLayout()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(m_titleLayout);
    mainLayout->addWidget(m_basicGroup);
    mainLayout->addWidget(m_saveGroup);

    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);
}

void SetPaper::createOptions()
{
    //Basic settings
    m_basicGroup = new QGroupBox(tr("Basic Setting"));
    //Minimize to tray
    m_miniTotray = new QCheckBox(tr("Minimize to tray"));
    //Close to tray
    m_closeTotray = new QCheckBox(tr("Close to tray"));

    QHBoxLayout *l_totray = new QHBoxLayout;
    l_totray->addWidget(m_miniTotray);
    l_totray->addWidget(m_closeTotray);

    //Automatically switch wallpaper
    autoSetWallpaper();

    QVBoxLayout *basicLayout = new QVBoxLayout;
    basicLayout->addLayout(l_totray);
    //basicLayout->addWidget(m_closeTotray);
    basicLayout->addWidget(m_autoSetpaper);
    basicLayout->addLayout(m_valueLayout);
    m_basicGroup->setLayout(basicLayout);

    //Save picture path
    m_saveGroup = new QGroupBox(tr("Wallpaper save location"));
    m_dirEdit= new QLineEdit(QDesktopServices::storageLocation(QDesktopServices::PicturesLocation) + QDir::separator());
    QPushButton *browseButton = new QPushButton(tr("Browse..."));
    connect(browseButton, SIGNAL(clicked()), this, SLOT(on_browse()));

    QHBoxLayout *saveLayout = new QHBoxLayout;
    saveLayout->addWidget(m_dirEdit);
    saveLayout->addWidget(browseButton);
    m_saveGroup->setLayout(saveLayout);
}

void SetPaper::on_browse()
{
    QString directory = QFileDialog::getExistingDirectory(this,
                               tr("Save location"), QDir::currentPath());

    if (!directory.isEmpty())
    {
            m_dirEdit->setText(directory);
    }
}

void SetPaper::autoSetWallpaper()
{
    m_autoSetpaper = new QCheckBox(tr("Automatically switch wallpaper"));
    m_spinBox = new QSpinBox(this);
    m_sliDer = new QSlider(Qt::Horizontal, this);
    m_spinBox->setRange(1, 120);
    m_sliDer->setRange(1, 120);
    connect(m_sliDer,  SIGNAL(valueChanged(int)),
                     m_spinBox, SLOT(setValue(int)));
    connect(m_spinBox, SIGNAL(valueChanged(int)),
                     m_sliDer,  SLOT(setValue(int)));
    m_spinBox->setValue(30);

    m_valueLayout = new QHBoxLayout;
    m_valueLayout->addWidget(m_spinBox);
    m_valueLayout->addWidget(m_sliDer);
}

void SetPaper::createTitle()
{
    //logo
    QLabel *titleIcon = new QLabel;
    QPixmap logo(":/icons/logo");
    titleIcon->setPixmap(logo);

    //text
    QLabel *titleText = new QLabel;
    titleText->setText(tr("Options"));

    //close button
    QToolButton *closeBtn = new QToolButton(this);
    setBtnIcon(closeBtn, eBtnStateDefault);
    closeBtn->installEventFilter(this);
    connect(closeBtn, SIGNAL(clicked()), this, SLOT(close()));

    //layout
    m_titleLayout = new QHBoxLayout;
    m_titleLayout->addWidget(titleIcon);
    m_titleLayout->addWidget(titleText);
    m_titleLayout->addStretch(1);
    m_titleLayout->addWidget(closeBtn);

    //set Margin
    m_titleLayout->setContentsMargins(0,0,5,0);

    //border:0px -- Remove the border line
    titleIcon->setStyleSheet("margin-left:2px;border:0px");
    titleText->setStyleSheet("margin-left:2px;border:0px");

    //Set text color ...
    setStyleSheet("QLabel{color:#CCCCCC;font-size:12px;font-weight:bold;}QToolButton{border:0px;}");

    //Set layout horizontal expand and vertical fixed
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

bool SetPaper::eventFilter(QObject *obj, QEvent *event)
{
    //Button state
    eBtnMoustState eState = eBtnStateNone;
    //QEvent::Enter
    if (event->type() == QEvent::Enter)
    {
        eState = eBtnStateHover;
    }
    //QEvent::Leave
    if (event->type() == QEvent::Leave)
    {
        eState = eBtnStateDefault;
    }
    //QEvent::MouseButtonPress
    if (event->type() == QEvent::MouseButtonPress && ((QMouseEvent*)(event))->button()== Qt::LeftButton)
    {
        eState = eBtnStatePress;
    }
    //State in effect
    if(eState != eBtnStateNone)
    {
        setBtnIcon((QToolButton *)obj, eState);
        return false;
    }
    return QWidget::eventFilter(obj, event);
}

void SetPaper::setBtnIcon(QToolButton *pBtn, eBtnMoustState state)
{
    QPixmap close(":/icons/close");

    //icons w and h
    int w = close.width();
    int h = close.height();
    //State
    if(state != eBtnStateNone)
    {
        //1/4 icons
        pBtn->setIcon(close.copy((w/4)*(state-1), 0, w/4, h));
        //Set icons size
        pBtn->setIconSize(QSize(w/4, h));
    }
}

void SetPaper::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    //Linear gradient
    QLinearGradient objLinear(rect().topLeft(), rect().bottomRight());
    objLinear.setColorAt(0, Qt::black);
    objLinear.setColorAt(0.5, Qt::white);
    objLinear.setColorAt(1, Qt::black);
    painter.fillRect(rect(), objLinear);
}

void SetPaper::on_settings()
{
    show();
}
