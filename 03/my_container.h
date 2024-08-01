#ifndef MY_CONTAINER_H
#define MY_CONTAINER_H

#include <memory>
#include <iostream>
#include <typeinfo>

template<typename T>
struct Node
{
	Node()
		: next(nullptr)
	{}

	Node(T data, Node<T> *next = nullptr)
		: data(data)
		, next(next)
	{}

	~Node() = default;

	T data;
	Node<T> *next;
};

template<typename T, typename Allocator=std::allocator<Node<T>>>
class MyStack
{
public:
	MyStack()
		: top(nullptr)
		, _size(0)
	{}

	~MyStack()
	{
		while (top)
		{
			Node<T> *next = top->next;
			// destroy
			// deallocate
			top = next;
		}
	}

	void push(T data)
	{
		// allocate
		Node<T> *node = allocator.allocate(1);

		// construct
		allocator.construct(node, data, top);

		// new top
		top = node;

		_size++;
	}

	T pop()
	{
		if (!top)
			return T();

		Node<T> *next = top->next;
		T return_value = top->data;

		// destroy
		allocator.destroy(top);

		// deallocate
		allocator.deallocate(top, 1);

		top = next;

		_size--;
		return return_value;
	}

	std::size_t size() const
	{
		return _size;
	}

	void print()
	{
		std::cout << "MyStack: size=" << _size << "\n";
		std::size_t level = 0;
		Node<T> *node = top;
		while (node)
		{
			std::cout << level << " -> " << node->data << "\n";
			node = node->next;
			level++;
		}
		std::cout << std::flush;
	}

private:
	Node<T> *top;
	std::size_t _size;

	Allocator allocator;
};

#endif // MY_CONTAINER_H
