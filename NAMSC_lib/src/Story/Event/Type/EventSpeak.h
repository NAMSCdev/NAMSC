#pragma once
#include "Global.h"

#include "Story/Event/Type/EventNarrate.h"

///Displays text said by one of the Characters, defaults to the default Character's voice, but can be customized
class EventSpeak final //TODO: need fix due to the need of lack of inheritance
{
	EventSpeak(unsigned executionOrder, QString&& label, QVector<Sentence>&& speech, QString&& voice, QString&& characterName, QString&& displayedName);
	EventSpeak(const EventSpeak& obj) { *this = obj; }
	EventSpeak& operator=(const EventSpeak& obj)
	{
		if (this == &obj) return *this;

		Event::operator=(obj);
		characterName = obj.characterName;
		character     = obj.character;
		displayedName = obj.displayedName;

		return *this;
	}

	///Executes Event's logic
	void run() override;

	///Accepts EventVisitor
	void accept(EventVisitor* visitor) override { visitor->visitEventNarrate(this); }

private:
	///Needed for serialization, to know the class of an object before the loading performed
	SerializationID getType() const override	{ return SerializationID::EventSpeak; }

	///Character identification name
	QString		characterName;
	Character	*character;

	///The speaking Character's displayed name
	QString		displayedName;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream& dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream& dataStream) const override;
};