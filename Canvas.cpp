#include "Canvas.h"
#include <QStyleOption>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

Canvas::Canvas(QRect size, QWidget *parent)
    : QWidget{parent},
      m_size(size),
      m_color(QColor(100,100,110)),
      m_lineColor(QColor(190,140,148)),
      m_lineThickness(2),
      m_drawLine(false),
      m_drawSmoothLine(true),
      m_currentPath(nullptr)
{
    setGeometry(size);

    m_menu = new QMenu(this);
    m_menu->setStyleSheet("border:1px solid gray;");//background-color: #D1D1D1;

    QAction *newNode = new QAction("Create Node", this);
    QAction *clear = new QAction("Clear All", this);
    m_menu->addAction(newNode);
    connect(newNode,&QAction::triggered,this,&Canvas::onNewNode);
    m_menu->addAction(clear);
    connect(clear,&QAction::triggered,this,&Canvas::onClear);
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

    if (m_drawLine)
    {
        m_currentPath = new QPainterPath();

        m_currentPath->moveTo(m_startPoint);

        if (m_drawSmoothLine)
        {
            m_handleStart.setY(m_startPoint.y());
            m_handleStart.setX(m_startPoint.x()+(m_endPoint.x()-m_startPoint.x())*0.4);

            m_handleEnd.setY(m_endPoint.y());
            m_handleEnd.setX(m_endPoint.x()-(m_endPoint.x()-m_startPoint.x())*0.4);
            m_currentPath->cubicTo(m_handleStart, m_handleEnd, m_endPoint);
        }
        else
        {
            m_currentPath->lineTo(m_endPoint);
        }

        painter.drawPath(*m_currentPath);
    }

    if(!m_pathList.empty())
    {
        for(QPainterPath* path: qAsConst(m_pathList))
        {
            painter.drawPath(*path);
        }
    }
}


void Canvas::mousePressEvent(QMouseEvent *event)
{
    m_startPoint = mapToParent(event->pos());
    m_startPoint.setX(m_startPoint.x()-m_size.x());
    m_startPoint.setY(m_startPoint.y()-m_size.y());
    m_drawLine = true;
}


void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED( event );
    m_drawLine = false;
    m_pathList.append(m_currentPath);
}


void Canvas::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED( event );
}


void Canvas::mouseMoveEvent(QMouseEvent *event)
{

    m_endPoint = mapToParent(event->pos());
    m_endPoint.setX(m_endPoint.x()-m_size.x());
    m_endPoint.setY(m_endPoint.y()-m_size.y());
    update();
}


void Canvas::contextMenuEvent(QContextMenuEvent *event)
{
    m_menu->popup(mapToGlobal(event->pos()));
}

void Canvas::onClear()
{
//    qDebug() << "Clear Action Clicked";
    m_pathList.clear();
    update();
}

void Canvas::onNewNode()
{
    qDebug() << "NewNode Action Clicked";
}
