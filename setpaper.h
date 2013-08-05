#ifndef SETPAPER_H
#define SETPAPER_H

#include <QDir>
#include <QLabel>
#include <QDialog>
#include <QSlider>
#include <QSpinBox>
#include <QPainter>
#include <QGroupBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QFileDialog>
#include <QMouseEvent>
#include <QToolButton>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDesktopServices>

class SetPaper : public QFrame
{
    Q_OBJECT
public:
    SetPaper(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent*);
    bool eventFilter(QObject*, QEvent*);

public slots:
    void on_settings();
    void on_browse();

private:
    //Enumeration button state
    enum eBtnMoustState
    {
         eBtnStateNone,
         eBtnStateDefault,
         eBtnStateHover,
         eBtnStatePress
    };

    QSlider *m_sliDer;
    QSpinBox *m_spinBox;
    QLineEdit *m_dirEdit;
    QCheckBox *m_miniTotray;
    QCheckBox *m_closeTotray;
    QHBoxLayout *m_titleLayout;
    QCheckBox *m_autoSetpaper;
    QHBoxLayout *m_valueLayout;
    QGroupBox *m_basicGroup;
    QGroupBox *m_saveGroup;
    QPushButton *m_okButton, *m_closeButton;

private:
    void createTitle();
    void createOptions();
    void createButtons();
    void createLayout();
    void autoSetWallpaper();
    void setBtnIcon(QToolButton*, eBtnMoustState);
};

#endif // SETPAPER_H
