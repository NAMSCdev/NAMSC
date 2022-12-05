#include "Novel/Data/Stat/Stat.h"

Stat::Stat(const QString& name, const QString& displayName, bool bShow, uint priority, ShowNotification showNotification)
	: name(name), displayName(displayName), bShow(bShow), priority(priority), showNotification(showNotification)
{
	if (displayName.isEmpty())
		this->displayName = name;
	//checkForErrors(true);
}

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

void Stat::serializableLoad(QDataStream& dataStream)
{
	dataStream >> name >> displayName >> bShow >> priority >> showNotification;
	//checkForErrors();
}

void Stat::serializableSave(QDataStream& dataStream) const
{
	dataStream << getType() << name << displayName << bShow << priority << showNotification;
}