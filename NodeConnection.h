#ifndef NODECONNECTION_H
#define NODECONNECTION_H

#include <QObject>
#include <QWidget>

class NodeConnection : public QWidget
{
    Q_OBJECT
public:
    explicit NodeConnection(QSize size, QWidget *parent = nullptr);

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

private:
    QSize   m_size;
    QColor  m_color;
    QColor  m_lineColor;
    int     m_lineThickness;
};

#endif // NODECONNECTION_H
