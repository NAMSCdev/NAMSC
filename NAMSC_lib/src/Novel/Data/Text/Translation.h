#pragma once

#include <qhashfunctions.h>
#include <unordered_map>

#include "Novel/Data/NovelSettings.h"

/// Class representing every Speech that is to be spoken by a Character or Narrator
/// [optional] It also contains duration of every word if it's to be voiced
class Translation
{
	//Other friends
	friend class NovelSettings;
	/// Swap trick
	friend void swap(Translation& first, Translation& second) noexcept;
public:
	/// \param translations	Store text for different languages
	Translation(const std::unordered_map<QString, QString>& translations = std::unordered_map<QString, QString>());
	Translation(const Translation& obj)            noexcept = default;
	Translation(Translation&& obj)                 noexcept = default;
	Translation& operator=(const Translation& obj) noexcept = default;
	//Translation& operator=(Translation obj)        noexcept;
	bool operator==(const Translation& obj) const  noexcept = default;
	bool operator!=(const Translation& obj) const  noexcept = default;

	/// \return Whether an Error has occurred
	bool errorCheck(bool bComprehensive) const;

	/// Returns the text in the given language
	/// \param language Returns text in this language, or if it doesn't have it - in default one (`NovelSettings::defaultLanguage`)
	const QString text(const QString language = NovelSettings::getInstance().language) noexcept;

	/// Adds or replaces a Translation to the `translations` map
	void setTranslation(const QString& language, const QString& newText);

	/// Removes Ttranslation from `translations` list
	/// \param language The language of the Translation to be deleted
	void deleteTranslation(const QString& translationLanguage);

	//[optional] Return word durations
	//const std::vector<uint>	durations();

private:
	/// If there is no translation for the new one, it is copied from previous 
	/// \param defaultLanguage Previous default language
	void defaultLanguageChangeFix(const QString& newDefaultLanguage);

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// Store text for different languages
	std::unordered_map<QString, QString> /*textT*/translations_;

	//std::unordered_map<QString, QSound*> speechTranslations_;

	//[optional] Store word durations for [Sentence::WordAppearType::WordByWord] appear type for different languages
	//std::unordered_map<QString, const std::vector<uint>>	wordDurations;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream);
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const;
};