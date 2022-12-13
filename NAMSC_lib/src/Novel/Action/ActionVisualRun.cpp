#include "Novel/Action/ActionsAll.h"

#include "Novel/Data/Save/NovelState.h"

void ActionCharacter::run()
{
	Action::run();

	character_ = NovelState::getCurrentlyLoadedState()->scenery.getDisplayedCharacter(characterName_);
}

void ActionSceneryObjectAnimColor::run()
{
	NovelState::getCurrentlyLoadedState()->scenery.addAnimator(AnimatorSceneryObjectColor(sceneryObject_, assetAnim_, priority, startDelay, speed, timesPlayed, bStopAnimationAtEventEnd));

	if (onRun_)
		onRun_(parentEvent_, parentScene_, sceneryObject_, assetAnim_, priority, startDelay, speed, timesPlayed, bStopAnimationAtEventEnd);
}

void ActionSceneryObjectAnimMove::run()
{
	NovelState::getCurrentlyLoadedState()->scenery.addAnimator(AnimatorSceneryObjectMove(sceneryObject_, assetAnim_, priority, startDelay, speed, timesPlayed, bStopAnimationAtEventEnd));

	if (onRun_)
		onRun_(parentEvent_, parentScene_, sceneryObject_, assetAnim_, priority, startDelay, speed, timesPlayed, bStopAnimationAtEventEnd);
}

void ActionSceneryObjectAnimRotate::run()
{
	NovelState::getCurrentlyLoadedState()->scenery.addAnimator(AnimatorSceneryObjectRotate(sceneryObject_, assetAnim_, priority, startDelay, speed, timesPlayed, bStopAnimationAtEventEnd));

	if (onRun_)
		onRun_(parentEvent_, parentScene_, sceneryObject_, assetAnim_, priority, startDelay, speed, timesPlayed, bStopAnimationAtEventEnd);
}

void ActionSceneryObjectAnimScale::run()
{
	NovelState::getCurrentlyLoadedState()->scenery.addAnimator(AnimatorSceneryObjectScale(sceneryObject_, assetAnim_, priority, startDelay, speed, timesPlayed, bStopAnimationAtEventEnd));

	if (onRun_)
		onRun_(parentEvent_, parentScene_, sceneryObject_, assetAnim_, priority, startDelay, speed, timesPlayed, bStopAnimationAtEventEnd);
}

void ActionSceneryObjectAnimFade::acceptVisitor(ActionVisitor* visitor) 
{
	visitor->visitActionSceneryObjectAnimFade(this);
}
