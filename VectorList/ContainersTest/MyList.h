#pragma once

#include "SpyAllocator.h"

namespace my
{
	template <typename T, class Allocator = SpyAllocator<T>>
	class list
	{
	public:
		list();
		~list();

		list(const list& other);
		list(list&& other) noexcept;

		struct node;

		class iterator
		{
		public:
			iterator(node* val);

			bool operator!=(const iterator& otherIt) const;
			bool operator==(const iterator& otherIt) const;
			iterator& operator++();
			iterator operator++(const int a);
			iterator operator--(const int a);
			const T* operator->() const;
			T& operator*();
			

		private:
			friend list;

			struct node*			 m_itNode = nullptr;

		};

		size_t size();
		iterator begin();
		iterator end();

		void remove(const T& val);
		iterator insert(const iterator pos, T&& val);
		iterator insert(const iterator pos, const T& val);
		iterator insert(const iterator pos, size_t n, const T& val);
		template <class InputIterator>
		iterator insert(const iterator pos, InputIterator first, InputIterator last);
		list& operator=(list&& other) noexcept;

		void push_back(const T& val);
		void push_back(T&& val);

		template <class... Args>
		void emplace_back(Args&&... args);

	private:
		struct node
		{
			node(const T& val) :
				m_data(val)
			{}

			node(T&& val) :
				m_data(std::move(val))
			{}

			T				 m_data;
			node*		 	 m_next = nullptr;
			node*	 		 m_prev = nullptr;
		};

		node*				 m_head = nullptr;
		node*				 m_tail = nullptr;
		size_t				 m_size = 0;
	};

#include "MyList.hpp"
}