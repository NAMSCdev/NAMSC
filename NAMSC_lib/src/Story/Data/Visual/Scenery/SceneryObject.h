#pragma once
#include "Global.h"

#include "Story/Data/Asset/Type/FontAsset.h"
#include "Story/Data/Asset/AssetManager.h"

///This hasn't been thought through yet. It is very WIP
///todo: comment this
class SceneryObject
{
	///Friends for serialization
	friend QDataStream& operator>>(QDataStream&, SceneryObject&);
	friend QDataStream& operator<<(QDataStream&, const SceneryObject&);
public:
	SceneryObject() = default;
	SceneryObject() = default;
	///TODO: add a special constructor, once fields are set in stone
	///SceneryObject(
	virtual ~SceneryObject() = default;

	///Animation values
	///Image's position in the Scenery
	///@todo [optional] allow for setting position in Z-dimension and do proper maths about it
	double pos[2/*3*/] = { 0.0, 0.0/*, 0.0*/ };
	///Image's scale
	double scale[2] = { 1.0, 1.0 };
	///Image's rotation
	double rotation = 0.0;
	///Color multiplicatives for image
	double color[4] = { 1.0, 1.0, 1.0, 1.0 };

protected:
	///TODO: copy comment from other label
	QString		label;

	///Name to the Image that will be rendered
	QString		imageAssetName;
	//Image that will be rendered
	ImageAsset	*imageAsset;
	///[optional] create this class and it will store ImageAssets with custom names for image filtering (useful in Editor)
	//QVector<SceneryObjectPart> parts;

	///TODO: serialization
	//---SERIALIZATION---
	///Loading an object from a binary file
	virtual void serializableLoad(QDataStream &dataStream)
	{
		dataStream >> label >> imageAssetName;
	}
	///Saving an object to a binary file
	virtual void serializableSave(QDataStream &dataStream) const
	{
	}
};