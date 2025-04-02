#include "pch.h"
#include "framework.h"
#include "Expression.h"

//main methods
double Expression::solve() {
	for (int i = 0; i < expressionVec.size() - 1; i++) {
		if (expressionVec[i] == "*") {
			string answer = to_string(stod(expressionVec[i - 1]) * stod(expressionVec[i + 1]));
			auto it = expressionVec.begin() + (i - 1);
			expressionVec.erase(it, it + 3);
			expressionVec.insert(expressionVec.begin() + (i - 1), answer);
			solve();
		}
		else if (expressionVec[i] == "/") {
			string answer = to_string(stod(expressionVec[i - 1]) / stod(expressionVec[i + 1]));
			auto it = expressionVec.begin() + (i - 1);
			expressionVec.erase(it, it + 3);
			expressionVec.insert(expressionVec.begin() + (i - 1), answer);
			solve();
		}
	}
	for (int i = 0; i < expressionVec.size() - 1; i++) {
		if (expressionVec[i] == "+") {
			string answer = to_string(stod(expressionVec[i - 1]) + stod(expressionVec[i + 1]));
			auto it = expressionVec.begin() + (i - 1);
			expressionVec.erase(it, it + 3);
			expressionVec.insert(expressionVec.begin() + (i - 1), answer);
			solve();
		}
		else if (expressionVec[i] == "-") {
			string answer = to_string(stod(expressionVec[i - 1]) - stod(expressionVec[i + 1]));
			auto it = expressionVec.begin() + (i - 1);
			expressionVec.erase(it, it + 3);
			expressionVec.insert(expressionVec.begin() + (i - 1), answer);
			solve();
		}
	}
	//return stod(expressionVec[0]); <- to solved()
	return stod(expressionVec[0]);
}
double Expression::solved() {
	static vector<string> exprVec(expressionVec);
	for (int i = 0; i < exprVec.size() - 1; i++) {
		if (exprVec[i] == "*") {
			string answer = to_string(stod(exprVec[i - 1]) * stod(exprVec[i + 1]));
			auto it = exprVec.begin() + (i - 1);
			exprVec.erase(it, it + 3);
			exprVec.insert(exprVec.begin() + (i - 1), answer);
			solved();
		}
		else if (exprVec[i] == "/") {
			string answer = to_string(stod(exprVec[i - 1]) / stod(exprVec[i + 1]));
			auto it = exprVec.begin() + (i - 1);
			exprVec.erase(it, it + 3);
			exprVec.insert(exprVec.begin() + (i - 1), answer);
			solved();
		}
	}
	for (int i = 0; i < exprVec.size() - 1; i++) {
		if (exprVec[i] == "+") {
			string answer = to_string(stod(exprVec[i - 1]) + stod(exprVec[i + 1]));
			auto it = exprVec.begin() + (i - 1);
			exprVec.erase(it, it + 3);
			exprVec.insert(exprVec.begin() + (i - 1), answer);
			solved();
		}
		else if (exprVec[i] == "-") {
			string answer = to_string(stod(exprVec[i - 1]) - stod(exprVec[i + 1]));
			auto it = exprVec.begin() + (i - 1);
			exprVec.erase(it, it + 3);
			exprVec.insert(exprVec.begin() + (i - 1), answer);
			solved();
		}
	}
	return stod(exprVec[0]);
}
Expression& Expression::multiply(double num) {
	for_each(expressionVec.begin(), expressionVec.end(),
		[num, this](string& element) {
			if (is_number(element)) element = to_string(stod(element) * num); 
			element.erase(element.find_last_not_of('0') + 1, string::npos); //cleaning from zeros
			element.erase(element.find_last_not_of('.') + 1, string::npos); //
		});
	return *this;
}
Expression& Expression::divide(double num) {
	for_each(expressionVec.begin(), expressionVec.end(),
		[num, this](string& element) {
			if (is_number(element)) element = to_string(stod(element) / num);
			element.erase(element.find_last_not_of('0') + 1, string::npos); //cleaning from zeros
			element.erase(element.find_last_not_of('.') + 1, string::npos); //
		});
	return *this;
}
Expression& Expression::subtract(double num) {
	for_each(expressionVec.begin(), expressionVec.end(),
		[num, this](string& element) {
			if (is_number(element)) element = to_string(stod(element) - num);
			element.erase(element.find_last_not_of('0') + 1, string::npos); //cleaning from zeros
			element.erase(element.find_last_not_of('.') + 1, string::npos); //
		});
	return *this;
}
Expression& Expression::add(double num) {
	for_each(expressionVec.begin(), expressionVec.end(),
		[num, this](string& element) {
			if (is_number(element)) element = to_string(stod(element) + num);
			element.erase(element.find_last_not_of('0') + 1, string::npos); //cleaning from zeros
			element.erase(element.find_last_not_of('.') + 1, string::npos); //
		});
	return *this;
}

//setters
void Expression::set_expr(string exprStr) {
	try {
		expressionStr = exprStr;
		string tmpExprStr;
		for (int i = 0; i <= expressionStr.length(); i++) {
			if (isdigit(expressionStr[i]) || expressionStr[i] == '.')
				tmpExprStr += expressionStr[i];
			else if (expressionStr[i] == '(') {
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
					if (i + 1 == expressionStr.length()) throw "missing ')'";
					//cout << "cnt: " << cnt << "\n";
				}
				brackets.push_back(underExprStr);
				Expression expression(underExprStr);
				string ans = to_string(expression.solve());
				ans.erase(ans.find_last_not_of('0') + 1, string::npos); 
				ans.erase(ans.find_last_not_of('.') + 1, string::npos); 
				expressionVec.push_back(ans);
			}
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
		cout << "Error: " << message << "\n";
		return;
	}
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
	const char* operators = new char[4] {'*', '/', '+', '-'};
	if (symbol.length() != 1) return false;
	for (int j = 0; j < 4; j++) {
		if (to_char(symbol) == operators[j]) return true;
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

