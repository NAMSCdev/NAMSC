#pragma once
#include "Global.h"

/// This code comes from a fist NAMSC prototype and general evaluator code from one of the author's
/// other project that wasn't made based on QT and not considering new NAMSC data structures

/// TODO: Refactor this code, make it use QT structures and new NAMSC data structures
/// TODO: use templates instead of void *
/// TODO: get rid of helper functions like softStoiCheck and use QT functions instead
/// TODO: add exceptions
/// TODO: implement tests on mocked objects
/// TODO: split declaration and definition into two files
/// TODO: consider moving LogicEvaluator into another files
class Evaluator		/// There is no error finding at "parsing the scenario" stage
{
/// public:
/// 	static void *evaulate(std::string expression)	/// todo: here errors too should be replaced for the ParseErr ones
/// 	{
/// 		QVector<std::string>	postfix = toPostfix(move(expression));
/// 		QVector<StatData>		Vars;
/// 
/// 		for (auto it = postfix.begin(), end = postfix.end(); it != end; ++it)
/// 		{
/// 			uint operation = strToOp(*it);
/// 
/// 			if (operation == 0)
/// 			{
/// 		long long number = 0;
/// 		/// Do a stoi
/// 		if (!softStoiCheck(*it, number, 0))
/// 		{
/// 			Stat* stat;
/// 			/// Check if it's first character is  
/// 			if ((*it)[0] == '"')
/// 			{
/// 		Vars.emplace_back(*it);
/// 		continue;
/// 			}
/// 			if (!saveData.findStat(*it, stat))
/// 		throw Err("Couldn't recognize '" + *it + "' while trying to evaluate following logic expression \"" + expression + "\". It is not a Stat nor a value", __func__, __FILE__, __LINE__);
/// 			std::string value = stat->logicValue();
/// 			if (value[0] == '"')
/// 		Vars.emplace_back(value);
/// 			else Vars.emplace_back(stoiCheck(value));
/// 		}
/// 		else Vars.emplace_back(number);
/// 			}
/// 			else
/// 			{
/// 		StatData result(0);
/// 		if (Vars.empty())
/// 			throw Err("There are not enough variables in \"" + expression + "\"", __func__, __FILE__, __LINE__);
/// 		StatData *data = &Vars.back();
/// 		StatData *data2;
/// 		if (Vars.size() > 1) data2 = &*(Vars.end() - 2);
/// 		else data2 = data;
/// 
/// 		if (process(*it, data, data2, result, expression)) Vars.erase(Vars.end() - 1);
/// 		Vars.erase(Vars.end() - 1);
/// 		Vars.push_back(result);
/// 			}
/// 		}
/// 		if (Vars.size() > 1)
/// 			throw Warn("There are redundant variables in \"" + expression + "\"", __func__, __FILE__, __LINE__);
/// 
/// 		switch (Vars.back().type)
/// 		{
/// 		case StatData::Type::STR:
/// 			return new std::string(Vars.back().strVal.c_str());
/// 		default:
/// 			return new long long(Vars.back().intVal);
/// 		}
/// 	}
/// protected:
/// 	struct StatData
/// 	{
/// 		enum class Type { STR, INT } type = Type::INT;
/// 
/// 		StatData() {};
/// 		StatData(const StatData &copied)
/// 		{
/// 			*this = copied;
/// 		};
/// 
/// 		StatData(long long value) { this->intVal = value; type = Type::INT; };
/// 		StatData(std::string value) { this->strVal = value; type = Type::STR; };
/// 
/// 		~StatData()
/// 		{
/// 			if (type == Type::STR)
/// 		strVal.clear();
/// 		}
/// 		const StatData &operator=(const StatData &copied)
/// 		{
/// 			type = copied.type;
/// 			if (type == Type::STR)
/// 		this->strVal = copied.strVal;
/// 			else
/// 		this->intVal = copied.intVal;
/// 			return *this;
/// 		}
/// 
/// 		union
/// 		{
/// 			std::string strVal = "";
/// 			long long intVal;
/// 			/// double dVal;
/// 		};
/// 	};
/// 
/// 	virtual uint strToOp(const char c, const char cNext, uint* i = nullptr) = 0;
/// 
/// 	virtual std::string opToStr(uint operation) noexcept = 0;
/// 
/// 	virtual uint priority(uint operation) = 0;
/// 
/// 	virtual bool process(std::string operationName, StatData *data, StatData *data2, StatData &result, std::string &expression) = 0;
/// 
/// 	uint strToOp(std::string oper)
/// 	{
/// 		if (oper.empty() || oper.size() > 2) return 0;
/// 		return strToOp(oper[0], ((oper.size() == 1) ? '\0' : oper[1]));
/// 	}
/// 
/// 	uint priority(std::string elem)
/// 	{
/// 		for (char c : elem)
/// 			if (!isalnum(c, std::locale()) & &c != '-' & &c != '(')
/// 		return priority(strToOp(elem));
/// 		return 0;
/// 	}
/// 
/// 	static QVector<std::string> toPostfix(std::string &&expr)
/// 	{
/// 		std::string name = "";
/// 		QVector<std::string> stack, ret;
/// 
/// 		bool bNameProcess = false;
/// 		for (size_t i = 0, end = expr.size(); ; ++i)
/// 		{
/// 			if (i == end)
/// 			{
/// 		if (bNameProcess)
/// 			throw Err("A lone '\"' found while trying to evaluate following expression \"" + expr + '\"', __func__, __FILE__, __LINE__);
/// 		
/// 		if (!name.empty())
/// 		{
/// 			ret.push_back(name);
/// 			name.clear();
/// 		}
/// 		break;
/// 			}
/// 
/// 			const char c = expr[i];
/// 			if (bNameProcess)
/// 			{
/// 		if (c == '\\' & &(i + 1) != expr.size() & &expr[i + 1] == '"')
/// 		{
/// 			++i;
/// 			name += '"';
/// 		}
/// 		else
/// 		{
/// 			if (c == '"')
/// 		bNameProcess = false;
/// 			name += c;
/// 		}
/// 		continue;
/// 			}
/// 			else if (isspace(c, std::locale())) continue;
/// 			else if (isalnum(c, std::locale()) || c == '"')
/// 			{
/// 		if (c == '"')
/// 			bNameProcess = true;
/// 		name += c;
/// 		continue;
/// 			}
/// 			if (!name.empty())
/// 			{
/// 		ret.push_back(name);
/// 		name.clear();
/// 			}
/// 			if (c == '(')
/// 		stack.push_back("(");
/// 			else if (c == ')')
/// 			{
/// 		while (true)
/// 		{
/// 			if (stack.empty())
/// 		throw Err("A lone ')' found while trying to evaluate following expression \"" + expr + '\"', __func__, __FILE__, __LINE__);
/// 			std::string elem = stack.back();
/// 			if (elem == "(")
/// 			{
/// 		stack.pop_back();
/// 		break;
/// 			}
/// 			ret.push_back(elem);
/// 			stack.pop_back();
/// 		}
/// 			}
/// 			else
/// 			{
/// 		const char cNext = ((i + 1) != end) ? expr[i + 1] : '\0';
/// 		uint operation = strToOp(c, cNext, &i);
/// 		if (!operation)
/// 			throw Err("Couldn't recognize \"" + std::string(c + ((cNext == '\0') ? "" : std::string({ cNext }))) + "\" while trying to evaluate following expression \"" + expr + "\". It is not a Stat nor a value", __func__, __FILE__, __LINE__);
/// 
/// 		while (!stack.empty())
/// 		{
/// 			std::string elem = stack.back();
/// 			if (priority(operation) > priority(strToOp(elem)))
/// 		break;
/// 			ret.push_back(elem);
/// 			stack.pop_back();
/// 		}
/// 		stack.push_back(opToStr(operation));
/// 			}
/// 		}
/// 		while (!stack.empty())
/// 		{
/// 			ret.push_back(stack.back());
/// 			stack.pop_back();
/// 		}
/// 		return ret;
/// 	}
}; 
/// 
class LogicEvaluator final : public Evaluator		/// There is no error finding at "parsing the scenario" stage
{
/// public:
/// 	Evaluator::evaulate;
/// private:
/// 	enum class Operation
/// 	{
/// 		Failure,
/// 		Equal,
/// 		NotEqual,
/// 		Greater,
/// 		GreaterEq,
/// 		Lesser,
/// 		LesserEq,
/// 		And,
/// 		Or,
/// 		Not
/// 	};
/// 
/// 	/// Needed to transform user input into meaningful action
/// 	uint strToOp(const char c, const char cNext, uint *i = nullptr)
/// 	{
/// 		Operation operation;
/// 		switch (c)
/// 		{
/// 		case '>':
/// 			operation = Operation::Greater;
/// 			if (cNext == '=') { operation = Operation::GreaterEq; if (i) ++(*i); }
/// 			break;
/// 		case '<':
/// 			operation = Operation::Lesser;
/// 			if (cNext == '=') { operation = Operation::LesserEq; if (i) ++(*i); }
/// 			else if (cNext == '>') { operation = Operation::NotEqual; if (i) ++(*i); }
/// 			break;
/// 		case '=':
/// 			operation = Operation::Equal;
/// 			if (i & &cNext == '=') ++(*i);
/// 			break;
/// 		case '&':
/// 			operation = Operation::And;
/// 			if (i & &cNext == '&') ++(*i);
/// 			break;
/// 		case '|':
/// 			operation = Operation::Or;
/// 			if (i & &cNext == '|') ++(*i);
/// 			break;
/// 		case '!':
/// 		case '~':
/// 			operation = Operation::Not;
/// 			if (cNext == '=') { operation = Operation::NotEqual; if (i) ++(*i); }
/// 			break;
/// 		default:
/// 			operation = Operation::Failure;
/// 			break;
/// 		}
/// 		return static_cast<uint>(operation);
/// 	}
/// 
/// 	std::string opToStr(uint operationID) noexcept
/// 	{
/// 		Operation operation = static_cast<Operation>(operationID);
/// 		switch (operation)
/// 		{
/// 		case Operation::NotEqual:
/// 			return "!=";
/// 		case Operation::Greater:
/// 			return ">";
/// 		case Operation::GreaterEq:
/// 			return ">=";
/// 		case Operation::Lesser:
/// 			return "<";
/// 		case Operation::LesserEq:
/// 			return "<=";
/// 		case Operation::And:
/// 			return "&";
/// 		case Operation::Or:
/// 			return "|";
/// 		case Operation::Not:
/// 			return "!";
/// 		case Operation::Equal:
/// 			return "=";
/// 		default:
/// 			return "?";
/// 		}
/// 	}
/// 
/// 	uint priority(uint operationID)
/// 	{
/// 		Operation operation = static_cast<Operation>(operationID);
/// 		switch (operation)
/// 		{
/// 		case Operation::Not:
/// 			return 3;
/// 			break;
/// 		case Operation::And:
/// 		case Operation::Or:
/// 			return 1;
/// 			break;
/// 		default:
/// 			return 2;
/// 		}
/// 	}
/// 
/// 	bool process(std::string operationName, StatData *data, StatData *data2, StatData &result, std::string &expression)
/// 	{
/// 		Operation operation = static_cast<Operation>(Evaluator::strToOp(operationName));
/// 		if (operation == Operation::Not)
/// 		{
/// 			switch (data->type)
/// 			{
/// 			case StatData::Type::STR:
/// 		throw Err("Tried to perform logical \"NOT\" on a string \"" + data->strVal + "\"! It occured in the following expression\"" + expression + "\"", __func__, __FILE__, __LINE__);
/// 			default:
/// 		result.intVal = !data->intVal;
/// 		break;
/// 			}
/// 			return false;
/// 		}
/// 
/// 		if (data == data2)
/// 			throw Err("Tried to perform a binary logical operation, but passed only one argument in \"" + expression + "\"", __func__, __FILE__, __LINE__);
/// 
/// 		if (data->type != data2->type)
/// 			throw Err("Tried to compare different types in \"" + expression + "\"", __func__, __FILE__, __LINE__);
/// 		switch (data->type)
/// 		{
/// 		case StatData::Type::STR:
/// 			switch (operation)
/// 			{
/// 			case Operation::NotEqual:
/// 		result.intVal = data2->strVal != data->strVal;
/// 		break;
/// 			case Operation::Greater:
/// 		result.intVal = data2->strVal > data->strVal;
/// 		break;
/// 			case Operation::GreaterEq:
/// 		result.intVal = data2->strVal >= data->strVal;
/// 		break;
/// 			case Operation::Lesser:
/// 		result.intVal = data2->strVal < data->strVal;
/// 		break;
/// 			case Operation::LesserEq:
/// 		result.intVal = data2->strVal <= data->strVal;
/// 		break;
/// 			case Operation::And:
/// 		throw Err("Tried to perform logical \"AND\" on a string \"" + data->strVal + "\"! It occured in the following expression\"" + expression + "\"", __func__, __FILE__, __LINE__);
/// 		break;
/// 			case Operation::Or:
/// 		throw Err("Tried to perform logical \"OR\" on a string \"" + data->strVal + "\"! It occured in the following expression\"" + expression + "\"", __func__, __FILE__, __LINE__);
/// 		break;
/// 			case Operation::Equal:
/// 		result.intVal = data2->strVal == data->strVal;
/// 		break;
/// 			default:
/// 		throw Err("Couldn't recognize operation '" + operationName + "' while trying to evaluate following logic expression \"" + expression + '"', __func__, __FILE__, __LINE__);
/// 			}
/// 			break;
/// 		case StatData::Type::INT:
/// 			switch (operation)
/// 			{
/// 			case Operation::NotEqual:
/// 		result.intVal = data2->intVal != data->intVal;
/// 		break;
/// 			case Operation::Greater:
/// 		result.intVal = data2->intVal > data->intVal;
/// 		break;
/// 			case Operation::GreaterEq:
/// 		result.intVal = data2->intVal >= data->intVal;
/// 		break;
/// 			case Operation::Lesser:
/// 		result.intVal = data2->intVal < data->intVal;
/// 		break;
/// 			case Operation::LesserEq:
/// 		result.intVal = data2->intVal <= data->intVal;
/// 		break;
/// 			case Operation::And:
/// 		result.intVal = data2->intVal  &data->intVal;
/// 		break;
/// 			case Operation::Or:
/// 		result.intVal = data2->intVal | data->intVal;
/// 		break;
/// 			case Operation::Equal:
/// 		result.intVal = data2->intVal == data->intVal;
/// 		break;
/// 			default:
/// 		throw Err("Couldn't recognize operation '" + operationName + "' while trying to evaluate following logic expression \"" + expression + '"', __func__, __FILE__, __LINE__);
/// 			}
/// 		}
/// 		return true;
/// 	}
/// };
/// 
/// class ArithmethicsEvaluator final : Evaluator		/// There is no logic error finding at parsing the text level
/// {
/// public:
/// 	Evaluator::evaulate;
/// private:
/// 	enum class Operation	/// I guess bitshifts aren't necessary?
/// 	{
/// 		Failure,
/// 		Plus,
/// 		Minus,
/// 		Multiply,
/// 		Divide,
/// 		Modulo
/// 	};
/// 
/// 	static uint strToOp(const char c, const char cNext, uint* i = nullptr)
/// 	{
/// 		Operation operation;
/// 		switch (c)
/// 		{
/// 		case '+':
/// 			operation = Operation::Plus;
/// 			break;
/// 		case '-':
/// 			operation = Operation::Minus;
/// 			break;
/// 		case '*':
/// 			operation = Operation::Multiply;
/// 			break;
/// 		case '/':
/// 			operation = Operation::Divide;
/// 			break;
/// 		case '%':
/// 			operation = Operation::Modulo;
/// 			break;
/// 		default:
/// 			operation = Operation::Failure;
/// 			break;
/// 		}
/// 		return static_cast<uint>(operation);
/// 	}
/// 
/// 	static std::string opToStr(uint operationID) noexcept
/// 	{
/// 		Operation operation = static_cast<Operation>(operationID);
/// 		switch (operation)
/// 		{
/// 		case Operation::Plus:
/// 			return "+";
/// 		case Operation::Minus:
/// 			return "-";
/// 		case Operation::Multiply:
/// 			return "*";
/// 		case Operation::Divide:
/// 			return "/";
/// 		case Operation::Modulo:
/// 			return "%";
/// 		default: 
/// 			return "?";
/// 		}
/// 	}
/// 
/// 	uint priority(uint operationID)
/// 	{
/// 		Operation operation = static_cast<Operation>(operationID);
/// 		switch (operation)
/// 		{
/// 		case Operation::Minus:
/// 		case Operation::Plus:
/// 			return 1;
/// 		default:
/// 			return 2;
/// 		}
/// 	}
/// 
/// 	bool process(std::string operationName, StatData* data, StatData* data2, StatData &result, std::string &expression)
/// 	{
/// 		Operation operation = static_cast<Operation>(Evaluator::strToOp(operationName));
/// 
/// 		if (data == data2)
/// 			throw Err("Tried to perform a binary arithmetics operation, but passed only one argument in \"" + expression + "\"", __func__, __FILE__, __LINE__);
/// 
/// 		if (data->type != data2->type)
/// 			throw Err("Tried to compare different types in \"" + expression + "\"", __func__, __FILE__, __LINE__);
/// 
/// 		switch (data->type)
/// 		{
/// 		case StatData::Type::STR:
/// 			result.type = StatData::Type::STR;
/// 			switch (operation)
/// 			{
/// 			case Operation::Plus:
/// 		result.strVal = data2->strVal + data->strVal;
/// 		break;
/// 			default:
/// 		throw Err("Couldn't recognize or cannot perform operation '" + operationName + "' while trying to evaluate following arithmetics expression \"" + expression + '"', __func__, __FILE__, __LINE__);
/// 			}
/// 			break;
/// 		case StatData::Type::INT:
/// 			switch (operation)
/// 			{
/// 			case Operation::Plus:
/// 		result.intVal = data2->intVal + data->intVal;
/// 		break;
/// 			case Operation::Minus:
/// 		result.intVal = data2->intVal - data->intVal;
/// 		break;
/// 			case Operation::Multiply:
/// 		result.intVal = data2->intVal * data->intVal;
/// 		break;
/// 			case Operation::Divide:
/// 		result.intVal = data2->intVal / data->intVal;
/// 		break;
/// 			case Operation::Modulo:
/// 		result.intVal = data2->intVal % data->intVal;
/// 		break;
/// 			default:
/// 		throw Err("Couldn't recognize operation '" + operationName + "' while trying to evaluate following logic expression \"" + expression + '"', __func__, __FILE__, __LINE__);
/// 			}
/// 		}
/// 		return true;
/// 	}
};