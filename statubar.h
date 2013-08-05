#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QLabel>
#include <QDebug>
#include <QStatusBar>

class StatuBar : public QStatusBar
{
    Q_OBJECT
public:
    StatuBar(QWidget *parent = 0);

private slots:
    void hideMsgBar(bool);
    void showMsgBar(int, QString);
};

#endif // TOOLBAR_H
