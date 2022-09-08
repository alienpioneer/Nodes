#include "Node.h"
#include <QStyleOption>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

Node::Node(QRect size, QWidget *parent)
    : QWidget{parent},
    m_size(size),
    m_color(QColor(80,80,80,255)),
    m_enableMovement(false)
{
    setGeometry(size);
    setStyleSheet("border-width: 1px; border-style: solid; border-radius: 6px;"
                  "border-color: rgb(42, 43, 46, 255); background-color: rgb(80,80,80,255)");
//    setAttribute(Qt::WA_TranslucentBackground);
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
    if(event->button() == Qt::LeftButton)
    {
        //qDebug() << "Node: mouse press";
        emit selectNode(this);
        m_enableMovement = true;
        m_currentMousePosition = event->pos();
    }
}


void Node::mouseReleaseEvent(QMouseEvent *event)
{

    if(event->button() == Qt::LeftButton)
    {
        m_enableMovement = false;
    }
}


void Node::mouseMoveEvent(QMouseEvent *event)
{
    if (m_enableMovement)
    {
        event->accept();
        emit moveNode(mapToParent(event->pos()) - m_currentMousePosition);
    }
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
