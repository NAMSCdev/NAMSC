#include "Novel/Data/Visual/Animation/AnimNode.h"

template struct AnimNodeDouble<1>;
template struct AnimNodeDouble<2>;
template struct AnimNodeDouble<3>;
template struct AnimNodeDouble<4>;

template struct AnimNodeLongLong<1>;
template struct AnimNodeLongLong<2>;
template struct AnimNodeLongLong<3>;
template struct AnimNodeLongLong<4>;

AnimNodeBase::AnimNodeBase(uint timeStamp, AnimInterpolationMethod interpolationMethod)
    : timeStamp(timeStamp), interpolationMethod(interpolationMethod)
{
}

bool AnimNodeBase::operator<(const AnimNodeBase& rhs) const noexcept
{
	return timeStamp < rhs.timeStamp;
}

bool AnimNodeBase::operator<(uint rhs) const noexcept
{
    return timeStamp < rhs;
}

bool AnimNodeBase::operator==(const AnimNodeBase& rhs) const noexcept
{
    return timeStamp == rhs.timeStamp;
}

bool AnimNodeBase::operator==(uint rhs) const noexcept
{
    return timeStamp == rhs;
}

void AnimNodeBase::serializableLoad(QDataStream& dataStream)
{
    dataStream >> timeStamp >> interpolationMethod;
}

void AnimNodeBase::serializableSave(QDataStream& dataStream) const
{
    dataStream << timeStamp << interpolationMethod;
}

template<uint dimension>
AnimNodeDouble<dimension>::AnimNodeDouble(uint timeStamp, AnimInterpolationMethod interpolationMethod, const QVarLengthArray<double, dimension>& state)
    : AnimNodeBase(timeStamp, interpolationMethod), state_(state)
{
}

template<uint dimension>
void AnimNodeDouble<dimension>::serializableLoad(QDataStream& dataStream)
{
    AnimNodeBase::serializableLoad(dataStream);
    for (uint i = 0; i != dimension; ++i)
        dataStream >> state_[dimension];
}

template<uint dimension>
void AnimNodeDouble<dimension>::serializableSave(QDataStream& dataStream) const
{
    AnimNodeBase::serializableSave(dataStream);
    for (uint i = 0; i != dimension; ++i)
        dataStream << state_[dimension];
}

template<uint dimension>
AnimNodeLongLong<dimension>::AnimNodeLongLong(uint timeStamp, AnimInterpolationMethod interpolationMethod, const QVarLengthArray<long long, dimension>& state)
    : AnimNodeBase(timeStamp, interpolationMethod), state_(state)
{
}

template<uint dimension>
void AnimNodeLongLong<dimension>::serializableLoad(QDataStream& dataStream)
{
    AnimNodeBase::serializableLoad(dataStream);
    for (uint i = 0; i != dimension; ++i)
        dataStream >> state_[dimension];
}

template<uint dimension>
void AnimNodeLongLong<dimension>::serializableSave(QDataStream& dataStream) const
{
    AnimNodeBase::serializableSave(dataStream);
    for (uint i = 0; i != dimension; ++i)
        dataStream << state_[dimension];
}