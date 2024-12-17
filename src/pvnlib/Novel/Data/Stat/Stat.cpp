#include "pvnLib/Novel/Data/Stat/Stat.h"

Stat::~Stat() = default;

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(Stat& first, Stat& second) noexcept
{
	using std::swap;
	swap(first.name,             second.name);
	swap(first.displayName,      second.displayName);
	swap(first.bShow,            second.bShow);
	swap(first.priority,         second.priority);
	swap(first.showNotification, second.showNotification);
}

Stat::Stat(const QString& name, const QString& displayName, bool bShow, uint priority, ShowNotification showNotification)
	: name(name), 
	displayName(displayName), 
	bShow(bShow), 
	priority(priority),
	showNotification(showNotification)
{
}

void Stat::serializableLoad(QDataStream& dataStream)
{
	dataStream >> name >> displayName >> bShow >> priority >> showNotification;
}

void Stat::serializableSave(QDataStream& dataStream) const
{
	dataStream << getType() << name << displayName << bShow << priority << showNotification;
}

//  MEMBER_FIELD_SECTION_CHANGE END

bool Stat::operator<(const Stat &rhs) const noexcept
{
	if (priority == rhs.priority)
		return (name.compare(rhs.name, Qt::CaseInsensitive) < 0);
	return priority < rhs.priority;
}

bool Stat::operator==(const QString& name) const noexcept 
{
	return this->name == name; 
}

bool Stat::operator!=(const QString& name) const noexcept 
{ 
	return (*this == name); 
}