#pragma once
#include "Global.h"

#include "Novel/Event/Event.h"

#include "Novel/Data/Text/Sentence.h"
#include "Novel/Data/Text/Voice.h"

///Displays narrated text
class EventNarrate : public Event
{
public:
	EventNarrate() = default;
	EventNarrate(uint executionOrder, QString&& label, QVector<Sentence>&& speech, QString && voiceName) :
		Event(executionOrder, move(label)), speech(move(speech)), voiceName(move(voiceName)) { }
	EventNarrate(const EventNarrate& obj) { *this = obj; }
	EventNarrate& operator=(const EventNarrate& obj);

	///Executes this Event's logic
	virtual void run() override;

	///Accepts an EventVisitor
	virtual void accept(EventVisitor* visitor) override { visitor->visitEventNarrate(this); }

signals:
	///A Qt signal executing after the Event's `run()` allowing for data read (and write if it is a pointer)
	void onRun(QVector<Sentence> speech, Voice* voice);

protected:
	///Needed for serialization, to know the class of an object before the loading performed
	virtual SerializationID	getType() const override { return SerializationID::EventNarrate; }

	///Text to be displayed
	QVector<Sentence> speech;

	///Name to the Voice used to play this Speech
	QString voiceName;
	///todo:description
	Voice*  voice;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream& dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream& dataStream) const override;
};

inline EventNarrate& EventNarrate::operator=(const EventNarrate& obj)
{
	if (this == &obj) return *this;

	Event::operator=(obj);
	speech = obj.speech;
	voiceName = obj.voiceName;
	voice = obj.voice;

	return *this;
}