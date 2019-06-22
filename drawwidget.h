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
#include <vector>
#include <graph.h>


#define LENGTH 1080
#define WIDTH 640

using namespace std;

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
    void repaintGraph(myGraph *g);
    int getUndoSize();
    int getRedoSize();

    void undo();
    void redo();

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

    vector<class myGraph *> undoList;
    vector<class myGraph *> redoList;

    QPoint startPos;
    QPoint endPos;

    int style;
    int weight;
    int graphType;
    QColor color;
    QString openFileAddr;

    QColor backgroundColor;

    bool isDrawing;
    bool normalizeGraph;
    bool isSaved;
};

#endif // DRAWWIDGET_H
