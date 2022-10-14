#include "Exceptions.h"
#include <iostream>
#include <QDateTime>

QFile logFile(LOG_FILENAME);

void Exception::handle() noexcept
{
	QTextStream logStream(&logFile);
	details =	'['  + type + "] [" +																	//Type
				QDateTime::currentDateTime().toString(DATE_FORMAT).replace("T", " ") + "] [" +			//Date
				file.right(std::find(file.rbegin(), file.rend(), '\\') - file.rbegin()) +				//FileName
				"::" + function +																		//Function
				"(" + QString::number(line) + ")] " +													//Line
				msg +																					//Message
				'\n';																					//New line
	logStream << details;
	logStream.flush();
}

inline void info(const QString &&msg)
{
	QTextStream logStream(&logFile);
	logStream	<< '[' << QDateTime::currentDateTime().toString(DATE_FORMAT).replace("T", " ") << "] "  //Date
				<< msg																					//Message
				<< '\n';																				//New line
	logStream.flush();
}

Exception::~Exception() = default;