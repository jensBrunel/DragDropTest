#include "gridscene.h"
#include <QVarLengthArray>
#include <QLineF>
#include <QPainter>

GridScene::GridScene(QWidget* parent)
    : QGraphicsScene(parent)
    , mCellSize(40, 25)
    , mCellOffset(5,5)
{

}

GridScene::~GridScene()
{

}

QSize GridScene::getCellSize()
{
    return mCellSize;
}

QSize GridScene::getCellOffset()
{
    return mCellOffset;
}

void GridScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    qreal left = int(rect.left()) - (int(rect.left()) % mCellSize.width());
    qreal top = int(rect.top()) - (int(rect.top()) % mCellSize.height());

    left += mCellOffset.rwidth();
    top += mCellOffset.rheight();

    QVarLengthArray<QLineF, 100> lines;

    for (qreal x = left; x < rect.right(); x += mCellSize.width())
        lines.append(QLineF(x, rect.top(), x, rect.bottom()));
    for (qreal y = top; y < rect.bottom(); y += mCellSize.height())
        lines.append(QLineF(rect.left(), y, rect.right(), y));

    painter->drawLines(lines.data(), lines.size());
}
