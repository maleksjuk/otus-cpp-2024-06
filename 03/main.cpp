#include "my_allocator.h"
#include "my_container.h"

#include <vector>
#include <iostream>

int main()
{
	// std::vector<int, MyAllocator<int>> v;
	
	// for (int i = 0; i < 30; i++)
	// {
	// 	std::cout << "Add " << i << std::endl;
	// 	v.push_back(i);
	// }

	// for (auto item : v)
	// 	std::cout << item << " ";
	// std::cout << std::endl;

	MyStack<int> stack;
	stack.push(10);
	stack.push(20);
	stack.push(30);
	stack.print();
	std::cout << "pop: " << stack.pop() << std::endl;
	stack.print();
	std::cout << "pop: " << stack.pop() << std::endl;
	stack.print();
	std::cout << "pop: " << stack.pop() << std::endl;
	stack.print();
	std::cout << "pop: " << stack.pop() << std::endl;
	stack.print();

	return 0;
}
