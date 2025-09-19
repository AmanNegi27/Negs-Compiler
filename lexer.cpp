#include "lexer.h"
#include <regex>
#include <algorithm>
#include <unordered_set>
#include <iostream> 

const std::unordered_set<std::string> keywords = { "craft", "give", "echo", "set", "int", "as", "add", "sub", "mul", "div", "mod", "log","fact","pow","sqrt","inc","dec","pyt","lcm","max","min","sqr_area","rect_area","tri-area","circle_area","to_binary","to_decimal","age","CF","BMI","gcd","leapyear","mean","mode","fib","len","upper","lower","sum","abs","reverse","rev_num","armstrong","mul_table","eo","concat","palindrom","count_div","swap","max_arr","min_arr","rev_arr","push","pop","sum_arr","sort","search","insert","delete","si","mul_table","replicate" };

std::vector<Token> tokenize(const std::string& code) {
	std::vector<Token> tokens;

	std::regex tokenPatterns(R"(\b(craft|give|echo|set|int|as|add|sub|mul|div|mod|fact|pow|sqrt|inc|dec|pyt|log|max|min|sqr_area|rect_area|tri_area|circle_area|age|CF|BMI|gcd|lcm|to_binary|to_decimal|leapyear|mean|mode|fib|len|upper|lower|sum|abs|reverse|rev_num|armstrong|mul_table|eo|concat|palindrom|count_div|max-arr|min_arr|rev_arr|push|pop|sum_arr|sort|search|insert|delete|si|mul_table)\b|[a-zA-Z_]\w*|\d+(\.\d+)?|[=+*/%-{}(),;\[\]])");
	std::sregex_iterator iter(code.begin(), code.end(), tokenPatterns);
	std::sregex_iterator end;

	while (iter != end) {
		std::string match = iter->str();
		Token token;

		std::cout << "DEBUG: Token found -> " << match << std::endl;

		if (keywords.find(match) != keywords.end()) {
			token.type = TOKEN_KEYWORD;
		}
		else if (std::regex_match(match, std::regex(R"(\d+(\.\d+)?)"))) {
			token.type = TOKEN_LITERAL;
		}
		else if (std::regex_match(match, std::regex(R"([a-zA-Z_]\w*)"))) {
			token.type = TOKEN_IDENTIFIER;
		}
		else if (std::regex_match(match, std::regex(R"(=|\+|\-|\*|\/|\%)"))) {
			token.type = TOKEN_OPERATOR;
		}
		else if (match == "{" || match == "}" || match == "(" || match == ")" || match == "[" || match == "]") {
			token.type = TOKEN_BRACKET;
		}
		else if (match == ";" || match == ",") {
			token.type = TOKEN_DELIMITER;
		}
		else if (match.rfind("//", 0) == 0 || match.rfind("/*", 0) == 0) {
			token.type = TOKEN_COMMENT;
		}
		else {
			token.type = TOKEN_UNKNOWN;
		}

		token.value = match;
		tokens.push_back(token);
		++iter;
	}

	return tokens;
}

bool isKeyword(const std::string& word) {
	return keywords.find(word) != keywords.end();
}
