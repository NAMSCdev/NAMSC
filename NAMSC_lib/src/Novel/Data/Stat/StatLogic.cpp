#include "Novel/Data/Stat/StatDouble.h"
#include "Novel/Data/Stat/StatLongLong.h"
#include "Novel/Data/Stat/StatString.h"

#include "Exceptions.h"

void StatDouble::setValueFromString(const QString& str)
{
	bool ok = true;
	double doubleValue = str.toDouble(&ok);
	if (!ok)
		qCritical() << "Could not parse a value from" << str << "for a StatDouble \"" + name + '\"';
	value = doubleValue;
}

void StatLongLong::setValueFromString(const QString& str)
{
	bool ok = true;
	int longlongValue = str.toLongLong(&ok);
	if (!ok)
	{
		double doubleValue = str.toDouble(&ok);
		if (!ok)
			qCritical() << "Could not parse a value from" << str << "for a StatLongLong \"" + name + '\"';
		if (doubleValue > 0)
			doubleValue -= 0.5;
		else doubleValue += 0.5;

		longlongValue = qRound(doubleValue);
	}
	value = longlongValue;
}

void StatString::setValueFromString(const QString& str)
{
	value = str;
}