#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Expression
{
public:
	//constructors / destructor
	Expression(string exprStr) { set_expr(exprStr); }
	Expression()               { set_expr("1-1"); }
	~Expression()              { delete[] operators; }

	//main methods
	double solve();
	double solved();
	Expression& multiply(double);
	Expression& divide(double);
	Expression& subtract(double);
	Expression& add(double);

	//operators
	bool operator== (Expression expr) {
		return solved() == expr.solve();
	}
	bool operator!= (Expression expr) { 
		return solved() != expr.solve();
	}

	//setters
	bool set_expr(string);
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

	const short CNT_OF_OPERATORS = 6;
	const char* operators = new char[CNT_OF_OPERATORS]
		{'*', '/', '+', '-', '^', '%'};

	//local methods
	void clean_vector();
	bool is_operator(string);
	bool is_operator(char);
	bool is_number(string);
	char to_char(string);
	void do_action(vector<string>&, int, char);
	void apply_to_all(int, char);
};