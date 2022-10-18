#include "Global.h"

#include "Novel/Data/Text/Sentence.h"
#include "Novel/Data/Text/Translation.h"
#include "Novel/Data/Novel.h"

Sentence::Sentence(Translation &&content, QString &&voiceName, uint cps,
				   bool bEndWithInput, double waitBeforeContinueTime) : 
	content(move(content)), voiceName(move(voiceName)), cps(cps), bEndWithInput(bEndWithInput), 
	waitBeforeContinueTime(waitBeforeContinueTime)
{
	voice = Novel::getInstance().findVoice(this->voiceName); 
}

const QString Translation::text(const QString language)
{
	NovelSettings &storySettings = NovelSettings::getInstance();
	AssetText *text = nullptr;
	if (translations.find(language) != translations.end())
		text = &translations[language];
	if (translations.find(storySettings.defaultLanguage) != translations.end())
		text = &translations[storySettings.defaultLanguage];

	if (text == nullptr)
	{		
		///TODO: Exceptions
		return "";
	}

	if (!text->isLoaded())
		text->load();

	return *text->getText();
};
 
//[optional]
/*
const QVector<uint> Translation::durations()
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
	QVector<uint> durations;
	if (wordDurations.find(NovelSettings::language) != wordDurations.end())
		durations = wordDurations[NovelSettings::language];
	if (wordDurations.find(NovelSettings::defaultLanguage) != wordDurations.end())
		durations = wordDurations[NovelSettings::defaultLanguage];

	///Check if size 
	if (words.size() != durations.size())
	{
		///todo: WARN USER ABOUT THIS
		///returns empty (invalid) durations, which will default the speed to CharByChar instead
		return QVector<uint>();
	}
	return durations;
}*/