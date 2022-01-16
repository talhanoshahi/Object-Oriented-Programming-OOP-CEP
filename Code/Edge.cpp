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
	
	Edge::Edge()
	{
		Weight = 0;
		EdgeNodes.first = '\0';
		EdgeNodes.second = '\0';
	}
	
	Edge::Edge(const int Weight, const std::string firstNode, const std::string secondNode)
	{
		this->Weight = Weight;
		EdgeNodes.first = firstNode;
		EdgeNodes.second = secondNode;
	}
	
	Edge::Edge(const Edge & Copy)
	{
		this->Weight = Copy.Weight;
		this->EdgeNodes = Copy.EdgeNodes;
	}
	
	void Edge::setEdgeWeight(const int Weight)
	{
		this->Weight = Weight;
	}
	
	void Edge::setEdge (const std::string firstNode, const std::string secondNode)
	{
		this->EdgeNodes.first = firstNode;
		this->EdgeNodes.second = secondNode;
	}
	
	int Edge::getEdgeWeight() const
	{
		return this->Weight;
	}
	
	std::pair <std::string, std::string> Edge::getEdge() const
	{
		return EdgeNodes;
	}
	
	Edge::~Edge()
	{
	}
	
} // namespace BOT

