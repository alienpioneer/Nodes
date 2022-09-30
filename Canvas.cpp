#include "Canvas.h"
#include <QStyleOption>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QDebug>

Canvas::Canvas(QRect size, QWidget *parent)
    : QWidget{parent},
      m_size(size),
      m_color(QColor(100,100,110)),
      m_lineColor(QColor(200,140,148)),
      m_lineThickness(2),
      m_currentMousePosition(QPoint(0,0)),
      m_startDrawLine(false),
      m_drawSmoothLines(true),
      m_currentPath(nullptr),
      m_currentNode(nullptr)
{
    setGeometry(size);
    setStyleSheet("border:1px solid; border-color: rgb(52, 53, 56);");

    // Create Right-Click Menu
    m_menu = new QMenu(this);
    m_nodeSubmenu = m_menu->addMenu("Create Node");
    m_menu->setStyleSheet("border:1px solid gray;");
    m_nodeSubmenu->setStyleSheet("border:1px solid gray;");

    QAction *clearCurves = new QAction("Clear Curves", this);
    m_menu->addAction(clearCurves);
    connect(clearCurves,&QAction::triggered,this,&Canvas::on_clearCurves);

    QAction *clear = new QAction("Clear All", this);
    m_menu->addAction(clear);
    connect(clear,&QAction::triggered,this,&Canvas::on_clearAll);

    // One input one output
    QAction *newNode = new QAction("Default", this);
    m_nodeSubmenu->addAction(newNode);
    connect(newNode,&QAction::triggered,this,&Canvas::on_newNode);

    // Operation of 2
    QAction *newNodeOp2 = new QAction("Operation 2", this);
    m_nodeSubmenu->addAction(newNodeOp2);
    connect(newNodeOp2,&QAction::triggered,this,&Canvas::on_newNode);

    // Operation of 2
    QAction *newNodeOp4 = new QAction("Operation 4", this);
    m_nodeSubmenu->addAction(newNodeOp4);
    connect(newNodeOp4,&QAction::triggered,this,&Canvas::on_newNode);

    NODE_WIDTH = width()/6;
    NODE_HEIGHT = height()/8;

//    qDebug() << width() <<" "<< height();
//    qDebug() << NODE_WIDTH <<" "<< NODE_HEIGHT;

    MAX_W = width() - NODE_WIDTH;
    MAX_H = height() - NODE_HEIGHT;

    m_redrawBkg = true;
    m_redrawStyles = true;
}

void Canvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED( event );

    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing);
    QPen pen( m_lineColor, m_lineThickness, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin );
    painter.setPen( pen );

    if (m_redrawBkg)
    {
        QRect geo(0, 0, width(), height());
        painter.fillRect(geo, m_color);
        //m_redrawBkg = false;
    }

    if (m_redrawStyles)
    {
        QStyleOption styleOpt;
        styleOpt.init(this);
        style()->drawPrimitive(QStyle::PE_Widget, &styleOpt, &painter, this);
        //m_redrawStyles = false;
    }

    if (m_startDrawLine)
    {
        if (!m_currentPath)
            m_currentPath = new QPainterPath();
        else
            m_currentPath->clear();

        m_currentPath->moveTo(m_startPoint);

        if (m_drawSmoothLines)
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

// TODO FIX THIS
void Canvas::on_newNode()
{
    //TODO Add context to create node
    m_currentNode = new Node(QRect(0, 0, NODE_WIDTH, NODE_HEIGHT), this);
    connect(m_currentNode, &Node::moveNode, this, &Canvas::on_moveNode);
    connect(m_currentNode, &Node::selectNode, this, &Canvas::on_selectNode);
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
        m_startDrawLine = true;
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_startDrawLine = false;
        m_pathList.append(m_currentPath);

//        delete m_currentPath;
        m_currentPath = nullptr;
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

void Canvas::on_clearAll()
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

void Canvas::on_clearCurves()
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

void Canvas::on_moveNode(const QPoint position)
{
    QPoint movePosition = position;

    if ( position.x() <= 0 )
        movePosition.setX(0);
    if (position.x() >= MAX_W)
        movePosition.setX(MAX_W);
    if ( position.y() <= 0 )
        movePosition.setY(0);
    if (position.y() >= MAX_H)
        movePosition.setY(MAX_H);

    m_currentNode->move(movePosition);
}


void Canvas::on_selectNode(Node *node)
{
    m_currentNode = node;
}
