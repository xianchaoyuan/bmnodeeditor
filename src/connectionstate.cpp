#include "connectionstate.hpp"

#include <iostream>
#include <QPointF>

#include "flowscene.hpp"
#include "node.hpp"

ConnectionState::~ConnectionState()
{
    resetLastHoveredNode();
}

void ConnectionState::interactWithNode(Node *node)
{
    if (node) {
        _lastHoveredNode = node;
    } else {
        resetLastHoveredNode();
    }
}

void ConnectionState::setLastHoveredNode(Node *node)
{
    _lastHoveredNode = node;
}

void ConnectionState::resetLastHoveredNode()
{
    if (_lastHoveredNode)
        _lastHoveredNode->resetReactionToConnection();

    _lastHoveredNode = nullptr;
}
