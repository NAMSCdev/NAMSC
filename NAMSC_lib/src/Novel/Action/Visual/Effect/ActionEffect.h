//#pragma once
//#include "Global.h"
//
//#include "Novel/Action/Visual/ActionSceneryObject.h"
//
///// [optional] Base class for the rest of the ActionEffects
//class ActionEffect : public ActionSceneryObject
//{
//public:
//	enum class EffectShape
//	{
//		Ellipse,
//		Rectangle
//	};
//
//	ActionEffect() noexcept = default;
//	ActionEffect(QString&& sceneryObjectName, EffectShape effectShape, QPoint pos, QSize size, uint strength);
//	ActionEffect(const ActionEffect& obj) noexcept { *this = obj; }
//	ActionEffect& operator=(const ActionEffect& obj) noexcept;
//
//protected:
//	/// Determines the shape of the effect: area that will affect an Image
//	EffectShape effectShape;
//
//	/// Specifies where the effect is placed in local position (in relation to the object's origin, not the vieport's, unless the affected object is the entire Viewport itself)
//	QPoint pos;
//
//	/// Semi-major and semi-minor axes of an Ellipse or size of a Rectangle
//	QSize size;	
//
//	/// Strength of the Effect
//	double strength = 1.0;
//
//	//---SERIALIZATION---
//	/// Loading an object from a binary file
//	/// \param dataStream Stream (presumably connected to a QFile) to read from
//	virtual void serializableLoad(QDataStream& dataStream) override;
//	/// Saving an object to a binary file
//	/// \param dataStream Stream (presumably connected to a QFile) to save to
//	virtual void serializableSave(QDataStream& dataStream) const override;
//};
//
//
//
//
//inline ActionEffect::ActionEffect(QString&& sceneryObjectName, EffectShape effectShape, QPoint pos, QSize size, uint strength) :
//	ActionSceneryObject(move(sceneryObjectName)), effectShape(effectShape), pos(pos), size(size), strength(strength) 
//{
//}
//
//inline ActionEffect& ActionEffect::operator=(const ActionEffect& obj)
//{
//	if (this == &obj) return *this;
//
//	ActionSceneryObject::operator=(obj);
//	effectShape = obj.effectShape;
//	pos         = obj.pos;
//	size        = obj.size;
//	strength    = obj.strength;
//
//	return *this;
//}