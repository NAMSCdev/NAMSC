#pragma once
#include "Global.h"

#include "Story/Event/Event.h"
#include "Story/Event/Type/EventJump.h"
#include "Story/Data/Text/Translation.h"

///Creates a Choice selection window
class EventChoice final : public Event
{
public:
	class Choice
	{
		///Friends for serialization
		friend QDataStream& operator>>(QDataStream&, Choice&);
		friend QDataStream& operator<<(QDataStream&, const Choice&);
	public:
		Choice()	= default;
		Choice(Translation &&text, QString &&condition, EventJump &&jump, QString &&label) :
			text(move(text)), condition(condition), jump(move(jump)), label(move(label)) {}
		///A label that will be displayed in the Editor (and RenPy if implemented) to help navigation
		QString		label;
		///Text that is displayed as a Choice for the player
		Translation	text;
		///Logical condition that needs to be fulfilled in order for this Choice to be available
		QString		condition;
		///If player chooses this Choice, this jump will be performed
		EventJump	jump;
		///[optional] Choice display settings
		struct ChoiceDisplayOptions
		{
			///Friends for serialization
			friend QDataStream& operator>>(QDataStream&, ChoiceDisplayOptions&);
			friend QDataStream& operator<<(QDataStream&, const ChoiceDisplayOptions&);

			ChoiceDisplayOptions() = default;
			ChoiceDisplayOptions(QFont &&font, unsigned fontSize, bool bHideIfConditionNotMet) : 
		font(move(font)), fontSize(fontSize), bHideIfConditionNotMet(bHideIfConditionNotMet) {}

			QFont			font;
			unsigned		fontSize;
			///Normally, if the Choice is not available, it will be greyed out, setting this to [true] will make the Choice not appear at all
			bool			bHideIfConditionNotMet;
        private:
            //---SERIALIZATION---
            /// Loading an object from a binary file
            void serializableLoad(QDataStream &dataStream) 
			{
		dataStream >> font >> fontSize >> bHideIfConditionNotMet;
            }
            /// Saving an object to a binary file
            void serializableSave(QDataStream &dataStream) const 
			{
		dataStream << font << fontSize << bHideIfConditionNotMet;
            }
        }			choiceDisplayOptions;

	private:
		//---SERIALIZATION---
		///Loading an object from a binary file
		void serializableLoad(QDataStream &dataStream)
		{
	
            dataStream >> label >> text >> condition >> jump;
		}
		///Saving an object to a binary file
		void serializableSave(QDataStream &dataStream) const
		{
	
            dataStream << label << text << condition << jump;
		}
	};

	EventChoice() = default;
	EventChoice(unsigned sceneID, unsigned executionOrder, Translation &&text, QVector<Choice> &&choices, QString &&label = "") :
		Event(sceneID, executionOrder, move(label)), text(move(text)), choices(move(choices)) {}
	
	///Executes Event's logic
	void			run		() override;

	///Accepts EventVisitor
	void			accept	(EventVisitor* visitor) override		{ visitor->visitEventChoice(this); }
	 
protected:
	///Needed for serialization, to know the class of an object before the loading performed
	SerializationID	getType	() const override		{ return SerializationID::EventChoice; }

	///A text to be displayed dNameng Choice selection screen
	Translation		text;

	///Contains all available choices
	QVector<Choice>	choices;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream) override
	{
		Event::serializableLoad(dataStream);

		dataStream >> text;

		unsigned choicesSize;
		dataStream >> choicesSize;
		for (unsigned i = 0u; i != choicesSize; ++i)
		{
			Choice choice;
			dataStream >> choice;
			choices.push_back(move(choice));
		}
	}
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const override
	{
		Event::serializableSave(dataStream);

		dataStream << text << choices.size();
		for (const Choice &choice : choices)
			dataStream << choice;
	}
};