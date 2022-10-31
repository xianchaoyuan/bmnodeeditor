#pragma once

#include "nodestyle.h"
#include "connectionstyle.h"
#include "flowviewstyle.h"

class StyleCollection
{
public:
    static const NodeStyle &nodeStyle();
    static ConnectionStyle const &connectionStyle();
    static FlowViewStyle const &flowViewStyle();

public:
    static void setNodeStyle(NodeStyle);
    static void setConnectionStyle(ConnectionStyle);
    static void setFlowViewStyle(FlowViewStyle);

private:
    StyleCollection() = default;
    StyleCollection(StyleCollection const &) = delete;

    StyleCollection &operator=(StyleCollection const &) = delete;

    static StyleCollection &instance();

private:
    NodeStyle m_node_style_;
    ConnectionStyle _connectionStyle;
    FlowViewStyle _flowViewStyle;
};
