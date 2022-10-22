//#pragma once
//#include "Global.h"
//
//#include "Novel/Action/Visual/Filter/ActionFilter.h"
//
///// [optional] Creates a Blur Filter at a SceneryObject or the Viewport
//class ActionFilterBlur final : public ActionFilter
//{
//public:
//	/// Algorithm used for blurring
//	enum class BlurType
//	{
//		Gaussian
//	};
//
//	ActionFilterBlur() noexcept = default;
//	ActionFilterBlur(QString&& sceneryObjectName, double intensivness, double strength, BlurType blurType);
//	ActionFilterBlur(const ActionFilterBlur& obj) noexcept { *this = obj; }
//	ActionFilterBlur& operator=(const ActionFilterBlur& obj) noexcept;
//
//	/// Executes the ActionFilterBlur's logic
//	void run() override;
//
//	/// Accepts an ActionVisitor
//	/// \param vistor Pointer to a concrete Visitor derived from an ActionVisitor
//	void accept(ActionVisitor* visitor) override { visitor->visitActionFilterBlur(this); }
//
//signals:
//	/// A Qt signal emitted after the ActionFilterBlur's `void run()` allowing for data read
//	void onRun(const SceneryObject* sceneryObject, QPoint pos, QSize size, double intensivness, uint strength, BlurType blurType) const;
//
//private:
//	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
//	SerializationID	getType() const override { return SerializationID::ActionFilterBlur; }
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
//inline ActionFilterBlur::ActionFilterBlur(QString&& sceneryObjectName, double intensivness, double strength, BlurType blurType) :
//	ActionFilter(move(sceneryObjectName), intensivness, strength), blurType(blurType) 
//{
//}
//
//inline ActionFilterBlur& ActionFilterBlur::operator=(const ActionFilterBlur& obj)
//{
//	if (this == &obj) return *this;
//
//	ActionFilter::operator=(obj);
//	blurType = obj.blurType;
//
//	return *this;
//}