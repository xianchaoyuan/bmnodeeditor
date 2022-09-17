#pragma once

#include <QPainter>

#include "nodegeometry.h"
#include "nodedatamodel.h"

/**
 * @brief 允许自定义绘制
 */
class NodePainterDelegate
{
public:
    virtual ~NodePainterDelegate() = default;
    virtual void paint(QPainter *painter, NodeGeometry const &geom, NodeDataModel const *model) = 0;
};
