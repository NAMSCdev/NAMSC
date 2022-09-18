#pragma once
#include <QMessageBox>
#include <QString>
#include <QFile>

//TODO: consider replacing std::strings with QT ones
//TODO: check QT Exception system 
//TODO: consider defining logfile

struct Exception
{
	Exception(std::string &&msg, std::string &&function, std::string &&file, unsigned &&line) noexcept
		: msg(move(msg)), file(move(file)), function(move(function)), line(move(line)) {}

	virtual void handle() noexcept
	{
		time_t curtime;
		time(&curtime);
		char *date = new char[256];
		ctime_s(date, 256, &curtime);
		std::string sDate = date;
		delete[] date;
		size_t lastpos = sDate.rfind(' ');
		size_t firstpos = sDate.rfind(' ', lastpos-1);
		sDate = sDate.substr(firstpos+1, lastpos - firstpos-1);
		details = '[' + sDate + "] [" + file.substr(file.rfind('\\') + 1) + "::" + function + '(' + std::to_string(line) + ")] ";
		//TODO: define logfile
		//logfile << details;
	}
protected:
	std::string details;
	const std::string msg;
private:
	const std::string function, file;
	const unsigned line;
};

struct Warn final : Exception
{
	Warn(std::string &&msg, std::string &&function, std::string &&file, unsigned &&line) noexcept
		: Exception(move(msg), move(function), move(file), move(line)) {}
	void handle() noexcept
	{
		handle(false);
	}
	void handle(bool bDisplay) noexcept
	{
		Exception::handle();
		//logfile << "[WARN] " << msg << std::endl;
		details += msg;
		if (bDisplay) QMessageBox(QMessageBox::Icon::Information, "Warning", details.c_str());
	}
};

struct Err final : Exception, std::runtime_error
{
	Err(std::string &&msg, std::string &&function, std::string &&file, unsigned &&line) noexcept
		: runtime_error("Parsing Error!"), Exception(move(msg), move(function), move(file), move(line)) {}

	void handle() noexcept
	{
		Exception::handle();
		//logfile << "[ERROR] " << msg;
		details += msg;
		QMessageBox(QMessageBox::Icon::Critical, "Error", details.c_str());
	}
};

struct CriticalErr final : Exception, std::runtime_error
{
	CriticalErr(std::string &&msg, std::string &&function, std::string &&file, unsigned &&line)
		: runtime_error("Critical Error!"), Exception(move(msg), move(function), move(file), move(line)) {}

	void handle() noexcept
	{
		Exception::handle();
		//logfile << "[!CRITICAL_ERROR!] " << msg;
		details += msg;
		QMessageBox(QMessageBox::Icon::Critical, "Critical Error", details.c_str());
	}
};