#pragma once
#include "Global.h"

#include "Novel/Event/Event.h"
#include "Novel/Event/Type/EventJump.h"
#include "Novel/Data/Text/Translation.h"

///Creates a Choice selection window
class EventChoice final : public Event
{
public:
	class Choice
	{
		//Friends for serialization
		friend QDataStream& operator>>(QDataStream&, Choice&);
		friend QDataStream& operator<<(QDataStream&, const Choice&);
	public:
		Choice()	= default;
		Choice(Translation&& text, QString&& condition, EventJump&& jump, QString&& label) :
			text(move(text)), condition(condition), jump(move(jump)), label(move(label)) { }
		Choice(const Choice& obj) { *this = obj; }
		Choice& operator=(const Choice& obj);

		void run();

		///Text that is displayed as a Choice for the player
		Translation	text;

		///[optional] Choice display settings
		struct ChoiceDisplayOptions
		{
			//Friends for serialization
			friend QDataStream& operator>>(QDataStream&, ChoiceDisplayOptions&);
			friend QDataStream& operator<<(QDataStream&, const ChoiceDisplayOptions&);

			ChoiceDisplayOptions() = default;
			ChoiceDisplayOptions(QString &&fontName, uint fontSize, bool bHideIfConditionNotMet) : 
				fontName(move(fontName)), fontSize(fontSize), bHideIfConditionNotMet(bHideIfConditionNotMet) { }
			ChoiceDisplayOptions(const ChoiceDisplayOptions& obj) { *this = obj; }
			ChoiceDisplayOptions& operator=(const ChoiceDisplayOptions& obj);

			QString fontName;
			AssetFont *font;
			uint fontSize;

			///Normally, if the Choice is not available, it will be greyed out, setting this to [true] will make the Choice not appear at all
			bool bHideIfConditionNotMet;

        private:
            //---SERIALIZATION---
            /// Loading an object from a binary file
			void serializableLoad(QDataStream& dataStream);
            /// Saving an object to a binary file
			void serializableSave(QDataStream& dataStream) const;
        } choiceDisplayOptions;
	
	signals:
		void onRun(Translation& text, ChoiceDisplayOptions& choiceDisplayOptions, QString& label, QString& condition);
	
	private:
		///A label that will be displayed in the Editor (and RenPy if implemented) to help navigation
		QString label;

		///Logical condition that needs to be fulfilled in order for this Choice to be available
		QString condition;

		///If player chooses this Choice, this jump will be performed
		EventJump jump;

		//---SERIALIZATION---
		///Loading an object from a binary file
		void serializableLoad(QDataStream& dataStream);
		///Saving an object to a binary file
		void serializableSave(QDataStream& dataStream) const;
	};

	EventChoice() = default;
	EventChoice(uint executionOrder, QString&& label, Translation&& text, QVector<Choice>&& choices) :
		Event(executionOrder, move(label)), text(move(text)), choices(move(choices)) { }
	EventChoice(const EventChoice& obj) { *this = obj; }
	EventChoice& operator=(const EventChoice& obj);

	///Executes this Event's logic
	void run() override;

	///Accepts an EventVisitor
	void accept(EventVisitor* visitor) override		{ visitor->visitEventChoice(this); }

signals:
	///A Qt signal executing after the Event's `run()` allowing for data read (and write if it is a pointer)
	void onRun(Translation text);

private:
	///Needed for serialization, to know the class of an object before the loading performed
	SerializationID	getType() const override		{ return SerializationID::EventChoice; }

	///A text to be displayed during Choice selection screen
	Translation text;

	///Contains all available choices
	QVector<Choice>	choices;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream& dataStream) override;
	///Saving an object to a binary file
	void serializableSave(QDataStream& dataStream) const override;
};

inline EventChoice::Choice& EventChoice::Choice::operator=(const Choice& obj)
{
	if (this == &obj) return *this;

	label = obj.label;
	text = obj.text;
	condition = obj.condition;
	jump = obj.jump;
	label = obj.label;
	choiceDisplayOptions = obj.choiceDisplayOptions;

	return *this;
}

inline EventChoice::Choice::ChoiceDisplayOptions& EventChoice::Choice::ChoiceDisplayOptions::operator=(const ChoiceDisplayOptions& obj)
{
	if (this == &obj) return *this;

	fontName = obj.fontName;
	font = obj.font;
	fontSize = obj.fontSize;
	bHideIfConditionNotMet = obj.bHideIfConditionNotMet;

	return *this;
}

inline EventChoice& EventChoice::operator=(const EventChoice& obj)
{
	if (this == &obj) return *this;

	Event::operator=(obj);
	label = obj.label;
	text = obj.text;
	choices = obj.choices;

	return *this;
}