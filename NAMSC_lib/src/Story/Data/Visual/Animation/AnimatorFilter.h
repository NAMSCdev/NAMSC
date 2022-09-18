#pragma once
#include "Global.h"

#include "Story/Data/Visual/Animation/Animator.h"
//TODO: figure out the best way to create AnimAssets and finish these classes

//Does maths behind Blur Filter Animation
class AnimatorFilterBlur		final : public Animator2D<double>
{
public:
	AnimatorFilterBlur() = default;

protected:
	SerializationID			getType() const override	{ return SerializationID::AnimatorFilterBlur; }
};

//Does the maths behind Brightness Filter Animation
class AnimatorFilterBrightness 	final : public Animator1D<double>
{
public:
	AnimatorFilterBrightness() = default;

protected:
	SerializationID			getType() const override	{ return SerializationID::AnimatorFilterBrightness; }
};

//Does the maths behind Dilation Filter Animation
class AnimatorFilterDilation	final : public Animator1D<double>
{
public:
	AnimatorFilterDilation() = default;

protected:
	SerializationID			getType() const override	{ return SerializationID::AnimatorFilterDilation; }
};

//Does the maths behind Erosion Filter Animation
class AnimatorFilterErosion		final : public Animator1D<double>
{
public:
	AnimatorFilterErosion() = default;

protected:
	SerializationID			getType() const override	{ return SerializationID::AnimatorFilterErosion; }
};

//Does the maths behind Hue Filter Animation
class AnimatorFilterHue			final : public Animator1D<double>
{
public:
	AnimatorFilterHue() = default;

protected:
	SerializationID			getType() const override	{ return SerializationID::AnimatorFilterHue; }
};

//Does the maths behind Saturation Filter Animation
class AnimatorFilterSaturation	final : public Animator1D<double>
{
public:
	AnimatorFilterSaturation() = default;

protected:
	SerializationID			getType() const override	{ return SerializationID::AnimatorFilterSaturation; }
};
