#pragma once
#include "Global.h"

/// Base class for an animation node 
struct AnimNodeBase
{
	//Friends for serialization
	friend QDataStream& operator>>(QDataStream& dataStream, AnimNodeBase& t);
	friend QDataStream& operator<<(QDataStream& dataStream, const AnimNodeBase& t);

	/// Time point in milliseconds since the start of an Event, when the animation will achieve its state
	int timeStamp;

	/// How the interpolation in an animation is performed
	enum class AnimInterpolationMethod
	{
		Linear,
		Exponential,	//[optional]
		Hyperbolic		//[optional]
	} interpolationMethod;

protected:
	//---SERIALIZATION---
	/// Loading an object from a binary file/// \param dataStream Stream (presumably connected to a QFile) to read from
	virtual void serializableLoad(QDataStream& dataStream);
	/// Saving an object to a binary file/// \param dataStream Stream (presumably connected to a QFile) to save to
	virtual void serializableSave(QDataStream& dataStream) const;
};

/// Base class for an animation node 
template<uint dimension>
struct AnimNodeDouble final : public AnimNodeBase
{
	/// This state will be reached exactly at [timestamp] time point
	double state[dimension];

private:
	//---SERIALIZATION---
	/// Loading an object from a binary file/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};

/// Base class for an animation node 
template<uint dimension>
struct AnimNodeLongLong final : public AnimNodeBase
{
	/// Time point in milliseconds since the start of an Event, when the animation will achieve its state
	int timestamp;

	/// This state will be reached exactly at [timestamp] time point
	long long state[dimension];

private:
	//---SERIALIZATION---
	/// Loading an object from a binary file/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override
	{
		AnimNodeBase::serializableLoad(dataStream);
		for (uint i = 0; i != dimension; ++i)
			dataStream >> state[dimension];
	}
	/// Saving an object to a binary file/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override
	{
		AnimNodeBase::serializableSave(dataStream);
		for (uint i = 0; i != dimension; ++i)
			dataStream << state[dimension];
	}
};

/// An animation node with a one dimensional `double` state
using AnimNodeDouble1D = AnimNodeDouble<1>;

/// An animation node with a two dimensional `double` state
using AnimNodeDouble2D = AnimNodeDouble<2>;

/// An animation node with a three dimensional `double` state
using AnimNodeDouble3D = AnimNodeDouble<3>;

/// An animation node with a four dimensional `double` state
using AnimNodeDouble4D = AnimNodeDouble<4>;

/// An animation node with a one dimensional `double` state
using AnimNodeLongLong1D = AnimNodeLongLong<1>;

/// An animation node with a two dimensional `double` state
using AnimNodeLongLong2D = AnimNodeLongLong<2>;

/// An animation node with a three dimensional `double` state
using AnimNodeLongLong3D = AnimNodeLongLong<3>;

/// An animation node with a four dimensional `double` state
using AnimNodeLongLong4D = AnimNodeLongLong<4>;