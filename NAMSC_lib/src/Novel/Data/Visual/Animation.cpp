#pragma once
#include "Global.h"

#include "Novel/Data/Visual/Animation/Type/AnimatorTransform.h"

#include "Novel/Data/Novel.h"

bool AnimatorSceneryObjectInterface::checkForErrors()
{
    try
    {
        if (sceneryObjectName.isEmpty())
            return false;
        Novel::getInstance().findSceneryObject(sceneryObjectName);
    }
    catch (...)
    {
        return false;
    }
    return true;
}

//AnimatorBase

template<typename AnimNode>
void AnimatorBase<AnimNode>::run()
{
        ensureResourcesAreLoaded();
    startTime = QTime::currentTime();
    currentNode = nodes->cbegin();
    nextNode = currentNode + 1;
}

//TODO: przekopiuj i przeskaluj QVector<AnimNode> *nodes w konstruktorze; zamiast za kazdym razym mnozyc speed
template<typename AnimNode>
AnimNode AnimatorBase<AnimNode>::currentAnimState()
{
    if (timesPlayed == 0)
        return nodes->back();

    int elapsedTime = startTime.msecsTo(QTime::currentTime());
    if (elapsedTime > qRound(nodes->back().timeStamp * speed))
    {
        if (--timesPlayed == 0)
            return nodes->back();

        elapsedTime %= qRound(nodes->back().timeStamp * speed);
        currentNode = nodes->cbegin();
        nextNode = currentNode + 1;
    }

    AnimNode ret = *currentNode;

    if (nextNode == nodes->cend())
        return ret;

    double	deltaTime = elapsedTime - qRound(currentNode->timeStamp * speed),
        duration = qRound((nextNode->timeStamp - currentNode->timeStamp) * speed);
    switch (nextNode->interpolationMethod)
    {
    case AnimNode::AnimInterpolationMethod::Linear:
    default:
        for (uint i = 0; i != (sizeof(ret.state) / sizeof(ret.state[0])); ++i)
            ret.state[i] += (nextNode->state[i] - ret.state[i]) * (deltaTime / duration);
        break;
    }
    return ret;
}

