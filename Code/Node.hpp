#ifndef Node_HPP
#define Node_HPP 

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

} // namespace BOT

#endif // !Node_HPP