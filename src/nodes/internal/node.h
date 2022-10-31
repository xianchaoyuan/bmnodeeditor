#pragma once

#include <QObject>
#include <QUuid>
#include <QJsonObject>

#include "porttype.h"
#include "nodestate.h"
#include "nodegeometry.h"
#include "nodedata.h"
#include "nodegraphicsobject.h"
#include "connectiongraphicsobject.h"
#include "serializable.h"

class Connection;
class ConnectionState;
class NodeGraphicsObject;
class NodeDataModel;

class Node : public QObject, public Serializable
{
    Q_OBJECT

public:
    //! NodeDataModel应为右值，并移动到节点中
    Node(std::unique_ptr<NodeDataModel> &&dataModel);
    virtual ~Node();

public:
    QJsonObject save() const override;
    void restore(QJsonObject const &json) override;

public:
    QUuid id() const;
    void reactToPossibleConnection(PortType,
                                   NodeDataType const &,
                                   QPointF const &scenePoint);
    void resetReactionToConnection();

public:
    NodeGraphicsObject const &nodeGraphicsObject() const;
    NodeGraphicsObject &nodeGraphicsObject();

    void setGraphicsObject(std::unique_ptr<NodeGraphicsObject> &&graphics);

    NodeGeometry &nodeGeometry();
    NodeGeometry const &nodeGeometry() const;
    NodeState const &nodeState() const;
    NodeState &nodeState();
    NodeDataModel *nodeDataModel() const;

public slots:
    //! 将传入数据传播到基础模型。
    void propagateData(std::shared_ptr<NodeData> nodeData,
                       PortIndex inPortIndex,
                       const QUuid &connectionId) const;

    //! 从模型的out索引端口获取数据并将其传播到连接
    void onDataUpdated(PortIndex index);

    //! 将空数据传播到连接
    void onDataInvalidated(PortIndex index);

    //! 如果embeddedwidget的大小更改，则更新图形部件
    void onNodeSizeUpdated();

private:
    std::unique_ptr<NodeDataModel> m_node_data_model_;    // data
    std::unique_ptr<NodeGraphicsObject> m_node_graphics_object_;

    QUuid m_uuid_;
    NodeState m_node_state_;
    NodeGeometry m_node_geometry_;    // painting
};
