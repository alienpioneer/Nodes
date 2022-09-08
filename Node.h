#ifndef NODE_H
#define NODE_H

#include <QObject>
#include <QWidget>

class Node : public QWidget
{
    Q_OBJECT
public:
    explicit Node(QRect size, QWidget *parent = nullptr);

signals:
    void moveNode(const QPoint position);
    void selectNode(Node* node);

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void contextMenuEvent(QContextMenuEvent *event) override;

private:
    QRect   m_size;
    QColor  m_color;
    bool    m_enableMovement;
    QPoint  m_currentMousePosition;
};

#endif // NODE_H
