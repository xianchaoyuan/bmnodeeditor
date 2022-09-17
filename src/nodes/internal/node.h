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

public slots: // data propagation
    /// Propagates incoming data to the underlying model.
    void propagateData(std::shared_ptr<NodeData> nodeData,
                       PortIndex inPortIndex,
                       const QUuid& connectionId) const;

    /// Fetches data from model's OUT #index port
    /// and propagates it to the connection
    void onDataUpdated(PortIndex index);

    /// Propagates empty data to the attached connection.
    void onDataInvalidated(PortIndex index);

    /// update the graphic part if the size of the embeddedwidget changes
    void onNodeSizeUpdated();

private:
    // addressing
    QUuid _uid;

    // data
    std::unique_ptr<NodeDataModel> _nodeDataModel;

    NodeState _nodeState;

    // painting
    NodeGeometry _nodeGeometry;

    std::unique_ptr<NodeGraphicsObject> _nodeGraphicsObject;
};
