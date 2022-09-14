#ifndef NODECORE_H
#define NODECORE_H

#include <QObject>
#include <QWidget>

class NodeCore : public QWidget
{
    Q_OBJECT
public:
    explicit NodeCore(QRect size, QWidget *parent = nullptr);

signals:
    void moveNode(const QPoint position);
    void selectNode(NodeCore* node);

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    QRect   m_size;
    QColor  m_color;
    bool    m_enableMovement;
    QPoint  m_currentMousePosition;
};

#endif // NODECORE_H
