#include "pvnLib/Novel/Data/Stat/StatDouble.h"
#include "pvnLib/Novel/Data/Stat/StatLongLong.h"
#include "pvnLib/Novel/Data/Stat/StatString.h"

#include "pvnLib/Exceptions.h"

bool StatDouble::errorCheck(bool bComprehensive) const
{
	bool bError = false;
	auto errorChecker = [this](bool bComprehensive)
	{
		if (min > max)
			qCritical() << NovelLib::ErrorType::StatMinMax << "StatDouble (object's name: \"" + name + "\") has its min value higher than its max value";
		else if (value > max || value < min)
			qCritical() << NovelLib::ErrorType::StatValue << "StatDouble (object's name: \"" + name + "\") has its value in invalid range (not in <min, max>)";
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "Error occurred in StatDouble::errorCheck \"" + name + '\"';

	return bError;
}

bool StatLongLong::errorCheck(bool bComprehensive) const
{
	bool bError = false;
	auto errorChecker = [this](bool bComprehensive)
	{
		if (min > max)
			qCritical() << NovelLib::ErrorType::StatMinMax << "StatLongLong (object's name: \"" + name + "\") has its min value higher than its max value";
		else if (value > max || value < min)
			qCritical() << NovelLib::ErrorType::StatValue << "StatLongLong (object's name: \"" + name + "\") has its value in invalid range (not in <min, max>)";
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "Error occurred in StatLongLong::errorCheck \"" + name + '\"';

	return bError;
}

bool StatString::errorCheck(bool bComprehensive) const
{
	bool bError = false;

	auto errorChecker = [this](bool bComprehensive)
	{
		//todo: check evaulation
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "Error occurred in StatString::errorCheck \"" + name + '\"';

	return bError;
}
