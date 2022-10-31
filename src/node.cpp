#include "node.h"

#include <QObject>
#include <utility>
#include <iostream>

#include "flowscene.h"
#include "nodegraphicsobject.h"
#include "nodedatamodel.h"
#include "connectiongraphicsobject.h"
#include "connectionstate.h"

Node::Node(std::unique_ptr<NodeDataModel> &&dataModel)
    : m_uuid_(QUuid::createUuid()),
      m_node_data_model_(std::move(dataModel)),
      m_node_state_(m_node_data_model_),
      m_node_geometry_(m_node_data_model_),
      m_node_graphics_object_(nullptr)
{
    m_node_geometry_.recalculateSize();

    // propagate data: model => node
    connect(m_node_data_model_.get(), &NodeDataModel::dataUpdated,
            this, &Node::onDataUpdated);

    connect(m_node_data_model_.get(), &NodeDataModel::dataInvalidated,
            this, &Node::onDataInvalidated);

    connect(m_node_data_model_.get(), &NodeDataModel::embeddedWidgetSizeUpdated,
            this, &Node::onNodeSizeUpdated );
}

Node::~Node() = default;

QJsonObject Node::save() const
{
    QJsonObject nodeJson;
    nodeJson["id"] = m_uuid_.toString();
    nodeJson["model"] = m_node_data_model_->save();

    QJsonObject obj;
    obj["x"] = m_node_graphics_object_->pos().x();
    obj["y"] = m_node_graphics_object_->pos().y();
    nodeJson["position"] = obj;

    return nodeJson;
}

void Node::restore(QJsonObject const &json)
{
    m_uuid_ = QUuid(json["id"].toString());

    QJsonObject positionJson = json["position"].toObject();
    QPointF     point(positionJson["x"].toDouble(),
            positionJson["y"].toDouble());
    m_node_graphics_object_->setPos(point);

    m_node_data_model_->restore(json["model"].toObject());
}

QUuid Node::id() const
{
    return m_uuid_;
}

void Node::reactToPossibleConnection(PortType reactingPortType,
                                     NodeDataType const &reactingDataType,
                                     QPointF const &scenePoint)
{
    QTransform const t = m_node_graphics_object_->sceneTransform();
    QPointF p = t.inverted().map(scenePoint);

    m_node_geometry_.setDraggingPosition(p);
    m_node_graphics_object_->update();
    m_node_state_.setReaction(NodeState::REACTING,
                           reactingPortType,
                           reactingDataType);
}

void Node::resetReactionToConnection()
{
    m_node_state_.setReaction(NodeState::NOT_REACTING);
    m_node_graphics_object_->update();
}

NodeGraphicsObject const &Node::nodeGraphicsObject() const
{
    return *m_node_graphics_object_.get();
}

NodeGraphicsObject &Node::nodeGraphicsObject()
{
    return *m_node_graphics_object_.get();
}

void Node::setGraphicsObject(std::unique_ptr<NodeGraphicsObject>&& graphics)
{
    m_node_graphics_object_ = std::move(graphics);
    m_node_geometry_.recalculateSize();
}

NodeGeometry &Node::nodeGeometry()
{
    return m_node_geometry_;
}


NodeGeometry const &Node::nodeGeometry() const
{
    return m_node_geometry_;
}

NodeState const &Node::nodeState() const
{
    return m_node_state_;
}

NodeState &Node::nodeState()
{
    return m_node_state_;
}

NodeDataModel *Node::nodeDataModel() const
{
    return m_node_data_model_.get();
}

void Node::propagateData(std::shared_ptr<NodeData> nodeData,
                         PortIndex inPortIndex,
                         const QUuid &connectionId) const
{
    m_node_data_model_->setInData(std::move(nodeData), inPortIndex, connectionId);

    // Recalculate the nodes visuals. A data change can result in the
    // node taking more space than before, so this forces a
    // recalculate+repaint on the affected node.
    m_node_graphics_object_->setGeometryChanged();
    m_node_geometry_.recalculateSize();
    m_node_graphics_object_->update();
    m_node_graphics_object_->moveConnections();
}

void Node::onDataUpdated(PortIndex index)
{
    auto nodeData = m_node_data_model_->outData(index);

    auto const &connections =
            m_node_state_.connections(PortType::Out, index);

    for (auto const &c : connections)
        c.second->propagateData(nodeData);
}

void Node::onDataInvalidated(PortIndex index)
{
    auto const &connections =
            m_node_state_.connections(PortType::Out, index);

    for (auto const &c : connections)
        c.second->propagateEmptyData();
}

void Node::onNodeSizeUpdated()
{
    if(nodeDataModel()->embeddedWidget()) {
        nodeDataModel()->embeddedWidget()->adjustSize();
    }
    nodeGeometry().recalculateSize();
    for (PortType type: {PortType::In, PortType::Out}) {
        for (auto &conn_set : nodeState().getEntries(type)) {
            for (auto &pair: conn_set) {
                Connection* conn = pair.second;
                conn->getConnectionGraphicsObject().move();
            }
        }
    }
}
