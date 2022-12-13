#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectColor.h"
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectMove.h"
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectRotate.h"
#include "Novel/Data/Visual/Animation/AnimatorSceneryObjectScale.h"

#include "Novel/Data/Visual/Scenery/SceneryObject.h"

void AnimatorSceneryObjectColor::run()
{
}

bool AnimatorSceneryObjectColor::update(uint elapsedTime)
{
    AnimNodeDouble4D node = currentAnimState(elapsedTime);
    for (int i = 0; i != 4; ++i)
        parentSceneryObject_->colorMultiplier[i] = node.state_[i];

    return elapsedTime >= getDuration();
}

void AnimatorSceneryObjectMove::run()
{
}

bool AnimatorSceneryObjectMove::update(uint elapsedTime)
{
    AnimNodeDouble2D node = currentAnimState(elapsedTime);
    parentSceneryObject_->pos = QPoint(node.state_[0], node.state_[1]);

    return elapsedTime >= getDuration();
}

void AnimatorSceneryObjectRotate::run()
{
}

bool AnimatorSceneryObjectRotate::update(uint elapsedTime)
{
    AnimNodeDouble1D node = currentAnimState(elapsedTime);
    parentSceneryObject_->rotationDegree = node.state_[0];

    return elapsedTime >= getDuration();
}

void AnimatorSceneryObjectScale::run()
{
}

bool AnimatorSceneryObjectScale::update(uint elapsedTime)
{
    AnimNodeDouble2D node = currentAnimState(elapsedTime);
    parentSceneryObject_->scale = QSize(node.state_[0], node.state_[1]);

    return elapsedTime >= getDuration();
}
