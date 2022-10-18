#pragma once
#include "Global.h"

#include "Novel/Data/Asset/Type/AssetText.h"

///Class representing every Speech that is to be spoken by a Character or Narrator
///[optional] It also contains duration of every word if it's to be voiced/slowed down
class Translation
{
	//Friends for serialization
	friend QDataStream& operator>>(QDataStream&, Translation&);
	friend QDataStream& operator<<(QDataStream&, const Translation&);
public:
	Translation() = default;
	Translation(const QMap<QString, AssetText>&& translations/*, const QVector<uint>>	&&wordDurations*/) :
		translations(move(translations))/*, wordDurations(move(wordDurations))*/ {}
	Translation(const Translation& obj) { *this = obj; }
	Translation& operator=(const Translation& obj);

	///Return text in the language that is set in NovelSettings
	const QString text(const QString language = NovelSettings::getInstance().language);

	///Adds or replaces a translation(pair of const QString and AssetText) to the `translations` list
	void addTranslation(const QString &language, const AssetText &translation) { translations[language] = translation; }

	///Removes translation from `translations` list
	///@todo cannot remove NovelSettings::defaultLanguage
	void deleteTranslation(const QString& language) { translations.remove(language); }

	//[optional] Return word durations
	//const QVector<uint>	durations();

private:
	///Store text for different languages
	QMap<QString, AssetText> translations;

	//[optional] Store word durations for [Sentence::WordAppearType::WordByWord] appear type for different languages
	//QMap<const QString, const QVector<uint>>	wordDurations;

	//---SERIALIZATION---
	///Loading an object from a binary file
	void serializableLoad(QDataStream &dataStream);
	///Saving an object to a binary file
	void serializableSave(QDataStream &dataStream) const;
};

inline Translation& Translation::operator=(const Translation& obj)
{
	if (this == &obj) return *this;

	translations = obj.translations;

	return *this;
}