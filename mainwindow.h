#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolButton>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QCloseEvent>
#include "drawwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createToolBar();
    void createMenu();

protected:
    void closeEvent(QCloseEvent *);

public slots:
    void showStyle();
    void showColor();
    bool save();
    bool saveAs();
    void openFile();
    void drawLineActionTrigger();
    void drawPenActionTrigger();
    void drawEclipseActionTrigger();
    void drawRectangleActionTrigger();
    void drawTriangleActionTrigger();
    void undoTrigger();
    void redoTrigger();
//    void setActionStatus();


private:
    DrawWidget *drawWidget;
    /* draw */
    QLabel *styleLabel;
    QComboBox * styleComboBox;
    QLabel *widthLable;
    QSpinBox *widthSpinBox;
    QToolButton *colorBtn;
    QToolButton *clearBtn;
    /* file*/
    QString openFileAddr;
    QString saveFileAddr;
    Ui::MainWindow *ui;

//    QAction *redoAct;
//    QAction *undoAct;
};

#endif // MAINWINDOW_H

