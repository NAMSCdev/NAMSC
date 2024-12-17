#include "SceneryObjectVariant.h"

QDebug operator<<(QDebug dbg, const SceneryObjectVariant& object)
{
	QDebugStateSaver saver(dbg);

	if (!object.name.isNull()) {
		dbg.nospace() << "SceneryObjectVariant(" << object.name << ")";
	}

	return dbg;
}
