#include "titlebar.h"

TitleBar::TitleBar(QWidget *parent)
    : QWidget(parent)
    , maxNormal(false)
    , leftPress(false)
{
    //!1 !!11 !2
    setMouseTracking(true);

    //Create widget
    CreateWidget();

    //Create layout
    CreateLayout();

    //Event fiter
    CreateEventFiter();
}

void TitleBar::CreateWidget()
{
    //logo
    m_pLabelIcon = new QLabel(this);
    QPixmap objPixmap(":/icons/logo");
    m_pLabelIcon->setPixmap(objPixmap);//.scaled(TITLE_H,TITLE_H));

    //title
    m_pLabelTitle = new QLabel(this);
    m_pLabelTitle->setText(tr("Change WallPaper"));

    //skin
    m_pBtnSkin = new QToolButton(this);
    //Set button icons
    SetBtnIcon(m_pBtnSkin, eBtnStateDefault);

    //Min
    m_pBtnMin = new QToolButton(this);
    SetBtnIcon(m_pBtnMin, eBtnStateDefault);

    //Max
    m_pBtnMax = new QToolButton(this);
    SetBtnIcon(m_pBtnMax, eBtnStateDefault);

    //Close
    m_pBtnClose = new QToolButton(this);
    SetBtnIcon(m_pBtnClose, eBtnStateDefault);

    //Get child widget
    const QObjectList &objList = children();
    for(int nIndex=0; nIndex<objList.count(); nIndex++)
    {
        //!2 MouseTracking attr !!11
        ((QWidget*)(objList.at(nIndex)))->setMouseTracking(true);

        if(0 == qstrcmp(objList.at(nIndex)->metaObject()->className(), "QToolButton"))
        {
            connect(((QToolButton*)(objList.at(nIndex))), SIGNAL(clicked()), this, SLOT(slot_BtnClick()));
        }
    }
}

void TitleBar::SetBtnIcon(QToolButton *pBtn, eBtnMoustState state)
{
    //Get icons path
    QString strImagePath = GetBtnImagePath(pBtn);
    QPixmap objPixmap(strImagePath);
    //icons w and h
    int nPixWidth = objPixmap.width();
    int nPixHeight = objPixmap.height();

    //State
    if(state != eBtnStateNone)
    {
        //1/4 icons
        pBtn->setIcon(objPixmap.copy((nPixWidth/4)*(state-1), 0, nPixWidth/4, nPixHeight));
        //Set icons size
        pBtn->setIconSize(QSize(nPixWidth/4, nPixHeight));
    }
}

const QString TitleBar::GetBtnImagePath(QToolButton *pBtn)//, bool bInit/*=false*/)
{
    QString strImagePath;
    //Skin button
    if(m_pBtnSkin == pBtn)
    {
        strImagePath = ":/icons/skin";
    }
//    //meun button
//    if(m_pBtnMenu == pBtn)
//    {
//        strImagePath = ":/icons/menu";
//    }
    //Minimize button
    if(m_pBtnMin == pBtn)
    {
        strImagePath = ":/icons/min";
    }
    //Maximize/Restore button
    if(m_pBtnMax == pBtn)
    {
        if(maxNormal)
        {
            //Restore icons path
            strImagePath = ":/icons/restore";
        }
        else
        {    
            //Maximize icons path
            strImagePath = ":/icons/max";
        }
    }
    //Close button
    if(m_pBtnClose == pBtn)
    {
        strImagePath = ":/icons/close";
    }
    return strImagePath;
}

void TitleBar::CreateLayout()
{
    //HBox
    m_pLayout = new QHBoxLayout(this);
    //Add widget
    m_pLayout->addWidget(m_pLabelIcon);
    m_pLayout->addWidget(m_pLabelTitle);

    //Add scale items
    m_pLayout->addStretch(1);

    //Add widget
    m_pLayout->addWidget(m_pBtnSkin);
    //m_pLayout->addWidget(m_pBtnMenu);
    m_pLayout->addWidget(m_pBtnMin);
    m_pLayout->addWidget(m_pBtnMax);
    m_pLayout->addWidget(m_pBtnClose);

    //set Margin
    m_pLayout->setContentsMargins(0,0,5,0);

    //Set space
    m_pLayout->setSpacing(0);
    setLayout(m_pLayout);

    //border:0px -- Remove the border line
    m_pLabelIcon->setStyleSheet("margin-left:2px;border:0px");
    m_pLabelTitle->setStyleSheet("margin-left:2px;border:0px");

    //Set text color ...
    setStyleSheet("QLabel{color:#E6E6FA;font-size:12px;font-weight:bold;}QToolButton{border:0px;}");

    //Set layout horizontal expand and vertical fixed
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

void TitleBar::CreateEventFiter()
{
    m_pBtnSkin->installEventFilter(this);
    //m_pBtnMenu->installEventFilter(this);
    m_pBtnMin->installEventFilter(this);
    m_pBtnMax->installEventFilter(this);
    m_pBtnClose->installEventFilter(this);
}

bool TitleBar::eventFilter(QObject *obj, QEvent *event)
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
    //Judge button
    if(m_pBtnSkin==obj || m_pBtnMin==obj || m_pBtnMax==obj || m_pBtnClose==obj)
    {
        //State in effect
        if(eState != eBtnStateNone)
        {
            SetBtnIcon((QToolButton *)obj, eState);
            return false;
        }
    }
    return QWidget::eventFilter(obj, event);
}

void TitleBar::slot_BtnClick()
{ 
    QToolButton *pBtn = (QToolButton*)(sender());
    if(pBtn == m_pBtnMin)
    {
        //Qt5 problems
        parentWidget()->showMinimized();
    }
    if(pBtn == m_pBtnMax)
    {
        if(maxNormal)
        {
            parentWidget()->showNormal();
        }
        else
        {
            parentWidget()->showMaximized();
        }
        maxNormal = !maxNormal;
    }
    if(pBtn == m_pBtnClose)
    {
        parentWidget()->close();
    }
//    if(pBtn == m_pBtnSkin)
//    {

//    }
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
    startPos = event->globalPos();
    clickPos = event->pos();
    leftPress = (event->button() == Qt::LeftButton);
    //event->ignore();
}

void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if(maxNormal)
        return;
    if(leftPress)
        //!!11
        parentWidget()->move(event->globalPos() - clickPos);

    //!!11
    event->ignore();
}

void TitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        leftPress = false;
    event->ignore();
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    //Judge leftbutton
    if(event->button() != Qt::LeftButton)
        return;

    if(maxNormal)
    {
        parentWidget()->showNormal();
    }
    else
    {
        parentWidget()->showMaximized();
    }
    maxNormal = !maxNormal;
}
