#include "Novel/Data/Stat/StatString.h"

#include "Exceptions.h"

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(StatString& first, StatString& second) noexcept
{
	using std::swap;
	//Static cast, because no check is needed and it's faster
	swap(static_cast<Stat&>(first), static_cast<Stat&>(second));
	swap(first.value,    second.value);
	swap(first.maxChars, second.maxChars);
}

StatString::StatString(const QString& name, const QString& displayName, bool bShow, uint priority, const ShowNotification showNotification, const QString& value, uint maxChars) 
	: Stat(name, displayName, bShow, priority, showNotification), 
	value(value),
	maxChars(maxChars)
{ 
	errorCheck(true);
}

//defaulted
//StatString::StatString(const StatString& obj) noexcept
//	: Stat(obj.name, obj.displayName, obj.bShow, obj.priority, obj.showNotification),
//	value(obj.value),
//	maxChars(obj.maxChars)
//{
//}

//defaulted
//bool StatString::operator==(const StatString& obj) const noexcept
//{
//	if (this == &obj) return true;
//
//	return Stat::operator==(obj)    &&
//		   value    == obj.value    &&
//		   maxChars == obj.maxChars;
//}

void StatString::serializableLoad(QDataStream& dataStream)
{
	Stat::serializableLoad(dataStream);
	dataStream >> value >> maxChars;
}

void StatString::serializableSave(QDataStream& dataStream) const
{
	Stat::serializableSave(dataStream);
	dataStream << value << maxChars;
}

//  MEMBER_FIELD_SECTION_CHANGE END

//defaulted
//StatString::StatString(StatString&& obj) noexcept
//	: StatString()
//{
//	swap(*this, obj);
//}

//defaulted
//StatString& StatString::operator=(StatString obj) noexcept
//{
//	if (this == &obj) return *this;
//
//	swap(*this, obj);
//
//	return *this;
//}

NovelLib::SerializationID StatString::getType() const noexcept
{ 
	return NovelLib::SerializationID::StatString; 
}