#include "pvnLib/Novel/Data/Chapter.h"

#include "pvnLib/Novel/Data/Novel.h"

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(Chapter& first, Chapter& second) noexcept
{
	using std::swap;
	swap(first.name,        second.name);
	swap(first.parentName_, second.parentName_);
	swap(first.parent_,     second.parent_);
}

Chapter::Chapter(const QString& name, const QString& parentName)
	: name(name)
{
	setParent(parentName);
}

//defaulted
//Chapter::Chapter(const Chapter& obj) noexcept
//	: name(obj.name),
//	parentName_(obj.parentName_),
//	parent_(obj.parent_)
//{
//}

///defaulted
//bool Chapter::operator==(const Chapter& obj) const noexcept
//{
//	if (this == &obj)
//		return true;
//
//	return name        == obj.name        &&
//		   parentName_ == obj.parentName_;
//}

void Chapter::serializableLoad(QDataStream& dataStream)
{
	dataStream >> name >> parentName_;

	if (!parentName_.isEmpty())
		parent_ = Novel::getInstance().getChapter(parentName_);
}

void Chapter::serializableSave(QDataStream& dataStream) const
{
	dataStream << name << parentName_;
}

//  MEMBER_FIELD_SECTION_CHANGE END

//defaulted
//Chapter::Chapter(Chapter&& obj) noexcept
//	: Chapter()
//{
//	swap(*this, obj);
//}

//defaulted 
//Chapter& Chapter::operator=(Chapter obj) noexcept
//{
//	if (this == &obj) return *this;
//
//	swap(*this, obj);
//
//	return *this; 
//}

bool Chapter::operator==(const QString& name) const noexcept
{
	return this->name == name; 
}

bool Chapter::operator!=(const QString& name) const noexcept
{ 
	return this->name != name;
}

QString Chapter::getParentName() const noexcept
{
	return parentName_;
}

const Chapter* Chapter::getParent() const noexcept
{
	return parent_;
}

Chapter* Chapter::getParent() noexcept
{
	return parent_;
}

void Chapter::setParent(const QString& parentName, Chapter* parent) noexcept
{
	if (parent)
	{
		if (parent->name != parentName)
		{
			qCritical() << NovelLib::ErrorType::ChapterMissing << "Chapter's name missmatch (parentName=\"" + parentName + "\", parent->name=\"" + parent->name + "\")";
			return;
		}
	}
	else parent = Novel::getInstance().getChapter(parentName);

	if (!parent)
	{
		qCritical() << NovelLib::ErrorType::ChapterMissing << "Chapter \"" + parentName + "\" does not exist";
		return;
	}
	parentName_ = parentName;
	parent_     = parent;
}