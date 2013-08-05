#include "statubar.h"

StatuBar::StatuBar(QWidget *parent)
    : QStatusBar(parent)
{
    //!1
    setMouseTracking(true);
    //Set layout horizontal expand and vertical fixed
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    //Tip message
    showMessage(tr("Sending request ..."));
    setStyleSheet("margin-left:2px;border:0px;color:#1A1A1A;font-size:12px;font-weight:bold;");
}

void StatuBar::showMsgBar(int p, QString title)
{
    show();
    if(p == 100 && title == "")
        showMessage(tr("This page can not be displayed"));
    else
        showMessage(tr("%1 (%2%)").arg(title).arg(p));
}

void StatuBar::hideMsgBar(bool flag)
{
//    if(flag)
//        hide();
//    else
//        showMessage(tr("This page can not be displayed"));
}
