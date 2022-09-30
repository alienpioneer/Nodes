#ifndef CANVAS_H
#define CANVAS_H

#include <QObject>
#include <QWidget>
#include <QMenu>
#include "Node.h"

class Canvas : public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QRect size, QWidget *parent = nullptr);

private slots:
    void    on_newNode();
    void    on_clearCurves();
    void    on_clearAll();

    void    on_selectNode(Node* node);
    void    on_moveNode(const QPoint position);

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void contextMenuEvent(QContextMenuEvent *event) override;

private:
    QRect   m_size;
    QColor  m_color;
    QColor  m_lineColor;
    int     m_lineThickness;

    QPoint  m_currentMousePosition;

    QPoint  m_startPoint, m_endPoint;
    QPoint  m_handleStart, m_handleEnd;

    bool    m_startDrawLine;
    bool    m_drawSmoothLines;
    bool    m_redrawBkg;
    bool    m_redrawStyles;

    QMenu*  m_menu;
    QMenu*  m_nodeSubmenu;

    QPainterPath* m_currentPath;
    QList<QPainterPath*> m_pathList;

    Node* m_currentNode;
    QList<Node*> m_nodeList;

    int MAX_W, MAX_H;
    int NODE_WIDTH, NODE_HEIGHT;
};

#endif // CANVAS_H
