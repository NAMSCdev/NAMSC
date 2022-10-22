//#pragma once
//#include "Global.h"
//
//#include "Novel/Action/Stat/ActionStat.h"
//
///// [optional] Makes a Stat visible or not in a special Stat Display Menu 
//class ActionStatVisibility final : public ActionStat
//{
//public:
//	ActionStatVisibility() noexcept = default;
//	ActionStatVisibility(QString&& statName, bool visibility);
//	ActionStatVisibility(const ActionStatVisibility& obj) noexcept { *this = obj; }
//	ActionStatVisibility& operator=(const ActionStatVisibility& obj) noexcept;
//
//	/// Executes the ActionStatVisibility's logic
//	void run() override;
//
//	/// Accepts an ActionVisitor
//	/// \param vistor Pointer to a concrete Visitor derived from an ActionVisitor
//	void accept(ActionVisitor* visitor) override { visitor->visitActionStatVisibility(this); }
//
//signals:
//	/// A Qt signal emitted after the ActionStatVisibility's `void run()` allowing for data read
//	/// \param stat The Stat that had its `bVisibility` affected
//	void onRun(const Stat* stat) const;
//	
//private:
//	/// Needed for Serialization, to know the class of an object about to be Serialization loaded
//	SerializationID	getType() const override { return SerializationID::ActionStatVisibility; }
//
//	/// Whether the Stat is set to visible or not
//	bool visibility;
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
//inline ActionStatVisibility::ActionStatVisibility(QString&& statName, bool visibility) :
//	ActionStat(move(statName)), visibility(visibility)
//{
//}
//
//inline ActionStatVisibility& ActionStatVisibility::operator=(const ActionStatVisibility& obj)
//{
//	if (this == &obj) return *this;
//
//	ActionStat::operator=(obj);
//	visibility = obj.visibility;
//
//	return *this;
//}