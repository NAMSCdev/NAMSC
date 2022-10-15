#pragma once
#include "Global.h"

#include "Story/Event/Event.h"

#include "Story/Data/Text/Sentence.h"
#include "Story/Data/Text/Voice.h"

///Displays narrated text
class EventNarrate : public Event
{
public:
	EventNarrate() = default;
	EventNarrate(unsigned executionOrder, QString&& label, QVector<Sentence>&& speech, QString && voiceName) :
		Event(executionOrder, move(label)), speech(move(speech)), voiceName(move(voiceName)) {}
	EventNarrate(const EventNarrate& obj) { *this = obj; }
	EventNarrate& operator=(const EventNarrate& obj)
	{
		if (this == &obj) return *this;

		Event::operator=(obj);
		speech    = obj.speech;
		voiceName = obj.voiceName;
		voice     = obj.voice;

		return *this;
	}
	///Executes Event's logic
	virtual void run() override;

	///Accepts EventVisitor
	virtual void accept(EventVisitor* visitor) override { visitor->visitEventNarrate(this); }

protected:
	///Needed for serialization, to know the class of an object before the loading performed
	virtual SerializationID	getType() const override	{ return SerializationID::EventNarrate; }

	///Text to be displayed
	QVector<Sentence> speech;

	///Name to the Voice used to play this Speech
	QString voiceName;
	///todo:description
	Voice   *voice;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream& dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream& dataStream) const override;
};