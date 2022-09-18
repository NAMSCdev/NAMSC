#pragma once
#include "Global.h"

//How the interpolation in an animation is performed
enum class AnimInterpolationMethod
{
	Linear,
	Exponential,
	Hyperbolic
};

//Base class for an animation node 
template<class DataType, unsigned dimension>
struct AnimNode
{
	//Time point in seconds since the start of an Event, when the animation will achieve its state
	double		timestamp;

	//This state will be reached exactly at [timestamp] time point
	DataType	state[dimension];
};

//An animation node with a one dimensional state
template <class DataType>
using Anim1DNode = AnimNode<DataType, 1>;

//An animation node with a two dimensional state
template <class DataType>
using Anim2DNode = AnimNode<DataType, 2>;

//An animation node with a three dimensional state
template <class DataType>
using Anim3DNode = AnimNode<DataType, 3>;

//An animation node with a four dimensional state
template <class DataType>
using Anim4DNode = AnimNode<DataType, 4>;

