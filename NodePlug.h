#ifndef NODEPLUG_H
#define NODEPLUG_H

#include <QObject>
#include <QWidget>

class NodePlug : public QWidget
{
    Q_OBJECT
public:
    explicit NodePlug(QSize size, QWidget *parent = nullptr);

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

signals:
    void beginNewConnection(NodePlug* plug);
    void endNewConnection(NodePlug* plug);

private:
    QSize   m_size;
    QColor  m_color;
    QColor  m_lineColor;
    int     m_lineThickness;
};

#endif // NODEPLUG_H
