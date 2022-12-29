#include "Exceptions.h"

namespace NovelLib
{
	bool catchExceptions(const std::function<void(bool bComprehensive)> &errorChecker, bool bComprehensive)
	{
		try
		{
			errorChecker(bComprehensive);
		}
		catch (QException& ex)
		{
			qCritical() << NovelLib::ErrorType::Critical << "[CRITICAL] UNINDENTIFIED `QException` HAS OCCURED OUTSIDE \"qCritical()\" MESSAGE HANDLER:\n" << ex.what(); //todo: check if '\n' is legal here
			return true;
		}
		catch (std::exception& ex)
		{
			qCritical() << NovelLib::ErrorType::Critical << "[CRITICAL] UNINDENTIFIED `std::exception` HAS OCCURED:\n" << ex.what();
			return true;
		}
		catch (...)
		{
			qCritical() << NovelLib::ErrorType::Critical << "[CRITICAL] UNINDENTIFIED EXCEPTION HAS OCCURED\n";
			return true;
		}
		return false;
	}
}