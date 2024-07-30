#ifndef MY_ALLOCATOR_H
#define MY_ALLOCATOR_H

#include <cstring>
#include <exception>
#include <iostream>
#include <memory>

template<typename T>
struct s_pool
{
	s_pool()
		: size(0)
		, ptr(nullptr)
		, is_free(false)
		, next(nullptr)
	{}

	s_pool(std::size_t n)
		: size(n)
		, ptr(nullptr)
		, is_free(false)
		, next(nullptr)
	{
		if (n > 0)
			ptr = reinterpret_cast<T*>(std::malloc(n * sizeof(T)));
	}

	~s_pool()
	{
		if (ptr) {
			std::free(ptr);
			ptr = nullptr;
		}
	}

	void clear()
	{
		std::memset(ptr, 0, size * sizeof(T));
		is_free = true;
	}

	std::size_t size;
	T *ptr;
	bool is_free;
	s_pool *next;
};

template<typename T>
class MyAllocator
{
public:
	using value_type = T;
	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;

	template<typename U>
	struct rebind {
		using other = MyAllocator<U>;
	};

	MyAllocator()
	{
		pool_head = createPool(0);
		// std::cout << "MyAllocator created" << std::endl;
	}

	~MyAllocator()
	{
		s_pool<T> *prev = pool_head;
		pool_head = pool_head->next;
		while (prev)
		{
			prev->~s_pool();
			std::free(prev);
			prev = pool_head;
			if (pool_head)
				pool_head = pool_head->next;
		}
		// std::cout << "MyAllocator deleted" << std::endl;
	}

	T *allocate(std::size_t n)
	{
		// std::cout << "Allocate memory for n=" << n << std::endl;

		s_pool<T> *curr_pool = pool_head;
		while (curr_pool)
		{
			if (curr_pool->size >= n && curr_pool->is_free) {
				curr_pool->is_free = false;
				return curr_pool->ptr;
			}
			if (!curr_pool->next)
				break;
			curr_pool = curr_pool->next;
		}

		auto new_pool = createPool(n);
		curr_pool->next = new_pool;
		return new_pool->ptr;
	}

	void deallocate(T *ptr, std::size_t n)
	{
		// std::cout << "Deallocate memory for ptr=" << ptr << " n=" << n << std::endl;
		(void)n;
		
		auto curr_pool = pool_head;
		while (curr_pool && curr_pool->ptr != ptr)
			curr_pool = curr_pool->next;

		if (curr_pool)
			curr_pool->clear();
	}

	template<typename U, typename... Args>
	void construct(U *ptr, Args &&...args)
	{
		// std::cout << "Construct" << std::endl;
		new (ptr) U(std::forward<Args>(args)...);
	}

	template<typename U>
	void destroy(U *ptr)
	{
		// std::cout << "Destroy" << std::endl;
		ptr->~U();
	}

private:
	s_pool<T> *createPool(std::size_t n)
	{
		s_pool<T> *pool = reinterpret_cast<s_pool<T>*>(std::malloc(sizeof(s_pool<T>)));
		if (!pool)
			throw std::bad_alloc();
		new (pool) s_pool<T>(n);
		return pool;
	}

	s_pool<T> *pool_head;
};

#endif // MY_ALLOCATOR_H
