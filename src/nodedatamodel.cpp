#include "nodedatamodel.h"
#include "stylecollection.h"

NodeDataModel::NodeDataModel()
    : m_node_style_(StyleCollection::nodeStyle())
{
    // Derived classes can initialize specific style here
}

QJsonObject NodeDataModel::save() const
{
    QJsonObject modelJson;
    modelJson["name"] = name();

    return modelJson;
}

const NodeStyle &NodeDataModel::nodeStyle() const
{
    return m_node_style_;
}

void NodeDataModel::setNodeStyle(const NodeStyle &style)
{
    m_node_style_ = style;
}
