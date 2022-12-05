#pragma once

#include <QtGlobal>

/// More abstract Interface that allows to call `bool update()` (inherited from NovelFlowInterface) regardless of the template arguments
class AnimatorInterface
{
public:
	AnimatorInterface()                                 = delete;
	AnimatorInterface(uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd);
	AnimatorInterface(const AnimatorInterface& obj)     = delete;
	AnimatorInterface(AnimatorInterface&& obj)          = default;
	AnimatorInterface& operator=(AnimatorInterface obj) = delete;
	bool operator<(const AnimatorInterface& obj) const noexcept;
	bool operator==(const AnimatorInterface& obj) const = delete;
	bool operator!=(const AnimatorInterface& obj) const = delete;
	//The destructor needs to be virtual, so the proper destructor will always be called when destroying an AnimatorInterface pointer
	virtual ~AnimatorInterface()                        = default;

	virtual void run() = 0;
	/// \return Whether the Animation has ended
	virtual bool update(uint elapsedTime) = 0;

protected:
	/// Delay in milliseconds before the Animation will be played after the last Animator ended playing
	uint startDelay = 0;

	/// Cannot be negative
	double speed    = 1.0;

	/// If set to -1, it will be looped infinitely
	/// \todo Automatically correct when a new Animator is added past this one
	int	timesPlayed = 1;

	/// Incompatible with `timesPlayed = -1`, but it is possible to place same Animator in subsequent Events and continue Animation without an interruption
	/// \todo Do not interrupt the Animation
	bool bStopAnimationAtEventEnd = true;

	uint priority      = 0;
};