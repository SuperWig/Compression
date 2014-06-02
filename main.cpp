#include "Compress.h"
#include "Decompress.h"
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
	try
	{
		if (argc != 4)
		{
			std::cerr << "3 arguments are required" << std::endl
				<< "Usage: Compression [-option] [input file] [output file]" << std::endl;
			return EXIT_FAILURE;
		}

		if (strcmp(argv[1], "-c") && strcmp(argv[1], "-d"))
		{
			std::cerr << "Incorrect option" << std::endl
				<< "Usage: -c for compression, -d for decompression" << std::endl;
			return EXIT_FAILURE;
		}

		std::ifstream inFile(argv[2]);
		if (!inFile.is_open())
		{
			std::cerr << "Error opening file " << argv[2] << std::endl;
			return EXIT_FAILURE;
		}

		std::ofstream outFile(argv[3]);
		if (!outFile.is_open())
		{
			std::cerr << "Error opening file " << argv[3] << std::endl;
			return EXIT_FAILURE;
		}

		if (!strcmp(argv[1], "-c"))
		{
			std::vector<std::string> dict;
			std::stringstream comp{};
			std::string input;
			while (std::getline(inFile, input))
			{
				comp << compress(input, dict);
				if (!inFile.eof())
					comp << "R ";
			}
			comp << "E";
			outFile << print(dict);
			outFile << comp.str();
		}
		if (!strcmp(argv[1], "-d"))
		{
			std::vector<std::string> dict;
			std::string input;
			size_t count;
			inFile >> count;
			for (size_t i = 0; i < count; ++i)
			{
				std::string word;
				inFile >> word;
				dict.push_back(word);
			}
			while (std::getline(inFile, input))
			{
				outFile << decomp(dict, input);
			}
		}
		inFile.close();
		outFile.close();
		std::cout << "Process completed successfully" << std::endl;
		return 0;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		std::cerr << "Process failed" << std::endl;
		return EXIT_FAILURE;
	}
}