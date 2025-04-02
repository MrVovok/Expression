#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Expression
{
public:
	//constructors
	Expression(string exprStr)
	{
		set_expr(exprStr);
	}
	Expression() : expressionStr(""), expressionVec(NULL) {}

	//main methods
	double solve();
	double solved();
	Expression& multiply(double num);
	Expression& divide(double num);
	Expression& subtract(double num);
	Expression& add(double num);

	//operators
	bool operator== (Expression expr) {
		return solve() == expr.solve();
	}
	bool operator!= (Expression expr) { 
		return solve() != expr.solve();
	}

	//setters
	void set_expr(string exprStr);
	void set_value(int index, string val) { expressionVec[index] = val; }

	//getters
	int size()                    { return expressionVec.size(); }
	string at(int index)          { return expressionVec[index]; }
	string get_string()           { return expressionStr; }
	vector<string> get_vector()   { return expressionVec; }
	vector<string> get_brackets() { return brackets; }

	//print methods
	void print_vector() {
		for (string el : expressionVec) {
			printf("[%s] ", el.c_str());
		}
		cout << "\n";
	}
	void print_brackets() {
		for_each(brackets.begin(), brackets.end(),
			[](string content) {cout << "(" << content << ") "; });
		cout << "\n";
	}
	void print_string() {
		cout << expressionStr << "\n";
	}

private:
	string expressionStr;         //string expression
	vector<string> expressionVec; //divided into parts expression
	vector<string> brackets;      //content in brackets

	//local methods
	void clean_vector();
	bool is_operator(string symbol);
	bool is_number(string symbol);
	char to_char(string symbol);
};