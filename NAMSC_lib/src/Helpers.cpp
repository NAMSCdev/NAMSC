#include "Helpers.h"

QString NovelLib::Helpers::parentMsg(const QString& parentType, const QString& parentName, const QString& parentParentType, const QString& parentParentName)
{
	QString parentMessage = "";
	if (!parentParentName.isEmpty())
		parentMessage += " in " + parentParentType + " \"" + parentParentName + '\"';
	if (!parentName.isEmpty())
		parentMessage = " in " + parentType + "  \"" + parentName + '\"';
	return parentMessage;
}