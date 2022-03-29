#pragma once

template<typename T, class Allocator>
my::vector<T, Allocator>::vector()
{
	
}

template<typename T, class Allocator>
my::vector<T, Allocator>::vector(const vector& other)
{
	reserve(other.m_capacity);

	for (int iObj = 0; iObj < other.m_size; iObj++)
	{
		push_back(other[iObj]);
	}
}

template<typename T, class Allocator>
my::vector<T, Allocator>::vector(vector&& other) noexcept
{
	m_capacity = other.m_capacity;
	m_size = other.m_size;
	m_data = other.m_data;

	other.m_capacity = 0;
	other.m_size = 0;
	other.m_data = nullptr;
}

template<typename T, class Allocator>
my::vector<T, Allocator>::~vector()
{
	clear();

	if (m_capacity != 0)
	{
		Allocator().deallocate(m_data, m_capacity);
	}
}

template<typename T, class Allocator>
size_t my::vector<T, Allocator>::capacity() const
{
	return m_capacity;
}

template<typename T, class Allocator>
size_t my::vector<T, Allocator>::size() const
{
	return m_size;
}

template<typename T, class Allocator>
void my::vector<T, Allocator>::clear() noexcept
{
	for (int iObj = 0; iObj < m_size; iObj++)
	{
		m_data[iObj].~T();
	}

	m_size = 0;
}

template<typename T, class Allocator>
void my::vector<T, Allocator>::reserve(size_t newCapacity)
{
	if (m_capacity >= newCapacity)
	{
		return;
	}

	T* newArray = Allocator().allocate(newCapacity);

	if (m_size != 0)
	{
		for (int iObj = 0; iObj < m_size; iObj++)
		{
			new (&newArray[iObj]) T(m_data[iObj]);
			m_data[iObj].~T();
		}

		Allocator().deallocate(m_data, m_capacity);
	}

	m_data = newArray;
	m_capacity = newCapacity;
}

template<typename T, class Allocator>
void my::vector<T, Allocator>::resize(size_t newSize)
{
	reserve(newSize);

	if (newSize == m_size)
	{
		return;
	}

	if (newSize < m_size)
	{
		for (size_t iObj = newSize; iObj < m_size; iObj++)
		{
			m_data[iObj].~T();
		}
	}

	else if (newSize > m_size)
	{
		for (size_t iObj = m_size; iObj < m_capacity; iObj++)
		{
			new (&m_data[iObj]) T();
		}
	}

	m_size = newSize;
}

template<typename T, class Allocator>
void my::vector<T, Allocator>::resize(size_t newSize, const T& val)
{
	reserve(newSize);

	if (newSize == m_size)
	{
		return;
	}

	if (newSize < m_size)
	{
		for (int iObj = newSize; iObj < m_size; iObj++)
		{
			m_data[iObj].~T();
		}
	}

	else if (newSize > m_size)
	{
		for (int iObj = m_size; iObj < m_capacity; iObj++)
		{
			push_back(val);
		}
	}

	m_size = newSize;
}

template<typename T, class Allocator>
void my::vector<T, Allocator>::push_back(const T& item)
{
	if (m_size == m_capacity)
	{
		if (m_capacity == 0)
		{
			reserve(1);
			new (&m_data[m_size]) T(item);
		}

		else
		{
			T* newArray = Allocator().allocate(2 * m_capacity);

			new (&newArray[m_size]) T(item);

			for (int iObj = 0; iObj < m_size; iObj++)
			{
				new (&newArray[iObj]) T(m_data[iObj]);
			}

			for (int iObj = 0; iObj < m_size; iObj++)
			{
				m_data[iObj].~T();
			}

			Allocator().deallocate(m_data, m_capacity);


			m_data = newArray;
			m_capacity *= 2;
		}
	}

	else
	{
		new (&m_data[m_size]) T(item);
	}

	m_size++;
}

template<typename T, class Allocator>
void my::vector<T, Allocator>::push_back(T&& item)
{
	if (m_size == m_capacity)
	{
		if (m_capacity == 0)
		{
			reserve(1);
			new (&m_data[m_size]) T(std::move(item));
		}

		else
		{
			T* newArray = Allocator().allocate(2 * m_capacity);

			new (&newArray[m_size]) T(std::move(item));

			for (int iObj = 0; iObj < m_size; iObj++)
			{
				new (&newArray[iObj]) T(m_data[iObj]);
			}

			for (int iObj = 0; iObj < m_size; iObj++)
			{
				m_data[iObj].~T();
			}

			Allocator().deallocate(m_data, m_capacity);


			m_data = newArray;
			m_capacity *= 2;
		}
	}

	else
	{
		new (&m_data[m_size]) T(std::move(item));
	}

	m_size++;
}


template<typename T, class Allocator>
template <class... Args>
void my::vector<T, Allocator>::emplace_back(Args&&... args)
{
	if (m_size == m_capacity)
	{
		if (m_capacity == 0)
		{
			reserve(1);
			new (&m_data[m_size]) T(args...);
		}

		else
		{
			T* newArray = Allocator().allocate(2 * m_capacity);

			new (&newArray[m_size]) T(args...);

			for (int iObj = 0; iObj < m_size; iObj++)
			{
				new (&newArray[iObj]) T(m_data[iObj]);
			}

			for (int iObj = 0; iObj < m_size; iObj++)
			{
				m_data[iObj].~T();
			}

			Allocator().deallocate(m_data, m_capacity);


			m_data = newArray;
			m_capacity *= 2;
		}
	}

	else
	{
		new (&m_data[m_size]) T(args...);
	}

	m_size++;
}

template<typename T, class Allocator>
T& my::vector<T, Allocator>::operator[](const size_t i)
{
	return m_data[i];
}

template<typename T, class Allocator>
const T& my::vector<T, Allocator>::operator[](const size_t i)const
{
	return m_data[i];
}

template<typename T, class Allocator>
my::vector<T, Allocator>& my::vector<T, Allocator>::operator=(const my::vector<T, Allocator>& other)
{
	clear();

	reserve(other.m_capacity);

	for (int iObj = 0; iObj < other.m_size; iObj++)
	{
		push_back(other[iObj]);
	}

	return *this;
}

template<typename T, class Allocator>
my::vector<T, Allocator>& my::vector<T, Allocator>::operator=(my::vector<T, Allocator>&& other) noexcept
{
	clear();

	if (m_capacity != 0)
	{
		Allocator().deallocate(m_data, m_capacity);
	}
	
	m_capacity = other.m_capacity;
	m_size = other.m_size;
	m_data = other.m_data;

	other.m_capacity = 0;
	other.m_size = 0;
	other.m_data = nullptr;

	return *this;
}

template<typename T, class Allocator>
my::vector<T, Allocator>::iterator::iterator(T* data)
{
	m_data = data;
}

template<typename T, class Allocator>
typename my::vector<T, Allocator>::iterator my::vector<T, Allocator>::begin()
{
	return iterator(&m_data[0]);
}

template<typename T, class Allocator>
typename my::vector<T, Allocator>::iterator my::vector<T, Allocator>::end()
{
	return iterator(&m_data[m_size]);
}

template<typename T, class Allocator>
bool my::vector<T, Allocator>::iterator::operator!=(const iterator& otherIt) const
{
	return (otherIt.m_data != this->m_data);
}

template<typename T, class Allocator>
bool my::vector<T, Allocator>::iterator::operator==(const iterator& otherIt) const
{
	return (otherIt.m_data == this->m_data);
}

template<typename T, class Allocator>
typename my::vector<T, Allocator>::iterator& my::vector<T, Allocator>::iterator::operator++()
{
	m_data++;

	return *this;
}

template<typename T, class Allocator>
T& my::vector<T, Allocator>::iterator::operator*()
{
	return *this->m_data;
}

template<typename T, class Allocator>
typename my::vector<T, Allocator>::iterator my::vector<T, Allocator>::iterator::operator-(const int a) const
{
	iterator it(this->m_data - a);

	return it;
}

template<typename T, class Allocator>
typename my::vector<T, Allocator>::iterator my::vector<T, Allocator>::iterator::operator+(const int a) const
{
	iterator it(this->m_data + a);

	return it;
}

template<typename T, class Allocator>
const T* my::vector<T, Allocator>::iterator::operator->() const
{
	return m_data;
}

template<typename T, class Allocator>
typename my::vector<T, Allocator>::iterator& my::vector<T, Allocator>::iterator::operator+=(const int a)
{
	m_data += a;

	return *this;
}

template<typename T, class Allocator>
typename my::vector<T, Allocator>::iterator& my::vector<T, Allocator>::iterator::operator-=(const int a)
{
	m_data -= a;

	return *this;
}

template<typename T, class Allocator>
typename my::vector<T, Allocator>::iterator my::vector<T, Allocator>::iterator::operator--(const int a)
{
	iterator it(this->m_data);
	*this -= 1;

	return it;
}

template<typename T, class Allocator>
typename my::vector<T, Allocator>::iterator my::vector<T, Allocator>::iterator::operator++(const int a)
{
	iterator it(this->m_data);
	*this += 1;

	return it;
}