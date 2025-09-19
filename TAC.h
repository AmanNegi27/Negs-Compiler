#pragma once
#include <vector>
#include <string>

inline std::vector<std::string> generateTAC(const std::string& functionName) {
	std::vector<std::string> tac;

	if (functionName == "add") {
		tac.push_back("t1 = a");
		tac.push_back("t2 = b");
		tac.push_back("t3 = t1 + t2");
		tac.push_back("return t3");
	}
	else if (functionName == "sub") {
		tac.push_back("t1 = a");
		tac.push_back("t2 = b");
		tac.push_back("t3 = t1 - t2");
		tac.push_back("return t3");
	}
	else if (functionName == "mul") {
		tac.push_back("t1 = a");
		tac.push_back("t2 = b");
		tac.push_back("t3 = t1 * t2");
		tac.push_back("return t3");
	}
	else if (functionName == "div") {
		tac.push_back("t1 = a");
		tac.push_back("t2 = b");
		tac.push_back("t3 = t1 / t2");
		tac.push_back("return t3");
	}
	else if (functionName == "mod") {
		tac.push_back("t1 = a");
		tac.push_back("t2 = b");
		tac.push_back("t3 = t1 % t2");
		tac.push_back("return t3");
	}
	else if (functionName == "pow") {
		tac.push_back("t1 = a");
		tac.push_back("t2 = b");
		tac.push_back("t3 = 1");
		tac.push_back("for i = 0 to t2-1:");
		tac.push_back("    t3 = t3 * t1");
		tac.push_back("return t3");
	}
	else if (functionName == "inc") {
		tac.push_back("t1 = a");
		tac.push_back("t2 = t1 + 1");
		tac.push_back("return t2");
	}
	else if (functionName == "dec") {
		tac.push_back("t1 = a");
		tac.push_back("t2 = t1 - 1");
		tac.push_back("return t2");
	}
	else if (functionName == "sqrt") {
		tac.push_back("t1 = a");
		tac.push_back("t2 = sqrt(t1)");
		tac.push_back("return t2");
	}
	else if (functionName == "pyt") {
		tac.push_back("t1 = a");
		tac.push_back("t2 = b");
		tac.push_back("t3 = t1 * t1");
		tac.push_back("t4 = t2 * t2");
		tac.push_back("t5 = t3 + t4");
		tac.push_back("t6 = sqrt(t5)");
		tac.push_back("return t6");
	}
	else if (functionName == "max") {
		tac.push_back("t1 = a");
		tac.push_back("t2 = b");
		tac.push_back("if t1 > t2:");
		tac.push_back("    return t1");
		tac.push_back("else:");
		tac.push_back("    return t2");
	}
	else if (functionName == "min") {
		tac.push_back("t1 = a");
		tac.push_back("t2 = b");
		tac.push_back("if t1 < t2:");
		tac.push_back("    return t1");
		tac.push_back("else:");
		tac.push_back("    return t2");
	}
	else if (functionName == "sqr_area") {
		tac.push_back("t1 = a");
		tac.push_back("t2 = t1 * t1");
		tac.push_back("return t2");
	}
	else if (functionName == "rect_area") {
		tac.push_back("t1 = a");
		tac.push_back("t2 = b");
		tac.push_back("t3 = t1 * t2");
		tac.push_back("return t3");
	}
	else if (functionName == "tri_area") {
		tac.push_back("t1 = a");
		tac.push_back("t2 = b");
		tac.push_back("t3 = (t1 * t2) / 2");
		tac.push_back("return t3");
	}
	else if (functionName == "circle_area") {
		tac.push_back("t1 = a");
		tac.push_back("t2 = 3.14");
		tac.push_back("t3 = t1 * t1 * t2");
		tac.push_back("return t3");
	}
	else if (functionName == "age") {
		tac.push_back("t1 = currentYear");
		tac.push_back("t2 = birthYear");
		tac.push_back("t3 = t1 - t2");
		tac.push_back("return t3");
	}
	else if (functionName == "CF") {
		tac.push_back("t1 = a");
		tac.push_back("t2 = (t1 * 9 / 5) + 32");
		tac.push_back("return t2");
	}
	else if (functionName == "BMI") {
		tac.push_back("t1 = a");
		tac.push_back("t2 = b");
		tac.push_back("t3 = t1 / (t2 * t2)");
		tac.push_back("return t3");
	}
	else if (functionName == "leapyear") {
		tac.push_back("t1 = a");
		tac.push_back("if (t1 % 4 == 0 && (t1 % 100 != 0 || t1 % 400 == 0)):");
		tac.push_back("    return true");
		tac.push_back("else:");
		tac.push_back("    return false");
	}
	else if (functionName == "fact") {
		tac.push_back("t1 = a");
		tac.push_back("t2 = 1");
		tac.push_back("for i = 1 to t1:");
		tac.push_back("    t2 = t2 * i");
		tac.push_back("return t2");
	}
	else if (functionName == "fib") {
		tac.push_back("t1 = 0");
		tac.push_back("t2 = 1");
		tac.push_back("i = 2");
		tac.push_back("while i < n:");
		tac.push_back("    t3 = t1 + t2");
		tac.push_back("    t1 = t2");
		tac.push_back("    t2 = t3");
		tac.push_back("    i = i + 1");
		tac.push_back("return t2");
	}
	else if (functionName == "mean") {
		tac.push_back("sum = 0");
		tac.push_back("i = 0");
		tac.push_back("while i < n:");
		tac.push_back("    sum = sum + arr[i]");
		tac.push_back("    i = i + 1");
		tac.push_back("mean = sum / n");
		tac.push_back("return mean");
	}
	else if (functionName == "mode") {
		tac.push_back("t1 = list");
		tac.push_back("t2 = frequency_count(t1)");
		tac.push_back("t3 = most_frequent_element(t2)");
		tac.push_back("return t3");
	}
	else if (functionName == "len") {
		tac.push_back("t1 = str");
		tac.push_back("t2 = length_of(t1)");
		tac.push_back("return t2");
	}
	else if (functionName == "reverse") {
		tac.push_back("t1 = string");
		tac.push_back("t2 = reverse_string(t1)");
		tac.push_back("return t2");
}

	else if (functionName == "concat") {
		tac.push_back("t1 = str1");
		tac.push_back("t2 = str2");
		tac.push_back("t3 = t1 + t2");
		tac.push_back("return t3");
	}
	else if (functionName == "replicate") {
		tac.push_back("t1 = str");
		tac.push_back("t2 = count");
		tac.push_back("t3 = replicate_string(t1, t2)");
		tac.push_back("return t3");
	}
	else if (functionName == "upper") {
		tac.push_back("t1 = str");
		tac.push_back("t2 = convert_to_uppercase(t1)");
		tac.push_back("return t2");
	}
	else if (functionName == "lower") {
		tac.push_back("t1 = str");
		tac.push_back("t2 = convert_to_lowercase(t1)");
		tac.push_back("return t2");
	}
	else if (functionName == "sum") {
		tac.push_back("t1 = n");
		tac.push_back("t2 = 0");
		tac.push_back("for i = 1 to t1 - 1:");
		tac.push_back("    t2 = t2 + i");
		tac.push_back("return t2");
	}
	else if (functionName == "abs") {
		tac.push_back("t1 = a");
		tac.push_back("if (t1 < 0):");
		tac.push_back("    t2 = -t1");
		tac.push_back("else:");
		tac.push_back("    t2 = t1");
		tac.push_back("return t2");
	}
	else if (functionName == "rev_num") {
		tac.push_back("t1 = num");
		tac.push_back("t2 = reverse_number(t1)");
		tac.push_back("return t2");
	}
	else if (functionName == "armstrong") {
		tac.push_back("t1 = num");
		tac.push_back("t2 = sum_of_cubes_of_digits(t1)");
		tac.push_back("if (t1 == t2):");
		tac.push_back("    return true");
		tac.push_back("else:");
		tac.push_back("    return false");
	}
	else if (functionName == "mul_table") {
		tac.push_back("t1 = num");
		tac.push_back("for i = 1 to 10:");
		tac.push_back("    t2 = t1 * i");
		tac.push_back("    print(t2)");
		tac.push_back("return");
	}
	else if (functionName == "sort") {
		tac.push_back("t1 = list");
		tac.push_back("t2 = n");
		tac.push_back("t3 = sort_list(t1, t2)");
		tac.push_back("return t3");
	}
	else if (functionName == "swap") {
		tac.push_back("t1 = a");
		tac.push_back("t2 = b");
		tac.push_back("temp = t1");
		tac.push_back("t1 = t2");
		tac.push_back("t2 = temp");
		tac.push_back("return t1, t2");
		}
	else if (functionName == "si") {
		tac.push_back("t1 = principal");
		tac.push_back("t2 = rate");
		tac.push_back("t3 = time");
		tac.push_back("t4 = (t1 * t2 * t3) / 100");
		tac.push_back("return t4");
	}
	else if (functionName == "search") {
		tac.push_back("t1 = list");
		tac.push_back("t2 = key");
		tac.push_back("t3 = find_key_in_list(t1, t2)");
		tac.push_back("return t3");
	}
	else if (functionName == "eo") {
		tac.push_back("t1 = num");
		tac.push_back("if (t1 % 2 == 0):");
		tac.push_back("    return true");
		tac.push_back("else:");
		tac.push_back("    return false");
	}
	else if (functionName == "count_div") {
		tac.push_back("t1 = limit");
		tac.push_back("t2 = divisor");
		tac.push_back("t3 = count_divisible(t1, t2)");
		tac.push_back("return t3");
	}
	else if (functionName == "swap") {
		tac.push_back("t1 = a");
		tac.push_back("t2 = b");
		tac.push_back("swap(t1, t2)");
		tac.push_back("return [t1, t2]");
	}
	else if (functionName == "max_arr") {
		tac.push_back("t1 = array");
		tac.push_back("t2 = n");
		tac.push_back("t3 = find_max_in_array(t1, t2)");
		tac.push_back("return t3");
	}
	else if (functionName == "min_arr") {
		tac.push_back("t1 = array");
		tac.push_back("t2 = n");
		tac.push_back("t3 = find_min_in_array(t1, t2)");
		tac.push_back("return t3");
	}
	else if (functionName == "rev_arr") {
		tac.push_back("t1 = array");
		tac.push_back("t2 = reverse_array(t1)");
		tac.push_back("return t2");
	}
	else if (functionName == "push") {
		tac.push_back("t1 = stack");
		tac.push_back("t2 = element");
		tac.push_back("push_to_stack(t1, t2)");
		tac.push_back("return t1");
	}
	else if (functionName == "pop") {
		tac.push_back("t1 = stack");
		tac.push_back("t2 = pop_from_stack(t1)");
		tac.push_back("return t1");
	}
	else if (functionName == "sum_arr") {
		tac.push_back("t1 = array");
		tac.push_back("t2 = n");
		tac.push_back("t3 = sum_array_elements(t1, t2)");
		tac.push_back("return t3");
	}
	else if (functionName == "gcd") {
		tac.push_back("t1 = a");
		tac.push_back("t2 = b");
		tac.push_back("t3 = gcd(t1, t2)");
		tac.push_back("return t3");
	}
	else if (functionName == "lcm") {
		tac.push_back("t1 = a");
		tac.push_back("t2 = b");
		tac.push_back("t3 = lcm(t1, t2)");
		tac.push_back("return t3");
	}
	else if (functionName == "to_binary") {
		tac.push_back("t1 = num");
		tac.push_back("t2 = decimal_to_binary(t1)");
		tac.push_back("return t2");
	}
	else if (functionName == "to_decimal") {
		tac.push_back("t1 = binary_str");
		tac.push_back("t2 = binary_to_decimal(t1)");
		tac.push_back("return t2");
	}

	else if (functionName == "palindrom") {
		tac.push_back("str = input");
		tac.push_back("rev = reverse(str)");
		tac.push_back("if str == rev:");
		tac.push_back("    return true");
		tac.push_back("else:");
		tac.push_back("    return false");
	}
	else if (functionName == "insert") {
		tac.push_back("i = n - 1");
		tac.push_back("while i >= pos:");
		tac.push_back("    arr[i + 1] = arr[i]");
		tac.push_back("    i = i - 1");
		tac.push_back("arr[pos] = element");
		tac.push_back("n = n + 1");
		tac.push_back("return arr");
	}
	else if (functionName == "delete") {
		tac.push_back("i = 0");
		tac.push_back("while i < n:");
		tac.push_back("    if arr[i] == element:");
		tac.push_back("        break");
		tac.push_back("    i = i + 1");
		tac.push_back("while i < n - 1:");
		tac.push_back("    arr[i] = arr[i + 1]");
		tac.push_back("    i = i + 1");
		tac.push_back("n = n - 1");
		tac.push_back("return arr");
	}

	return tac;
}
