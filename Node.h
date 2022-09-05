#ifndef NODE_H
#define NODE_H

#include <QObject>
#include <QWidget>

class Node : public QWidget
{
    Q_OBJECT
public:
    explicit Node(QWidget *parent = nullptr);

signals:

};

#endif // NODE_H
