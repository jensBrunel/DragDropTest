#include "mygraphicsview.h"
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QGraphicsScene>

MyGraphicsView::MyGraphicsView(QWidget* parent)
    : QGraphicsView(parent)
{
    setAcceptDrops(true);
    pushbutton = new QPushButton("Hello");

    QGraphicsScene* scene = new QGraphicsScene(this);
    QBrush brush(Qt::red, Qt::SolidPattern);
    setScene(scene);
    scene->setSceneRect(0,0,width(), height());
    scene->setBackgroundBrush(brush);
    proxy = scene->addWidget(pushbutton);
    setAlignment(Qt::AlignLeft | Qt::AlignTop );
    proxy->setPos(0,0);


}
MyGraphicsView::~MyGraphicsView()
{
    delete pushbutton;
}

void MyGraphicsView::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();
}

void MyGraphicsView::dragMoveEvent(QDragMoveEvent *event)
{

}

void MyGraphicsView::dropEvent(QDropEvent *event)
{
    if(0 != scene())
    {
        proxy->setPos(QPointF(event->pos()));
        QString coordinates = QString::number(proxy->pos().toPoint().rx());
        coordinates.append(",");
        coordinates.append(QString::number(proxy->pos().toPoint().ry()));
        pushbutton->setText(coordinates);
    }
}

void MyGraphicsView::mousePressEvent(QMouseEvent *event)
{

}
