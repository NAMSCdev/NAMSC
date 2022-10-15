#include "Global.h"

#include "Story/Data/Text/Sentence.h"
#include "Story/Data/Text/Translation.h"
#include "Story/Data/Story.h"

Sentence::Sentence(Translation &&content, QString &&voiceName, unsigned cps,
				   bool bEndWithInput, double waitBeforeContinueTime) : 
	content(move(content)), voiceName(move(voiceName)), cps(cps), bEndWithInput(bEndWithInput), 
	waitBeforeContinueTime(waitBeforeContinueTime)
{
	voice = Story::getInstance().findVoice(this->voiceName); 
}

const QString Translation::text()
{
	AssetText *text = nullptr;
	if (translations.find(StorySettings::language) != translations.end())
		text = &translations[StorySettings::language];
	if (translations.find(StorySettings::defaultLanguage) != translations.end())
		text = &translations[StorySettings::defaultLanguage];

	if (text == nullptr)
	{		
		///TODO: Exceptions
		return "";
	}

	if (!text->isLoaded())
		text->load();

	return *text->getText();
};
        
const QVector<unsigned int> Translation::durations()
{
	///Skip empty words, so if someone made multiple spaces between words, they will not create empty words
	QStringList words = text().split(" ", Qt::SplitBehaviorFlags::SkipEmptyParts);

	///Remove things that are not words (made of whitechars only)
	words.removeIf([](const QString word) -> bool
		   {
			   for (QChar c : word)
		   if (!c.isSpace())
			   return false;
			   return true;
		   });

	///Try to retrieve durations for this language
	QVector<unsigned int> durations;
	if (wordDurations.find(StorySettings::language) != wordDurations.end())
		durations = wordDurations[StorySettings::language];
	if (wordDurations.find(StorySettings::defaultLanguage) != wordDurations.end())
		durations = wordDurations[StorySettings::defaultLanguage];

	///Check if size 
	if (words.size() != durations.size())
	{
		///todo: WARN USER ABOUT THIS
		///returns empty (invalid) durations, which will default the speed to CharByChar instead
		return QVector<unsigned int>();
	}
	return durations;
}