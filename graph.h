#ifndef GRAPH_H
#define GRAPH_H

#include <QPoint>

class myGraph
{
public:
    enum graphType{
            PEN,
            LINE,
            ECLIPSE,
            RECTANGLE,
            TRIANGLE
        };

    QPoint p1;
    QPoint p2;
    int type;

    myGraph(QPoint p1, QPoint p2, int type);

};

#endif // GRAPH_H
