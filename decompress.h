#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <regex>

std::string decomp(std::vector<std::string>& dict, const std::string& input)
{
	std::regex reg{ R"((\d+)([!\^]+)|([!\-,.;\:\?RE])|(\d+))" };
	auto end = std::sregex_iterator();
	auto iter = std::sregex_iterator(input.begin(), input.end(), reg);
	std::string output{};
	for (; iter != end; ++iter)
	{
		std::string word{};
		std::smatch m = *iter;
		//if word
		if (m[1].matched || m[4].matched)
		{
			word = dict[std::stoi(iter->str())];
			//matched a modifier
			if (m[2].matched)
			{
				if (iter->str(2) == "^")
					word[0] = toupper(word[0]);
				if (iter->str(2) == "!")
					for (auto& c : word)
						c = toupper(c);
			}
			word += " ";
		}
		//if punctuation
		if (m[3].matched)
		{
			if (iter->str() == "R")
				word = "\n";
			else if (iter->str() == "E")
				break;
			else
			{
				output.pop_back();
				if (iter->str() != "-")
					word = iter->str() + " ";
				else
					word = iter->str();
			}
		}
		output += word;
	}
	return output;
}

