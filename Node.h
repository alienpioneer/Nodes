#ifndef NODE_H
#define NODE_H

#include <QObject>
#include <QWidget>
#include "NodeCore.h"
#include "NodeConnection.h"

class Node : public QWidget
{
    Q_OBJECT

    enum class Connexion
    {
        IN = 0,
        OUT
    };

public:
    explicit Node(QRect size, QWidget *parent = nullptr);

signals:
    void moveNode(const QPoint position);
    void selectNode(Node* node);

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void contextMenuEvent(QContextMenuEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

private:
    void createConnexions(Connexion type, int count);
    void addConnexions(Connexion type, int count);

private:
    QRect                   m_size;
    QRect                   m_connectorSize;
    bool                    m_enableMovement;
    QPoint                  m_currentMousePosition;

    int                     m_connexionSize;

    NodeCore*               m_nodeCore;
    NodeConnection*         m_nodeConnection;
    QList<NodeConnection*>  m_IN_connectList;
    QList<NodeConnection*>  m_OUT_connectList;
};

#endif // NODE_H
