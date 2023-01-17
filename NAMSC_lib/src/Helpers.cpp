#include "Helpers.h"

QString NovelLib::parentMsg(const QString& parentType, const QString& parentName, const QString& parentParentType, const QString& parentParentName)
{
	QString parentMessage = "";
	if (!parentName.isEmpty())
	{
		parentMessage = " in " + parentType + "  \"" + parentName + '\"';
		if (!parentParentName.isEmpty())
			parentMessage += " in " + parentParentType + " \"" + parentParentName + '\"';
	}
	return parentMessage;
}