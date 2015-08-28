#pragma once

namespace data
{
	template <typename T>
	class bintree
	{
	public:

		struct node
		{
			node*	left;
			node*	right;
			T		data;


			node() : left(nullptr), right(nullptr), data(T())	{}
			node(const T& data_) : left(nullptr), right(nullptr), data(data_)	{}
			~node()	
			{
				if (left)
					delete left;

				if (right)
					delete right;
			}
		};

		struct traverse_all
		{
			bool operator()() { return true;  }
		};

		const size_t ndeep = -1;

		bintree() : m_root(nullptr) {};

		virtual ~bintree()
		{
			if (m_root)
				delete m_root;
		}

		void addNode(const T& data)
		{
			addNode(data, &m_root);
		}

		template <typename Visitor, typename...Args>
		void visit(Visitor visitor, Args...args)
		{
			if (!m_root)
				return;

			visitor(std::cref(*m_root), args...);
		}

	private:

		void addNode(const T& data, node** root)
		{
			if (*root)
			{
				if (data < (*root)->data)
					addNode(data, &((*root)->left));
				else
					addNode(data, &((*root)->right));
			}
			else
			{
				*root = new node(data);
			}
		}

		node* m_root;

	private:

	};
}