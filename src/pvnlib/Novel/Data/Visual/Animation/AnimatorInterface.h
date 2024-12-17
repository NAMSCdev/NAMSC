#pragma once

#include <QtGlobal>

/// More abstract Interface that allows to call `bool update()` (inherited from NovelFlowInterface) regardless of the template arguments
class AnimatorInterface
{
	/// Swap trick
	friend void swap(AnimatorInterface& first, AnimatorInterface& second) noexcept;
public:
	/// \param priority Allows animation queueing
	/// \param startDelay Delay in milliseconds before the Animation will be played after the last Animator ended playing
	/// \param speed Cannot be negative
	/// \param timesPlayed If set to -1, it will be looped infinitely
	/// \param bFinishAnimationAtEventEnd Incompatible with `timesPlayed = -1`, but it is possible to place same Animator in subsequent Events and continue Animation without an interruption
	explicit AnimatorInterface(uint priority, uint startDelay = 0, double speed = 1.0, int timesPlayed = 1, bool bFinishAnimationAtEventEnd = false);
	AnimatorInterface(const AnimatorInterface& obj)            noexcept = delete;
	AnimatorInterface(AnimatorInterface&& obj)                 noexcept = delete;
	AnimatorInterface& operator=(const AnimatorInterface& obj) noexcept = delete;
	bool operator<(const AnimatorInterface& obj)  const        noexcept;
	bool operator<(uint priority)                 const        noexcept;
	bool operator==(const AnimatorInterface& obj) const        noexcept = default;
	bool operator!=(const AnimatorInterface& obj) const        noexcept = default;
	//The destructor needs to be virtual, so the proper destructor will always be called when destroying an AnimatorInterface pointer
	virtual ~AnimatorInterface()          = 0;

	virtual void run() = 0;
	/// \return Whether the Animation has ended
	virtual bool update(uint elapsedTime) = 0;

protected:
	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// Allows animation queueing
	uint priority   = 0;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// Delay in milliseconds before the Animation will be played after the last Animator ended playing
	uint startDelay = 0;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// Cannot be negative
	double speed    = 1.0;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// If set to -1, it will be looped infinitely
	/// \todo Automatically correct when a new Animator is added past this one
	int	timesPlayed = 1;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// Incompatible with `timesPlayed = -1`, but it is possible to place same Animator in subsequent Events and continue Animation without an interruption
	/// \todo Do not interrupt the Animation
	bool bFinishAnimationAtEventEnd = false;
};