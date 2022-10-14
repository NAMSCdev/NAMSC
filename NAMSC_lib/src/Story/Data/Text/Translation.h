#pragma once
#include "Global.h"

#include "Story/Data/Asset/Type/TextAsset.h"

///Class representing every Speech that is to be spoken by a Character or Narrator
///[optional] It also contains duration of every word if it's to be voiced/slowed down
class Translation
{
	///Friends for serialization
	friend QDataStream& operator>>(QDataStream&, Translation&);
	friend QDataStream& operator<<(QDataStream&, const Translation&);
public:
	Translation() = default;
	Translation(const QMap<QString, TextAsset>&& translations/*, const QVector<unsigned int>>	&&wordDurations*/) :
		translations(move(translations))/*, wordDurations(move(wordDurations))*/ {}

	///Return text in the language that is set in StorySettings
	const QString text(const QString language = StorySettings::getInstance().language);

	///Adds or replaces a translation(pair of const QString and TextAsset) to the `translations` list
	void addTranslation(const QString &language, const TextAsset &translation) { translations[language] = translation; }

	///Removes translation from `translations` list
	///@todo cannot remove StorySettings::defaultLanguage
	void deleteTranslation(const QString& language) { translations.remove(language); }

	//[optional] Return word durations
	//const QVector<unsigned int>	durations();

private:
	///Store text for different languages
	QMap<QString, TextAsset> translations;

	//[optional] Store word durations for [Sentence::WordAppearType::WordByWord] appear type for different languages
	//QMap<const QString, const QVector<unsigned int>>	wordDurations;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream);
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const;
};