#include "connectionblureffect.hpp"
#include "connectiongraphicsobject.hpp"
#include "connectionpainter.hpp"

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
