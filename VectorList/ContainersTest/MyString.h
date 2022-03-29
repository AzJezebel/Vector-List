#pragma once

#include "SpyAllocator.h"

namespace my
{
	template <typename T, class Allocator = std::allocator<T>>
	class basic_string
	{
		const static int SHORT_STRING_LEN = 16;

	public:
		basic_string();
		~basic_string();
		basic_string(const T* other);
		basic_string(const basic_string& other);
		basic_string(basic_string&& other) noexcept;

		size_t length() const;
		T& operator[](const size_t a);
		basic_string& operator=(const basic_string& other);
		const T* c_str() const noexcept;
		basic_string operator+(const basic_string& other) const;

	private:
		vector<T>		m_char;
		T*				m_smallChar = nullptr;

	};

	typedef basic_string<char> string;

#include "MyString.hpp"
}