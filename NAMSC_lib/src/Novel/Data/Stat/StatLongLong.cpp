#include "Novel/Data/Stat/StatLongLong.h"

#include "Exceptions.h"

StatLongLong::StatLongLong(const QString& name, const QString& displayName, bool bShow, uint priority, const ShowNotification showNotification, int value, int min, int max)
	: Stat(name, displayName, bShow, priority, showNotification), value(value), min(min), max(max)
{
	checkForErrors(true);
}

StatLongLong& StatLongLong::operator=(StatLongLong obj) noexcept
{
	if (this == &obj) return *this;

	std::swap(*this, obj);

	return *this;
}

//bool StatLongLong::operator==(const StatLongLong& obj) const
//{
//	if (this == &obj) return true;
//
//	return	Stat::operator==(obj) &&
//			value == obj.value    &&
//			min   == obj.min      &&
//			max   == obj.max;
//}

bool StatLongLong::checkForErrors(bool bComprehensive) const
{
	bool bError = false;
	static auto errorChecker = [&](bool bComprehensive)
	{
		if (min > max)
		{
			bError = true;
			qCritical() << this << NovelLib::ErrorType::StatMinMax << "StatLongLong (object's name: \"" << name << "\") has its min value higher than its max value";
		}
		else if (value > max || value < min)
		{
			bError = true;
			qCritical() << this << NovelLib::ErrorType::StatValue << "StatLongLong (object's name: \"" << name << "\") has its value in invalid range (not in <min, max>)";
		}
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive); 
	if (bError)
		qDebug() << "Error occurred in StatLongLong::checkForErrors \"" << name << '\"';

	return bError;
}


void StatLongLong::setValueFromString(const QString& str)
{
	bool ok = true;
	int longlongValue = str.toLongLong(&ok);
	if (!ok)
	{
		double doubleValue = str.toDouble(&ok);
		if (!ok)
			qCritical() << this << "Could not parse a value from " << str << " for a StatLongLong \"" << name << '\"';
		if (doubleValue > 0)
			doubleValue -= 0.5;
		else doubleValue += 0.5;

		longlongValue = qRound(doubleValue);
	}
	value = longlongValue;
}


/// Needed for Serialization, to know the class of an object about to be Serialization loaded
/// \return NovelLib::SerializationID corresponding to the class of a serialized object

NovelLib::SerializationID StatLongLong::getType() const noexcept { return NovelLib::SerializationID::StatLongLong; }

void StatLongLong::serializableLoad(QDataStream& dataStream)
{
	Stat::serializableLoad(dataStream);
	dataStream >> value >> min >> max;
	//checkForErrors();
}

void StatLongLong::serializableSave(QDataStream& dataStream) const
{
	Stat::serializableSave(dataStream);
	dataStream << value << min << max;
}