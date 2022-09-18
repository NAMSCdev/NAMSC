#pragma once
#include "Global.h"

#include "Story/Data/Visual/Animation/Animator.h"
//TODO: figure out the best way to create AnimAssets and finish these classes

//Does the maths behind Move Animation
class AnimatorMove			final : public Animator3D<double>
{
public:
	AnimatorMove() = default;

protected:
	SerializationID			getType() const override	{ return SerializationID::AnimatorMove; }
};

//Does the maths behind Rotate Animation
class AnimatorRotate		final : public Animator1D<double>
{
public:
	AnimatorRotate() = default;

protected:
	SerializationID			getType() const override	{ return SerializationID::AnimatorRotate; }
};

//Does the maths behind Scale Animation
class AnimatorScale			final : public Animator3D<double>
{
public:
	AnimatorScale() = default;

protected:
	SerializationID			getType() const override	{ return SerializationID::AnimatorScale; }
};

//Does the maths behind Color Animation
class AnimatorColor		final : public Animator4D<double>
{
public:
	AnimatorColor() = default;

protected:
	SerializationID			getType() const override	{ return SerializationID::AnimatorColor; }
};