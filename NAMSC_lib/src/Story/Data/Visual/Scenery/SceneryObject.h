#pragma once
#include "Global.h"

#include "Story/Data/Asset/Type/AssetFont.h"
#include "Story/Data/Asset/AssetManager.h"

///A drawable object on Scene
class SceneryObject
{
	///Friends for serialization
	friend QDataStream& operator>>(QDataStream&, SceneryObject&);
	friend QDataStream& operator<<(QDataStream&, const SceneryObject&);
public:
	SceneryObject() = default;
	SceneryObject(QPoint pos, QSize scale, double rotation, QColor color, QString &&label, QString &&imageAssetName) :
		pos(pos), scale(scale), rotation(rotation), color(color), label(move(label)), imageAssetName(move(imageAssetName))
	{
		imageAsset = AssetManager::getInstance().findSceneryObjectAssetImage(imageAssetName);
	}


	virtual ~SceneryObject() = default;

	///Animation values
	///Image's position in the Scenery
	///@todo [optional] allow for setting position in Z-dimension and do proper maths about it
	QPoint pos		= { 0.0, 0.0/*, 0.0*/ };

	///Image's scale
	QSize scale		= { 1.0, 1.0 };
	
	///Image's rotation
	double rotation = 0.0;
	
	///Color multiplicatives for image
	double color[4] = {1.0, 1.0, 1.0, 1.0};

protected:
	///Label for quicker identification in the Editor
	QString label;

	///Name of the Image that will be rendered
	QString imageAssetName;
	//Image that will be rendered
	AssetImage	*imageAsset;
	///[optional] create this class and it will store AssetImages with custom names for image filtering (useful in Editor)
	//QVector<SceneryObjectPart> parts;

	//---SERIALIZATION---
	///Loading an object from a binary file
	virtual void serializableLoad(QDataStream& dataStream);
	///Saving an object to a binary file
	virtual void serializableSave(QDataStream& dataStream) const;
};