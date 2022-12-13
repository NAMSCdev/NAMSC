#pragma once

#include <QDataStream>
#include <QVarLengthArray>
#include "Serialization.h"

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
	AnimNodeBase() = default;
	AnimNodeBase(uint timeStamp, AnimInterpolationMethod interpolationMethod);

	bool operator<(const AnimNodeBase& rhs) const noexcept;
	bool operator<(uint rhs) const noexcept;
	bool operator==(const AnimNodeBase& rhs) const noexcept;
	bool operator==(uint rhs) const noexcept;

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
	AnimNodeDouble() = default;
	AnimNodeDouble(uint timeStamp, AnimInterpolationMethod interpolationMethod, const QVarLengthArray<double, dimension>& state);

	/// This state will be reached exactly at `timeStamp` time point
	QVarLengthArray<double, dimension> state_;

private:

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};

/// Animation Node, which state is an array of `double`
template<uint dimension>
struct AnimNodeLongLong final : public AnimNodeBase
{
	AnimNodeLongLong() = default;
	AnimNodeLongLong(uint timeStamp, AnimInterpolationMethod interpolationMethod, const QVarLengthArray<long long, dimension>& state);
	/// This state will be reached exactly at `timeStamp` time point
	QVarLengthArray<long long, dimension> state_;

private:

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream) override;
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const override;
};

using AnimNodeDouble1D = AnimNodeDouble<1>;
using AnimNodeDouble2D = AnimNodeDouble<2>;
using AnimNodeDouble3D = AnimNodeDouble<3>;
using AnimNodeDouble4D = AnimNodeDouble<4>;

using AnimNodeLongLong1D = AnimNodeLongLong<1>;
using AnimNodeLongLong2D = AnimNodeLongLong<2>;
using AnimNodeLongLong3D = AnimNodeLongLong<3>;
using AnimNodeLongLong4D = AnimNodeLongLong<4>; 