#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <regex>
#include <cmath>
#include <unordered_map>
#include <algorithm>
#include <cctype>


struct EvalResult {
	enum class Type { Number, String, Boolean, List } type;
	double number = 0.0;
	std::string str;
	bool bool_value = false;
	std::vector<double> list;
};

class ExpressionEvaluator {
public:
	static EvalResult evaluate(const std::string& expression) {
		
		std::regex pattern(R"(^\s*craft\s+(\w+)\s*\(\s*(\[.*?\]|-?\d*\.?\d+|"[^"]*")\s*(?:,\s*(\[.*?\]|-?\d*\.?\d+|"[^"]*"))?\s*(?:,\s*(\[.*?\]|-?\d*\.?\d+|"[^"]*"))?\s*\)\s*$)");

		std::smatch matches;

		if (!std::regex_match(expression, matches, pattern)) {
			throw std::invalid_argument("Invalid expression format");
		}

		std::string operation = matches[1];
		std::string arg1Str = matches[2];
		std::string arg2Str = matches[3].matched ? matches[3].str() : "";

		EvalResult result;

		auto isQuotedString = [](const std::string& s) {
			return s.size() >= 2 && s.front() == '"' && s.back() == '"';
			};

		// ---------- STRING FUNCTIONS ----------
		if (isQuotedString(arg1Str)) {
			std::string strArg1 = arg1Str.substr(1, arg1Str.size() - 2);
			std::string strArg2 = isQuotedString(arg2Str) ? arg2Str.substr(1, arg2Str.size() - 2) : "";

			if (operation == "len") {
				result.type = EvalResult::Type::Number;
				result.number = static_cast<double>(strArg1.length());
			}
			else if (operation == "upper") {
				std::transform(strArg1.begin(), strArg1.end(), strArg1.begin(), ::toupper);
				result.type = EvalResult::Type::String;
				result.str = strArg1;
			}
			else if (operation == "lower") {
				std::transform(strArg1.begin(), strArg1.end(), strArg1.begin(), ::tolower);
				result.type = EvalResult::Type::String;
				result.str = strArg1;
			}
			else if (operation == "reverse") {
				std::reverse(strArg1.begin(), strArg1.end());
				result.type = EvalResult::Type::String;
				result.str = strArg1;
			}
			else if (operation == "concat") {
				result.type = EvalResult::Type::String;
				result.str = strArg1 + strArg2;
			}
			else if (operation == "palindrom") {
				bool isPalin = true;
				int start = 0, end = strArg1.size() - 1;
				while (start < end) {
					if (strArg1[start++] != strArg1[end--]) {
						isPalin = false;
						break;
					}
				}
				result.type = EvalResult::Type::Boolean;
				result.bool_value = isPalin;
			}
			else if (operation == "replicate") {
				if (strArg1.empty() || arg2Str.empty())
					throw std::invalid_argument("replication requires a string and a number");

				int n = std::stoi(arg2Str);
				if (n < 0) throw std::invalid_argument("Negative replication count not allowed");

				std::string replicated;
				for (int i = 0; i < n; ++i) {
					replicated += strArg1;
				}

				result.type = EvalResult::Type::String;
				result.str = replicated;
			}

			else {
				throw std::invalid_argument("Unknown string function: " + operation);
			}
			return result;
		}

		// ---------- LIST FUNCTIONS ----------
		if (arg1Str.front() == '[') {
			std::vector<double> numbers;
			std::string listContent = arg1Str.substr(1, arg1Str.size() - 2);
			std::stringstream ss(listContent);
			std::string item;

			while (std::getline(ss, item, ',')) {
				item.erase(remove_if(item.begin(), item.end(), ::isspace), item.end());
				if (!item.empty()) numbers.push_back(std::stod(item));
			}

			if (operation == "mean") {
				if (numbers.empty()) throw std::runtime_error("List is empty.");
				double sum = 0;
				for (double d : numbers) sum += d;
				result.type = EvalResult::Type::Number;
				result.number = sum / numbers.size();
			}
			else if (operation == "mode") {
				std::unordered_map<double, int> freq;
				double modeVal = numbers[0];
				int maxCount = 0;
				for (double d : numbers) {
					freq[d]++;
					if (freq[d] > maxCount) {
						maxCount = freq[d];
						modeVal = d;
					}
				}
				result.type = EvalResult::Type::Number;
				result.number = modeVal;
			}
			else if (operation == "max_arr") {
				result.type = EvalResult::Type::Number;
				result.number = *std::max_element(numbers.begin(), numbers.end());
			}
			else if (operation == "min_arr") {
				result.type = EvalResult::Type::Number;
				result.number = *std::min_element(numbers.begin(), numbers.end());
			}
			else if (operation == "rev_arr") {
				std::reverse(numbers.begin(), numbers.end());
				result.type = EvalResult::Type::List;
				result.list = numbers;
			}
			else if (operation == "push") {
				// arg2 is value to push
				if (arg2Str.empty()) throw std::invalid_argument("push requires a second argument");
				double value = std::stod(arg2Str);
				numbers.push_back(value);
				result.type = EvalResult::Type::List;
				result.list = numbers;
			}
			else if (operation == "pop") {
				if (arg1Str.front() != '[')
					throw std::invalid_argument("pop requires a list.");

				std::vector<double> stack;
				std::string listContent = arg1Str.substr(1, arg1Str.size() - 2);
				std::stringstream ss(listContent);
				std::string item;

				while (std::getline(ss, item, ',')) {
					item.erase(remove_if(item.begin(), item.end(), ::isspace), item.end());
					if (!item.empty()) stack.push_back(std::stod(item));
				}

				if (stack.empty()) {
					throw std::runtime_error("Stack underflow: Cannot pop from an empty stack.");
				}

				stack.pop_back(); // ✅ POP operation

				result.type = EvalResult::Type::List;
				result.list = stack;
			}
			else if (operation == "sum_arr") {
				if (arg1Str.front() != '[')
					throw std::invalid_argument("sum_arr requires a list as the first argument.");

				if (arg2Str.empty())
					throw std::invalid_argument("sum_arr requires a size as the second argument.");

				std::vector<double> numbers;
				std::string listContent = arg1Str.substr(1, arg1Str.size() - 2);
				std::stringstream ss(listContent);
				std::string item;

				while (std::getline(ss, item, ',')) {
					item.erase(remove_if(item.begin(), item.end(), ::isspace), item.end());
					if (!item.empty()) numbers.push_back(std::stod(item));
				}

				int expectedSize = std::stoi(arg2Str);
				if (numbers.size() != expectedSize) {
					throw std::runtime_error("List size does not match the given count.");
				}

				double sum = 0;
				for (double val : numbers) sum += val;

				result.type = EvalResult::Type::Number;
				result.number = sum;
			}
			else if (operation == "sort") {
				if (arg1Str.front() != '[')
					throw std::invalid_argument("sort requires a list as the first argument.");

				if (arg2Str.empty())
					throw std::invalid_argument("sort requires a size as the second argument.");

				std::vector<double> numbers;
				std::string listContent = arg1Str.substr(1, arg1Str.size() - 2);
				std::stringstream ss(listContent);
				std::string item;

				while (std::getline(ss, item, ',')) {
					item.erase(remove_if(item.begin(), item.end(), ::isspace), item.end());
					if (!item.empty()) numbers.push_back(std::stod(item));
				}

				int expectedSize = std::stoi(arg2Str);
				if (numbers.size() != expectedSize) {
					throw std::runtime_error("List size does not match the given count.");
				}

				// Bubble Sort
				for (int i = 0; i < expectedSize; ++i) {
					for (int j = 0; j < expectedSize - i - 1; ++j) {
						if (numbers[j] > numbers[j + 1]) {
							std::swap(numbers[j], numbers[j + 1]);
						}
					}
				}

				result.type = EvalResult::Type::List;
				result.list = numbers;
			}
			else if (operation == "search") {
				if (arg2Str.empty())
					throw std::invalid_argument("search requires a second argument (key to find)");

				double key = std::stod(arg2Str);
				int index = -1;
				for (size_t i = 0; i < numbers.size(); ++i) {
					if (numbers[i] == key) {
						index = static_cast<int>(i);
						break;
					}
				}

				result.type = EvalResult::Type::Number;
				result.number = static_cast<double>(index);
			}
			else if (operation == "insert") {
				// Manually extract the third argument from the expression
				std::regex insertPattern(R"(craft\s+insert\s*\(\s*(\[.*?\])\s*,\s*(-?\d+)\s*,\s*(-?\d+)\s*\))");
				std::smatch insertMatches;

				if (!std::regex_match(expression, insertMatches, insertPattern)) {
					throw std::invalid_argument("insert requires a list, position, and value.");
				}

				std::string listStr = insertMatches[1];
				int position = std::stoi(insertMatches[2]);
				double value = std::stod(insertMatches[3]);

				// Parse the list
				std::vector<double> numbers;
				std::string listContent = listStr.substr(1, listStr.size() - 2);
				std::stringstream ss(listContent);
				std::string item;

				while (std::getline(ss, item, ',')) {
					item.erase(remove_if(item.begin(), item.end(), ::isspace), item.end());
					if (!item.empty()) numbers.push_back(std::stod(item));
				}

				// Insert value
				if (position < 0 || position > numbers.size()) {
					throw std::out_of_range("Insert position is out of range.");
				}
				numbers.insert(numbers.begin() + position, value);

				result.type = EvalResult::Type::List;
				result.list = numbers;
			}

			else if (operation == "delete") {
				if (arg2Str.empty()) throw std::invalid_argument("delete requires a number to be deleted");

				double valueToDelete = std::stod(arg2Str);

				// Remove all occurrences of the value
				numbers.erase(std::remove(numbers.begin(), numbers.end(), valueToDelete), numbers.end());

				result.type = EvalResult::Type::List;
				result.list = numbers;
			}

			else {
				throw std::invalid_argument("Unknown list function: " + operation);
			}
			return result;
		}

		// ---------- NUMBER FUNCTIONS ----------
		double arg1 = std::stod(arg1Str);
		double arg2 = arg2Str.empty() ? 0 : std::stod(arg2Str);

		result.type = EvalResult::Type::Number;

		if (operation == "add") {
			
			result.number = arg1+arg2;
		}
		else if (operation == "sub") result.number = arg1 - arg2;
		else if (operation == "mul") result.number = arg1 * arg2;
		else if (operation == "div") {
			if (arg2 == 0) throw std::runtime_error("Division by zero");
			result.number = arg1 / arg2;
		}
		else if (operation == "mod") {
			if (arg2 == 0) throw std::runtime_error("Modulo by zero");
			result.number = std::fmod(arg1, arg2);
		}
		else if (operation == "pow") result.number = std::pow(arg1, arg2);
		else if (operation == "sqrt") result.number = std::sqrt(arg1);
		else if (operation == "fact") {
			if (arg1 < 0) throw std::runtime_error("Negative factorial");
			int fact = 1;
			for (int i = 1; i <= static_cast<int>(arg1); ++i) fact *= i;
			result.number = fact;
		}
		else if (operation == "pyt") result.number = std::sqrt(arg1 * arg1 + arg2 * arg2);
		else if (operation == "max") result.number = std::fmax(arg1, arg2);
		else if (operation == "min") result.number = std::fmin(arg1, arg2);
		else if (operation == "sqr_area") result.number = arg1 * arg1;
		else if (operation == "rect_area") result.number = arg1 * arg2;
		else if (operation == "tri_area") result.number = 0.5 * arg1 * arg2;
		else if (operation == "circle_area") result.number = 3.141592653589793 * arg1 * arg1;
		else if (operation == "age") result.number = arg2 - arg1;
		else if (operation == "inc") result.number= arg1 + 1;
		else if (operation == "dec") result.number = arg1 - 1;

		else if (operation == "age") {
			result.number = arg2 - arg1;
		}
		else if (operation == "CF") {
			result.number = (arg1 * 9.0 / 5.0) + 32;
		}
		else if (operation == "BMI") {
			if (arg2 == 0) throw std::runtime_error("Height cannot be zero in BMI calculation");
			result.number = arg1 / (arg2 * arg2);
		}
		else if (operation == "leapyear") {
			int year = static_cast<int>(arg1);
			result.type = EvalResult::Type::Boolean;
			result.bool_value = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
		}
		else if (operation == "fib") {
			if (arg1 < 0) throw std::runtime_error("Fibonacci not defined for negative numbers.");
			int n = static_cast<int>(arg1);
			if (n == 0) result.number = 0;
			else if (n == 1) result.number = 1;
			else {
				int a = 0, b = 1, c = 0;
				for (int i = 2; i <= n; ++i) {
					c = a + b;
					a = b;
					b = c;
				}
				result.number = b;
			}
		}
		else if (operation == "eo") {
			int num = static_cast<int>(arg1);
			result.type = EvalResult::Type::String;
			result.str = (num % 2 == 0) ? "Even" : "Odd";
		}
		else if (operation == "count_div") {
			if (arg2 == 0) throw std::runtime_error("Division by zero is not allowed.");
			int n = static_cast<int>(arg1);
			int k = static_cast<int>(arg2);
			int count = 0;
			for (int i = 1; i <= n; ++i) {
				if (i % k == 0) count++;
			}
			result.type = EvalResult::Type::Number;
			result.number = static_cast<double>(count);
		}
		else if (operation == "swap") {
			double a = arg1;
			double b = arg2;

			a = a + b;
			b = a - b;
			a = a - b;

			result.type = EvalResult::Type::List;
			result.list = { a, b };
		}
		else if (operation == "si") {
			if (arg1Str.empty() || arg2Str.empty())
				throw std::invalid_argument("si requires three arguments: principal, rate, and time");
			std::regex threeArgPattern(R"(\(\s*(\-?\d*\.?\d+)\s*,\s*(\-?\d*\.?\d+)\s*,\s*(\-?\d*\.?\d+)\s*\))");
			std::smatch argMatch;
			if (!std::regex_search(expression, argMatch, threeArgPattern))
				throw std::invalid_argument("Invalid format for si");

			double principal = std::stod(argMatch[1]);
			double rate = std::stod(argMatch[2]);
			double time = std::stod(argMatch[3]);

			double si = (principal * rate * time) / 100.0;

			result.type = EvalResult::Type::Number;
			result.number = si;
		}
		else if (operation == "mul_table") {
			if (arg1Str.empty())
				throw std::invalid_argument("mul_table requires one argument");

			double n = std::stod(arg1Str);
			std::vector<double> table;

			for (int i = 1; i <= 10; ++i) {
				table.push_back(n * i);
			}

			result.type = EvalResult::Type::List;
			result.list = table;
		}
		else if (operation == "armstrong") {
			if (arg1Str.empty())
				throw std::invalid_argument("armstrong requires one argument");

			int num = std::stoi(arg1Str);
			int originalNum = num;
			int sum = 0;

			// Count number of digits
			int digits = 0;
			int temp = num;
			while (temp > 0) {
				temp /= 10;
				digits++;
			}

			// Calculate sum of powered digits
			temp = num;
			while (temp > 0) {
				int digit = temp % 10;
				sum += std::pow(digit, digits);
				temp /= 10;
			}

			result.type = EvalResult::Type::Boolean;
			result.bool_value = (sum == originalNum);
		}
		else if (operation == "rev_num") {
			if (arg1Str.empty())
				throw std::invalid_argument("reverse_num requires one argument");

			int num = std::stoi(arg1Str);
			int reversed = 0;

			while (num != 0) {
				int digit = num % 10;
				reversed = reversed * 10 + digit;
				num /= 10;
			}

			result.type = EvalResult::Type::Number;
			result.number = reversed;
		}
		else if (operation == "sum") {
			if (arg1Str.empty())
				throw std::invalid_argument("sum requires one argument");

			int n = std::stoi(arg1Str);
			int total = 0;

			for (int i = 1; i <= n; ++i) {
				total += i;
			}

			result.type = EvalResult::Type::Number;
			result.number = total;
		}
		else if (operation == "fact") {
			if (arg1Str.empty()) throw std::invalid_argument("fact requires a number argument");
			int n = std::stoi(arg1Str);
			if (n < 0) throw std::invalid_argument("Factorial of negative number not defined.");

			double factorial = 1;
			for (int i = 1; i <= n; ++i) {
				factorial *= i;
			}

			result.type = EvalResult::Type::Number;
			result.number = factorial;
		}
		else if (operation == "gcd") {
			if (arg1Str.empty() || arg2Str.empty())
				throw std::invalid_argument("gcd requires two numeric arguments");

			int a = static_cast<int>(std::stod(arg1Str));
			int b = static_cast<int>(std::stod(arg2Str));

			while (b != 0) {
				int temp = b;
				b = a % b;
				a = temp;
			}

			result.type = EvalResult::Type::Number;
			result.number = static_cast<double>(a);
		}
		else if (operation == "lcm") {
			if (arg1Str.empty() || arg2Str.empty())
				throw std::invalid_argument("lcm requires two numeric arguments");

			int a = static_cast<int>(std::stod(arg1Str));
			int b = static_cast<int>(std::stod(arg2Str));

			if (a == 0 || b == 0) {
				result.number = 0;
			}
			else {
				// Compute GCD first
				int gcdVal = a;
				int temp = b;
				while (temp != 0) {
					int t = temp;
					temp = gcdVal % temp;
					gcdVal = t;
				}
				int lcmVal = std::abs(a * b) / gcdVal;
				result.number = static_cast<double>(lcmVal);
			}

			result.type = EvalResult::Type::Number;
		}
		else if (operation == "to_binary") {
			int decimal = static_cast<int>(std::stod(arg1Str));
			std::string binary = "";

			if (decimal == 0) binary = "0";
			else {
				while (decimal > 0) {
					binary = std::to_string(decimal % 2) + binary;
					decimal /= 2;
				}
			}

			result.type = EvalResult::Type::String;
			result.str = binary;
		}
		else if (operation == "to_decimal") {
			std::string binaryStr = arg1Str;
			binaryStr.erase(remove_if(binaryStr.begin(), binaryStr.end(), ::isspace), binaryStr.end());

			int decimal = 0;
			for (char bit : binaryStr) {
				if (bit != '0' && bit != '1') {
					throw std::invalid_argument("Invalid binary number.");
				}
				decimal = decimal * 2 + (bit - '0');
			}

			result.type = EvalResult::Type::Number;
			result.number = static_cast<double>(decimal);
		}
		else if (operation == "log") {
			double number = std::stod(arg1Str);
			if (number <= 0) throw std::invalid_argument("log10 requires positive number.");
			result.type = EvalResult::Type::Number;
			result.number = std::log10(number);
		}

		else {
			throw std::invalid_argument("Unknown function: " + operation);
		}

		return result;
	}
};