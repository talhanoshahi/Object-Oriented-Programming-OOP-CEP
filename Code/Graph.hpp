#ifndef Graph_HPP
#define Graph_HPP 

#include "Edge.hpp"
#include "Node.hpp"
namespace BOT
{
	class Graph
	{
	private:
		std::vector <Node> Nodes;
		std::vector <Edge> Edges;
		bool isDiGraph;
	public:
		Graph();
		Graph(const std::vector <Node> &, const std::vector <Edge> &);
		Graph(const Graph &);

		void setGraphType (bool);
		bool getGraphType ();

		friend std::ifstream & operator >> (std::ifstream &, Graph &);
		friend std::ofstream & operator << (std::ofstream &, Graph &);
		
		void Display();
		~Graph();
	};

	
} // namespace BOT

#endif // !Graph_HPP