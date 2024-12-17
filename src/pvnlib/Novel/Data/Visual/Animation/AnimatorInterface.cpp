#include "pvnLib/Novel/Data/Visual/Animation/AnimatorInterface.h"

AnimatorInterface::~AnimatorInterface() = default;

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(AnimatorInterface& first, AnimatorInterface& second) noexcept
{
	using std::swap;
	swap(first.priority,                   second.priority);
	swap(first.startDelay,                 second.startDelay);
	swap(first.speed,                      second.speed);
	swap(first.timesPlayed,                second.timesPlayed);
	swap(first.bFinishAnimationAtEventEnd, second.bFinishAnimationAtEventEnd);
}

AnimatorInterface::AnimatorInterface(uint priority, uint startDelay, double speed, int timesPlayed, bool bFinishAnimationAtEventEnd)
	: priority(priority),
	startDelay(startDelay),
	speed(speed),
	timesPlayed(timesPlayed), 
	bFinishAnimationAtEventEnd(bFinishAnimationAtEventEnd)
{
}

//defaulted
//bool AnimatorInterface::operator==(const AnimatorInterface& obj) const
//{
//    if (this == &obj)
//        return true;
//
//	return priority                   == obj.priority                   &&
//		   startDelay                 == obj.startDelay                 &&
//		   speed                      == obj.speed                      &&
//		   timesPlayed                == obj.timesPlayed                &&
//		   bFinishAnimationAtEventEnd == obj.bFinishAnimationAtEventEnd;
//}

//  MEMBER_FIELD_SECTION_CHANGE END

bool AnimatorInterface::operator<(const AnimatorInterface& obj) const noexcept
{ 
	return priority < obj.priority;
}

bool AnimatorInterface::operator<(uint priority) const noexcept
{
	return this->priority < priority;
}
