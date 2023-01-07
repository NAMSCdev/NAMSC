#include "Novel/Data/Text/Choice.h"

#include "Exceptions.h"

Choice::Choice(const QString& name, const Translation& text, const QString& condition, const QString& jumpToSceneName, const ChoiceDisplayOptions& choiceDisplayOptions)
	: name(name), text(text), condition(condition), jumpToSceneName(jumpToSceneName), choiceDisplayOptions(choiceDisplayOptions)
{
	//checkForErrors(true);
}

Choice::ChoiceDisplayOptions::ChoiceDisplayOptions(const QString& fontName, uint fontSize, bool bHideIfConditionNotMet, uint buttonWeight, uint spacerWeight)
	: fontName_(fontName), fontSize(fontSize), bHideIfConditionNotMet(bHideIfConditionNotMet), buttonWeight(buttonWeight), spacerWeight(spacerWeight)
{
	font_ = QFont(fontName);
}

Choice& Choice::operator=(Choice obj) noexcept
{
	if (this == &obj) return *this;

	std::swap(this->name,                 obj.name);
	std::swap(this->text,                 obj.text);
	std::swap(this->condition,            obj.condition);
	std::swap(this->jumpToSceneName,      obj.jumpToSceneName);
	std::swap(this->choiceDisplayOptions, obj.choiceDisplayOptions);

	return *this;
}

bool Choice::operator==(const Choice& obj) const noexcept
{
	if (this == &obj) return true;

	return	name                 == obj.name                &&
			text                 == obj.text                &&
			condition            == obj.condition           &&
			jumpToSceneName      == obj.jumpToSceneName     &&
			choiceDisplayOptions == obj.choiceDisplayOptions;
}

void Choice::run()
{
}

Choice::ChoiceDisplayOptions& Choice::ChoiceDisplayOptions::operator=(ChoiceDisplayOptions obj) noexcept
{
	if (this == &obj) return *this;

	std::swap(this->fontName_,              obj.fontName_);
	std::swap(this->fontSize,               obj.fontSize);
	std::swap(this->bHideIfConditionNotMet, obj.bHideIfConditionNotMet);
	std::swap(this->buttonWeight,           obj.buttonWeight);
	std::swap(this->spacerWeight,           obj.spacerWeight);

	return *this;
}

bool Choice::checkForErrors(bool bComprehensive) const
{
	bool bError = false;
	static auto errorChecker = [&](bool bComprehensive)
	{
		if (jumpToSceneName == "")
		{
			bError = true;
			qCritical() << NovelLib::ErrorType::JumpInvalid << "Choice is missing a jumpToSceneName";
		}

		//todo: check `condition`
	};

	bError |= choiceDisplayOptions.checkForErrors(bComprehensive) || NovelLib::catchExceptions(errorChecker, bComprehensive);
		qDebug() << "Error occurred in Choice::checkForErrors";

	return bError;
}

void Choice::setOnRunListener(std::function<void(QString name, Translation* text, QString condition, QString jumpToSceneName)> onRun) noexcept
{ 
	onRun_ = onRun;
}

bool Choice::ChoiceDisplayOptions::checkForErrors(bool bComprehensive) const
{
	bool bError = false;
	static auto errorChecker = [&](bool bComprehensive)
	{
		if (fontName_ == "")
		{
			bError = true;
			qCritical() << NovelLib::ErrorType::General << "No Font set";
		}
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive); 
	if (bError)
		qDebug() << "Error occurred in ChoiceDisplayOptions::checkForErrors";

	return bError;
}

void Choice::ChoiceDisplayOptions::setFont(const QString& fontName) noexcept 
{
	fontName_ = fontName;
	font_     = QFont(fontName); 
}

const QFont* Choice::ChoiceDisplayOptions::getFont() const noexcept
{
	return &font_; 
}

QString Choice::ChoiceDisplayOptions::getFontName() const noexcept 
{ 
	return fontName_; 
}

void Choice::serializableLoad(QDataStream& dataStream)
{
	dataStream >> name >> text >> condition >> jumpToSceneName >> choiceDisplayOptions;
}

void Choice::serializableSave(QDataStream& dataStream) const
{
	dataStream << name << text << condition << jumpToSceneName << choiceDisplayOptions;
}

void Choice::ChoiceDisplayOptions::serializableLoad(QDataStream& dataStream)
{
	dataStream >> fontName_ >> fontSize >> bHideIfConditionNotMet >> buttonWeight >> spacerWeight;
}

void Choice::ChoiceDisplayOptions::serializableSave(QDataStream& dataStream) const
{
	dataStream << fontName_ << fontSize << bHideIfConditionNotMet << buttonWeight << spacerWeight;
}