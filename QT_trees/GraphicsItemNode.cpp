#include "GraphicsItemNode.h"
#include <QPainter>
#include <QtMath>

GraphicsItemNode::GraphicsItemNode(const QString &text, QGraphicsItem *parent)
    :QGraphicsSimpleTextItem(text, parent)
{
}

//void GraphicsItemNode::setBalance(int balance)
//{
//    m_balance = balance;
//    update();
//}

QColor GraphicsItemNode::textColor() const
{
    return m_textColor;
}
QColor GraphicsItemNode::borderColor() const
{
    return m_borderColor;
}
QColor GraphicsItemNode::fillColor() const
{
    return m_fillColor;
}

int GraphicsItemNode::fontSize() const
{
    return font().pointSize();
}

void GraphicsItemNode::setTextColor(const QColor &color)
{
    m_textColor = color;
    update();
}
void GraphicsItemNode::setBorderColor(const QColor &color)
{
    m_borderColor = color;
    update();
}
void GraphicsItemNode::setFillColor(const QColor &color)
{
    m_fillColor = color;
    update();
}

void GraphicsItemNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF textRect = QGraphicsSimpleTextItem::boundingRect();
    textRect.moveTo((boundingRect().width() - textRect.width()) / 2, (boundingRect().height() - textRect.height()) / 2);
    painter->setBrush(QBrush(m_fillColor));
    painter->drawEllipse(boundingRect());
    painter->translate(textRect.x(), textRect.y());
    QGraphicsSimpleTextItem::paint(painter, option, widget);
//    QPointF balancePosition = boundingRect().topLeft() - QPointF(50, 0);
//    painter->drawText(balancePosition, QString("%1").arg(m_balance));
}

void GraphicsItemNode::setFontSize(int size)
{
    QFont font = this->font();
    font.setPointSize(size);
    this->setFont(font);
}

 QRectF GraphicsItemNode::boundingRect() const
{
    QRectF rect = QGraphicsSimpleTextItem::boundingRect();
    int width = rect.width() * sqrt(2);
    int height = rect.height() * sqrt(2);
    rect.setWidth(qMax(width,height));
    rect.setHeight(qMax(width,height) + 20);
    return rect;
}
