#ifndef HASHTABLE_H
#define HASHTABLE_H

#endif // HASHTABLE_H
#include <string>

class HashTable
{
public:
        HashTable()
        {
                capacity = TABLE_CAPACITY;
                valueCount = 0;
                resetStats();
                values = new std::string[capacity];
        }
        ~HashTable()
        {
                delete[] values;
        }

        unsigned int add(std::string* element)
        {
            //calculate hash
            unsigned int hash = hashString(lowerString(element));
            //get index from hash
            unsigned int index = hash - HASH_MIN;
            compares++;
            //if the slot is occupied
            if (values [index] != EMPTY_STRING 
                && values[index] != *element)
            {
                //rehash, retry
                hash = rehash(hash);
                index = hash - HASH_MIN;
            }
            //set the element in the slot
            values[index] = *element;
            valueCount++;

            return hash;
        }

        void remove(std::string* element)
        {
            //calculate hash
            unsigned int hash = hashString(element);
            //get index
            unsigned int index = hash - HASH_MIN;

            //table bounds check
            while (index < HASH_MAX-HASH_MIN)
            {
                compares++;
                //if the element is found
                if (values[index] == *element)
                {
                    //clear the slot
                    values[index] = EMPTY_STRING;
                    valueCount--;
                    return;
                }
                index++;
            }
            //if nothing found, throw
            throw;
        }

        bool contains(std::string* element)
        {
            //get hash and index
            unsigned int hash = hashString(element);
            //bounds check
            while (hash <= HASH_MAX && hash >= HASH_MIN)
			{
				unsigned int index = hash - HASH_MIN;
                compares++;
                //if element is found
                if (values[index] == *element)
                {
                    return true;
                }
                if (values[index] == EMPTY_STRING)
                {
                    return false;
                }
                //else rehash
                hash += 3;
                if (hash >= HASH_MAX)
                {
                    hash -= HASH_MAX;
                }
                if (hash <= HASH_MIN)
                {
                    hash += HASH_MIN;
                }
            }
            return false;
        }

        void resetStats()
        {
            //_keyCompares = 0;
            compares = 0;
        }
        unsigned int getCompares() { return compares; }

        static unsigned int hashString(std::string* str)
        {
                //sum of the first, 1/3rd and the last chars
                int first = (int)str->at(1);
                int second = (int)str->at(str->length() / 2);
                int third = (int)str->at(str->length() - 2);

                unsigned int hash = first + second + third;

                return hash;
        }

private:
        //convert the string to lowercase (AAA->aaa)
        std::string* lowerString(std::string* line)
        {
                for (int i = 0; i < line->length(); i++)
                {
                        line->at(i) = std::tolower(line->at(i));
                }
                return line;
        }

        //recalculate the hash
        unsigned int rehash(unsigned int hash)
        {
                while (true)
                {
                    hash += 3;

                    if (hash >= HASH_MAX)
                    {
                        hash -= HASH_MAX;
                    }
                    if (hash < HASH_MIN)
                    {
                        hash+=HASH_MIN;
                    }
                    if (values[hash-HASH_MIN] == EMPTY_STRING)
                    {
                        return hash;
                    }
                }
                throw;
        }


        //Hash min value (offset to get the array index)
        const unsigned int HASH_MIN = 144;
        //Hash max value
        const unsigned int HASH_MAX = 366;
        //Greatest prime number <HASH_MAX
        const unsigned int PRIME = 359;
        //The capacity for _keys and _values
        const unsigned int TABLE_CAPACITY = 256;
        //Empty string
        const std::string EMPTY_STRING = "";

        //unsigned int* _keys;
        std::string* values;
        unsigned int valueCount;
        unsigned int capacity;

        //unsigned int _keyCompares;
        unsigned int compares;
};
