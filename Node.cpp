#include "Node.h"
#include <QStyleOption>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

Node::Node(QRect size, QWidget *parent)
    : QWidget{parent},
    m_size(size),
    m_color(QColor(80,80,80,255))
{
    setGeometry(size);
    setStyleSheet("border-width: 1px; border-style: solid; border-radius: 6px;"
                  " border-color: rgb(42, 43, 46, 255);background-color: rgb(80,80,80,255)");
//    setAttribute(Qt::WA_TranslucentBackground);
//    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
}


void Node::paintEvent(QPaintEvent *event)
{
    Q_UNUSED( event );

    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing);

//    QRect geo(0, 0, width(), height());
//    painter.fillRect(geo, m_color);

    QStyleOption styleOpt;
    styleOpt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &styleOpt, &painter, this);
}


void Node::mousePressEvent(QMouseEvent *event)
{

}


void Node::mouseReleaseEvent(QMouseEvent *event)
{

}


void Node::mouseMoveEvent(QMouseEvent *event)
{

}


void Node::enterEvent(QEvent *event)
{

}


void Node::leaveEvent(QEvent *event)
{

}


void Node::contextMenuEvent(QContextMenuEvent *event)
{

}
