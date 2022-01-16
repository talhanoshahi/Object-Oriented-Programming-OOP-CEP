#ifndef Functions_HPP
#define Functions_HPP 

#include <vector>
#include "Graph.hpp"

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

#endif // !Functions_HPP