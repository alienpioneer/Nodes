#ifndef CANVAS_H
#define CANVAS_H

#include <QObject>
#include <QWidget>
#include <QMenu>

class Canvas : public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QRect size, QWidget *parent = nullptr);

private slots:
    void    onNewNode();
    void    onClear();

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
    QPoint  m_startPoint, m_endPoint;
    QPoint  m_handleStart, m_handleEnd;

    bool    m_drawLine;
    bool    m_drawSmoothLine;

    QMenu*  m_menu;
    QList<QPainterPath*> m_pathList;
};

#endif // CANVAS_H
