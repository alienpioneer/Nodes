#include "NodeCore.h"
#include <QStyleOption>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

NodeCore::NodeCore(QRect size, QWidget *parent)
    : QWidget{parent},
    m_size(size),
    m_color(QColor(80,80,80)),
    m_enableMovement(false)
{
    setGeometry(size);
    setStyleSheet("border-width: 1px; border-style: solid; border-radius: 6px;"
                  "border-color: rgb(42, 43, 46); background-color: rgb(80,80,80)");
//    setAttribute(Qt::WA_TranslucentBackground);
}


void NodeCore::paintEvent(QPaintEvent *event)
{
    Q_UNUSED( event );

    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing);

//    QRect geo(0, 0, width(), height());
//    painter.fillRect(geo, m_color);

    QStyleOption styleOpt;
    styleOpt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &styleOpt, &painter, this);
}
