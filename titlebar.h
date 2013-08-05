#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QtGui>
#include <QLabel>
#include <QString>
#include <QWidget>
#include <QPixmap>
#include <QStyle>
#include <QLabel>
#include <QDebug>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QToolButton>

class TitleBar : public QWidget
{
    Q_OBJECT
    
public:
    TitleBar(QWidget *parent = 0);

public slots:
    void slot_BtnClick();

protected:
    void mouseMoveEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    bool eventFilter(QObject*, QEvent*);
    void mouseDoubleClickEvent(QMouseEvent*);

private:
    QToolButton *minimize;
    QToolButton *maximize;
    QToolButton *close;
    bool maxNormal, leftPress;
    QPixmap maxPix, restorePix;
    QPoint startPos, clickPos;

    QLabel *m_pLabelTitle, *m_pLabelIcon;
    QToolButton *m_pBtnSkin;//, *m_pBtnMenu;
    QToolButton *m_pBtnMin, *m_pBtnMax, *m_pBtnClose;
    QHBoxLayout *m_pLayout;

    //Enumeration button state
    enum eBtnMoustState
    {
         eBtnStateNone,
         eBtnStateDefault,
         eBtnStateHover,
         eBtnStatePress
    };

private:
    void CreateWidget();
    void CreateLayout();
    void CreateEventFiter();
    const QString GetBtnImagePath(QToolButton*);
    void SetBtnIcon(QToolButton*, eBtnMoustState);
};

#endif // TITLEBAR_H
