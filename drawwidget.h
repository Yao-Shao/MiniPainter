#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include <QtGui>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QColor>
#include <QPixmap>
#include <QPoint>
#include <QPainter>
#include <QPalette>

class DrawWidget : public QWidget
{
    Q_OBJECT


public:
    explicit DrawWidget(QWidget *parent = nullptr);
    ~DrawWidget();
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void paintEvent(QPaintEvent *);
    void drawPix(QPixmap *);
    void resizeEvent(QResizeEvent *);

    bool getSaveStatus();
    bool saveFile(QString addr);
    bool openFile(QString addr);

    enum graphType{
        PEN,
        LINE,
        ECLIPSE,
        RECTANGLE,
        TRIANGLE
    };

signals:

public slots:
    void setStyle(int);
    void setWidth(int);
    void setColor(QColor);
    void setGraphType(int);
    void clear();

private:
    QPixmap *pix;
    QPixmap *tmpPix;

    QPoint startPos;
    QPoint endPos;

    int style;
    int weight;
    int graphType;
    QColor color;

    QColor backgroundColor;

    bool isDrawing;
    bool normalizeGraph;
    bool isSaved;
};

#endif // DRAWWIDGET_H
