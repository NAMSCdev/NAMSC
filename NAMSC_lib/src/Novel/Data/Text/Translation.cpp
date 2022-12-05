#include "Novel/Data/Text/Translation.h"

#include "Exceptions.h"
#include "Serialization.h"

Translation::Translation(const QHash<QString, QString>& translations)
	: translations_(translations)
{
}

Translation& Translation::operator=(Translation obj) noexcept
{
	if (this == &obj)
		return *this;

	std::swap(*this, obj);

	return *this;
}

bool Translation::checkForErrors(bool bComprehensive) const
{
	bool bError = false;
	static auto errorChecker = [&](bool bComprehensive)
	{
		if (!translations_.contains(NovelSettings::getInstance().defaultLanguage))
		{
			bError = true;
			qCritical() << this << NovelLib::ErrorType::General << "Translation doesn't have default language set";
		}
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	
	if (bError)
		qDebug() << "Error occurred in Translation::checkForErrors";

	return bError;
}


/// Adds or replaces a Translation to the `translations` map
/// \param language The language of the text to add/overwrite
/// \param newText The text to add/overwrite

void Translation::setTranslation(const QString& language, const QString& newText)
{ 
	translations_[language] = newText; 
}

void Translation::deleteTranslation(const QString& translationLanguage)
{
	if (translationLanguage == NovelSettings::getInstance().defaultLanguage)
		qInfo() << "Tried to remove default language \"" << translationLanguage << "\".The option to do so should not be allowed at all";
	else
		translations_.remove(translationLanguage);
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
		return translations_.value(language);
	
	return translations_.value(NovelSettings::getInstance().defaultLanguage);
}

void Translation::serializableLoad(QDataStream& dataStream)
{
	uint translationsSize;
	dataStream >> translationsSize;

	for (uint i = 0; i != translationsSize; ++i)
	{
		QPair<QString, QString> pair;
		dataStream >> pair;
		translations_.insert(pair.first, pair.second);
	}
}

void Translation::serializableSave(QDataStream& dataStream) const
{
	dataStream << translations_.size();
	for (auto it = translations_.constKeyValueBegin(); it != translations_.constKeyValueEnd(); ++it)
		dataStream << *it;
}