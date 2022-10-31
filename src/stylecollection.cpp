#include "stylecollection.h"

const NodeStyle &StyleCollection::nodeStyle()
{
    return instance().m_node_style_;
}

ConnectionStyle const &StyleCollection::connectionStyle()
{
    return instance()._connectionStyle;
}

FlowViewStyle const &StyleCollection::flowViewStyle()
{
    return instance()._flowViewStyle;
}

void StyleCollection::setNodeStyle(NodeStyle nodeStyle)
{
    instance().m_node_style_ = nodeStyle;
}

void StyleCollection::setConnectionStyle(ConnectionStyle connectionStyle)
{
    instance()._connectionStyle = connectionStyle;
}

void StyleCollection::setFlowViewStyle(FlowViewStyle flowViewStyle)
{
    instance()._flowViewStyle = flowViewStyle;
}

StyleCollection &StyleCollection::instance()
{
    static StyleCollection collection;
    return collection;
}
