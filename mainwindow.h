#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//Qt5
//#include <QtWidgets>
//Qt4
#include <QtGui>
#include <QPainter>
#include <QBitmap>
#include <QDebug>
#include <QVBoxLayout>
#include "titlebar.h"
#include "webview.h"
#include "statubar.h"
#include "download.h"
#include "setpaper.h"

class MainWindow : public QFrame
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *);
    void closeEvent(QCloseEvent* );
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

public slots:
    void iconActivated(QSystemTrayIcon::ActivationReason);

private:
    void initWindow();
    void createActions();
    void setSizeWindow();

private:
    TitleBar *m_titleBar;
    AWebView *m_webView;
    StatuBar *m_statuBar;
    DownLoad *m_downLoad;
    SetPaper *m_setPaper;
    QVBoxLayout *m_Layout;
    QSystemTrayIcon *m_systemTray;

    QPoint m_oldPos;
    bool m_pressMouse;
    bool left, right, top, bottom;
};

#endif // MAINWINDOW_H
