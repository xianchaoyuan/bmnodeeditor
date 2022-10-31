#pragma once

#include <QWidget>

#include "porttype.h"
#include "nodedata.h"
#include "serializable.h"
#include "nodestyle.h"
#include "nodepainterdelegate.h"

class NodePainterDelegate;

// 节点验证状态
enum class NodeValidationState
{
    Valid,
    Warning,
    Error
};

class Connection;
class StyleCollection;

/**
 * @brief 节点数据模型
 */
class NodeDataModel : public QObject, public Serializable
{
    Q_OBJECT

public:
    NodeDataModel();
    virtual ~NodeDataModel() = default;

    //! 说明
    virtual QString caption() const = 0;
    virtual bool captionVisible() const { return true; }

    //! 端口标题在GUI中用于标记各个端口
    virtual QString portCaption(PortType, PortIndex) const { return QString(); }
    virtual bool portCaptionVisible(PortType, PortIndex) const { return false; }

    //! 模型的独一无二的名字（绝对不能重复）
    virtual QString name() const = 0;

public:
    QJsonObject save() const override;

public:
    virtual unsigned int nPorts(PortType portType) const = 0;
    virtual NodeDataType dataType(PortType portType, PortIndex portIndex) const = 0;

public:
    // 连接策略
    enum class ConnectionPolicy
    {
        One,
        Many,
    };

    virtual ConnectionPolicy portOutConnectionPolicy(PortIndex) const
    {
        return ConnectionPolicy::Many;
    }

    virtual ConnectionPolicy portInConnectionPolicy(PortIndex) const
    {
        return ConnectionPolicy::One;
    }

    const NodeStyle &nodeStyle() const;
    void setNodeStyle(const NodeStyle &style);

public:
    //! 触发算法
    virtual void setInData(std::shared_ptr<NodeData> nodeData, PortIndex port) = 0;

    //! 如果portInConnectPolicy返回ConnectionPolicy:：Many，请使用此选项
    virtual void setInData(std::shared_ptr<NodeData> nodeData, PortIndex port, const QUuid &connectionId)
    {
        Q_UNUSED(connectionId);
        setInData(nodeData, port);
    }

    virtual std::shared_ptr<NodeData> outData(PortIndex port) = 0;

    //! 嵌入的小部件使用此函数创建，而不是构造函数
    virtual QWidget *embeddedWidget() = 0;

    virtual bool resizable() const { return false; }

    virtual NodeValidationState validationState() const { return NodeValidationState::Valid; }

    virtual QString validationMessage() const { return QString(""); }

    virtual NodePainterDelegate *painterDelegate() const { return nullptr; }

public slots:
    virtual void inputConnectionCreated(Connection const&)
    {
    }

    virtual void inputConnectionDeleted(Connection const&)
    {
    }

    virtual void outputConnectionCreated(Connection const&)
    {
    }

    virtual void outputConnectionDeleted(Connection const&)
    {
    }

signals:
    //! 触发下游节点中的更新。
    void dataUpdated(PortIndex index);

    //! 触发下游空数据的传播。
    void dataInvalidated(PortIndex index);

    void computingStarted();
    void computingFinished();

    void embeddedWidgetSizeUpdated();

private:
    NodeStyle m_node_style_;
};
