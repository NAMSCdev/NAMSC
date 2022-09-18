#pragma once
#include "Global.h"

#include "Story/Data/Asset/Type/TextAsset.h"

//Class representing every Word that is to be spoken by a Character or Narrator
//[optional] It also contains duration of every word if it's to be voiced/slowed down
class Translation
{
	//Friends for serialization
	friend QIODevice& operator>>(QIODevice &device, Translation &t);
	friend QIODevice& operator<<(QIODevice &device, const Translation &t);
public:
	Translation() = default;
	Translation(std::map<const QString, TextAsset> &&translations, std::map<const QString, const std::vector<unsigned int>>	&&wordDurations) :
		translations(move(translations)), wordDurations(move(wordDurations)){}

	//TODO: move to .cpp
	//Return text in the given language
	const QString												text			() 
	{
		TextAsset	*text = nullptr;
		if (translations.find(StorySettings::language) != translations.end())
			text = &translations[StorySettings::language];
		if (translations.find(StorySettings::defaultLanguage) != translations.end())
			text = &translations[StorySettings::defaultLanguage];

		if (text == nullptr)
		{		
			//TODO: Exceptions
			return "";
		}

		if (!text->isLoaded())
			text->load();

		return *text->getText();
	};
        
	// TODO: move to .cpp
	//[optional] Return word durations
	const std::vector<unsigned int>								durations		()
	{
		//Skip empty words, so if someone made multiple spaces between words, they will not create empty words
		QStringList words = text().split(" ", Qt::SplitBehaviorFlags::SkipEmptyParts);
		
		//Remove things that are not words (made of whitechars only)
		words.removeIf([](const QString word) -> bool
			{
				for (QChar c : word)
					if (!c.isSpace())
						return false;
					return true;
			});

		//Try to retrieve durations for this language
		std::vector<unsigned int> durations;
		if (wordDurations.find(StorySettings::language) != wordDurations.end())
			durations = wordDurations[StorySettings::language];
		if (wordDurations.find(StorySettings::defaultLanguage) != wordDurations.end())
			durations = wordDurations[StorySettings::defaultLanguage];

		//Check if size 
		if (words.size() != durations.size())
		{
			//todo: WARN USER ABOUT THIS
			//returns empty (invalid) durations, which will default the speed to CharByChar instead
			return std::vector<unsigned int>();
		}
		return durations;
	}

protected:
	//Store text for different languages
	std::map<const QString, TextAsset>							translations;

	//Store word durations for [Sentence::WordAppearType::WordByWord] appear type for different languages
	std::map<const QString, const std::vector<unsigned int>>	wordDurations;

	//TODO: serializing maps is easy, but I have no time right now to do that
	//---SERIALIZATION---
	//Loading an object from a binary file
	void serializableLoad(QIODevice &ar)
	{
		QDataStream dataStream(&ar);
        dataStream /*>> translations >> wordDurations*/;
	}
	//Saving an object to a binary file
	void serializableSave(QIODevice &ar) const
	{
		QDataStream dataStream(&ar);
		dataStream << SerializationID::Translation /*<< translations << wordDurations*/;
	}
};