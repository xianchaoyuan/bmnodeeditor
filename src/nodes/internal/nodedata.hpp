#pragma once

#include <QString>

struct NodeDataType
{
    QString id;
    QString name;

    friend bool operator<(NodeDataType const &d1, NodeDataType const &d2)
    {
        return d1.id < d2.id;
    }

    friend bool operator==(const NodeDataType &d1, const NodeDataType &d2)
    {
        return d1.id == d2.id;
    }
};


/**
 * @brief 表示节点之间传输的数据，实际数据存储在子类型中
 * @param type用于比较类型
 */
class NodeData
{
public:
    virtual ~NodeData() = default;

    virtual bool sameType(NodeData const &nodeData) const
    {
        return (this->type().id == nodeData.type().id);
    }

    //! 内部使用类型
    virtual NodeDataType type() const = 0;
};
