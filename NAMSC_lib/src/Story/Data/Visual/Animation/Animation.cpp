#pragma once
#include "Story/Data/Visual/Animation/Animator.h"

#include "Story/Data/Story.h"

//TODO: przekopiuj i przeskaluj 	QVector<AnimNode>	*nodes; zamiast za kazdym razym mozyc speed
template<typename AnimNode>
AnimNode Animator<AnimNode>::currentAnimState()
{
    int elapsedTime = startTime.msecsTo(QTime::currentTime());
    if (bLoop && (elapsedTime > round(nodes->back().timeStamp) * speed))
    {
        elapsedTime %= round(nodes->back().timeStamp * speed);
        currentNode = nodes->cbegin();
        nextNode = currentNode + 1;
    }

    AnimNode ret = *currentNode;

    if (nextNode == nodes->cend())
        return ret;

    double	deltaTime = elapsedTime - round(currentNode->timeStamp * speed),
            duration = round((nextNode->timeStamp - currentNode->timeStamp) * speed);
    switch (nextNode->interpolationMethod)
    {
    case AnimNode::AnimInterpolationMethod::Linear:
    default:
        for (unsigned i = 0; i != (sizeof(ret.state) / sizeof(ret.state[0])); ++i)
            ret.state[i] += (nextNode->state[i] - ret.state[i]) * (deltaTime / duration);
        break;
    }
    return ret;
};

template<typename AnimNode>
AnimatorSceneryObject<AnimNode>::AnimatorSceneryObject(QString &&animAssetName, double speed, bool bLoop, QString &&sceneryObjectName) :
    Animator<AnimNode>(move(animAssetName), speed, bLoop), sceneryObjectName(move(sceneryObjectName))
{
    sceneryObject = Story::getInstance().;
}