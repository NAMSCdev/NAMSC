#include "Novel/Data/Text/Translation.h"

#include "Exceptions.h"
#include "Serialization.h"

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(Translation& first, Translation& second) noexcept
{
	using std::swap;
	swap(first.translations_, second.translations_);
}

Translation::Translation(const std::unordered_map<QString, QString>& translations)
	: translations_(translations)
{
}

//defaulted
//Translation::Translation(const Translation& obj) noexcept
//	: translations_(obj.translations_)
//{
//}

//defaulted
//Translation& Translation::operator=(const Translation& obj) noexcept
//{
//	if (this == &obj)
//		return *this;
//
//	translations_ = obj.translations_;
//
//	return *this;
//}

void Translation::serializableLoad(QDataStream& dataStream)
{
	uint translationsSize;
	dataStream >> translationsSize;

	for (uint i = 0; i != translationsSize; ++i)
	{
		std::pair<QString, QString> translation;
		dataStream >> translation;
		translations_.insert(translation);
	}
}

void Translation::serializableSave(QDataStream& dataStream) const
{
	dataStream << static_cast<uint>(translations_.size());
	for (std::pair<QString, QString> translation : translations_)
		dataStream << translation;
}

//  MEMBER_FIELD_SECTION_CHANGE END

//defaulted
//Translation::Translation(Translation&& obj) noexcept
//	: Translation()
//{
//	swap(*this, obj);
//}

void Translation::setTranslation(const QString& language, const QString& newText)
{ 
	translations_[language] = newText; 
}

void Translation::deleteTranslation(const QString& translationLanguage)
{
	if (translationLanguage == NovelSettings::getInstance().defaultLanguage)
		qInfo() << "Tried to remove default language \"" + translationLanguage + "\".The option to do so should not be allowed at all";
	else
		translations_.erase(translationLanguage);
}

void Translation::defaultLanguageChangeFix(const QString& oldDefaultLanguage)
{
	if (translations_.contains(NovelSettings::getInstance().defaultLanguage))
		return;

	if (oldDefaultLanguage == NovelSettings::getInstance().defaultLanguage)
		qInfo() << "Copying old defaultLanguage Translation text to the new defaultLanguage. Possible inconsistency: languages should differ, but to fill the empty space, we copy the very probably wrong one, so any text can be displayed at all";
}

const QString Translation::text(const QString language) noexcept
{
	if (translations_.contains(language))
		return translations_.at(language);
	
	if (!translations_.contains(NovelSettings::getInstance().defaultLanguage))
	{
		///todo: add Exception
		return QString();
	}

	return translations_.at(NovelSettings::getInstance().defaultLanguage);
}