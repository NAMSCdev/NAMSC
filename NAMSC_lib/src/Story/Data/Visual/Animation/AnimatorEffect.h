#pragma once
#include "Global.h"

#include "Story/Data/Visual/Animation/Animator.h"
//TODO: figure out the best way to create AnimAssets and finish these classes

//Does the maths behind Blur Effect Animation
class AnimatorEffectBlur		final : public Animator4D<double>
{
public:
	AnimatorEffectBlur() = default;

protected:
	SerializationID			getType() const override	{ return SerializationID::AnimatorEffectBlur; }
};

//Does the maths behind Distort Effect Animation
class AnimatorEffectDistort		final : public Animator3D<double>
{
public:
	AnimatorEffectDistort() = default;

protected:
	SerializationID			getType() const override	{ return SerializationID::AnimatorEffectDistort; }
};

//Does the maths behind Glow Effect Animation
class AnimatorEffectGlow		final : public Animator3D<double>
{
public:
	AnimatorEffectDistort() = default;

protected:
	SerializationID			getType() const override	{ return SerializationID::AnimatorEffectDistort; }
};
