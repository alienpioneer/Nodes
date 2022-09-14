#include "Node.h"
#include <QMouseEvent>
#include <QDebug>
#include <QPainter>
#include <QStyleOption>

Node::Node(QRect size, QWidget *parent)
    : QWidget{parent},
      m_size(size),
      m_enableMovement(false)
{
    setGeometry(size);
    m_nodeCore = new NodeCore(QRect(5, 0, size.width()-10, size.height()), this);
    NodeConnection* con1 = new NodeConnection(QRect(0, 0, 10, 10), this);
    NodeConnection* con2 = new NodeConnection(QRect(0, 0, 10, 10), this);
    con1->move(0,10);
    con2->move(0,30);
}

void Node::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        //qDebug() << "Node mouse press";
        emit selectNode(this);
        m_enableMovement = true;
        m_currentMousePosition = event->pos();
    }
}

void Node::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        //qDebug() << "Node mouse release" << "_enableMovement " << m_enableMovement;
        m_enableMovement = false;
    }
}

void Node::mouseDoubleClickEvent(QMouseEvent *event)
{

}

void Node::mouseMoveEvent(QMouseEvent *event)
{
    if (m_enableMovement)
    {
        //qDebug() << "Node mouseMoveEvent() mouse move";
        event->accept();
        emit moveNode(mapToParent(event->pos()) - m_currentMousePosition);
    }
}

void Node::contextMenuEvent(QContextMenuEvent *event)
{

}

void Node::paintEvent(QPaintEvent *event)
{
    Q_UNUSED( event );

    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing);

    QStyleOption styleOpt;
    styleOpt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &styleOpt, &painter, this);
}
