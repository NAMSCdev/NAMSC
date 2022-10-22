//#pragma once
//#include "Global.h"
//
//#include "Novel/Action/Visual/Effect/ActionEffect.h"
//
///// [optional] Creates a Blur Effect at some point in a SceneryObject or the viewport
//class ActionEffectBlur final : public ActionEffect
//{
//public:
//	/// Algorithm used for blurring
//	enum class BlurType
//	{
//		Gaussian
//	};
//
//	ActionEffectBlur() noexcept = default;
//	ActionEffectBlur(QString&& sceneryObjectName, EffectShape effectShape, QPoint pos, QSize size, uint strength, BlurType blurType);
//	ActionEffectBlur(const ActionEffectBlur& obj) noexcept { *this = obj; }
//	ActionEffectBlur& operator=(const ActionEffectBlur& obj) noexcept;
//
//	/// Executes the ActionEffectBlur's logic
//	void run() override;
//
//	/// Accepts an ActionVisitor
//	/// \param vistor Pointer to a concrete Visitor derived from an ActionVisitor
//	void accept(ActionVisitor* visitor) override { visitor->visitActionEffectBlur(this); }
//
//signals:
//	/// A Qt signal emitted after the ActionEffectBlur's `void run()` allowing for data read
//	void onRun(const SceneryObject* sceneryObject, EffectShape effectShape, QPoint pos, QSize size, uint strength, BlurType blurType) const;
//
//private:
//	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
//	SerializationID	getType() const override { return SerializationID::ActionEffectBlur; }
//
//	/// Algorithm used for blurring
//	BlurType blurType = BlurType::Gaussian;
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
//inline ActionEffectBlur::ActionEffectBlur(QString&& sceneryObjectName, EffectShape effectShape, QPoint pos,
//										  QSize size, uint strength, BlurType blurType) :
//	ActionEffect(move(sceneryObjectName), effectShape, pos, size, strength), blurType(blurType)
//{
//}
//
//inline ActionEffectBlur& ActionEffectBlur::operator=(const ActionEffectBlur& obj)
//{
//	if (this == &obj) return *this;
//
//	ActionEffect::operator=(obj);
//	blurType = obj.blurType;
//
//	return *this;
//}