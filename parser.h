#pragma once
#include <string>
#include <stack>
#include <cctype>
#include <stdexcept>
#include <unordered_map>
#include "expression.h"

class Parser {
public:
	static double evaluateExpression(const std::string& expression) {
		std::stack<double> values;
		std::stack<char> ops;
		std::unordered_map<char, int> precedence = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'%', 2} };

		auto applyOperation = [](double a, double b, char op) -> double {
			switch (op) {
			case '+': return a + b;
			case '-': return a - b;
			case '*': return a * b;
			case '/': if (b == 0) throw std::runtime_error("Division by zero"); return a / b;
			case '%': if (b == 0) throw std::runtime_error("Modulo by zero"); return std::fmod(a, b);
			default: throw std::invalid_argument("Unknown operator");
			}
			};

		for (size_t i = 0; i < expression.length(); i++) {
			if (std::isspace(expression[i])) continue;

			if (std::isdigit(expression[i]) || expression[i] == '.') {
				size_t j = i;
				while (j < expression.length() && (std::isdigit(expression[j]) || expression[j] == '.')) j++;
				values.push(std::stod(expression.substr(i, j - i)));
				i = j - 1;
			}
			else if (expression[i] == '(') {
				ops.push(expression[i]);
			}
			else if (expression[i] == ')') {
				while (!ops.empty() && ops.top() != '(') {
					double val2 = values.top(); values.pop();
					double val1 = values.top(); values.pop();
					char op = ops.top(); ops.pop();
					values.push(applyOperation(val1, val2, op));
				}
				ops.pop(); // Remove '(' from stack
			}
			else if (precedence.count(expression[i])) {
				while (!ops.empty() && precedence[ops.top()] >= precedence[expression[i]]) {
					double val2 = values.top(); values.pop();
					double val1 = values.top(); values.pop();
					char op = ops.top(); ops.pop();
					values.push(applyOperation(val1, val2, op));
				}
				ops.push(expression[i]);
			}
		}

		while (!ops.empty()) {
			double val2 = values.top(); values.pop();
			double val1 = values.top(); values.pop();
			char op = ops.top(); ops.pop();
			values.push(applyOperation(val1, val2, op));
		}

		return values.top();
	}
};
