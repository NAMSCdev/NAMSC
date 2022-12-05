#include "Novel/Data/Stat/StatDouble.h"

#include "Exceptions.h"

StatDouble::StatDouble(const QString& name, const QString& displayName, bool bShow, uint priority, const ShowNotification showNotification, double value, double min, double max)
	: Stat(name, displayName, bShow, priority, showNotification), value(value), min(min), max(max)
{
	checkForErrors(true);
}

StatDouble& StatDouble::operator=(StatDouble obj) noexcept
{
	if (this == &obj) return *this;

	std::swap(*this, obj);

	return *this;
}

//bool StatDouble::operator==(const StatDouble& obj) const noexcept
//{
//	if (this == &obj) return true;
//
//	return	Stat::operator==(obj) &&
//			value == obj.value    &&
//			min   == obj.min      &&
//			max   == obj.max;
//}

bool StatDouble::checkForErrors(bool bComprehensive) const
{
	bool bError = false;
	static auto errorChecker = [&](bool bComprehensive)
	{
		if (min > max)
		{
			bError = true;
			qCritical() << this << NovelLib::ErrorType::StatMinMax << "StatDouble (object's name: \"" << name << "\") has its min value higher than its max value";
		}
		else if (value > max || value < min)
		{
			bError = true;
			qCritical() << this << NovelLib::ErrorType::StatValue << "StatDouble (object's name: \"" << name << "\") has its value in invalid range (not in <min, max>)";
		}
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "Error occurred in StatDouble::checkForErrors \"" << name << '\"';

	return bError;
}

void StatDouble::setValueFromString(const QString& str)
{
	bool ok = true;
	double doubleValue = str.toDouble(&ok);
	if (!ok)
		qCritical() << this << "Could not parse a value from " << str << " for a StatDouble \"" << name << '\"';
	value = doubleValue;
}

NovelLib::SerializationID StatDouble::getType() const noexcept
{
	return NovelLib::SerializationID::StatDouble; 
}

void StatDouble::serializableLoad(QDataStream& dataStream)
{
	Stat::serializableLoad(dataStream);
	dataStream >> value >> min >> max;
	//checkForErrors();
}

void StatDouble::serializableSave(QDataStream& dataStream) const
{
	Stat::serializableSave(dataStream);
	dataStream << value << min << max;
}