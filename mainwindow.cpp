#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QMenu>
#include <QToolBar>
#include <QColorDialog>
#include <QFileDialog>

#define LENGTH 1080
#define WIDTH 640

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    drawWidget = new DrawWidget;
    setCentralWidget(drawWidget);               /*set the paint area as central window*/

    createMenu();
    createToolBar();

    setMinimumSize(LENGTH, WIDTH);

    showStyle();                                /*init*/
    drawWidget->setWidth((widthSpinBox->value()));
    drawWidget->setColor(Qt::black);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createMenu()
{
    /* File */
    QMenu *fileMenu = ui->menuBar->addMenu("File");
    QAction *openAction = new QAction("Open");
    QAction *saveAction = new QAction("Save");
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);

    connect(openAction, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveFile()));
}

void MainWindow::createToolBar()
{
    QToolBar *toolBar = addToolBar("Tool");             /*add tool bar object*/

    /* Graph type */
    QActionGroup *graghGroup = new QActionGroup(toolBar);

    QAction *drawPenAction = new QAction("Pen", toolBar);
    drawPenAction->setIcon(QIcon(":/src/Pen.png"));
    drawPenAction->setToolTip(tr("Free draw"));
    drawPenAction->setCheckable(true);
    drawPenAction->setChecked(true);
    graghGroup->addAction(drawPenAction);
    toolBar->addAction(drawPenAction);

    QAction *drawLineAction = new QAction("Line", toolBar);
    drawLineAction->setIcon(QIcon(":/src/Line.png"));
    drawLineAction->setToolTip(tr("Line"));
    drawLineAction->setCheckable(true);
    graghGroup->addAction(drawLineAction);
    toolBar->addAction(drawLineAction);

    QAction *drawEclipseAction = new QAction("Eclipse", toolBar);
    drawEclipseAction->setIcon(QIcon(":/src/Eclipse.png"));
    drawEclipseAction->setToolTip(tr("Eclipse(ctrl for circle)"));
    drawEclipseAction->setCheckable(true);
    graghGroup->addAction(drawEclipseAction);
    toolBar->addAction(drawEclipseAction);

    QAction *drawRectangleAction = new QAction("Rectangle", toolBar);
    drawRectangleAction->setIcon(QIcon(":/src/Rectangle.png"));
    drawRectangleAction->setToolTip(tr("Rectangle(ctrl for square)"));
    drawRectangleAction->setCheckable(true);
    graghGroup->addAction(drawRectangleAction);
    toolBar->addAction(drawRectangleAction);

    QAction *drawTriangleAction = new QAction("Triangle", toolBar);
    drawTriangleAction->setIcon(QIcon(":/src/Triangle.png"));
    drawTriangleAction->setToolTip(tr("Triangle"));
    drawTriangleAction->setCheckable(true);
    graghGroup->addAction(drawTriangleAction);
    toolBar->addAction(drawTriangleAction);

    connect(drawPenAction, SIGNAL(triggered()), this, SLOT(drawPenActionTrigger()));
    connect(drawLineAction, SIGNAL(triggered()), this, SLOT(drawLineActionTrigger()));
    connect(drawEclipseAction, SIGNAL(triggered()), this, SLOT(drawEclipseActionTrigger()));
    connect(drawRectangleAction, SIGNAL(triggered()), this, SLOT(drawRectangleActionTrigger()));
    connect(drawTriangleAction, SIGNAL(triggered()), this, SLOT(drawTriangleActionTrigger()));


    /* Line Style */
    styleLabel = new QLabel(tr("Line style: "));
    styleComboBox = new QComboBox;
    styleComboBox->addItem(tr("SolidLine"), static_cast<int>(Qt::SolidLine));
    styleComboBox->addItem(tr("DashLine"), static_cast<int>(Qt::DashLine));
    styleComboBox->addItem(tr("DotLine"), static_cast<int>(Qt::DotLine));
    styleComboBox->addItem(tr("DashDotLine"), static_cast<int>(Qt::DashDotLine));
    styleComboBox->addItem(tr("DashDotDtLine"), static_cast<int>(Qt::DashDotDotLine));

    connect(styleComboBox, SIGNAL(activated(int)), this, SLOT(showStyle()));

    /* Line width */
    widthLable = new QLabel(tr("Line width: "));
    widthSpinBox = new QSpinBox;
    connect(widthSpinBox, SIGNAL(valueChanged(int)), drawWidget, SLOT(setWidth(int)));

    /* Color */
    colorBtn = new QToolButton;
    QPixmap pixmap(20, 20);
    pixmap.fill(Qt::black);
    colorBtn->setIcon(QIcon(pixmap));
    connect(colorBtn, SIGNAL(clicked()), this, SLOT(showColor()));

    /* Clear */
    clearBtn = new QToolButton;
    clearBtn->setText(tr("Clear"));
    connect(clearBtn, SIGNAL(clicked()), drawWidget, SLOT(clear()));

    toolBar->addWidget(styleLabel);
    toolBar->addWidget(styleComboBox);
    toolBar->addWidget(widthLable);
    toolBar->addWidget(widthSpinBox);
    toolBar->addWidget(colorBtn);
    toolBar->addWidget(clearBtn);
}

void MainWindow::showStyle()
{
    drawWidget->setStyle(styleComboBox->itemData(styleComboBox->currentIndex(), Qt::UserRole).toInt());
}

void MainWindow::showColor()
{
    QColor color = QColorDialog::getColor(static_cast<int>(Qt::black), this);
    if(color.isValid())
    {
        drawWidget->setColor(color);
        QPixmap p(20, 20);
        p.fill(color);
        colorBtn->setIcon(QIcon(p));
    }
}

void MainWindow::drawLineActionTrigger()
{
    drawWidget->setGraphType(DrawWidget::LINE);
}

void MainWindow::drawPenActionTrigger()
{
    drawWidget->setGraphType(DrawWidget::PEN);
}

void MainWindow::drawEclipseActionTrigger()
{
    drawWidget->setGraphType(DrawWidget::ECLIPSE);
}

void MainWindow::drawRectangleActionTrigger()
{
    drawWidget->setGraphType(DrawWidget::RECTANGLE);
}

void MainWindow::drawTriangleActionTrigger()
{
    drawWidget->setGraphType(DrawWidget::TRIANGLE);
}


void MainWindow::openFile()
{
    openFileAddr = QFileDialog::getOpenFileName(this, "Open File", "/", "png files(*.png *.jpg)");
    drawWidget->openFile(openFileAddr);
}

void MainWindow::saveFile()
{
    saveFileAddr = QFileDialog::getSaveFileName(this, "Save File", "/", "png files(*.png *.jpg)");
    drawWidget->saveFile(saveFileAddr);
}
