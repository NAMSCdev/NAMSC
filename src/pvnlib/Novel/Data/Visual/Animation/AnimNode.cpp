#include "pvnLib/Novel/Data/Visual/Animation/AnimNode.h"

AnimNodeBase::~AnimNodeBase() = default;

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

AnimNodeBase::AnimNodeBase(uint timeStamp, AnimInterpolationMethod interpolationMethod)
    : timeStamp(timeStamp), 
    interpolationMethod(interpolationMethod)
{
}

bool AnimNodeBase::operator==(const AnimNodeBase& rhs) const noexcept
{
    return timeStamp == rhs.timeStamp;
}

void AnimNodeBase::serializableLoad(QDataStream& dataStream)
{
    dataStream >> timeStamp >> interpolationMethod;
}

void AnimNodeBase::serializableSave(QDataStream& dataStream) const
{
    dataStream << timeStamp << interpolationMethod;
}

//template<uint dimension>
//AnimNodeDouble<dimension>::AnimNodeDouble(uint timeStamp, AnimInterpolationMethod interpolationMethod, const QVarLengthArray<double, dimension>& state)

//template<uint dimension>
//void AnimNodeDouble<dimension>::serializableLoad(QDataStream& dataStream)

//template<uint dimension>
//void AnimNodeDouble<dimension>::serializableSave(QDataStream& dataStream) const

//template<uint dimension>
//AnimNodeLongLong<dimension>::AnimNodeLongLong(uint timeStamp, AnimInterpolationMethod interpolationMethod, const QVarLengthArray<long long, dimension>& state)

//template<uint dimension>
//void AnimNodeLongLong<dimension>::serializableLoad(QDataStream& dataStream)

//template<uint dimension>
//void AnimNodeLongLong<dimension>::serializableSave(QDataStream& dataStream) const

//  MEMBER_FIELD_SECTION_CHANGE END

bool AnimNodeBase::operator<(const AnimNodeBase& rhs) const noexcept
{
	return timeStamp < rhs.timeStamp;
}

bool AnimNodeBase::operator<(uint rhs) const noexcept
{
    return timeStamp < rhs;
}

bool AnimNodeBase::operator==(uint rhs) const noexcept
{
    return timeStamp == rhs;
}