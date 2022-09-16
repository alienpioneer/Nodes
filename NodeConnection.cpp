#include "NodeConnection.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

NodeConnection::NodeConnection(QSize size, QWidget *parent)
    : QWidget{parent},
      m_size(size),
      m_color(QColor(180,120,20)),
      m_lineColor(QColor(20,30,40)),
      m_lineThickness(1)
{
    setFixedSize(size);
}

void NodeConnection::paintEvent(QPaintEvent *event)
{
    Q_UNUSED( event );

    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing);
    QPen pen( m_lineColor, m_lineThickness, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin );
    painter.setPen( pen );
    painter.setBrush(m_color);

    painter.drawChord(QRect(0,0,width(),height()), 0, 360*16);
}

void NodeConnection::mousePressEvent(QMouseEvent *event)
{
    qDebug() << mapToGlobal(QPoint(width()/2,height()/2));
    // On click send to canvas a pointer to this object and the position
    // So that the curve will be redrawn every time the node is moved
}

void NodeConnection::mouseReleaseEvent(QMouseEvent *event)
{
    
}

void NodeConnection::enterEvent(QEvent *event)
{
    m_color = QColor(220,160,60);
    m_lineColor = QColor(50,60,40);
    m_lineThickness = 4;
    update();
}

void NodeConnection::leaveEvent(QEvent *event)
{
    m_color = QColor(180,120,20);
    m_lineColor = QColor(20,30,40);
    m_lineThickness = 1;
    update();
}
