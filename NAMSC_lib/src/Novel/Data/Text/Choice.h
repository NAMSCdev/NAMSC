#pragma once

#include <QFont>

#include "Novel/Data/Asset/AssetImage.h"
#include "Novel/Data/Text/Translation.h"
#include "Novel/Event/EventJump.h"
#include "Serialization.h"

class Choice
{
	struct ChoiceDisplayOptions;
public:
	Choice()                                 = default;
	/// \exception Error `choiceDisplayOptions` might contain invalid Font or the jump is set to non-existent Scene or the `condition` is not formatted properly
	Choice(const QString& name, const Translation& text, const QString& condition, const QString& jumpToSceneName, const ChoiceDisplayOptions& displayOptions);
	Choice(const Choice& obj)                = default;
	Choice& operator=(Choice obj) noexcept;
	bool operator==(const Choice& obj) const noexcept;
	bool operator!=(const Choice& obj) const = default; //{ return !(*this == obj); }

	void run();

	/// \exception Error `choiceDisplayOptions` is invalid / `condition` is invalid / `jumpToSceneName` is invalid
	/// \return Whether an Error has occurred
	/// \todo check `condition`
	bool checkForErrors(bool bComprehensive) const;

	/// Sets a function pointer that is called (if not nullptr) after the Choice's `void run()` allowing for data read
	void setOnRunListener(std::function<void(QString name, Translation* text, QString condition, QString jumpToSceneName)> onRun) noexcept;

	QString name            = "";

	/// If the player chooses this Choice, they will jump to this Scene
	QString jumpToSceneName = "";

	/// The text that is displayed as a Choice for the player
	Translation text;

	/// Logical condition that needs to be fulfilled in order for this Choice to be available
	QString condition       = "";

	/// [optional] 
	struct ChoiceDisplayOptions
	{
		ChoiceDisplayOptions()                                 = default;
		/// \exception Error The found `font_` might be the wrong one (Qt finds the closest one, not the specific one) or could not be read at all
		ChoiceDisplayOptions(const QString& fontName, uint fontSize, bool bHideIfConditionNotMet, uint buttonWeight, uint spacerWeight);
		ChoiceDisplayOptions(const ChoiceDisplayOptions& obj)  = default;
		ChoiceDisplayOptions& operator=(ChoiceDisplayOptions obj) noexcept;
		bool operator==(const ChoiceDisplayOptions& obj) const = default;
		bool operator!=(const ChoiceDisplayOptions& obj) const = default; //{ return !(*this == obj); }

		/// \exception Error `font_`/`assetImage` is invalid
		/// \return Whether an Error has occurred
		bool checkForErrors(bool bComprehensive = false) const;

		uint fontSize     = 11;
			
		uint buttonWeight = 0,
			 spacerWeight = 0;

		/// Normally, if the Choice is not available, it will be greyed out, setting this to `true` will make the Choice not appear at all
		bool bHideIfConditionNotMet = false;

		void setFont(const QString& fontName) noexcept;
		const QFont* getFont() const noexcept;
		QString getFontName() const noexcept;

	private:
		QString fontName_          = "";
		QFont   font_;

		QString     assetImageName = "";
		/// Custom Image for a button
		AssetImage* assetImage     = nullptr;

	public:
		//---SERIALIZATION---
		/// Loading an object from a binary file
		/// \param dataStream Stream (presumably connected to a QFile) to read from
		void serializableLoad(QDataStream& dataStream);
		/// Saving an object to a binary file
		/// \param dataStream Stream (presumably connected to a QFile) to save to
		void serializableSave(QDataStream& dataStream) const;
	} choiceDisplayOptions;

private:
	std::function<void(QString name, Translation* text, QString condition, QString jumpToSceneName)> onRun_ = nullptr;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream);
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const;
};