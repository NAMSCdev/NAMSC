#include "Novel/Data/Chapter.h"

#include "Novel/Data/Novel.h"

Chapter& Chapter::operator=(Chapter obj) noexcept
{
	if (this == &obj) return *this;

	std::swap(obj, *this); 

	return *this; 
}

bool Chapter::operator==(const QString& name) const noexcept
{
	return this->name == name; 
}

bool Chapter::operator!=(const QString& name) const noexcept
{ 
	return this->name != name;
}

void Chapter::setParent(const QString& parentName, Chapter* parent) noexcept
{
	if (parent)
	{
		parentName_ = parentName;
		parent_     = parent;
		return;
	}

	Chapter* newParent = nullptr;
	newParent = Novel::getInstance().getChapter(parentName);
	if (newParent == nullptr)
		qCritical() << this << NovelLib::ErrorType::ChapterMissing << "Chapter \"" << parentName << "\" does not exist";
	else
	{
		parentName_ = parentName;
		parent_     = newParent;
	}
}

const Chapter* Chapter::getParent() const noexcept
{
	return parent_;
}

Chapter* Chapter::getParent() noexcept
{
	return parent_;
}

QString Chapter::getParentName() const noexcept
{
	return parentName_;
}

void Chapter::serializableLoad(QDataStream& dataStream)
{
	dataStream >> name >> parentName_;

	parent_ = Novel::getInstance().getChapter(parentName_);
}

void Chapter::serializableSave(QDataStream& dataStream) const
{
	dataStream << name << parentName_;
}