#include "Novel/Data/Stat/StatString.h"

#include "Exceptions.h"

StatString::StatString(const QString& name, const QString& displayName, bool bShow, uint priority,
					   const ShowNotification showNotification, const QString& value, uint maxChars) 
	: Stat(name, displayName, bShow, priority, showNotification), value(value), maxChars(maxChars)
{ 
	checkForErrors(true);
}

StatString& StatString::operator=(StatString obj) noexcept
{
	if (this == &obj) return *this;

	std::swap(*this, obj);

	return *this;
}

bool StatString::operator==(const StatString& obj) const noexcept
{
	if (this == &obj) return true;

	return	Stat::operator==(obj)    &&
			value    == obj.value    &&
			maxChars == obj.maxChars;
}

bool StatString::checkForErrors(bool bComprehensive) const
{
	bool bError = false;

	static auto errorChecker = [&](bool bComprehensive)
	{
		//todo: check evaulation
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive); 
	if (bError)
		qDebug() << "Error occurred in StatString::checkForErrors \"" << name << '\"';

	return bError;
}

void StatString::setValueFromString(const QString& str)
{ 
	value = str;
}

NovelLib::SerializationID StatString::getType() const noexcept
{ 
	return NovelLib::SerializationID::StatString; 
}

void StatString::serializableLoad(QDataStream& dataStream)
{
	Stat::serializableLoad(dataStream);
	dataStream >> value >> maxChars;
	//checkForErrors();
}

void StatString::serializableSave(QDataStream& dataStream) const
{
	Stat::serializableSave(dataStream);
	dataStream << value << maxChars;
}