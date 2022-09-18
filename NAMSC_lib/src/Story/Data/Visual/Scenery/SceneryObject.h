#pragma once
#include "Global.h"

#include "Story/Data/Asset/Type/FontAsset.h"
#include "Story/Data/Asset/AssetManager.h"

//This hasn't been thought through yet. It is very WIP
//todo: comment this
class SceneryObject
{
	//Friends for serialization
	friend QIODevice &operator>>(QIODevice &device, SceneryObject &t);
	friend QIODevice &operator<<(QIODevice &device, const SceneryObject &t);
public:
	SceneryObject() = default;
	//TODO: add a special constructor, once fields are set in stone
	//SceneryObject(
	virtual ~SceneryObject();

protected:
	//TODO: copy comment from other label
	QString			label;

	//TODO: create this class and it will store ImageAssets with custom names for image filtering (useful in Editor)
	std::vector<SceneryObjectPart> parts;

	//[optional] TODO: filters and effects. Different classes?
	
	//TODO: is this the good format? Check QT docs
	//TODO: Should these apply per part only, or global one too?
	double scale[3];
	double pos[3];
	double color[4];

	//TODO: serialization
	//---SERIALIZATION---
	//Loading an object from a binary file
	virtual void serializableLoad(QIODevice &ar)
	{
		QDataStream dataStream(&ar);
		dataStream;
	}
	//Saving an object to a binary file
	virtual void serializableSave(QIODevice &ar) const
	{
		QDataStream dataStream(&ar);
		dataStream;
	}
};