#pragma once

#include <QJsonObject>

/**
 * @brief 可序列化
 */
class Serializable
{
public:
    virtual ~Serializable() = default;
    virtual QJsonObject save() const = 0;

    virtual void restore(QJsonObject const &/*p*/) {}
};
