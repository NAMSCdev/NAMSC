#pragma once
#include "Global.h"

#include "Story/Event/Event.h"

///Displays narrated text
class EventNarrate : public Event
{
public:
	EventNarrate() = default;
	EventNarrate(unsigned sceneID, unsigned executionOrder, Translation &&text, QString &&voice, QString &&label = "") :
		Event(sceneID, executionOrder, move(label)), text(move(text)), voiceName(move(voiceName)) {}

	///Executes Event's logic
	virtual void			run		() override;

	///Accepts EventVisitor
	virtual void			accept	(EventVisitor* visitor) override { visitor->visitEventNarrate(this); }

protected:
	///Needed for serialization, to know the class of an object before the loading performed
	virtual SerializationID	getType	() const override { return SerializationID::EventNarrate; }

	///Text to be displayed
	Sentence	speech;

	///Name to the Voice used to play this Speech
	QString		voiceName;
	Voice		*voice;
	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream) override
	{
		EventNarrate::serializableLoad(dataStream);

		dataStream >> text >> voiceName;
	}
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const override
	{
		EventNarrate::serializableSave(dataStream);

		dataStream << text << voiceName;
	}
};