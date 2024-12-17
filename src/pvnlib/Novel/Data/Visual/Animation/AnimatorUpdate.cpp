#include "pvnLib/Novel/Data/Visual/Animation/AnimatorSceneryObjectColor.h"
#include "pvnLib/Novel/Data/Visual/Animation/AnimatorSceneryObjectMove.h"
#include "pvnLib/Novel/Data/Visual/Animation/AnimatorSceneryObjectRotate.h"
#include "pvnLib/Novel/Data/Visual/Animation/AnimatorSceneryObjectScale.h"

#include "pvnLib/Novel/Data/Visual/Scenery/SceneryObject.h"

//template<typename AnimNode>
//AnimNode AnimatorSceneryObjectInterface<AnimNode>::currentAnimState(uint elapsedTime)

bool AnimatorSceneryObjectColor::update(uint elapsedTime)
{
    AnimNodeDouble4D node = currentAnimState(elapsedTime);
    for (int i = 0; i != 4; ++i)
        parentSceneryObject_->colorMultiplier[i] = node.state_[i];

    return elapsedTime >= getDuration();
}

bool AnimatorSceneryObjectFade::update(uint elapsedTime)
{
    return false;
}

bool AnimatorSceneryObjectMove::update(uint elapsedTime)
{
    AnimNodeDouble2D node = currentAnimState(elapsedTime);
    parentSceneryObject_->pos = QPoint(node.state_[0], node.state_[1]);

    return elapsedTime >= getDuration();
}

bool AnimatorSceneryObjectRotate::update(uint elapsedTime)
{
    AnimNodeDouble1D node = currentAnimState(elapsedTime);
    parentSceneryObject_->rotationDegree = node.state_[0];

    return elapsedTime >= getDuration();
}

bool AnimatorSceneryObjectScale::update(uint elapsedTime)
{
    AnimNodeDouble2D node = currentAnimState(elapsedTime);
    parentSceneryObject_->scale = QSize(node.state_[0], node.state_[1]);

    return elapsedTime >= getDuration();
}