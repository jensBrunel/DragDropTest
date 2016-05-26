#include "mygraphicsview.h"
#include <QDragEnterEvent>
#include <QDropEvent>
#include "gridscene.h"

MyGraphicsView::MyGraphicsView(QWidget* parent)
    : QGraphicsView(parent)
{
    setAcceptDrops(true);
    pushbutton = new QPushButton("Hello");
    pushbutton->setFixedSize(80, 25);

    GridScene* scene = new GridScene(this);
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
    GridScene* gridScene = dynamic_cast<GridScene*>(scene());
    if(0 != gridScene)
    {
        QSize cellSize = gridScene->getCellSize();
        int x = floor(event->pos().x() / (cellSize.width())) * cellSize.width();
        int y = floor(event->pos().y() / cellSize.height()) * cellSize.height();

        QSize offset = gridScene->getCellOffset();
        proxy->setPos(QPointF(x+offset.width(),y+offset.height()));
        QString coordinates = QString::number(proxy->pos().toPoint().rx());
        coordinates.append(",");
        coordinates.append(QString::number(proxy->pos().toPoint().ry()));
        pushbutton->setText(coordinates);
    }
}

void MyGraphicsView::mousePressEvent(QMouseEvent *event)
{

}
