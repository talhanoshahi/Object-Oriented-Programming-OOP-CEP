#include <fstream>
#include <iostream>
#include <vector>
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
		
		~Graph();
	};

	Graph::Graph()
	{
		Nodes = {};
		Edges = {};
		isDiGraph = false;
	}

	Graph::Graph(const std::vector <BOT::Node> & Nodes,const std::vector <BOT::Edge> & Edges)
	{
		this->Nodes = Nodes;
		this->Edges = Edges;
		isDiGraph = false;
	}

	Graph::Graph(const Graph & Copy)
	{
		this->Nodes = Copy.Nodes;
		this->Edges = Copy.Edges;
		this->isDiGraph = Copy.isDiGraph;
	}

	void Graph::setGraphType (bool isDiGraph)
	{
		this->isDiGraph = isDiGraph;
	}

	bool Graph::getGraphType ()
	{
		return isDiGraph;
	}

	Graph::~Graph()
	{
	}

} // namespace BOT

