#include "Canvas.h"
#include <QStyleOption>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

Canvas::Canvas(QRect size, QWidget *parent)
    : QWidget{parent},
      m_size(size),
      m_color(QColor(100,100,110)),
      m_lineColor(QColor(200,140,148)),
      m_lineThickness(2),
      m_currentMousePosition(QPoint(0,0)),
      m_drawLine(false),
      m_drawSmoothLine(true),
      m_currentPath(nullptr),
      m_nodeWidth(100),
      m_nodeHeight(50),
      m_currentNode(nullptr)
{
    setGeometry(size);
    setStyleSheet("border:1px solid; border-color: rgb(52, 53, 56);");

    m_menu = new QMenu(this);
    m_menu->setStyleSheet("border:1px solid gray;");
    QAction *newNode = new QAction("Create Node", this);
    QAction *clearCurves = new QAction("Clear Curves", this);
    QAction *clear = new QAction("Clear All", this);
    m_menu->addAction(newNode);
    connect(newNode,&QAction::triggered,this,&Canvas::onNewNode);
    m_menu->addAction(clearCurves);
    connect(clearCurves,&QAction::triggered,this,&Canvas::onClearCurves);
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

// TO DO FIX THIS
void Canvas::onNewNode()
{
    m_currentNode = new Node(QRect(0,0,m_nodeWidth,m_nodeHeight), this);
    connect(m_currentNode, &Node::moveNode, this, &Canvas::onMoveNode);
    connect(m_currentNode, &Node::selectNode, this, &Canvas::onSelectNode);
    m_currentNode->show();
    m_currentNode->move( m_currentMousePosition - QPoint(m_size.x(),4*m_size.y())); // TO DO FIX THIS ???
    m_nodeList.append(m_currentNode);
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_startPoint = mapToParent(event->pos());
        m_startPoint.setX(m_startPoint.x()-m_size.x());
        m_startPoint.setY(m_startPoint.y()-m_size.y());
        m_drawLine = true;
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_drawLine = false;
        m_pathList.append(m_currentPath);
    }
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
    //qDebug() << "Canvas: mouse MOVE";
}

void Canvas::contextMenuEvent(QContextMenuEvent *event)
{
    m_currentMousePosition = mapToGlobal(event->pos());
    m_menu->popup(m_currentMousePosition);
}

void Canvas::onClear()
{
    if(!m_pathList.empty())
    {
        for (QPainterPath* path: qAsConst(m_pathList))
        {
            delete path;
            path = nullptr;
        }
        m_pathList.clear();
    }

    if(!m_nodeList.empty())
    {
        for (Node* node: qAsConst(m_nodeList))
        {
            node->hide();
            delete node;
            node = nullptr;
        }
        m_nodeList.clear();
    }

    update();
}

void Canvas::onClearCurves()
{
    if(!m_pathList.empty())
    {
        for (QPainterPath* path: qAsConst(m_pathList))
        {
            delete path;
            path = nullptr;
        }
        m_pathList.clear();
    }
    update();
}

void Canvas::onMoveNode(const QPoint position)
{
    m_currentNode->move( position );
}


void Canvas::onSelectNode(Node *node)
{
    m_currentNode = node;
}
