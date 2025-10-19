#pragma once
#include <iostream>
#include <vector>
template <typename T>
class CircularBuffer
{
private:
	std::vector<T> _buffer;
	size_t _capacity;
	size_t _size;
	int _tail;
	int _head;
public:
	CircularBuffer(size_t capacity)
		: _buffer(capacity), _size(0), _capacity(capacity), _tail(0), _head(0)
	{
	};

	inline size_t size()const { return _size; }
	inline size_t capacity() const { return _capacity; }
	inline bool empty() const
	{
		if (_size == 0)
		{
			return true;
		}
		return false;
	}

    void push_back(const T& item)
{
	_buffer[_tail] = item;
	_tail = (_tail + 1) % _capacity;
	if (_size < _capacity)
	{
		_size++;
	}
	else
	{
		_head = (_head + 1) % _capacity;
	}

}
void pop_front()
{
	if (!empty())
	{
		_size--;
		_head = (_head + 1) % _capacity;
	}
}
};