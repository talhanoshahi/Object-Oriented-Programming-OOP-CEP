#include <regex>
#include <fstream>
#include <iostream>
#include <experimental/filesystem>
#include <string>
#include <sstream>
#include <array>
#include "Graph.hpp"

namespace fs = std::experimental::filesystem;

const int SupportedExtensionsSize = 9;
const int DOT_ExtensionsSize = 2;

const std::string SupportedExtensions[SupportedExtensionsSize] = 
{
	"bmp" , "png" , "eps" , "gif" , "jpe" , "jpeg" , "jpg" , "pdf" , "ps"
};

const std::string DOT_Commands[] = 
{
	"dot -Tbmp " , "dot -Tpng " , "dot -Teps " , "dot -Tgif " , "dot -Tjpe " , "dot -Tjpeg " , "dot -Tjpg " , "dot -Tpdf " , "dot -Tps "
};

const std::string DOT_Extensions[DOT_ExtensionsSize] = {	"dot" , "gv"	};

namespace BOT
{
	void argc1 ();
	void argc2 (const char**);
	void argc3 (const char**);
	void argc4 (const char**);
	void redirect (int , const char**);
	void outputFileName (std::string &);
	void outputFile (std::ofstream & , Graph &);
	const int readingShift (const std::string &);
	const int CompareFileExtension(const std::string* , const std::string & , const int);
	std::string FindFileExtension(const std::string &);
	const int CheckEdgePattern (const std::string &);
	const int CheckNodePattern (const std::string &);
	void ConvertDOT_toPicture (const std::string* , const std::string &);
	std::ifstream & operator>> (std::ifstream &, Graph &);
	std::string SplitString(const std::string , const int);
	std::ofstream & operator << (std::ofstream &, Graph &);
	void inputFile (std::ifstream & , Graph & , const std::string &);
	void outputFile (std::ofstream & , Graph & , const char , const char**);
	const int returnIndex (const std::vector <Node> &, const std::string &);
} // namespace BOT

void BOT::redirect (int argc, const char** argv)
{
	switch (argc)
	{
	case 1:
		argc1 ();
		break;
	case 2:
		argc2 (argv);
		break;
	case 3:
		argc3 (argv);
		break;
	case 4:
		argc4 (argv);
		break;
	default:
		std::cerr << "Invalid number of aurguments." << '\n';
		break;
	}
}

void BOT::argc1 ()
{
	Graph Object;
	std::ifstream inputFileOpen;
	std::ofstream outputFileOpen;

	std::string inputFileName;
	std::cout << "Welcome to the program!" << std::endl;
	std::cout << "Please enter the input file name: " << std::endl;
	std::getline (std::cin,inputFileName);

	if (!(fs::exists (fs::path(inputFileName)))) 
	{
		std::cerr << "error: Input file not found." << '\n';
		return;
	}

	try
	{
		inputFile(inputFileOpen , Object , inputFileName);
	}
	catch(const int InputErrorOccured)
	{
		return;
	}
		
	try
	{
		outputFile(outputFileOpen , Object);
	}
	catch (const int OutputErrorOccured)
	{
		return;
	}

	std::cout << "Graph translated successfully!" << std::endl;

	return;
}

void BOT::argc2 (const char** argv)
{
	BOT::Graph Object;
	std::ifstream inputFileOpen;
	std::ofstream outputFileOpen;

	std::string inputFileName;

	if (!fs::exists (fs::path(argv[1]))) 
	{
		std::cerr << "error: Input file not found." << '\n';
		return;
	}

	try
	{
		inputFile(inputFileOpen , Object , argv[1]);
	}
	catch(const int InputErrorOccured)
	{
		return;
	}
		
	try
	{
		outputFile(outputFileOpen , Object , 'p' , argv);
	}
	catch (const int OutputErrorOccured)
	{
		return;
	}

	std::cout << "Graph translated successfully!" << std::endl;

	return;
}

void BOT::argc3 (const char** argv)
{
	BOT::Graph Object;
	std::ifstream inputFileOpen;
	std::ofstream outputFileOpen;

	if (!fs::exists (fs::path(argv[1]))) 
	{
		std::cerr << "error: Input file not found." << '\n';
		return;
	}

	try
	{
		inputFile(inputFileOpen , Object , argv[1]);
	}
	catch(const int InputErrorOccured)
	{
		return;
	}

	try
	{
		outputFile(outputFileOpen , Object , 'n' , argv);
	}
	catch (const int OutputErrorOccured)
	{
		return;
	}

	std::cout << "Graph translated successfully!" << std::endl;

	return;
}

void BOT::argc4 (const char** argv)
{
	BOT::Graph Object;
	std::ifstream inputFileOpen;
	std::ofstream outputFileOpen;

	if (!fs::exists (fs::path(argv[1]))) 
	{
		std::cerr << "error: Input file not found." << '\n';
		return;
	}

	try
	{
		inputFile(inputFileOpen , Object , argv[1]);
	}
	catch(const int InputErrorOccured)
	{
		return;
	}
		
	try
	{
		outputFile(outputFileOpen , Object , 'r' , argv);
	}
	catch (const int OutputErrorOccured)
	{
		return;
	}

	std::cout << "Graph translated successfully!" << std::endl;

	return;
}

void BOT::inputFile (std::ifstream & inputFile , Graph & inputGraph , const std::string & inputFileName)
{
	inputFile.open (inputFileName, std::ios::in);
	if (inputFile.is_open())
	{
		try
		{
			inputFile >> inputGraph;
			inputFile.close();
		}
		catch(const std::string & Error)
		{
			std::cerr << Error << '\n';
			throw -1;
		}
		catch (...)
		{
			throw -2;
		}
			
	}

	return;
}

void BOT::outputFile (std::ofstream & outputFile , Graph & outputGraph)
{
	std::string outputFileNameEntered;

	char choice;
	std::cout << "Do you want to keep DOT file (Y/n): ";
	std::cin>>choice;
		
	if (choice == 'Y' || choice == 'y')
	{
		std::string dotFileName;
		std::cout << "Please enter the DOT file name: ";
		std::cin.ignore();
		std::getline(std::cin , dotFileName);
			
		if (BOT::CompareFileExtension(DOT_Extensions , dotFileName , 2) == -1)	
		{
			std::cerr << "error: File extension not compatible." << '\n';
			throw -2;
		}

		try
		{
			outputFileName(outputFileNameEntered);
		}
		catch(const std::string & Error)
		{
			std::cerr << Error << '\n';
			throw -2;
		}
		

		outputFile.open (dotFileName, std::ios::out);
		if (outputFile.is_open())
		{
			outputFile << outputGraph;
			outputFile.close();
		}

		ConvertDOT_toPicture (&dotFileName , outputFileNameEntered);
	}
	else
	{
		try
		{
			outputFileName(outputFileNameEntered);
		}
		catch(const std::string & Error)
		{
			std::cerr << Error << '\n';
			throw -2;
		}

		outputFile.open ("General.dot", std::ios::out);
		if (outputFile.is_open())
		{
			outputFile << outputGraph;
			outputFile.close();
		}
			
		ConvertDOT_toPicture (NULL , outputFileNameEntered);
	}
		
}
	
void BOT::outputFile (std::ofstream & outputFile , Graph & outputGraph , const char keepDOT , const char** argv)
{
	std::string outputFileNameEntered;

	if (keepDOT == 'p' || keepDOT == 'p')
	{
		try
		{
			outputFileName(outputFileNameEntered);
		}
		catch(const std::string & Error)
		{
			std::cerr << Error << '\n';
			throw -2;
		}

		outputFile.open ("General.dot", std::ios::out);
		if (outputFile.is_open())
		{
			outputFile << outputGraph;
			outputFile.close();
		}

		ConvertDOT_toPicture (NULL , outputFileNameEntered);
	}
	else if (keepDOT == 'N' || keepDOT == 'n')
	{
		outputFile.open ("General.dot", std::ios::out);
		if (outputFile.is_open())
		{
			outputFile << outputGraph;
			outputFile.close();
		}

		if (CompareFileExtension(SupportedExtensions , FindFileExtension (std::string(argv[2])) , 9) == -1)
		{
			std::cerr << "error: Wrong output file format.\n";
			throw -2;
		}

		ConvertDOT_toPicture (NULL , std::string(argv[2]));
	}
	else
	{
		outputFile.open (argv[2], std::ios::out);
		if (outputFile.is_open())
		{
			outputFile << outputGraph;
			outputFile.close();
		}

		if (CompareFileExtension(SupportedExtensions , FindFileExtension (std::string(argv[3])) , 9) == -1)
		{
			std::cerr << "error: Wrong output file format.\n";
			throw -2;
		}

		std::string DOT_File = std::string (argv[2]);
		ConvertDOT_toPicture (&DOT_File , std::string(argv [3]));
	}
		
		
	return;
}

std::ifstream & BOT::operator>> (std::ifstream & inputFile, BOT::Graph & inputGraph)
{
	std::string reading;
	bool NodesReading = false;
	bool EdgesReading = false;
	bool GraphTypeReading = false;

	for (size_t i = 1 ; !inputFile.eof() ; i++)
	{
		getline(inputFile, reading);
		if (reading[0] == ';')
		{
			if (readingShift(reading) == 1)	
			{
				NodesReading = true;
				EdgesReading = false;
				GraphTypeReading = false;
			}
			else if (readingShift(reading) == 2)	
			{
				NodesReading = false;
				EdgesReading = true;
				GraphTypeReading = false;
			}
			else if (readingShift(reading) == 3)	
			{
				NodesReading = false;
				EdgesReading = false;
				GraphTypeReading = true;
			}
			continue;
		}
				
		else if ((reading[0] == '/' && reading[1] == '/') || reading.length() == 0 || reading[0] == '#') continue;
		else
		{
			if (NodesReading)
			{
				if((CheckNodePattern(reading)) == -1)
				{
					throw ("Nodes reading error.\nerror: Formatting error on line " + std::to_string(i) + " of input file.");
				}
				
				inputGraph.Nodes.push_back((SplitString(reading, 1)));
				
			}
			else if (EdgesReading)
			{
				if((CheckEdgePattern(reading)) == -1)
				{
					throw ("Edge reading error.\nerror: Formatting error on line " + std::to_string(i) + " of input file.");
				}

				inputGraph.Edges.push_back(Edge (std::stoi (SplitString(reading, 2)) , SplitString (reading, 0), SplitString (reading, 1)));

			}
			else if (GraphTypeReading)
			{
				if (reading == "DiGraph" || reading == "diGraph" || reading == "DirectedGraph" || reading == "Directed Graph")
				{
					inputGraph.isDiGraph = true;
				}
				else inputGraph.isDiGraph = false;
			}
		}
	}

	return inputFile;
}

std::ofstream & BOT::operator << (std::ofstream & outputFile, BOT::Graph & outputGraph)
{
	std::string operation;
		
	if (outputGraph.isDiGraph)
	{
		outputFile << "digraph" << std::endl;
		outputFile << "{" << std::endl;
		outputFile << "\tgraph[];" << std::endl;
		outputFile << std::endl;
			
		operation = "->";
	}
	else
	{
		outputFile << "graph" << std::endl;
		outputFile << "{" << std::endl;
		
		operation = "--";
	}


	outputFile << "\tnode [fontcolor=black, fontsize=28];" << std::endl;
	outputFile << "\tedge [fontsize=25, arrowhead=vee, arrowsize=0.5];" << std::endl;
	outputFile << std::endl;

	for (size_t i = 0; i < outputGraph.Nodes.size() ; i++)
	{
		outputFile << "\t\"" << i+1 << "\" [label=\"" << outputGraph.Nodes[i].getNodeName() << "\"];" << std::endl;
	}
	outputFile << std::endl;

	for (size_t i = 0; i < outputGraph.Edges.size() ; i++)
	{
		outputFile << "\t\"" << returnIndex ((outputGraph.Nodes) , (outputGraph.Edges[i].getEdge().first) ) + 1 << "\" " << operation << "\"" << returnIndex ((outputGraph.Nodes) , (outputGraph.Edges[i].getEdge().second) ) + 1 << "\" [label=\"" << outputGraph.Edges[i].getEdgeWeight() << "\"];" << std::endl;
	}
	outputFile << std::endl;

	outputFile << "}" << std::endl;
		
	return outputFile;
}
	
std::string BOT::SplitString(const std::string StringToSplit, const int PositionToReturn)
{
	std::vector <std::string> SplittedWords;
	int distancefromspace = 1;

	for (int i = 0 , j = 0 ; i < StringToSplit.length() ; i++)
	{
		if (StringToSplit[i] != ' ')
		{
			if (distancefromspace == 1)
			{
				std::string newWord;
				newWord += StringToSplit[i];
				SplittedWords.push_back (newWord);
				distancefromspace ++;
			}
			else 
			{
				SplittedWords[j] += StringToSplit[i];
			}
		}
		else if (StringToSplit [i] == ' ')
		{
			distancefromspace = 1;
			j++;
		}
	}
		
	return SplittedWords[PositionToReturn];
}

const int BOT::returnIndex (const std::vector <Node> & SourceVector, const std::string & stringToFind)
{
	for (size_t i = 0; i < SourceVector.size() ; i++)
	{
		if (SourceVector[i].getNodeName() == stringToFind)
		{
			return i;
		}
		else continue;
	}
	return 0;
}

const int BOT::readingShift (const std::string & input)
{
	std::regex ifNode(";Nodes");
	std::regex ifEdge(";Edges");
	std::regex ifGraphDirection(";Graph Type");

	if (std::regex_match( input , ifNode ))	return 1;
	else if (std::regex_match( input , ifEdge))	return 2;
	else if (std::regex_match( input , ifGraphDirection))	return 3;
	else return -1;
}
	
const int BOT::CheckNodePattern (const std::string & Source)
{
	std::regex NodePattern("(\\d+\\s+\\w)+[\\S\\s]*");
	if (!std::regex_match(Source, NodePattern))
	{
		return -1;
	}
	return 0;
}

const int BOT::CheckEdgePattern (const std::string & Source)
{
	std::regex EdgePattern("(\\w+\\s+\\w+\\s+\\d)+[\\S\\s]*");
	if (!std::regex_match(Source, EdgePattern))
	{
		return -1;
	}
	return 0;
}

void BOT::outputFileName(std::string & OutputFile)
{
	std::cout << "Please enter the output file name: " << std::endl;
	std::cout << "The available file formats are: ";
	for (size_t i = 0; i < SupportedExtensionsSize ; i++)
	{
		std::cout << SupportedExtensions[i];
		if (i<(SupportedExtensionsSize-1))	std::cout << " , ";
		else std::cout << std::endl;
	}

	std::cout << "Enter file name: " << std::endl;
	std::cin.ignore();
	std::getline (std::cin,OutputFile);	
	if (CompareFileExtension(SupportedExtensions , FindFileExtension (OutputFile) , 9) == -1)
	{
		throw "error: Wrong output file format.";
	}
	 
}

std::string BOT::FindFileExtension (const std::string & String)
{
	std::string extension;
	bool startReading = false;

	for (size_t i = 0 ; i < String.length() ; i++)
	{
		if (startReading)
		{
			extension += String[i];
		}
		
		if (String[i] == '.')
		{
			startReading = true;
		}
		
	}

	return extension;
	
}

const int BOT::CompareFileExtension (const std::string* ArrayAddress , const std::string & ExtensionToCompare, const int ArrayLength)
{
	for (size_t i = 0; i < ArrayLength; i++)
	{
		if (ArrayAddress[i] == ExtensionToCompare)
		{
			return i;
		}
		
	}
	return -1;	
}

void BOT::ConvertDOT_toPicture (const std::string* DOT_File , const std::string & OutPutFile)
{
	if (DOT_File != NULL)
	{
		std::string command = DOT_Commands[CompareFileExtension(SupportedExtensions , FindFileExtension (OutPutFile) , 9)] + (*DOT_File) + " -o " + OutPutFile;
		system (command.c_str());		 
	}
	else
	{
		std::string command = DOT_Commands[CompareFileExtension(SupportedExtensions , FindFileExtension (OutPutFile) , 9)] + "General.dot -o " + OutPutFile;
		system (command.c_str());
		system ("rm General.dot");
	}
	
	
}
