#pragma once
#include "Global.h"

///Contains references to the Sounds used while
///
class Sentence
{
	///Friends for serialization
	friend QDataStream& operator>>(QDataStream &dataStream, Sentence &t);
	friend QDataStream& operator<<(QDataStream &dataStream, const Sentence &t);
public:
	///Determines how the text should appear
	enum SentenceAppearType
	{
		///Text appearing character by character is a good option if the Speaker is mute, but also works nice if they aren't
		CharByChar,		///It gives a feeling of actual talking and it is possible to change character insertion sound (if Character is mute) and speed
		WordByWord		///[optional] Karaoke-like style, where words appear one after another
		///[optional] Words can be set as 
	};

	///[optional] Flags (they can be joined) that specify effect that appearing words have, if [wordAppearType = WordAppearType::WordByWord]
	///NOTE: RenPy doesn't support this by default (other than manual usage of Python), so integration with it would be hard. It is probably better to contribute to RenPy by adding this feature and then adding support for RenPy for it there
	enum SentenceStyle
	{
		Bold		= 0b1,			
		Italic		= 0b10,	
		Underscore	= 0b100,
		Color		= 0b1000		///Custom color
	};

	Sentence() = default;
	Sentence(Translation &&content, QString &&voiceURI) : 
		content(move(content), move(voiceURI)) {}

private:
	///Things to be said, in the chosen language in GlobalSettings
	Translation content;
	
	///URI to the Voice (visual formatting and some additionals) that will be used for this text
	QString		voiceURI;
	Voice		*voice;

	///Repeatedly calls function that forces characters/words to appear until it is no longer needed
	unsigned	cps;
	
	///Whether the user mousebutton or nextButton
	bool		bEndWithInput;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream)
	{
		dataStream >> content >> voiceURI;
		///TODO: load voice
	}
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const
	{
		dataStream << SerializationID::Sentence << content << voiceURI;
	}
};