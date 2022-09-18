#pragma once
//TODO: Make it work with templates somehow

//#include "Global.h"
//
//#include "Story/Data/Asset/Asset.h"
//#include "Story/Data/Visual/Animation/AnimNode.h"
//
////Allows Animation loading and its memory management
//template<class DataType, unsigned dimension>
//class AnimAsset final : public Asset
//{
//public:
//	AnimAsset(QString URI, QString &&location, unsigned pos = 0) :
//		Asset(move(URI), move(location), pos) {}
//
//	//Tries to load an Assent
//	//Throws a noncritical Exception on failure
//	bool					load() override				{ AnimAsset = uPtr<AnimAsset>(new AnimAsset(location)); return true; }
//
//	//Release resources allocated for this asset
//	void					unload() override			{ animNodes.reset(); }
//
// 	//Returns whether the asset is currently loaded
//	bool					isLoaded() override			{ return animNodes.get() != nullptr; }
//
//	//Returns a pointer to the AnimNodes that this Asset holds
//	animNodes*				getAnimationNodes()			{ return animNodes.get(); }
//
//protected:
//	//Needed for serialization, to know the class of an object about to be serialization loaded
//	SerializationID			getType() const override	{ return SerializationID::AnimAsset; }
//
//	//A smart pointer to the actual data
//	uPtr<std::vector<AnimNode<DataType, dimension>>>	animNodes;
//
//	//---SERIALIZATION---
//	//Loading an object from a binary file
//	void serializableLoad(QIODevice &ar) override
//	{
//		QDataStream dataStream(&ar);
//		dataStream >> location >> pos;
//	}
//	//Saving an object to a binary file
//	void serializableSave(QIODevice &ar) const override
//	{
//		QDataStream dataStream(&ar);
//		dataStream << getType() << location << pos;
//	}
//};