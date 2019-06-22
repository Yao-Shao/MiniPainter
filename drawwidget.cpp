#include "drawwidget.h"
#include <QtGui>
#include <QPen>
#include <QKeyEvent>
#include <iostream>
#include <QtDebug>
#include <graph.h>

DrawWidget::DrawWidget(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true);        /*set the backgroud color*/
    setPalette(QPalette(Qt::white));
    setFocusPolicy(Qt::StrongFocus);

    pix = new QPixmap(size());          /*create pixmap*/
    tmpPix = new QPixmap(size());
    qDebug() << size();

    backgroundColor = Qt::white;
    pix->fill( backgroundColor);               /*fill the background*/
    setGraphType(PEN);
    setMinimumSize(LENGTH, WIDTH);

    isDrawing = false;
    isSaved = false;
    normalizeGraph = false;
}

DrawWidget::~DrawWidget()
{
    delete pix;
    delete tmpPix;
}

void DrawWidget::setStyle(int s)
{
    style = s;
}

void DrawWidget::setWidth(int w)
{
    weight = w;
}

void DrawWidget::setColor(QColor c)
{
    color = c;
}

void DrawWidget::setGraphType(int t)
{
    graphType = t;
}

void DrawWidget::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        startPos = e->pos();
        isDrawing = true;
    }

}

void DrawWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(isDrawing)
    {
        isSaved = false;
        endPos = e->pos();
        *tmpPix = *pix;
        if(graphType == PEN){
            drawPix(pix);
        }else{
            drawPix(tmpPix);
        }
    }
}

void DrawWidget::mouseReleaseEvent(QMouseEvent *e)
{
    isDrawing = false;
    endPos = e->pos();
    if(graphType != PEN)
    {
        drawPix(pix);
    }
    update();

}

void DrawWidget::drawPix(QPixmap *p)
{
    QPainter *painter = new QPainter;

    QPen pen;
    pen.setStyle((Qt::PenStyle)style);
    pen.setWidth(weight);
    pen.setColor(color);

    painter->begin(p);
    painter->setPen(pen);


    switch(graphType){
    case PEN : {
        painter->drawLine(startPos, endPos);
        startPos = endPos;
        break;
    }
    case LINE : {
        painter->drawLine(startPos, endPos);
        break;
    }
    case ECLIPSE : {
        if(normalizeGraph == true){
            painter->drawEllipse(startPos.x(),
                                 startPos.y(),
                                 endPos.x() - startPos.x(),
                                 endPos.x() - startPos.x());
        }else{
            painter->drawEllipse(startPos.x(),
                                 startPos.y(),
                                 endPos.x() - startPos.x(),
                                 endPos.y() - startPos.y());
        }
        break;
    }
    case RECTANGLE : {
        if(normalizeGraph == true){
            painter->drawRect(startPos.x(),
                              startPos.y(),
                              endPos.x() - startPos.x(),
                              endPos.x() - startPos.x());
        }else{
            painter->drawRect(startPos.x(),
                              startPos.y(),
                              endPos.x() - startPos.x(),
                              endPos.y() - startPos.y());
        }
        break;
    }
    case TRIANGLE : {
        QPolygonF triangle;
        triangle << QPointF((startPos.x() + endPos.x())/2,startPos.y())
                 << QPointF(startPos.x(), endPos.y())
                 << QPointF(endPos.x(), endPos.y());
        painter->drawPolygon(triangle, Qt::WindingFill);
        break;
    }
    default:
    {
        qDebug() << "Unsupported graph type!\n";
        return;
    }
    }

    if(p==pix)
    {
        myGraph *tmpGraph = new myGraph(startPos, endPos, graphType);
        undoList.push_back(tmpGraph);
    }

    painter->end();
    update();
}

void DrawWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    if(isDrawing == true)
    {
        painter.drawPixmap(QPoint(0,0), *tmpPix);
    }
    else {
        painter.drawPixmap(QPoint(0,0), *pix);
    }

}

void DrawWidget::resizeEvent(QResizeEvent *event)
{
    if(height() > pix->height() || width() > pix->width())
    {
        QPixmap *newPix = new QPixmap(size());
        newPix->fill(Qt::white);
        QPainter p(newPix);
        p.drawPixmap(QPoint(0, 0), *pix);
        pix = newPix;
    }
    QWidget::resizeEvent(event);
}

void DrawWidget::clear()
{
    QPixmap *clearPix = new QPixmap(size());
    clearPix->fill(Qt::white);
    *pix = *clearPix;
    *tmpPix = *clearPix;
    delete clearPix;
    update();
}

bool DrawWidget::saveFile(QString addr)
{
    pix->save(addr, "PNG");
    isSaved = true;
    return true;
}

bool DrawWidget::openFile(QString addr)
{
    *pix = QPixmap(addr);
    return true;
}

void DrawWidget::keyPressEvent(QKeyEvent *e)
{
    switch(e->key()){
    case Qt::Key_Control : normalizeGraph = true;break;
    }
}

void DrawWidget::keyReleaseEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_Control : normalizeGraph = false;
    }
}

bool DrawWidget::getSaveStatus()
{
    return isSaved;
}

void DrawWidget::undo()
{
    redoList.push_back(undoList.back());
    undoList.pop_back();
    clear();
    qDebug() << undoList.size()<<"\n";
    for(vector<myGraph *>::iterator i = undoList.begin(); i != undoList.end(); i++){
        repaintGraph(*i);
    }
    *tmpPix = *pix;
    qDebug() << undoList.size()<<"\n";
}

void DrawWidget::redo()
{
    myGraph *redoGraph = redoList.back();
    redoList.pop_back();
    repaintGraph(redoGraph);
    undoList.push_back(redoGraph);
    *tmpPix = *pix;
}

void DrawWidget::repaintGraph(myGraph *g){
    QPainter *painter = new QPainter;
    QPen pen;
    pen.setStyle((Qt::PenStyle)style);
    pen.setWidth(weight);
    pen.setColor(color);

    painter->begin(pix);
    painter->setPen(pen);

    switch(g->type){
    case PEN : {
        painter->drawLine(g->p1, g->p2);
        g->p2 = g->p1;
        break;
    }
    case LINE : {
        painter->drawLine(g->p1, g->p2);
        break;
    }
    case ECLIPSE : {
        if(normalizeGraph == true){
            painter->drawEllipse(g->p1.x(),
                                 g->p1.y(),
                                 g->p2.x() - g->p1.x(),
                                 g->p2.x() - g->p1.x());
        }else{
            painter->drawEllipse(g->p1.x(),
                                 g->p1.y(),
                                 g->p2.x() - g->p1.x(),
                                 g->p2.y() - g->p1.y());
        }


        break;
    }
    case RECTANGLE : {
        if(normalizeGraph == true){
            painter->drawRect(g->p1.x(),
                              g->p1.y(),
                              g->p2.x() - g->p1.x(),
                              g->p2.x() - g->p1.x());
        }else{
            painter->drawRect(g->p1.x(),
                              g->p1.y(),
                              g->p2.x() - g->p1.x(),
                              g->p2.y() - g->p1.y());
        }
        break;
    }
    case TRIANGLE : {
        QPolygonF triangle;
        triangle << QPointF((g->p1.x() + g->p2.x())/2,g->p1.y())
                 << QPointF(g->p1.x(), g->p2.y())
                 << QPointF(g->p2.x(), g->p2.y());
        painter->drawPolygon(triangle, Qt::WindingFill);
        break;
    }
    default: break;
    }
    painter->end();
    update();
}

int DrawWidget::getUndoSize(){
    return int(undoList.size());
}

int DrawWidget::getRedoSize()
{
    return int(redoList.size());
}
