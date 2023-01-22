#pragma once

#include <QFont>

#include "Novel/Data/Asset/AssetImage.h"
#include "Novel/Data/Text/Translation.h"
#include "Novel/Event/EventJump.h"
#include "Serialization.h"

class Choice
{
	class ChoiceDisplayOptions;
	/// Swap trick
	friend void swap(Choice& first, Choice& second) noexcept;

public:
	class ChoiceDisplayOptions
	{
		/// Swap trick
		friend void swap(ChoiceDisplayOptions& first, ChoiceDisplayOptions& second) noexcept;
	public:
		ChoiceDisplayOptions()                                           noexcept = default;
		/// \param bHideIfConditionNotMet Normally, if the Choice is not available, it will be greyed out, setting this to `true` will make the Choice not appear at all
		/// \exception Error The found `font_` might be the wrong one (Qt finds the closest one, not the specific one) or could not be read at all
		explicit ChoiceDisplayOptions(const QString& fontName, uint fontSize = 11, bool bHideIfConditionNotMet = false, uint buttonWeight = 0, uint spacerWeight = 0);
		ChoiceDisplayOptions(const ChoiceDisplayOptions& obj)            noexcept = default;
		ChoiceDisplayOptions(ChoiceDisplayOptions&& obj)                 noexcept = default;
		ChoiceDisplayOptions& operator=(const ChoiceDisplayOptions& obj) noexcept = default;
		//ChoiceDisplayOptions& operator=(ChoiceDisplayOptions obj)        noexcept;
		bool operator==(const ChoiceDisplayOptions& obj) const           noexcept = default;
		bool operator!=(const ChoiceDisplayOptions& obj) const           noexcept = default;

		/// \exception Error `font_`/`assetImage` is invalid
		/// \return Whether an Error has occurred
		bool errorCheck(bool bComprehensive = false) const;

		uint fontSize = 11;

		//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
		/// Normally, if the Choice is not available, it will be greyed out, setting this to `true` will make the Choice not appear at all
		bool bHideIfConditionNotMet = false;

		uint buttonWeight = 0,
			 spacerWeight = 0;

		QString getFontName()  const noexcept;
		const QFont* getFont() const noexcept;
		QFont*       getFont()       noexcept;
		void setFont(const QString& fontName) noexcept;

	private:
		QString fontName_ = "";
		QFont   font_;

		//QString     buttonAssetImageName = "";
		/// Custom Image for a button
		//AssetImage* buttonAssetImage     = nullptr;

	public:
		//---SERIALIZATION---
		/// Loading an object from a binary file
		/// \param dataStream Stream (presumably connected to a QFile) to read from
		void serializableLoad(QDataStream& dataStream);
		/// Saving an object to a binary file
		/// \param dataStream Stream (presumably connected to a QFile) to save to
		void serializableSave(QDataStream& dataStream) const;
	};

	explicit Choice(EventChoice* const parentEvent) noexcept;
	/// \param Logical condition that needs to be fulfilled in order for this Choice to be available
	/// \exception Error `choiceDisplayOptions` might contain invalid Font or the jump is set to non-existent Scene or the `condition` is not formatted properly
	Choice(EventChoice* const parentEvent, const Translation& text, const QString& jumpToSceneName = "", const QString& condition = "", const ChoiceDisplayOptions& displayOptions = ChoiceDisplayOptions());
	Choice(const Choice& obj)                noexcept;
	Choice(Choice&& obj)                     noexcept;
	Choice& operator=(Choice obj)            noexcept;
	bool operator==(const Choice& obj) const noexcept;
	bool operator!=(const Choice& obj) const noexcept = default;

	void run();

	void render(SceneWidget* sceneWidget);

	/// \exception Error `choiceDisplayOptions` is invalid / `condition` is invalid / `jumpToSceneName` is invalid
	/// \return Whether an Error has occurred
	/// \todo check `condition`
	bool errorCheck(bool bComprehensive) const;

	/// Sets a function pointer that is called (if not nullptr) after the Choice's `void run()` allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it
	void setOnRunListener(std::function<void(const Translation* const translation, const QString& jumpToSceneName, const QString& condition, const ChoiceDisplayOptions& displayOptions)> onRun) noexcept;

	EventChoice* const parentEvent;

	Translation translation;

	QString jumpToSceneName = "";

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// Logical condition that needs to be fulfilled in order for this Choice to be available
	QString condition       = "";

	ChoiceDisplayOptions choiceDisplayOptions;

private:
	/// A function pointer that is called (if not nullptr) after the Choice's `void run()` allowing for data read. Consts are safe to be casted to non-consts, they are there to indicate you should not do that, unless you have a very reason for it
	std::function<void(const Translation* const translation, const QString& jumpToSceneName, const QString& condition, const ChoiceDisplayOptions& displayOptions)> onRun_ = nullptr;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	void serializableLoad(QDataStream& dataStream);
	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	void serializableSave(QDataStream& dataStream) const;
};