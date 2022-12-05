#include <QString>
#include <QRegularExpression>
#include <QJSEngine>

namespace
{
	QVector<QString> tokenize(const QString& expression)
	{
		QVector<QString> res;

		// Token pattern
		QRegularExpression re(R"re((["'](?:\\['"]|[^\'\"])*["']|[a-zA-Z_][\w_]*|[\*\+\-\^\/\%\&\|\!]{1,2}|\d+(\.\d+)?))re");

		QRegularExpressionMatch match = re.match(expression);


		if (match.hasMatch()) {
			for (qsizetype i = 1; i < match.capturedTexts().size(); ++i)
			{
				res.push_back(match.captured(i));
			}
		}

		return res;
	}
}

QString evaluate(const QString& expression, QJSEngine& evaluationEngine)
{
	QVector<QString> tokenList = tokenize(expression);
	QString res = "";

	if (not tokenList.empty())
	{
		//QJSEngine evaluationEngine;
		// TODO
		// Look up for variables and substitute them before passing them to engine
		// Look up for variables and instantiate them inside the engine (evaluationEngine.globalObject().setProperty("variableName", value);)
		// Substitute `\"` and `\'` for `\\"` `\\'` respectively.. Maybe?

		QString expressionForEngine = "";

		for (const auto& elem : tokenList)
		{
			expressionForEngine += elem;
		}

		const QJSValue evaluationResult = evaluationEngine.evaluate(expressionForEngine);
		res = evaluationResult.toString();
	}

	return res;
}