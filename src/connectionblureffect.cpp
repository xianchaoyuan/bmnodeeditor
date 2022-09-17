#include "connectionblureffect.h"
#include "connectiongraphicsobject.h"
#include "connectionpainter.h"

ConnectionBlurEffect::ConnectionBlurEffect(ConnectionGraphicsObject*)
{
    //
}

void ConnectionBlurEffect::draw(QPainter *painter)
{
    QGraphicsBlurEffect::draw(painter);

    //ConnectionPainter::paint(painter,
    //_object->connectionGeometry(),
    //_object->connectionState());

    //_item->paint(painter, nullptr, nullptr);
}
