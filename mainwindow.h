#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolButton>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
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

public slots:
    void showStyle();
    void showColor();
    void openFile();
    void saveFile();
    void drawLineActionTrigger();
    void drawPenActionTrigger();
    void drawEclipseActionTrigger();
    void drawRectangleActionTrigger();
    void drawTriangleActionTrigger();


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
};

#endif // MAINWINDOW_H

