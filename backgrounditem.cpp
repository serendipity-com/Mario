#include "backgrounditem.h"

BackgroundItem::BackgroundItem(const QPixmap &pixmap, QGraphicsItem * parent)
    : QGraphicsPixmapItem(pixmap, parent)
{
}
/*La collidingItems()función siempre devolverá los
 *  elementos de fondo, ya que el elemento del jugador
 *  está sobre todos ellos la mayor parte del tiempo.
 *  Para evitar la verificación continua si en realidad
 *  son monedas, utilizamos un truco. En lugar de usarlo
 *   QGraphicsPixmapItemdirectamente, lo subclasificamos
 *  y reimplementamos su shape()función virtual ,
 *  de la siguiente manera:*/
QPainterPath BackgroundItem::shape() const
{
    return QPainterPath();
}
