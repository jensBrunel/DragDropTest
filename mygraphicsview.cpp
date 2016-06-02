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

    proxyControl = scene->addRect(0, 0, pushbutton->width()+10, pushbutton->height()+10, QPen(Qt::black), QBrush(Qt::darkGreen));

    proxyControl->setFlag(QGraphicsItem::ItemIsMovable, true);
    proxyControl->setFlag(QGraphicsItem::ItemIsSelectable, true);

    proxy = scene->addWidget(pushbutton);
    proxy->setPos(5,5);
    proxy->setParentItem(proxyControl);
    setAlignment(Qt::AlignLeft | Qt::AlignTop );


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
        //proxy->setPos(QPointF(x+offset.width(),y+offset.height()));
        proxyControl->setPos(QPointF(x+offset.width(),y+offset.height()));
        QString coordinates = QString::number(proxyControl->pos().toPoint().rx());
        coordinates.append(",");
        coordinates.append(QString::number(proxyControl->pos().toPoint().ry()));
        pushbutton->setText(coordinates);
    }
}

void MyGraphicsView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
    viewport()->setCursor(Qt::ClosedHandCursor);
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
    viewport()->setCursor(Qt::ArrowCursor);
}
