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
    QPoint  m_startPoint, m_endPoint, m_mousePressOffset;
    bool    m_drawLine;

    QMenu*  m_menu;
};

#endif // CANVAS_H
