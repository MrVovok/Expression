#include "pch.h"
#include "framework.h"
#include "Expression.h"

//main methods
double Expression::solve() {
	for (int i = 0; i < expressionVec.size() - 1; i++) {
		if (expressionVec[i] == "^") {
			do_action(expressionVec, i, '^');
			solve();
		}
	}
	for (int i = 0; i < expressionVec.size() - 1; i++) {
		if (expressionVec[i] == "*") {
			do_action(expressionVec, i, '*');
			solve();
		}
		else if (expressionVec[i] == "/") {
			do_action(expressionVec, i, '/');
			solve();
		}
		else if (expressionVec[i] == "%") {
			do_action(expressionVec, i, '%');
			solve();
		}
	}
	for (int i = 0; i < expressionVec.size() - 1; i++) {
		if (expressionVec[i] == "+") {
			do_action(expressionVec, i, '+');
			solve();
		}
		else if (expressionVec[i] == "-") {
			do_action(expressionVec, i, '-');
			solve();
		}
	}
	//return stod(expressionVec[0]); <- to solved()
	return stod(expressionVec[0]);
}
double Expression::solved() {
	static vector<string> exprVec(expressionVec);
	for (int i = 0; i < exprVec.size() - 1; i++) {
		if (exprVec[i] == "^") {
			do_action(exprVec, i, '^');
			solved();
		}
	}
	for (int i = 0; i < exprVec.size() - 1; i++) {
		if (exprVec[i] == "*") {
			do_action(exprVec, i, '*');
			solved();
		}
		else if (exprVec[i] == "/") {
			do_action(exprVec, i, '/');
			solved();
		}
		else if (exprVec[i] == "%") {
			do_action(exprVec, i, '%');
			solved();
		}
	}
	for (int i = 0; i < exprVec.size() - 1; i++) {
		if (exprVec[i] == "+") {
			do_action(exprVec, i, '+');
			solved();
		}
		else if (exprVec[i] == "-") {
			do_action(exprVec, i, '-');
			solved();
		}
	}
	return stod(exprVec[0]);
}
Expression& Expression::multiply(double num) {
	apply_to_all(num, '*');
	return *this;
}
Expression& Expression::divide(double num) {
	apply_to_all(num, '/');
	return *this;
}
Expression& Expression::subtract(double num) {
	apply_to_all(num, '-');
	return *this;
}
Expression& Expression::add(double num) {
	apply_to_all(num, '+');
	return *this;
}

//setters
bool Expression::set_expr(string exprStr) {
	try {
		expressionStr = exprStr;
		expressionVec.clear();
		int cntBrClosed = count(expressionStr.begin(), expressionStr.end(), ')');
		int cntBrOpened = count(expressionStr.begin(), expressionStr.end(), '(');
		if (cntBrClosed > cntBrOpened) throw "missing '('";
		if (cntBrClosed < cntBrOpened) throw "missing ')'";
		if (is_operator(*(expressionStr.end() - 1))) throw "missing last number";
		if (is_operator(expressionStr[0])) throw "missing first number";
		string tmpExprStr;
		for (int i = 0; i <= expressionStr.length(); i++) {
			if (isdigit(expressionStr[i]) || expressionStr[i] == '.') {
				tmpExprStr += expressionStr[i];
				if (stod(tmpExprStr) > DBL_MAX) throw "number is too long";
			}
			else if (expressionStr[i] == '(') {
				if (expressionStr[i + 1] == ')') throw "empty bracket";
				string underExprStr;
				unsigned cnt = 0;
				while (1) { //expressionStr[i + 1] != ')'
					underExprStr += expressionStr[++i];
					switch (expressionStr[i])
					{
					case '(': cnt++; break;
					case ')': cnt--; break;
					}
					if (expressionStr[i + 1] == ')' && cnt == 0) break;
					//if (i + 1 == expressionStr.length()) throw "missing ')'";
					//cout << "cnt: " << cnt << "\n";
				}
				brackets.push_back(underExprStr);
				Expression expression;
				if (expression.set_expr(underExprStr)) throw "in bracket";
				string ans = to_string(expression.solve());
				ans.erase(ans.find_last_not_of('0') + 1, string::npos);
				ans.erase(ans.find_last_not_of('.') + 1, string::npos);
				expressionVec.push_back(ans);
			}
			else if (!is_operator(expressionStr[i]) &&
					 expressionStr[i] != ' ' &&
					 i != expressionStr.length() &&
					 expressionStr[i] != ')')
				throw "wrong operator";
			else if (is_operator(expressionStr[i]) && is_operator(expressionStr[i + 1]))
				throw "repeating operators";
			else {
				expressionVec.push_back(tmpExprStr);
				tmpExprStr = expressionStr[i];
				expressionVec.push_back(tmpExprStr);
				tmpExprStr = "";
			}
		}
		clean_vector();
	}
	catch (const char* message) {
		cout << "<!> Expression error: " << message << " <!>\n";
		set_expr("1-1");
		return true;
	}
	return false;
}

//local methods
void Expression::clean_vector() {
	auto deleted = remove_if(expressionVec.begin(), expressionVec.end(),
		[this](string element) {
			if (!is_number(element) && !is_operator(element)) return true;
			return false;
		});
	expressionVec.erase(deleted, expressionVec.end());

}
bool Expression::is_operator(string symbol) {
	if (symbol.length() != 1) return false;
	for (int j = 0; j < CNT_OF_OPERATORS; j++) {
		if (to_char(symbol) == operators[j]) return true;
	}
	return false;
}
bool Expression::is_operator(char symbol) {
	for (int j = 0; j < CNT_OF_OPERATORS; j++) {
		if (symbol == operators[j]) return true;
	}
	return false;
}
bool Expression::is_number(string symbol) {
	try {
		if (stod(symbol)) return true;
		return false;
	}
	catch (...) {
		return false;
	}
}
char Expression::to_char(string symbol) {
	try {
		if (symbol.length() != 1) throw "ti ebanat???";
		return symbol.c_str()[0];
	}
	catch (const char* message) {
		cout << message;
		return 0;
	}
}
void Expression::do_action(vector<string>& expr, int index, char action) {
	string answer;
	switch (action)
	{
	case '*':
		answer = to_string(stod(expr[index - 1]) * stod(expr[index + 1]));
		break;
	case '/':
		answer = to_string(stod(expr[index - 1]) / stod(expr[index + 1]));
		break;
	case '+':
		answer = to_string(stod(expr[index - 1]) + stod(expr[index + 1]));
		break;
	case '-':
		answer = to_string(stod(expr[index - 1]) - stod(expr[index + 1]));
		break;
	case '^':
		answer = to_string(pow(stod(expr[index - 1]), stod(expr[index + 1])));
		break;
	case '%':
		answer = to_string((int)round(stod(expr[index - 1])) % (int)round(stod(expr[index + 1])));
		break;
	}
	auto it = expr.begin() + (index - 1);
	expr.erase(it, it + 3);
	expr.insert(expr.begin() + (index - 1), answer);
}
void Expression::apply_to_all(int num, char action) {
	for_each(expressionVec.begin(), expressionVec.end(),
		[num, this, action](string& element) {
			if (is_number(element)) {
				switch (action)
				{
				case '*':
					element = to_string(stod(element) * num);
					break;
				case '/':
					element = to_string(stod(element) / num);
					break;
				case '+':
					element = to_string(stod(element) + num);
					break;
				case '-':
					element = to_string(stod(element) - num);
					break;
				case '^':
					element = to_string(pow(stod(element), num));
					break;
				}
				element.erase(element.find_last_not_of('0') + 1, string::npos);
				element.erase(element.find_last_not_of('.') + 1, string::npos);
			}
		});
}
