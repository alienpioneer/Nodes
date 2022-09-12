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
    void    onNewNode();
    void    onClearCurves();
    void    onClear();

    void    onSelectNode(Node* node);
    void    onMoveNode(const QPoint position);

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

    bool    m_drawLine;
    bool    m_drawSmoothLine;

    QMenu*  m_menu;
    QPainterPath* m_currentPath;
    QList<QPainterPath*> m_pathList;

    int m_nodeWidth,m_nodeHeight;
    Node* m_currentNode;
    QList<Node*> m_nodeList;

    int MAX_W, MAX_H;
};

#endif // CANVAS_H
