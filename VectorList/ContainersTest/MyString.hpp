#pragma once

template <typename T, class Allocator>
my::basic_string<T, Allocator>::basic_string()
{

}

template <typename T, class Allocator>
my::basic_string<T, Allocator>::basic_string(const T* other)
{
	const char* newStr = other;
	bool isSmall = true;
	size_t strLen = 0;

	for (strLen = 0; newStr[strLen] != '\0'; strLen++)
	{
		if (strLen > 16)
		{
			isSmall = false;
		}
	}

	if (isSmall)
	{
		m_smallChar = Allocator().allocate(strLen + 1);

		for (int i = 0; newStr[i] != '\0'; i++)
		{
			m_smallChar[i] = newStr[i];
		}
		m_smallChar[strLen] = '\0';
	}

	else
	{
		m_char.reserve(strLen + 1);

		for (int i = 0; newStr[i] != '\0'; i++)
		{
			m_char.push_back(newStr[i]);
		}

		m_char.push_back('\0');
	}
}

template<typename T, class Allocator>
my::basic_string<T, Allocator>::basic_string(const basic_string& other)
{
	if (other.m_smallChar == nullptr)
	{
		m_char = other.m_char;
	}

	else
	{
		m_smallChar = Allocator().allocate(other.length() + 1);

		for (int i = 0; other.m_smallChar[i] != '\0'; i++)
		{
			m_smallChar[i] = other.m_smallChar[i];
		}

		m_smallChar[other.length()] = '\0';
	}
}

template<typename T, class Allocator>
my::basic_string<T, Allocator>::basic_string(basic_string&& other) noexcept
{
	m_char = std::move(other.m_char);
	m_smallChar = other.m_smallChar;

	m_smallChar = nullptr;
}

template <typename T, class Allocator>
my::basic_string<T, Allocator>::~basic_string()
{

}

template <typename T, class Allocator>
size_t my::basic_string<T, Allocator>::length() const 
{
	if (m_smallChar == nullptr)
	{
		if (m_char.size() == 0)
		{
			return 0;
		}

		return (m_char.size() - 1);
	}

	else
	{
		size_t strLen;

		for (strLen = 0; m_smallChar[strLen] != '\0'; strLen++)
		{
		}

		return strLen;
	}
}

template <typename T, class Allocator>
T& my::basic_string<T, Allocator>::operator[](const size_t a)
{
	if (m_smallChar == nullptr)
	{
		return m_char[a];
	}

	else
	{
		return m_smallChar[a];
	}
}

template <typename T, class Allocator>
my::basic_string<T, Allocator>& my::basic_string<T, Allocator>::operator=(const basic_string& other)
{
	if (m_smallChar == nullptr)
	{
		Allocator().deallocate(m_smallChar, length() + 1);
		m_smallChar = nullptr;
	}
	
	m_char.clear();

	if (other.m_smallChar == nullptr)
	{
		m_char = other.m_char;
	}

	else
	{
		m_smallChar = Allocator().allocate(other.length() + 1);

		for (int i = 0; other.m_smallChar[i] != '\0'; i++)
		{
			m_smallChar[i] = other.m_smallChar[i];
		}

		m_smallChar[other.length()] = '\0';
	}

	return *this;
}

template <typename T, class Allocator>
const T* my::basic_string<T, Allocator>::c_str() const noexcept
{	
	if (m_smallChar == nullptr)
	{
		return &m_char[0];
	}

	else
	{
		return m_smallChar;
	}
}

template<typename T, class Allocator>
my::basic_string<T, Allocator> my::basic_string<T, Allocator>::operator+(const basic_string& other) const
{
	size_t newLen = 0;

	if (m_smallChar == nullptr)
	{
		newLen += this->m_char.size();
	}

	else
	{
		newLen += SHORT_STRING_LEN - 1;
	}

	if (other.m_smallChar == nullptr)
	{
		newLen += other.m_char.size();
	}

	else
	{
		newLen += SHORT_STRING_LEN - 1;
	}

	newLen++;

	string newStr;
	newStr.m_char.reserve(newLen);

	for (size_t i = 0; i < newLen - 1; i++)
	{
		if (i < this->length())
		{
			newStr.m_char.push_back(this->c_str()[i]);
		}

		else
		{
			newStr.m_char.push_back(other.c_str()[i - this->length()]);
		}
	}

	newStr.m_char.push_back('\0');

	return newStr;
}