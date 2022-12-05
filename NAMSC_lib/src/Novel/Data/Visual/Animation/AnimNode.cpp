#include "Novel/Data/Visual/Animation/AnimNode.h"

AnimNodeBase::AnimNodeBase(uint timeStamp, AnimInterpolationMethod interpolationMethod)
    : timeStamp(timeStamp), interpolationMethod(interpolationMethod)
{
}

bool AnimNodeBase::operator<(const AnimNodeBase& rhs)
{
	return timeStamp < rhs.timeStamp;
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