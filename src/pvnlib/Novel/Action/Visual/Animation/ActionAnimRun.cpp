#include "pvnLib/Novel/Action/Visual/Animation/ActionAnimAll.h"

void ActionSceneryObjectAnimColor::run()
{
	ActionSceneryObjectAnim::run();
	NovelState::getCurrentlyLoadedState()->scenery.addAnimator(AnimatorSceneryObjectColor(sceneryObject_, assetAnim_, priority, startDelay, speed, timesPlayed, bFinishAnimationAtEventEnd));

	if (onRun_)
		onRun_(parentEvent, sceneryObject_, assetAnim_, priority, startDelay, speed, timesPlayed, bFinishAnimationAtEventEnd);
}

void ActionSceneryObjectAnimFade::run()
{
	ActionSceneryObjectAnim::run();

	if (onRun_)
		onRun_(parentEvent, sceneryObject_, priority, startDelay, bFinishAnimationAtEventEnd, duration, bAppear);
}

void ActionSceneryObjectAnimMove::run()
{
	ActionSceneryObjectAnim::run();
	NovelState::getCurrentlyLoadedState()->scenery.addAnimator(AnimatorSceneryObjectMove(sceneryObject_, assetAnim_, priority, startDelay, speed, timesPlayed, bFinishAnimationAtEventEnd));

	if (onRun_)
		onRun_(parentEvent, sceneryObject_, assetAnim_, priority, startDelay, speed, timesPlayed, bFinishAnimationAtEventEnd);
}

void ActionSceneryObjectAnimRotate::run()
{
	ActionSceneryObjectAnim::run();
	NovelState::getCurrentlyLoadedState()->scenery.addAnimator(AnimatorSceneryObjectRotate(sceneryObject_, assetAnim_, priority, startDelay, speed, timesPlayed, bFinishAnimationAtEventEnd));

	if (onRun_)
		onRun_(parentEvent, sceneryObject_, assetAnim_, priority, startDelay, speed, timesPlayed, bFinishAnimationAtEventEnd);
}

void ActionSceneryObjectAnimScale::run()
{
	ActionSceneryObjectAnim::run();
	NovelState::getCurrentlyLoadedState()->scenery.addAnimator(AnimatorSceneryObjectScale(sceneryObject_, assetAnim_, priority, startDelay, speed, timesPlayed, bFinishAnimationAtEventEnd));

	if (onRun_)
		onRun_(parentEvent, sceneryObject_, assetAnim_, priority, startDelay, speed, timesPlayed, bFinishAnimationAtEventEnd);
}