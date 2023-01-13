#include "Novel/Data/Stat/StatDouble.h"

#include "Exceptions.h"

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(StatDouble& first, StatDouble& second) noexcept
{
	using std::swap;
	//Static cast, because no check is needed and it's faster
	swap(static_cast<Stat&>(first), static_cast<Stat&>(second));
	swap(first.value, second.value);
	swap(first.min,   second.min);
	swap(first.max,   second.max);
}

StatDouble::StatDouble(const QString& name, const QString& displayName, bool bShow, uint priority, const ShowNotification showNotification, double value, double min, double max)
	: Stat(name, displayName, bShow, priority, showNotification),
	value(value), 
	min(min), 
	max(max)
{
	errorCheck(true);
}

//defaulted
//StatDouble::StatDouble(const StatDouble& obj) noexcept
//	: Stat(obj.name, obj.displayName, obj.bShow, obj.priority, obj.showNotification),
//	value(obj.value),
//	min(obj.min),
//	max(obj.max)
//{
//}

//defaulted
//bool StatDouble::operator==(const StatDouble& obj) const noexcept
//{
//	if (this == &obj) return true;
//
//	return Stat::operator==(obj) &&
//		   value == obj.value    &&
//		   min   == obj.min      &&
//		   max   == obj.max;
//}

void StatDouble::serializableLoad(QDataStream& dataStream)
{
	Stat::serializableLoad(dataStream);
	dataStream >> value >> min >> max;
}

void StatDouble::serializableSave(QDataStream& dataStream) const
{
	Stat::serializableSave(dataStream);
	dataStream << value << min << max;
}

//  MEMBER_FIELD_SECTION_CHANGE END

//defaulted
//StatDouble::StatDouble(StatDouble&& obj) noexcept
//	: StatDouble()
//{
//	swap(*this, obj);
//}


//defaulted
//StatDouble& StatDouble::operator=(StatDouble obj) noexcept
//{
//	if (this == &obj) return *this;
//
//	swap(*this, obj);
//
//	return *this;
//}

NovelLib::SerializationID StatDouble::getType() const noexcept
{
	return NovelLib::SerializationID::StatDouble; 
}