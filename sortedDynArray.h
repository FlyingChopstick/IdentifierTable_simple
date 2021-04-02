#ifndef SORTEDDYNARRAY_H
#define SORTEDDYNARRAY_H

#endif // SORTEDDYNARRAY_H

template <class T>
class SortedList
{
public:
        SortedList()
        {
                capacity = 0;
                valueCount = 0;
                values = new T[capacity];
                compares = 0;
        }
        ~SortedList()
        {
                delete[] values;
        }

        void add(T data)
        {
                if (valueCount >= capacity)
                        resize();

                values[valueCount] = data;
                valueCount++;
                sort();
        }
        T* at(int index)
        {
                return &values[index];
        }
        void setAt(int index, T data)
        {
                if (index >= 0 && index <= valueCount)
                {
                        values[index] = data;
                }
        }
        void remove(T* element)
        {
                for (int i = 0; i < valueCount; i++)
                {
                        compares++;
                        if (values[i] == *element)
                        {
                                shiftLeft(i);
                                return;
                        }
                }
        }
        void removeAt(int index)
        {
                shiftLeft(index);
        }
        void clear(bool resetCapacity = true)
        {
                valueCount = 0;
                if (resetCapacity)
                        capacity = 1;

                delete[] values;
                values = new T[capacity];
        }
        bool contains(T element)
        {
                return indexOf(&element) != -1;
        }
        int indexOf(T* element)
        {
                int start = 0;
                int end = (valueCount);

                while (start < end)
                {
                        int middle = (start + end) / 2;

                        compares++;
                        if (*element == values[middle])
                        {
                                return middle;
                        }
                        compares++;
                        if (*element < values[middle])
                        {
                                end = middle;
                        }
                        else
                        {
                                start = middle + 1;
                        }
                }

                return -1;
        }

        unsigned int size() { return valueCount; }
        unsigned int getCompares() { return compares; }
        void resetStats() { compares = 0; }

private:
        void sort()
        {
                if (valueCount <= 1)
                {
                        return;
                }

                T key;
                int j;

                for (unsigned int i = 0; i < valueCount; i++)
                {
                        key = values[i];
                        j = i - 1;

                        while (j >= 0 && values[j] > key)
                        {
                                compares++;
                                values[j + 1] = values[j];
                                j--;
                        }
                        values[j + 1] = key;
                }
        }
        void resize()
        {
                int newCapacity;
                if (capacity <= 0)
                {
                        capacity = 1;
                        values = new T[capacity];
                        return;
                }
                else
                        newCapacity = capacity * 2;

                T* newData = new T[newCapacity];
                for (unsigned int i = 0; i < valueCount; i++)
                {
                        newData[i] = values[i];
                }

                delete[] values;
                values = newData;
                capacity = newCapacity;

        }
        void shiftLeft(int index)
        {
                if (index < capacity)
                {
                        int counter = 0;
                        T* newData = new T[capacity];
                        for (int i = 0; i < valueCount; i++)
                        {
                                if (i != index)
                                {
                                        newData[counter] = values[i];
                                        counter++;
                                }
                        }

                        delete[] values;
                        values = newData;
                        valueCount = counter;
                }
        }

        T* values;
        unsigned int valueCount;
        unsigned int capacity;

        unsigned int compares;
};
