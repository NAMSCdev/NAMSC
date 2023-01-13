#include "Novel/Data/Stat/StatLongLong.h"

#include "Exceptions.h"

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(StatLongLong& first, StatLongLong& second) noexcept
{
	using std::swap;
	//Static cast, because no check is needed and it's faster
	swap(static_cast<Stat&>(first), static_cast<Stat&>(second));
	swap(first.value, second.value);
	swap(first.min,   second.min);
	swap(first.max,   second.max);
}

StatLongLong::StatLongLong(const QString& name, const QString& displayName, bool bShow, uint priority, const ShowNotification showNotification, long long value, long long min, long long max)
	: Stat(name, displayName, bShow, priority, showNotification), 
	value(value),
	min(min),
	max(max)
{
	errorCheck(true);
}

//defaulted
//StatLongLong::StatLongLong(const StatLongLong& obj) noexcept
//	: Stat(obj.name, obj.displayName, obj.bShow, obj.priority, obj.showNotification),
//	value(obj.value),
//	min(obj.min),
//	max(obj.max)
//{
//}

//defaulted
//bool StatLongLong::operator==(const StatLongLong& obj) const noexcept
//{
//	if (this == &obj) return true;
//
//	return Stat::operator==(obj) &&
//		   value == obj.value    &&
//		   min   == obj.min      &&
//		   max   == obj.max;
//}

void StatLongLong::serializableLoad(QDataStream& dataStream)
{
	Stat::serializableLoad(dataStream);
	dataStream >> value >> min >> max;
}

void StatLongLong::serializableSave(QDataStream& dataStream) const
{
	Stat::serializableSave(dataStream);
	dataStream << value << min << max;
}

//  MEMBER_FIELD_SECTION_CHANGE END

//defaulted
//StatLongLong::StatLongLong(StatLongLong&& obj) noexcept
//	: StatLongLong()
//{
//	swap(*this, obj);
//}

//defaulted
//StatLongLong& StatLongLong::operator=(StatLongLong obj) noexcept
//{
//	if (this == &obj) return *this;
//
//	swap(*this, obj);
//
//	return *this;
//}

NovelLib::SerializationID StatLongLong::getType() const noexcept 
{ 
	return NovelLib::SerializationID::StatLongLong; 
}
