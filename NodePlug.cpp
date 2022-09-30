#include "NodePlug.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

NodePlug::NodePlug(QSize size, QWidget *parent)
    : QWidget{parent},
      m_size(size),
      m_color(QColor(180,120,20)),
      m_lineColor(QColor(20,30,40)),
      m_lineThickness(1)
{
    setFixedSize(size);
}

void NodePlug::paintEvent(QPaintEvent *event)
{
    Q_UNUSED( event );

    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing);
    QPen pen( m_lineColor, m_lineThickness, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin );
    painter.setPen( pen );
    painter.setBrush(m_color);

    painter.drawChord(QRect(m_lineThickness,m_lineThickness,
                            width()-m_lineThickness,height()-m_lineThickness), 0, 360*16);
}

void NodePlug::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        event->accept();
        emit beginNewConnection(this);
    }

    //qDebug() << "NodePlug::mousePressEvent " << mapToGlobal(QPoint(width()/2,height()/2));
    // On click send to canvas a pointer to this object and the position
    // So that the curve will be redrawn every time the node is moved
}

void NodePlug::mouseReleaseEvent(QMouseEvent *event)
{
    event->accept();
    emit endNewConnection(this);
}

void NodePlug::enterEvent(QEvent *event)
{
    event->accept();
    m_color = QColor(225,200,50);
    m_lineColor = QColor(50,60,40);
    update();
}

void NodePlug::leaveEvent(QEvent *event)
{
    event->accept();
    m_color = QColor(180,120,20);
    m_lineColor = QColor(20,30,40);
    update();
}
