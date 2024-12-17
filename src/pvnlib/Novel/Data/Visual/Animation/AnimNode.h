#pragma once

#include <QDataStream>
#include <QVarLengthArray>
#include "pvnLib/Serialization.h"

enum class AnimNodeType
{
	Unknown,
	Double,
	LongLong
};

/// Base class for an Animation Node 
struct AnimNodeBase
{
	enum class AnimInterpolationMethod
	{
		Linear,
		Exponential,	//[optional]
		Hyperbolic		//[optional]
	};
	/// \param timeStamp Time point (in milliseconds) when the Animation will achieve this Node's state
	AnimNodeBase(uint timeStamp = 0, AnimInterpolationMethod interpolationMethod = AnimInterpolationMethod::Linear);
	virtual ~AnimNodeBase() = 0;

	bool operator<(const AnimNodeBase& rhs)  const noexcept;
	bool operator<(uint rhs)                 const noexcept;
	bool operator==(const AnimNodeBase& rhs) const noexcept;
	bool operator==(uint rhs)                const noexcept;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// Time point (in milliseconds) when the Animation will achieve this Node's state
	uint timeStamp = 0;

	AnimInterpolationMethod interpolationMethod = AnimInterpolationMethod::Linear;

protected:

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	virtual void serializableLoad(QDataStream& dataStream);
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	virtual void serializableSave(QDataStream& dataStream) const;
};

/// Animation Node, which state is an array of `double`
template<uint dimension>
struct AnimNodeDouble final : public AnimNodeBase
{
	/// \param timeStamp Time point (in milliseconds) when the Animation will achieve this Node's state
	/// \param state This state will be reached exactly at `timeStamp` time point
	AnimNodeDouble(uint timeStamp = 0, AnimInterpolationMethod interpolationMethod = AnimInterpolationMethod::Linear, const QVarLengthArray<double, dimension>& state = QVarLengthArray<double, dimension>())
		: AnimNodeBase(timeStamp, interpolationMethod),
		state_(state)
	{
	}

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// This state will be reached exactly at `timeStamp` time point
	QVarLengthArray<double, dimension> state_;

private:

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override
	{
		AnimNodeBase::serializableLoad(dataStream);

		for (uint i = 0u; i != dimension; ++i)
			dataStream >> state_[dimension];
	}
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override
	{
		AnimNodeBase::serializableSave(dataStream);

		for (uint i = 0u; i != dimension; ++i)
			dataStream << state_[dimension];
	}
};

/// Animation Node, which state is an array of `double`
template<uint dimension>
struct AnimNodeLongLong final : public AnimNodeBase
{
	/// \param timeStamp Time point (in milliseconds) when the Animation will achieve this Node's state
	/// \param state This state will be reached exactly at `timeStamp` time point
	AnimNodeLongLong(uint timeStamp = 0, AnimInterpolationMethod interpolationMethod = AnimInterpolationMethod::Linear, const QVarLengthArray<long long, dimension>& state = QVarLengthArray<long long, dimension>())
		: AnimNodeBase(timeStamp, interpolationMethod),
		state_(state)
	{
	}

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// This state will be reached exactly at `timeStamp` time point
	QVarLengthArray<long long, dimension> state_;

private:

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override
	{
		AnimNodeBase::serializableLoad(dataStream);

		for (uint i = 0u; i != dimension; ++i)
			dataStream >> state_[dimension];
	}
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override
	{
		AnimNodeBase::serializableSave(dataStream);

		for (uint i = 0u; i != dimension; ++i)
			dataStream << state_[dimension];
	}
};

using AnimNodeDouble1D   = AnimNodeDouble<1>;
using AnimNodeDouble2D   = AnimNodeDouble<2>;
using AnimNodeDouble3D   = AnimNodeDouble<3>;
using AnimNodeDouble4D   = AnimNodeDouble<4>;

using AnimNodeLongLong1D = AnimNodeLongLong<1>;
using AnimNodeLongLong2D = AnimNodeLongLong<2>;
using AnimNodeLongLong3D = AnimNodeLongLong<3>;
using AnimNodeLongLong4D = AnimNodeLongLong<4>; 