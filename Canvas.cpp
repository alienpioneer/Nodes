#include "Canvas.h"
#include <QStyleOption>
#include <QPainter>
#include <QMouseEvent>
#include <QMenu>
#include <QDebug>

Canvas::Canvas(QRect size, QWidget *parent)
    : QWidget{parent},
      m_size(size),
      m_color(QColor(118,110,122)),
      m_lineColor(QColor(204,139,128)),
      m_lineThickness(2),
      m_drawLine(false)
{
    setGeometry(size);
}


void Canvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED( event );

    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing);
    QPen pen( m_lineColor, m_lineThickness, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin );
    painter.setPen( pen );

    QRect geo(0, 0, width(), height());
    painter.fillRect(geo, m_color);

    QStyleOption styleOpt;
    styleOpt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &styleOpt, &painter, this);

//    QPainterPath path;
//    path.moveTo(100,100);
//    path.lineTo(300,300);
//    painter.drawPath(path);
    if (m_drawLine)
    {
        QPainterPath path;
        path.moveTo(m_startPoint);
        path.lineTo(m_endPoint);
//        path.quadTo(handleAUp , midA);
//        path.quadTo(handleADown, endA);
//        path.moveTo(startB);
//        path.quadTo(handleBUp , midB);
//        path.quadTo(handleBDown, endB);
        painter.drawPath(path);
    }
}


void Canvas::mousePressEvent(QMouseEvent *event)
{
    m_startPoint = mapToParent(event->pos());
    m_startPoint.setX(m_startPoint.x()-m_size.x());
    m_startPoint.setY(m_startPoint.y()-m_size.y());
    //qDebug() << "Mouse press" << m_drawLine;
    update();
}


void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED( event );
    //qDebug() << "Mouse release";
    m_drawLine = false;
}


void Canvas::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED( event );
}


void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    m_drawLine = true;
    //qDebug() << "Mouse move";
    m_endPoint = mapToParent(event->pos());
    m_endPoint.setX(m_endPoint.x()-m_size.x());
    m_endPoint.setY(m_endPoint.y()-m_size.y());
    update();
}


void Canvas::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *menu = new QMenu(this);
    menu->setStyleSheet("border:1px solid gray;");//background-color: #D1D1D1;
    QAction *newNode = new QAction("Create Node", this);
    QAction *clear = new QAction("Clear All", this);
    menu->addAction(newNode);
    menu->addAction(clear);
    menu->popup(mapToGlobal(event->pos()));
    connect(newNode,&QAction::triggered,this,&Canvas::onNewNode);
    connect(clear,&QAction::triggered,this,&Canvas::onClear);
}

void Canvas::onClear()
{
    qDebug() << "Clear Action Clicked";
}

void Canvas::onNewNode()
{
    qDebug() << "NewNode Action Clicked";
}
