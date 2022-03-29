#pragma once

template<typename T, class Allocator>
my::list<T, Allocator>::list()
{
	
}

template<typename T, class Allocator>
my::list<T, Allocator>::~list()
{
	for (node* iNode = m_head; iNode != nullptr; /**/)
	{
		node* currNode = iNode;
		iNode = iNode->m_next;

		currNode->m_data.~T();
		currNode->~node();

		Allocator::template rebind<node>::other().deallocate(currNode, 1);
	}
}

template<typename T, class Allocator>
my::list<T, Allocator>::list(const list& other)
{
	for (node* iNode = other.m_head; iNode != nullptr; /**/)
	{
		push_back(iNode->m_data);
		iNode = iNode->m_next;
	}
}

template<typename T, class Allocator>
my::list<T, Allocator>::list(list&& other) noexcept
{
	m_head = other.m_head;
	m_tail = other.m_tail;
	m_size = other.m_size;

	other.m_head = nullptr;
	other.m_tail = nullptr;	
	other.m_size = 0;
}

template<typename T, class Allocator>
void my::list<T, Allocator>::push_back(const T& val)
{
	node* newNode = Allocator::template rebind<node>::other().allocate(1);

	new (newNode) node(val);

	newNode->m_next = nullptr;
	
	if (m_size == 0)
	{
		newNode->m_prev = nullptr;
		m_head = newNode;
	}

	else
	{
		m_tail->m_next = newNode;
		newNode->m_prev = m_tail;
	}

	m_tail = newNode;
	m_size++;
}

template<typename T, class Allocator>
void my::list<T, Allocator>::push_back(T&& val)
{
	node* newNode = Allocator::template rebind<node>::other().allocate(1);

	new (newNode) node(std::move(val));

	newNode->m_next = nullptr;

	if (m_size == 0)
	{
		newNode->m_prev = nullptr;
		m_head = newNode;
	}

	else
	{
		m_tail->m_next = newNode;
		newNode->m_prev = m_tail;
	}

	m_tail = newNode;
	m_size++;
}

template<typename T, class Allocator>
size_t my::list<T, Allocator>::size()
{
	return m_size;
}

template<typename T, class Allocator>
my::list<T, Allocator>::iterator::iterator(node* val)
{
	m_itNode = val;
}

template<typename T, class Allocator>
typename my::list<T, Allocator>::iterator my::list<T, Allocator>::begin()
{
	return iterator(m_head);
}

template<typename T, class Allocator>
typename my::list<T, Allocator>::iterator my::list<T, Allocator>::end()
{
	return iterator(nullptr);
}


template<typename T, class Allocator>
void my::list<T, Allocator>::remove(const T& val)
{
	for (node* iNode = m_head; iNode != nullptr; /**/)
	{
		node* currentNode = iNode;

		if (currentNode->m_data == val)
		{
			if (currentNode == m_head)
			{
				if (m_size == 1)
				{
					m_head = nullptr;
					m_tail = nullptr;
				}

				else
				{
					m_head = currentNode->m_next;
					m_head->m_prev = nullptr;
				}
			}

			else if (currentNode == m_tail)
			{
				m_tail = currentNode->m_prev;
				m_tail->m_next = nullptr;
			}

			else
			{
				currentNode->m_prev->m_next = currentNode->m_next;
				currentNode->m_next->m_prev = currentNode->m_prev;
			}
			
			iNode = iNode->m_next;

			currentNode->m_data.~T();
			currentNode->~node();
			Allocator::template rebind<node>::other().deallocate(currentNode, 1);
			m_size--;
		}

		else 
		{
			iNode = iNode->m_next;
		}
	}
}

template<typename T, class Allocator>
typename my::list<T, Allocator>::iterator my::list<T, Allocator>::insert(const iterator pos, T&& val)
{
	if (pos.m_itNode == nullptr)
	{
		return pos;
	}

	node* newNode = Allocator::template rebind<node>::other().allocate(1);
	new (newNode) node(std::move(val));

	newNode->m_prev = pos.m_itNode->m_prev;
	newNode->m_next = pos.m_itNode;
	pos.m_itNode->m_prev->m_next = newNode;
	pos.m_itNode->m_prev = newNode;
	m_size++;
	
	return iterator(newNode);
}

template<typename T, class Allocator>
typename my::list<T, Allocator>::iterator my::list<T, Allocator>::insert(const iterator pos, const T& val)
{
	if (pos.m_itNode == nullptr)
	{
		return pos;
	}

	node* newNode = Allocator::template rebind<node>::other().allocate(1);
	new (newNode) node(val);

	if (pos.m_itNode->m_prev == nullptr)
	{
		newNode->m_prev = nullptr;
		m_head = newNode;
	}

	else
	{
		newNode->m_prev = pos.m_itNode->m_prev;
		pos.m_itNode->m_prev->m_next = newNode;
	}
	
	newNode->m_next = pos.m_itNode;
	pos.m_itNode->m_prev = newNode;
	m_size++;

	return iterator(newNode);
}

template<typename T, class Allocator>
typename my::list<T, Allocator>::iterator my::list<T, Allocator>::insert(const iterator pos, size_t n, const T& val)
{
	if (pos.m_itNode == nullptr)
	{
		return pos;
	}

	iterator it = pos;

	for (size_t nElems = 0; nElems < n; nElems++)
	{
		if (nElems == 0)
		{
			it = insert(pos, val);
		}
		
		else
		{
			insert(pos, val);
		}
	}

	return it;
}

template<typename T, class Allocator>
template <class InputIterator>
typename my::list<T, Allocator>::iterator my::list<T, Allocator>::insert(const iterator pos, InputIterator first, InputIterator last)
{
	if (pos.m_itNode == nullptr)
	{
		return pos;
	}

	iterator it = pos;

	for (InputIterator iElems = first; iElems != last; iElems++)
	{
		if (iElems == first)
		{
			it = insert(pos, *iElems);
		}

		else
		{
			insert(pos, *iElems);
		}
	}

	return it;
}

template<typename T, class Allocator>
bool my::list<T, Allocator>::iterator::operator!=(const iterator& otherIt) const
{
	return (otherIt.m_itNode != this->m_itNode);
}

template<typename T, class Allocator>
bool my::list<T, Allocator>::iterator::operator==(const iterator& otherIt) const
{
	return (otherIt.m_itNode == this->m_itNode);
}

template<typename T, class Allocator>
const T* my::list<T, Allocator>::iterator::operator->() const
{
	return &m_itNode->m_data;
}

template<typename T, class Allocator>
typename my::list<T, Allocator>::iterator& my::list<T, Allocator>::iterator::operator++()
{
	this->m_itNode = m_itNode->m_next;

	return *this;
}

template<typename T, class Allocator>
typename my::list<T, Allocator>::iterator my::list<T, Allocator>::iterator::operator++(const int a)
{
	iterator it(this->m_itNode);

	if (m_itNode->m_next != nullptr)
	{
		*this = m_itNode->m_next;
	}

	return it;
}

template<typename T, class Allocator>
typename my::list<T, Allocator>::iterator my::list<T, Allocator>::iterator::operator--(const int a)
{
	iterator it(this->m_itNode);
	
	if (m_itNode->m_prev != nullptr)
	{
		*this = m_itNode->m_prev;
	}

	return it;
}


template<typename T, class Allocator>
T& my::list<T, Allocator>::iterator::operator*()
{
	return this->m_itNode->m_data;
}

template<typename T, class Allocator>
my::list<T, Allocator>& my::list<T, Allocator>::operator=(my::list<T, Allocator>&& other) noexcept
{
	for (node* iNode = m_head; iNode != nullptr; /**/)
	{
		node* currNode = iNode;
		iNode = iNode->m_next;

		currNode->m_data.~T();
		currNode->~node();

		Allocator::template rebind<node>::other().deallocate(currNode, 1);
	}

	m_head = other.m_head;
	m_tail = other.m_tail;
	m_size = other.m_size;

	other.m_head = nullptr;
	other.m_tail = nullptr;
	other.m_size = 0;

	return *this;
}

template<typename T, class Allocator>
template <class... Args>
void my::list<T, Allocator>::emplace_back(Args&&... args)
{
	node* newNode = Allocator::template rebind<node>::other().allocate(1);

	new (newNode) node(args...);

	newNode->m_next = nullptr;

	if (m_size == 0)
	{
		newNode->m_prev = nullptr;
		m_head = newNode;
	}

	else
	{
		m_tail->m_next = newNode;
		newNode->m_prev = m_tail;
	}

	m_tail = newNode;
	m_size++;
}