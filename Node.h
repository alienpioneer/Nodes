#ifndef NODE_H
#define NODE_H

#include <QObject>
#include <QWidget>
#include "NodeCore.h"
#include "NodePlug.h"

class Node : public QWidget
{
    Q_OBJECT

    enum class Connection
    {
        IN = 0,
        OUT
    };

public:
    explicit Node(QRect size, QWidget *parent = nullptr);

signals:
    void moveNode(const QPoint position);
    void selectNode(Node* node);
    void beginConnection(NodePlug* plug);
    void endConnection(NodePlug* plug);

private slots:
    void on_beginNewConnection(NodePlug* plug);
    void on_endNewConnection(NodePlug* plug);

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void contextMenuEvent(QContextMenuEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

private:
    void createConnectionSlots(Connection type, int count);
    void addConnectionSlots(Connection type, int count);

private:
    QRect               m_size;
    QRect               m_connectorSize;
    bool                m_enableMovement;
    QPoint              m_currentMousePosition;

    int                 m_connexionSize;

    NodeCore*           m_nodeCore;
    NodePlug*           m_nodeConnection;
    QList<NodePlug*>    m_IN_plugList;
    QList<NodePlug*>    m_OUT_plugList;
};

#endif // NODE_H
