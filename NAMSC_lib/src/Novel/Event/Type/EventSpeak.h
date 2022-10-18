#pragma once
#include "Global.h"

#include "Novel/Event/Type/EventNarrate.h"

///Displays text said by one of the Characters, defaults to the default Character's voice, but can be customized
class EventSpeak final : public EventNarrate //TODO: need fix due to the need of lack of inheritance
{
	EventSpeak(uint executionOrder, QString&& label, QVector<Sentence>&& speech, QString&& voice, QString&& characterName, QString&& displayedName);
	EventSpeak(const EventSpeak& obj) { *this = obj; }
	EventSpeak& operator=(const EventSpeak& obj)
	{
		if (this == &obj) return *this;

		EventNarrate::operator=(obj);
		characterName = obj.characterName;
		character     = obj.character;
		displayedName = obj.displayedName;

		return *this;
	}

	///Executes this Event's logic
	void run() override;

	///Accepts an EventVisitor
	void accept(EventVisitor* visitor) override { visitor->visitEventNarrate(this); }

signals:
	///A Qt signal executing after the Event's `run()` allowing for data read (and write if it is a pointer)
	void onRun(QVector<Sentence> speech, Voice* voice, Character* character, QString displayedName);

private:
	///Needed for serialization, to know the class of an object before the loading performed
	SerializationID getType() const override	{ return SerializationID::EventSpeak; }

	///Character identification name
	QString    characterName;
	Character* character;

	///The speaking Character's displayed name
	QString displayedName;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream& dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream& dataStream) const override;
};