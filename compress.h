#pragma once
#include <iostream>
#include <regex>
#include <sstream>

bool is_upper(const std::string& string)
{
	return string[0] == toupper(string[0]);
}
bool is_all_upper(const std::string& string)
{
	int count = std::count_if(string.begin(), string.end(), [](char c){return c >= 'A' && c <= 'Z'; });
	if (count != 1 && count != string.size())
		throw std::runtime_error("Incorrect capitalisation.");
	if (string.size() == 1)
		return false;
	for (auto& c : string)
	{
		if (c == tolower(c))
			return false;
	}
	return true;
}
void testCase(const std::string& string)
{
	for (size_t i = 1; i < string.size() - 1; ++i)
		if (string[i] == toupper(string[i]))
			throw std::runtime_error("Incorrect capitalisation or unexpected character in string.");
}
void addToDictionary(const std::string& s, std::vector<std::string>& dict, std::stringstream& ss)
{
	std::string string{ s };
	for (auto& letter : string)
		letter = tolower(letter);
	auto search = std::find(dict.begin(), dict.end(), string);
	if (search != dict.end())
		ss << std::distance(dict.begin(), search);
	else
	{
		dict.push_back(string);
		ss << dict.size() - 1;
	}
	if (is_upper(s) && is_all_upper(s))
		ss << "!";
	else if (is_upper(s) && !is_all_upper(s))
		ss << "^";
	else
		testCase(s);
	ss << " ";
}

std::string print(const std::vector<std::string>& dict)
{
	std::stringstream ss;
	ss << dict.size() << std::endl;
	for (auto& el : dict)
		 ss << el << std::endl;
	return ss.str();
}

std::string compress(std::string& input, std::vector<std::string>& dictionary)
{
	std::regex mismatch(R"([^\n\w\s,.?;!:-]|[,.?;!:\-][,.?;!:\-]+)");
	if (std::regex_search(input, mismatch))
		throw std::exception("Multiple symbols next to each other or unexpected characters found.");
	std::regex reg(R"(\w+|[.,\?;!\:\n\-])");
	std::stringstream output;
	std::sregex_iterator it(input.begin(), input.end(), reg);
	std::sregex_iterator end;
	for (; it != end; ++it)
	{
		auto find = it->str().find_first_of(",.?;:!-");
		if (find != std::string::npos)
			output << it->str() << " ";
		else if (!it->str().empty())
		{
			if (it->str() == "\n")
				output << "R ";
			else
				addToDictionary(it->str(), dictionary, output);
		}
	}
	return output.str();
}
