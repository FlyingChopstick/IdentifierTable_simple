#ifndef HASHTABLE_H
#define HASHTABLE_H

#endif // HASHTABLE_H
#include <string>
#include <math.h>

class DynamicArray
{
public:
	std::string* operator[](std::size_t index)
	{
		return this->at(index);
	}

	DynamicArray(unsigned int capacity = 1)
	{
		_data = new std::string[capacity];
		_capacity = capacity;
		_size = 0;

		resize();
	}
	DynamicArray(const DynamicArray& other)
	{
		_capacity = other._capacity;
		_size = other._size;
		_data = new std::string[_capacity];

		for (size_t i = 0; i < _size; i++)
		{
			_data[i] = other._data[i];
		}
	}

	void add(std::string element)
	{
		if (_size >= _capacity)
		{
			resize();
		}

		_data[_size] = element;
		_size++;
	}
	std::string* at(unsigned int index)
	{
		if (index >= _capacity)
		{
			resize();
		}

		auto test = _data[index];
		return &_data[index];
	}
    bool setAt(unsigned int index, std::string* value)
	{
		while (index >= _capacity)
		{
			resize();
		}

        std::string probe = _data[index];

		if (_data[index] == *value)
		{
			return true;
		}

		if (_data[index] != "EMPTY")
		{
			return false;
		}

		_data[index] = *value;

		return true;
	}
	void clearSlot(unsigned int index)
	{
		while (index < _size)
		{
			resize();
		}

		_data[index] = "EMPTY";
	}

	inline unsigned int size() { return _size; }
	inline unsigned int capacity() { return _capacity; }
private:
	void resize()
	{
		unsigned int newCapacity = _capacity * 2;
		std::string* newData = new std::string[newCapacity];

		for (unsigned int i = 0; i < _size; i++)
		{
			newData[i] = _data[i];
		}
		for (unsigned int i = _size; i < newCapacity; i++)
		{
			newData[i] = "EMPTY";
		}

		delete[] _data;
		_data = newData;
		_capacity = newCapacity;
	}
	void shiftLeft(unsigned int index)
	{
		for (size_t i = index; i < _size - 1; i++)
		{
			_data[i] = _data[i + 1];
		}

		_size--;
	}

	unsigned int
		_capacity,
		_size;
	std::string* _data;
};

class HashTable
{
public:
	unsigned int add(std::string* element)
	{
		auto h = hash(element);

		while (!values.setAt(h, element))
		{
            h++;// = rehash(h);
		}

        return h;
	}

	bool contains(std::string* element)
	{
		resetStats();
		auto h = hash(element);
		auto endIndex = h - 1;

		while (h != endIndex)
		{
			compares++;
			auto testElement = *(values.at(h));
			if (testElement == *element)
			{
				return true;
			}

			h++;
		}

		return false;
	}

	void resetStats()
	{
		compares = 0;
	}
    unsigned int getCompares() { return compares; }

	unsigned int hash(std::string* line)
	{
		double lineSum = 0.0f;

		for (unsigned int i = 0; i < line->length(); i++)
		{
			lineSum += (int)line->at(i);
		}

		return (unsigned int)(379 * fmod(lineSum * A, 1));
	}

private:
    //Used to calculate the hash
    const double A = 0.3457829945;
    DynamicArray values;
	unsigned int compares;
};
