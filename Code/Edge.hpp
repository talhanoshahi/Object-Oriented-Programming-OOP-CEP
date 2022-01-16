#ifndef Edge_HPP
#define Edge_HPP

#include <string>

namespace BOT
{
	class Edge
	{
	private:
		int Weight;
		std::pair <std::string, std::string> EdgeNodes;
	public:
		Edge();
		Edge(const int, const std::string, const std::string);
		Edge(const Edge &);
	
		void setEdgeWeight (const int);
		void setEdge (const std::string, const std::string);
		
		int getEdgeWeight () const;
		std::pair <std::string, std::string> getEdge () const;
		
		~Edge();
	};
	
} // namespace BOT

#endif // Edge_HPP