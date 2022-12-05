#include "Novel/Data/Visual/Animation/AnimatorInterface.h"

AnimatorInterface::AnimatorInterface(uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd)
	: priority(priority), startDelay(startDelay), speed(speed), timesPlayed(timesPlayed), bStopAnimationAtEventEnd(bStopAnimationAtEventEnd)
{
}

bool AnimatorInterface::operator<(const AnimatorInterface& obj) const noexcept
{ 
	return priority < obj.priority;
}

//AnimatorInterface::AnimatorInterface(const AnimatorInterface& obj)
//	: startDelay(obj.startDelay),
//	  speed(obj.speed), 
//	  timesPlayed(obj.timesPlayed),
//	  bStopAnimationAtEventEnd(obj.bStopAnimationAtEventEnd)//,
//	  //startTimer_(obj.startTimer_)
//{
//}

//bool AnimatorInterface::operator==(const AnimatorInterface& obj) const
//{
//    if (this == &obj)
//        return true;
//
//	return	startDelay               == obj.startDelay              &&
//			speed                    == obj.speed                   &&
//			timesPlayed              == obj.timesPlayed             &&
//			bStopAnimationAtEventEnd == obj.bStopAnimationAtEventEnd;
//}
