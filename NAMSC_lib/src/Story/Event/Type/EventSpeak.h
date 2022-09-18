#pragma once
#include "Global.h"

#include "Story/Event/Type/EventNarrate.h"

//Displays text said by one of the Characters, defaults to the default Character's voice, but can be customized
class EventSpeak final : public EventNarrate
{
	EventSpeak(unsigned sceneID, unsigned executionOrder, Translation &&text, QString &&voice, QString &&characterLabel, QString &&name, QString &&label = "") :
		EventNarrate(sceneID, executionOrder, text(move(text)), move(voiceURI), move(label)), characterLabel(move(characterLabel)), name(move(name)) {}

	//Executes Event's logic
	void			run		() override;

	//Accepts EventVisitor
	void			accept	(EventVisitor* visitor) override { visitor->visitEventNarrate(this); }

protected:
	//Needed for serialization, to know the class of an object before the loading performed
	SerializationID	getType	() const override				{ return SerializationID::EventSpeak; }

	//Character identification name
	QString			characterLabel;

	//The speaking Character's displayed name
	QString			name;

	//---SERIALIZATION---
	//Loading an object from a binary file
	void serializableLoad(QIODevice &ar) override
	{
		EventNarrate::serializableLoad(ar);
		QDataStream dataStream(&ar);
		dataStream >> characterLabel >> name;
	}
	//Saving an object to a binary file
	void serializableSave(QIODevice &ar) const override
	{
		EventNarrate::serializableSave(ar);
		QDataStream dataStream(&ar);
		dataStream << getType() << characterLabel << name;
	}
};