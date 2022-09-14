#include "NodeConnection.h"
#include <QPainter>

NodeConnection::NodeConnection(QRect size, QWidget *parent)
    : QWidget{parent},
      m_size(size),
      m_color(QColor(180,120,20)),
      m_lineColor(QColor(20,30,40)),
      m_lineThickness(1)
{
    setGeometry(size);
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
    
}

void NodeConnection::mouseReleaseEvent(QMouseEvent *event)
{
    
}

void NodeConnection::enterEvent(QEvent *event)
{
    
}

void NodeConnection::leaveEvent(QEvent *event)
{
    
}
