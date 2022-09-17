#pragma once

#include <QPainter>

#include "nodegeometry.hpp"
#include "nodedatamodel.hpp"
#include "export.hpp"

/**
 * @brief 允许自定义绘制
 */
class NodePainterDelegate
{
public:
    virtual ~NodePainterDelegate() = default;
    virtual void paint(QPainter *painter, NodeGeometry const &geom, NodeDataModel const *model) = 0;
};
