#pragma once
#include <Novel\Data\Visual\Scenery\SceneryObject.h>

class SceneryObjectVariant
	: public SceneryObject
{
	using SceneryObject::SceneryObject;
	~SceneryObjectVariant()
	{
		SceneryObject::~SceneryObject();
	}

};

Q_DECLARE_METATYPE(SceneryObjectVariant);

QDebug operator<<(QDebug dbg, const SceneryObjectVariant& object);