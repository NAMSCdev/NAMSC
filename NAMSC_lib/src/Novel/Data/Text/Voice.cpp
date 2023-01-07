#include "Novel/Data/Text/Voice.h"

#include "Exceptions.h"

Voice::Voice(const QString& name, const QString& fontName, uint fontSize, bool bold, bool italic, bool underscore, const QColor color, double cpsMultiplier, uint cpsOverwrite, const Qt::AlignmentFlag alignment, const LipSyncType lipSync) noexcept
	: name(name), fontName_(fontName), fontSize_(fontSize), bold(bold), italic(italic), underscore(underscore), cpsMultiplier(cpsMultiplier), cpsOverwrite(cpsOverwrite), color(color), alignment(alignment), lipSync(lipSync)
{
	font_ = QFont(fontName, fontSize_);
}

Voice& Voice::operator=(Voice obj) noexcept
{
	if (this == &obj) return *this;

	std::swap(this->name,          obj.name);
	std::swap(this->fontName_,     obj.fontName_);
	std::swap(this->fontSize_,     obj.fontSize_);
	std::swap(this->bold,          obj.bold);
	std::swap(this->italic,        obj.italic);
	std::swap(this->underscore,    obj.underscore);
	std::swap(this->cpsMultiplier, obj.cpsMultiplier);
	std::swap(this->cpsOverwrite,  obj.cpsOverwrite);
	std::swap(this->color,         obj.color);
	std::swap(this->alignment,     obj.alignment);
	std::swap(this->lipSync,       obj.lipSync);

	return *this;
}

bool Voice::operator==(const Voice& obj) const noexcept
{
	if (this == &obj) return true;

	return	name          == obj.name		   &&
			fontName_     == obj.fontName_	   &&
			fontSize_     == obj.fontSize_	   &&
			bold          == obj.bold		   &&
			italic        == obj.italic		   &&
			underscore    == obj.underscore	   &&
			cpsMultiplier == obj.cpsMultiplier &&
			cpsOverwrite  == obj.cpsOverwrite  &&
			color         == obj.color		   &&
			alignment     == obj.alignment     &&
			lipSync       == obj.lipSync;
}

bool Voice::checkForErrors(bool bComprehensive) const
{
	bool bError = false;
	static auto errorChecker = [&](bool bComprehensive)
	{
		if (fontName_ == "")
			qCritical() << NovelLib::ErrorType::General << "No Font set";

		return false;
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "An Error occurred in Voice::checkForErrors \"" + name + '\"';

	return bError;
}

void Voice::setFont(const QString& fontName) noexcept
{ 
	fontName_ = fontName; 
	font_ = QFont(fontName);
}

const QFont* Voice::getFont() const noexcept
{
	return &font_; 
}

QString Voice::getFontName() const noexcept 
{ 
	return fontName_; 
}

void Voice::serializableLoad(QDataStream& dataStream)
{
	dataStream >> name >> fontName_ >> fontSize_ >> bold >> italic >> underscore >> cpsMultiplier >> cpsOverwrite >> color >> alignment >> lipSync;
}

void Voice::serializableSave(QDataStream& dataStream) const
{
	dataStream << name << fontName_ << fontSize_ << bold << italic << underscore << cpsMultiplier << cpsOverwrite << color << alignment << lipSync;
}