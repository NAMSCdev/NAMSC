#pragma once
#include "Global.h"

#include "Story/Event/Event.h"

//Displays narrated text
class EventNarrate : public Event
{
public:
	EventNarrate() = default;
	EventNarrate(unsigned sceneID, unsigned executionOrder, Translation &&text, QString &&voice, QString &&label = "") :
		Event(sceneID, executionOrder, move(label)), text(move(text)), voiceURI(move(voiceURI)) {}

	//Executes Event's logic
	virtual void			run		() override;

	//Accepts EventVisitor
	virtual void			accept	(EventVisitor* visitor) override { visitor->visitEventNarrate(this); }

protected:
	//Needed for serialization, to know the class of an object before the loading performed
	virtual SerializationID	getType	() const override { return SerializationID::EventNarrate; }

	//Text to be displayed
	Translation				text;

	//URI to the Voice used to play this Speech
	QString					voiceURI;

	//---SERIALIZATION---
	//Loading an object from a binary file
	void serializableLoad(QIODevice &ar) override
	{
		EventNarrate::serializableLoad(ar);
		QDataStream dataStream(&ar);
		dataStream >> text >> voiceURI;
	}
	//Saving an object to a binary file
	void serializableSave(QIODevice &ar) const override
	{
		EventNarrate::serializableSave(ar);
		QDataStream dataStream(&ar);
		dataStream << text << voiceURI;
	}
};