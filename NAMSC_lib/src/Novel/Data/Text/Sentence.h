#pragma once
#include "Global.h"

#include "Novel/Data/Text/Translation.h"
#include "Novel/Data/Text/Voice.h"

///Represents one portion of the Dialogue that ends with user click if `bEndWithInput` is enabled or after `waitBeforeContinueTime` seconds
///This could be not only one sentence but also a longer text, but this name is kind of intuitional
class Sentence
{
	//Friends for serialization
	friend QDataStream& operator>>(QDataStream&, Sentence&);
	friend QDataStream& operator<<(QDataStream&, const Sentence&);
public:
	///Determines how the text should appear
	enum SentenceAppearType
	{
		///Text appearing character by character is a good option if the Speaker is mute, but also works nice if they aren't
		CharByChar,		///It gives a feeling of actual talking and it is possible to change character insertion sound (if Character is mute) and speed
		WordByWord		///[optional] Karaoke-like style, where words appear one after another
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
	Sentence(Translation &&content, QString &&voiceName, uint cps, bool bEndWithInput, double waitBeforeContinueTime);
	Sentence(const Sentence& obj) { *this = obj; }
	Sentence& operator=(const Sentence& obj);

private:
	///Things to be said, in the chosen language in GlobalSettings
	Translation content;
	
	///Name to the Voice (visual formatting and some additionals) that will be used for this text
	QString	voiceName;
	Voice *voice;

	///Characters per second
	uint cps;
	
	///Whether the user mouseButton or nextButton is needed to end the Sentence
	bool bEndWithInput;

	///If the `bEndWithInput` is set to false, this is the time the Engine will wait before moving to a new Sentence
	double waitBeforeContinueTime;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream);
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const;
};

inline Sentence& Sentence::operator=(const Sentence& obj)
{
	if (this == &obj) return *this;

	content = obj.content;
	voiceName = obj.voiceName;
	voice = obj.voice;
	cps = obj.cps;
	bEndWithInput = obj.bEndWithInput;
	waitBeforeContinueTime = obj.waitBeforeContinueTime;

	return *this;
}