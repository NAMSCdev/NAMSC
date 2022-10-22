#pragma once
#include "Global.h"

#define LOG_FILENAME "log.txt"
#define DATE_FORMAT Qt::ISODate

extern QFile logFile;

//Logs information in a `logFile`
inline void info()
{
	QTextStream(logFile);
};

/// Allows better Exception messaging and logging for debugging and User Warnings
struct Exception : QException
{
	Exception(const QString &&msg, const char type[], const char function[], const char file[], int line) noexcept
		: msg(move(msg)), type(move(type)), function(move(function)), file(move(file)), line(line) { }

	virtual ~Exception() = 0;

	virtual void handle() noexcept;
protected:
	/// Contains the
	QString details;
	const QString msg;
	const QString type;
private:
	const QString function, file;
	const int line;
};

#define warn(msg) throw Warn(msg, __func__, __FILE__, __LINE__)

//Warning that does not
struct Warn final : Exception
{
	Warn(const QString &&msg, const char function[], const char file[], int line) noexcept
		: Exception(move(msg), "WARNING", function, file, line) {}
	void handle() noexcept override
	{
		handle(false);
	}
	void handle(bool bDisplay) noexcept
	{
		Exception::handle();
		if (bDisplay) QMessageBox(QMessageBox::Icon::Information, "Warning", details).exec();
	}
};

#define error(msg) throw Error(msg, __func__, __FILE__, __LINE__)

//Error that causes some sort of rollback
struct Error final : Exception, std::runtime_error
{
	Error(const QString &&msg, const char function[], const char file[], int line) noexcept
		: runtime_error("Error!"), Exception(move(msg), "ERROR", move(function), move(file), line) {}

	void handle() noexcept override
	{
		Exception::handle();
		QMessageBox(QMessageBox::Icon::Critical, "Error", details).exec();
	}
};

#define criticalError(msg) throw CriticalError(msg, __func__, __FILE__, __LINE__)

//If a Critical Error is thrown the application must be terminated
struct CriticalError final : Exception, std::runtime_error
{
	CriticalError(const QString &&msg, const char function[], const char file[], int line)
		: runtime_error("Critical Error!"), Exception(move(msg), "CRITICAL ERROR", function, file, line) {}

	void handle() noexcept override
	{
		Exception::handle();
		QMessageBox(QMessageBox::Icon::Critical, "Critical Error", details).exec();
	}
};