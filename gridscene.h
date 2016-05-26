#ifndef GRIDSCENE_H
#define GRIDSCENE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QSize>

class GridScene : public QGraphicsScene
{
public:
    GridScene(QWidget* parent);
    virtual ~GridScene();
    QSize getCellSize();
    QSize getCellOffset();
protected:
    // Efficiently draws a grid in the background.
    // For more information: http://www.qtcentre.org/threads/5609-Drawing-grids-efficiently-in-QGraphicsScene?p=28905#post28905
    void drawBackground(QPainter *painter, const QRectF &rect);
private:
    QSize mCellSize;
    QSize mCellOffset;
};

#endif // GRIDSCENE_H
