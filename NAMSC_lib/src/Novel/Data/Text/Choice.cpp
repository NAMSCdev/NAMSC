#include "Novel/Data/Text/Choice.h"

#include "Exceptions.h"

Choice::Choice(Event* const parentEvent) noexcept
	: parentEvent(parentEvent)
{
}

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(Choice& first, Choice& second) noexcept
{
	using std::swap;
	swap(first.name,                 second.name);
	swap(first.text,                 second.text);
	swap(first.condition,            second.condition);
	swap(first.jumpToSceneName,      second.jumpToSceneName);
	swap(first.choiceDisplayOptions, second.choiceDisplayOptions);
}

void swap(Choice::ChoiceDisplayOptions& first, Choice::ChoiceDisplayOptions& second) noexcept
{
	std::swap(first.fontName_,              second.fontName_);
	std::swap(first.fontSize,               second.fontSize);
	std::swap(first.bHideIfConditionNotMet, second.bHideIfConditionNotMet);
	std::swap(first.buttonWeight,           second.buttonWeight);
	std::swap(first.spacerWeight,           second.spacerWeight);
	std::swap(first.font_,                  second.font_);
}

Choice::Choice(Event* const parentEvent, const QString& name, const Translation& text, const QString& condition, const QString& jumpToSceneName, const ChoiceDisplayOptions& choiceDisplayOptions)
	: parentEvent(parentEvent),
	name(name),
	text(text),
	condition(condition),
	jumpToSceneName(jumpToSceneName), 
	choiceDisplayOptions(choiceDisplayOptions)
{
}

//defaulted
Choice::Choice(const Choice& obj) noexcept
	: parentEvent(parentEvent),
	name(obj.name),
	text(obj.text),
	condition(obj.condition),
	jumpToSceneName(obj.jumpToSceneName),
	choiceDisplayOptions(obj.choiceDisplayOptions)
{
}

Choice::ChoiceDisplayOptions::ChoiceDisplayOptions(const QString& fontName, uint fontSize, bool bHideIfConditionNotMet, uint buttonWeight, uint spacerWeight)
	: fontName_(fontName),
	fontSize(fontSize),
	bHideIfConditionNotMet(bHideIfConditionNotMet),
	buttonWeight(buttonWeight),
	spacerWeight(spacerWeight)
{
	font_ = QFont(fontName);
}

//defaulted
//Choice::ChoiceDisplayOptions::ChoiceDisplayOptions(const ChoiceDisplayOptions& obj) noexcept
//	: fontName_(obj.fontName_),
//	fontSize(obj.fontSize),
//	bHideIfConditionNotMet(obj.bHideIfConditionNotMet),
//	buttonWeight(obj.buttonWeight),
//	spacerWeight(obj.spacerWeight),
//	font_(obj.font_)
//{
//}

bool Choice::operator==(const Choice& obj) const noexcept
{
	if (this == &obj) return true;

	return	name                 == obj.name                &&
			text                 == obj.text                &&
			condition            == obj.condition           &&
			jumpToSceneName      == obj.jumpToSceneName     &&
			choiceDisplayOptions == obj.choiceDisplayOptions;
}

//defaulted
//bool Choice::ChoiceDisplayOptions::operator==(const ChoiceDisplayOptions& obj) const noexcept
//{
//	if (this == &obj) return true;
//
//	return	fontName_              == obj.fontName_              &&
//			fontSize               == obj.fontSize               &&
//			bHideIfConditionNotMet == obj.bHideIfConditionNotMet &&
//			buttonWeight           == obj.buttonWeight           &&
//			spacerWeight           == obj.spacerWeight;
//}

void Choice::setOnRunListener(std::function<void(const QString& name, const Translation* const text, const QString& condition, const QString& jumpToSceneName)> onRun) noexcept
{
	onRun_ = onRun;
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

//  MEMBER_FIELD_SECTION_CHANGE END

Choice::Choice(Choice&& obj) noexcept
	: Choice(obj.parentEvent)
{
	swap(*this, obj);
}

Choice& Choice::operator=(Choice obj) noexcept
{
	if (this == &obj) return *this;

	swap(*this, obj);

	return *this;
}

//defaulted
//Choice::ChoiceDisplayOptions::ChoiceDisplayOptions(ChoiceDisplayOptions&& obj) noexcept
//	: ChoiceDisplayOptions()
//{
//	swap(*this, obj);
//}

//defaulted
//Choice::ChoiceDisplayOptions& Choice::ChoiceDisplayOptions::operator=(ChoiceDisplayOptions obj) noexcept
//{
//	if (this == &obj) return *this;
//
//	swap(*this, obj);
//
//	return *this;
//}

QString Choice::ChoiceDisplayOptions::getFontName() const noexcept
{
	return fontName_;
}

const QFont* Choice::ChoiceDisplayOptions::getFont() const noexcept
{
	return &font_; 
}

QFont* Choice::ChoiceDisplayOptions::getFont() noexcept
{
	return &font_;
}

void Choice::ChoiceDisplayOptions::setFont(const QString& fontName) noexcept
{
	fontName_ = fontName;
	font_     = QFont(fontName);
}