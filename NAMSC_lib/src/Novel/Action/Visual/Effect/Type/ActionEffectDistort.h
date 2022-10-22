//#pragma once
//#include "Global.h"
//
//#include "Novel/Action/Visual/Effect/ActionEffect.h"
//
///// [optional] Creates a Distort Effect at some point in a SceneryObject or the viewport
//class ActionEffectDistort final : public ActionEffect
//{
//public:
//	ActionEffectDistort() noexcept = default;
//	ActionEffectDistort(QString&& sceneryObjectName, EffectShape effectShape, QPoint pos, QSize size, uint strength);
//	ActionEffectDistort(const ActionEffectDistort& obj) noexcept { *this = obj; }
//	ActionEffectDistort& operator=(const ActionEffectDistort& obj) noexcept;
//
//	/// Executes the ActionEffectDistort's logic
//	void run() override;
//
//	/// Accepts an ActionVisitor
//	/// \param vistor Pointer to a concrete Visitor derived from an ActionVisitor
//	void accept(ActionVisitor* visitor) override { visitor->visitActionEffectDistort(this); }
//
//signals:
//	/// A Qt signal emitted after the ActionEffectDistort's `void run()` allowing for data read
//	void onRun(const SceneryObject* sceneryObject, EffectShape effectShape, QPoint pos, QSize size, uint strength) const;
//
//private:
//	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
//	SerializationID	getType() const override { return SerializationID::ActionEffectDistort; }
//
//	//---SERIALIZATION---
//	/// Loading an object from a binary file
//	/// \param dataStream Stream (presumably connected to a QFile) to read from
//	void serializableLoad(QDataStream& dataStream) override;
//	/// Saving an object to a binary file
//	/// \param dataStream Stream (presumably connected to a QFile) to save to
//	void serializableSave(QDataStream& dataStream) const override;
//};
//
//
//
//
//inline ActionEffectDistort::ActionEffectDistort(QString&& sceneryObjectName, EffectShape effectShape, QPoint pos, QSize size, uint strength) :
//	ActionEffect(move(sceneryObjectName), effectShape, pos, size, strength) 
//{
//}
//
//inline ActionEffectDistort& ActionEffectDistort::operator=(const ActionEffectDistort& obj)
//{
//	if (this == &obj) return *this;
//
//	ActionEffect::operator=(obj);
//
//	return *this;
//}