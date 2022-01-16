#include <string>

namespace BOT
{
	class Node
	{
	private:
		std::string Name;
	public:
		Node();
		Node(const std::string);
		Node(const Node &);

		void setNodeName (const std::string);
		std::string getNodeName() const;

		~Node();
	};

	Node::Node()
	{
		Name = '\0';
	}

	Node::Node(const std::string Name)
	{
		this->Name = Name;
	}

	Node::Node(const Node & Copy)
	{
		this->Name = Copy.Name;
	}

	void Node::setNodeName(const std::string Name)
	{
		this->Name = Name;
	}

	std::string Node::getNodeName() const
	{
		return this->Name;
	}

	Node::~Node()
	{
	}

} // namespace BOT