#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Expression
{
public:
	//������������
	Expression(string expressionStr) : expressionStr(expressionStr)
	{
		set_expr(expressionStr);
	}
	Expression() : expressionStr(""), expressionVec(NULL) {}

	//�������� �������
	double solve();
	Expression& multiply(double num);
	Expression& divide(double num);
	Expression& subtract(double num);
	Expression& add(double num);

	//���������
	bool operator== (Expression expr) {
		return solve() == expr.solve();
	}
	bool operator!= (Expression expr) { 
		return solve() != expr.solve();
	}

	//�������
	void set_expr(string exprStr);
	void set_value(int index, string val) { expressionVec[index] = val; }

	//�������
	int size()                    { return expressionVec.size(); }
	string at(int index)          { return expressionVec[index]; }
	string get_string()           { return expressionStr; }
	vector<string> get_vector()   { return expressionVec; }
	vector<string> get_brackets() { return brackets; }

	//������
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
	string expressionStr;         //��������� ������ ���������
	vector<string> expressionVec; //�������� �� ����� ���������
	vector<string> brackets;      //���������� � �������

	//���������� ������
	void clean_vector();
	bool is_operator(string symbol);
	bool is_number(string symbol);
	char to_char(string symbol);
};