#pragma once
#include "Global.h"

#include "Story/Data/Text/Translation.h"
#include "Story/Data/Text/Voice.h"

//This hasn't been fully thought through yet. It is WIP

//TODO: add this to Narrate and Speech Event
//A class representing one portion of the Dialogue that ends with user click if [bEndWithInput] is enabled or after [waitBeforeContinueTime]
//This could be not only one sentence but also a longer text, but this name is kind of intuitional
class Sentence
{
	//Friends for serialization
	friend QIODevice &operator>>(QIODevice &device, Sentence &t);
	friend QIODevice &operator<<(QIODevice &device, const Sentence &t);
public:
	//Determines how the text should appear
	enum SentenceAppearType
	{
								//Text appearing character by character is a good option if the Speaker is mute, but also works nice if they aren't
		CharByChar,				//It gives a feeling of actual talking and it is possible to change character insertion sound (if Character is mute) and speed
		WordByWord				//[optional] Karaoke-like style, where words appear one after another
	};

	//[optional] Flags (they can be joined) that specify effect that appearing words have, if [wordAppearType = WordAppearType::WordByWord]
	//NOTE: RenPy doesn't support this by default (other than manual usage of Python), so integration with it would be hard. It is probably better to contribute to RenPy by adding this feature and then adding support for RenPy for it there
	enum SentenceStyle
	{
		Bold	= 0b1,
		Italic	= 0b10,	
		Color	= 0b100,		//Custom color
		Glow	= 0b1000,		//A colored outline
		Shadow	= 0b10000		//Looking like a shadow cast from certain angle. Can be colored
	};

	Sentence() = default;
	Sentence(Translation &&content, QString &&voiceURI) : 
		content(move(content), move(voiceURI)) { ESGFGSSSGDSDG}

	//Create and run a QTimer (https://doc.qt.io/qt-6/qtimer.html) that will make the characters/words appear
	void				startAppear();

	//Stop [appearTimer] and display rest of the text if [bInterruptable = true]
	void				stopAppear();

private:
	//Things to be said, in the chosen language in GlobalSettings
	Translation			content;
	
	//URI to the Voice (visual formatting and some additionals) that will be used for this text
	QString				voiceURI;
	Voice				*voice;

	//Repeatedly calls function that forces characters/words to appear
	QTimer				appearTimer;
	
	//---SERIALIZATION---
	//Loading an object from a binary file
	void serializableLoad(QIODevice &ar)
	{
		QDataStream dataStream(&ar);
		dataStream >> content >> voiceURI;
		//TODO: load voice
	}
	//Saving an object to a binary file
	void serializableSave(QIODevice &ar) const
	{
		QDataStream dataStream(&ar);
		dataStream << SerializationID::Sentence << content << voiceURI;
	}
};