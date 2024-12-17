#include "pvnLib/Novel/Data/Text/Voice.h"

#include "pvnLib/Exceptions.h"

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(Voice& first, Voice& second) noexcept
{
	using std::swap;
	swap(first.name,          second.name);
	swap(first.fontName_,     second.fontName_);
	swap(first.fontSize_,     second.fontSize_);
	swap(first.bold,          second.bold);
	swap(first.italic,        second.italic);
	swap(first.underscore,    second.underscore);
	swap(first.cpsMultiplier, second.cpsMultiplier);
	swap(first.cpsOverwrite,  second.cpsOverwrite);
	swap(first.color,         second.color);
	swap(first.alignment,     second.alignment);
	swap(first.lipSync,       second.lipSync);
	swap(first.font_,         second.font_);
}

Voice::Voice(const QString& name, const QString& fontName, uint fontSize, bool bold, bool italic, bool underscore, const QColor color, double cpsMultiplier, uint cpsOverwrite, const Qt::AlignmentFlag alignment, const LipSyncType lipSync) noexcept
	: name(name), 
	fontName_(fontName), 
	fontSize_(fontSize),
	bold(bold), 
	italic(italic), 
	underscore(underscore),
	cpsMultiplier(cpsMultiplier), 
	cpsOverwrite(cpsOverwrite),
	color(color), 
	alignment(alignment), 
	lipSync(lipSync)
{
	font_ = QFont(fontName, fontSize_);
	errorCheck(true);
}

//defaulted
//Voice::Voice(const Voice& obj) noexcept
//	: name(obj.name),
//	fontName_(obj.fontName_),
//	fontSize_(obj.fontSize_),
//	bold(obj.bold),
//	italic(obj.italic),
//	underscore(obj.underscore),
//	cpsMultiplier(obj.cpsMultiplier),
//	cpsOverwrite(obj.cpsOverwrite),
//	color(obj.color),
//	alignment(obj.alignment),
//	lipSync(obj.lipSync),
//	font_(obj.font_)
//{
//}

bool Voice::operator==(const Voice& obj) const noexcept
{
	if (this == &obj)
		return true;

	return name          == obj.name          &&
           fontName_     == obj.fontName_     &&
           fontSize_     == obj.fontSize_     &&
           bold          == obj.bold          &&
           italic        == obj.italic        &&
           underscore    == obj.underscore    &&
           cpsMultiplier == obj.cpsMultiplier &&
           cpsOverwrite  == obj.cpsOverwrite  &&
           color         == obj.color         &&
           alignment     == obj.alignment     &&
           lipSync       == obj.lipSync;
}

void Voice::serializableLoad(QDataStream& dataStream)
{
	dataStream >> name >> fontName_ >> fontSize_ >> bold >> italic >> underscore >> cpsMultiplier >> cpsOverwrite >> color >> alignment >> lipSync;
}

void Voice::serializableSave(QDataStream& dataStream) const
{
	dataStream << name << fontName_ << fontSize_ << bold << italic << underscore << cpsMultiplier << cpsOverwrite << color << alignment << lipSync;
}

//  MEMBER_FIELD_SECTION_CHANGE END

//defaulted
//Voice::Voice(Voice&& obj) noexcept
//	: Voice()
//{
//	swap(*this, obj);
//}

//defaulted
//Voice& Voice::operator=(Voice obj) noexcept
//{
//	if (this == &obj) return *this;
//
//	swap(*this, obj);
//
//	return *this;
//}

QString Voice::getFontName() const noexcept
{
	return fontName_;
}

const QFont* Voice::getFont() const noexcept
{
	return &font_; 
}

QFont* Voice::getFont() noexcept
{
	return &font_;
}

void Voice::setFont(const QString& fontName) noexcept
{ 
	fontName_ = fontName; 
	font_     = QFont(fontName);
}