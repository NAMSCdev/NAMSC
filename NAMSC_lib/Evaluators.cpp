#include <QString>
#include <QTextStream>
#include <QStringView>
#include <QVector>
#include <QMap>

struct Token
{
public:

	enum class Type
	{
		Variable,
		Numeric,
		String,
		Operator
	};

	enum class OperatorType
	{
		And,
		Or,
		Xor,
		Not,
		Plus,
		Minus,
		Multiply,
		Divide,
		Modulus,
		Equal,
		NotEqual,
		Greater,
		Lesser,
		GreaterOrEqual,
		LesserOrEqual,
		LeftParenthesis,
		RightParenthesis,
		NOP
	};

	int getPriority() const
	{
		const static QMap<OperatorType, int> operatorPriorityMap = {
			{OperatorType::NOP, -1},
			{OperatorType::LeftParenthesis, 0},
			{OperatorType::RightParenthesis, 0},
			{OperatorType::Not, 1},
			{OperatorType::Multiply, 2},
			{OperatorType::Divide, 2},
			{OperatorType::Modulus, 2},
			{OperatorType::Plus, 3},
			{OperatorType::Minus, 3},
			{OperatorType::Greater, 4},
			{OperatorType::GreaterOrEqual, 4},
			{OperatorType::Lesser, 4},
			{OperatorType::LesserOrEqual, 4},
			{OperatorType::Equal, 5},
			{OperatorType::NotEqual, 5},
			{OperatorType::And, 6},
			{OperatorType::Xor, 7},
			{OperatorType::Or, 8}
		};

		return operatorPriorityMap[operatorType];
	}

	QString data;
	Type type;
	OperatorType operatorType;
};

namespace
{
	Token::Type getFirstCharType(QChar c)
	{
		Token::Type res;

		const QString operatorCharacters = "()!*/%+->=<&|^";

		if (c.isDigit())
		{
			res = Token::Type::Numeric;
		}
		else if (c.isLetter() || c == '_')
		{
			res = Token::Type::Variable;
		}
		else if (c == '"' or c == '\'')
		{
			res = Token::Type::String;
		}
		else if (operatorCharacters.indexOf(c) != -1)
		{
			res = Token::Type::Operator;
		}
		else
		{
			// TODO error
		}

		return res;
	}

	QString readVariableFrom(const QString& expression, const qsizetype pos)
	{
		// TODO
		// Pierwszy znak musi być isLetter() lub '_'
		// Kolejne isLetterOrNumber() lub '_'
	}

	QString readNumericFrom(const QString& expression, const qsizetype pos)
	{
		// TODO
		// Może wystąpić dokładnie 1 separator '.'
		// poza powyższym zawsze isDigit()
	}

	QString readStringFrom(const QString& expression, const qsizetype pos)
	{
		// TODO
		// Pierwszy znak to ' lub " i to należy zapamiętać
		// Wewnątrz stringa dopuszcza się isLetterOrDigit() lub '_' lub isSpace()
		// Ostatni znak musi być taki jak rozpoczynający
		// Do zapisu oddać bez ' lub "
	}

	QString readOperatorFrom(const QString& expression, const qsizetype pos)
	{
		const QString chainingOperatorCharacters = "=&|";

		// TODO
		// Tutaj się zastanawiam
	}

	Token::OperatorType classifyOperator(const QString& data)
	{
		const static QMap<QString, Token::OperatorType> stringToOperatorMapping = {
			{"(", Token::OperatorType::LeftParenthesis},
			{")", Token::OperatorType::RightParenthesis},
			{"!", Token::OperatorType::Not},
			{"*", Token::OperatorType::Multiply},
			{"/", Token::OperatorType::Divide},
			{"%", Token::OperatorType::Modulus},
			{"+", Token::OperatorType::Plus},
			{"-", Token::OperatorType::Minus},
			{">", Token::OperatorType::Greater},
			{">=", Token::OperatorType::GreaterOrEqual},
			{"<", Token::OperatorType::Lesser},
			{"<=", Token::OperatorType::LesserOrEqual},
			{"=", Token::OperatorType::Equal},
			{"==", Token::OperatorType::Equal},
			{"!=", Token::OperatorType::NotEqual},
			{"&", Token::OperatorType::And},
			{"&&", Token::OperatorType::And},
			{"^", Token::OperatorType::Xor},
			{"|", Token::OperatorType::Or},
			{"||", Token::OperatorType::Or}
		};

		return stringToOperatorMapping[data];
	}

	Token readTokenFrom(const QString& expression, const qsizetype pos)
	{
		if (not (expression.length() - pos - 1))
		{
			// TODO error
		}

		QString data;
		const Token::Type type = getFirstCharType(expression[0]);

		// Forward reading dependent on type
		switch (type)
		{
		case Token::Type::Variable:
			data = readVariableFrom(expression, pos);
			break;
		case Token::Type::Numeric:
			data = readNumericFrom(expression, pos);
			break;
		case Token::Type::String:
			data = readStringFrom(expression, pos);
			break;
		case Token::Type::Operator:
			data = readOperatorFrom(expression, pos);
			break;
		default:
			// TODO error
			break;
		}

		return Token{data, type, type == Token::Type::Operator ? classifyOperator(data) : Token::OperatorType::NOP};
	}

	qsizetype countLeadingSpacesFrom(const QString& expression, const qsizetype pos)
	{
		qsizetype count = 0;
		for (qsizetype i = pos; i < expression.length() && not expression[i].isSpace(); ++i)
		{
			++count;
		}

		return count;
	}

	QVector<Token> tokenizeToPostfix(const QString& expression)
	{
		QVector<Token> res;
		QVector<Token> resultStack, operatorStack;
		qsizetype pos = 0;

		// Consume whole expression
		while (pos < expression.length())
		{
			pos += countLeadingSpacesFrom(expression, pos);
			Token temp = readTokenFrom(expression, pos);

			res.push_back(temp);
			pos += temp.data.length();
		}

		for (auto& elem : res)
		{
			switch (elem.type)
			{
			case Token::Type::Numeric:
			case Token::Type::String:
				resultStack.push_back(elem);
				break;
			case Token::Type::Operator:
				if (elem.operatorType == Token::OperatorType::LeftParenthesis)
				{
					operatorStack.push_back(elem);
				}
				else if (elem.operatorType == Token::OperatorType::RightParenthesis)
				{
					bool openingBracketFlag = false;
					while (operatorStack.size())
					{
						if (operatorStack.back().operatorType == Token::OperatorType::LeftParenthesis)
						{
							operatorStack.removeLast();
							openingBracketFlag = true;
							break;
						}
						resultStack.push_back(operatorStack.back());
						operatorStack.removeLast();
					}

					if (not openingBracketFlag)
					{
						// TODO error
					}

				}
				else if (operatorStack.size() && operatorStack.back().getPriority() <= elem.getPriority())
				{
					do
					{
						resultStack.push_back(operatorStack.back());
						operatorStack.removeLast();
					} while (operatorStack.size() && operatorStack.back().getPriority() <= elem.getPriority());

					operatorStack.push_back(elem);
				}
				else
				{
					operatorStack.push_back(elem);
				}

				break;
			default:
				// TODO error
				break;
			}
		}

		return resultStack;
	}
}


QString evaluate(const QString& expression)
{
	QVector<Token> tokenList = tokenizeToPostfix(expression);

	QVector<Token> resultStack, operatorStack;

	// TODO

	if (resultStack.size() != 1)
	{
		// TODO error
	}

	return resultStack[0].data;
}