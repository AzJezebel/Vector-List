#pragma once

#include "SpyAllocator.h"

namespace my
{
	template <typename T, class Allocator = SpyAllocator<T>>
	class vector
	{
	public:
		vector();
		~vector();
		vector(const vector& other);
		vector(vector&& other) noexcept;

		class iterator
		{
		public:
			iterator(T* data);

			bool operator!=(const iterator& otherIt) const;
			bool operator==(const iterator& otherIt) const;
			iterator& operator++();
			T& operator*();
			iterator operator-(const int a) const;
			iterator operator+(const int a) const;
			const T* operator->() const;
			iterator& operator+=(const int a);
			iterator& operator-=(const int a);
			iterator operator--(const int a);
			iterator operator++(const int a);

		private:
			T*			m_data;

		};

		iterator begin();
		iterator end();

		size_t capacity() const;
		size_t size() const;

		void clear() noexcept;

		void reserve(size_t newCapacity);

		void resize(size_t newSize);
		void resize(size_t newSize, const T& val);

		void push_back(const T& item);
		void push_back(T&& item);

		T& operator[](const size_t i);
		const T& operator[](const size_t i) const;

		vector& operator=(const vector& other);
		vector& operator=(vector&& other) noexcept;

		template <class... Args>
		void emplace_back(Args&&... args);

	private:
		size_t						m_capacity = 0;
		size_t						m_size = 0;
		T*							m_data = nullptr;

	};

#include "MyVector.hpp"
}

