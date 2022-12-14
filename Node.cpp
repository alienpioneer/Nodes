#include "Node.h"
#include <QMouseEvent>
#include <QDebug>
#include <QPainter>
#include <QStyleOption>

Node::Node(QRect size, QWidget *parent)
    : QWidget{parent},
      m_size(size),
      m_enableMovement(false),
      m_connexionSize(10)
{
    setGeometry(size);
    m_nodeCore = new NodeCore(QRect(m_connexionSize/2, 0, size.width()-m_connexionSize, size.height()), this);
    addConnectionSlots(Connection::IN, 2);
    addConnectionSlots(Connection::OUT, 1);
    //setStyleSheet("border:1px solid black;");
}

void Node::on_beginNewConnection(NodePlug *plug)
{
    emit beginConnection(plug);
}

void Node::on_endNewConnection(NodePlug *plug)
{
    emit endConnection(plug);
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

//    QStyleOption styleOpt;
//    styleOpt.init(this);
//    style()->drawPrimitive(QStyle::PE_Widget, &styleOpt, &painter, this);
}

void Node::createConnectionSlots(Connection type, int count)
{

}

void Node::addConnectionSlots(Connection type, int count)
{
    QList<NodePlug*> connexionList;
    int xPosition;
    int yPositionOffset = height()/(count+1);

    if (type == Connection::IN)
    {
        connexionList = m_IN_plugList;
        xPosition = 0;
    }
    else
    {
        connexionList = m_OUT_plugList;
        xPosition = width()-m_connexionSize;
    }

    for(int i =0; i<count;i++)
    {
        connexionList.append(new NodePlug(QSize(m_connexionSize, m_connexionSize), this));
        connexionList[i]->move(xPosition,(i+1)*yPositionOffset-m_connexionSize/2);
        connect(connexionList[i], &NodePlug::beginNewConnection, this, &Node::on_beginNewConnection);
        connect(connexionList[i], &NodePlug::endNewConnection, this, &Node::on_endNewConnection);
    }
}
