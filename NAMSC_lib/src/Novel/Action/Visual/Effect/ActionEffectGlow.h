//#pragma once
//#include "Global.h"
//
//#include "Novel/Action/Visual/Effect/ActionEffect.h"
//
///// [optional] Creates a Glow Effect at some point in a SceneryObject or the entire Viewport
//class ActionEffectGlow final : public ActionEffect
//{
//public:
//	ActionEffectGlow() noexcept = default;
//	ActionEffectGlow(QString&& sceneryObjectName, EffectShape effectShape, QPoint pos, QSize size, uint strength);
//	ActionEffectGlow(const ActionEffectGlow& obj) noexcept { *this = obj; }
//	ActionEffectGlow& operator=(const ActionEffectGlow& obj) noexcept;
//
//	/// Executes the ActionEffectGlow's logic
//	void run() override;
//
//	/// Accepts an ActionVisitor
//	/// \param vistor Pointer to a concrete Visitor derived from an ActionVisitor
//	void accept(ActionVisitor* visitor) override { visitor->visitActionEffectGlow(this); }
//
//signals:
//	/// A Qt signal emitted after the ActionEffectGlow's `void run()` allowing for data read
//	void onRun(const SceneryObject* sceneryObject, EffectShape effectShape, QPoint pos, QSize size, uint strength) const;
//
//private:
//	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
//  /// \return SerializationID corresponding to the class of a serialized object
//	SerializationID	getType() const override { return SerializationID::ActionEffectGlow; }
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
//inline ActionEffectGlow::ActionEffectGlow(QString&& sceneryObjectName, EffectShape effectShape, QPoint pos, QSize size, uint strength) :
//	ActionEffect(move(sceneryObjectName), effectShape, pos, size, strength)
//{
//}
//
//inline ActionEffectGlow& ActionEffectGlow::operator=(const ActionEffectGlow& obj)
//{
//	if (this == &obj) return *this;
//
//	ActionEffect::operator=(obj);
//
//	return *this;
//}