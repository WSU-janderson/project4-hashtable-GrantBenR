/**
 * HashTable.cpp
 *
 * Author: Grant Rynders
 * Class: CS3100
 * Professor: James Anderson
 * Assignment: Project 4
 * Date Created 10/20/25
 *
 */
#include "HashTable.h"
#include "HashTableBucket.h"
#include <optional>
#include <string>
#include <ostream>
#include <random>
#include <vector>

const std::hash<std::string> HashTable::hasher = std::hash<std::string>{};

size_t HashTable::hash(const std::string& str, size_t multiplier)
{
    // size_t hash_val = 0;
    // for (char c : str)
    // {
    //     hash_val = (c * multiplier) + hash_val;
    // }
    return hasher(str);
}
/**
 * Only a single constructor that takes an initial capacity for the table is
 * necessary. If no capacity is given, it defaults to 8 initially
 *
 * @param initCapacity
 * @return void
 */
HashTable::HashTable(const size_t initCapacity)
{
    this->tableData = new std::vector<HashTableBucket>(initCapacity);
}
/**
 * Insert a new key-value pair into the table. Duplicate keys are NOT allowed. The
 * method should return true if the insertion was successful. If the insertion was
 * unsucessful, such as when a duplicate is attempted to be inserted, the method
 * should return false
 *
 * @param key
 * @param value
 * @return bool
 */
bool HashTable::insert(std::string key, size_t value)
{
    bool wasTableResized = checkTableSize();
    return false;
}
/**
 * If the key is in the table, remove will “erase” the key-value pair from the
 * table. This might just be marking a bucket as empty-after-remove
 *
 * @param key
 * @return
 */
bool HashTable::remove(std::string key)
{
    if (this->contains(key))
    {
        this->tableData->at(0).setEmptyAfterRemove();
        return true;
    }
    else
    {
        return false;
    }
}
/**
 * contains returns true if the key is in the table and false if the key is not in
 * the table.
 *
 * @param key
 * @return
 */
bool HashTable::contains(std::string key) const
{
    size_t N = this->size();
    size_t home = 0;
    for (const size_t offset_val : this->probeOffsets)
    {
        const size_t probe_val = (home + offset_val) % N;
        if (probe_val == 0)
        {
            return true;
        }
    }
    return false;
}
/**
 * If the key is found in the table, find will return the value associated with
 * that key. If the key is not in the table, find will return something called
 * nullopt, which is a special value in C++. The find method returns an
 * optional<size_t>, which is a way to denote a method might not have a valid value
 * to return. This approach is nicer than designating a special value, like -1, to
 * signify the return value is invalid. It's also much better than throwing an
 * exception if the key is not found.
 *
 * @param key
 * @return
 */
std::optional<size_t> HashTable::get(const std::string& key) const
{
    if (this->contains(key))
    {

    }
    else
    {
        return std::nullopt;
    }
}
/**
 * The bracket operator lets us access values in the map using a familiar syntax,
 * similar to C++ std::map or Python dictionaries. It behaves like get, returnin
 * the value associated with a given key:
 *  int idNum = hashTable[“James”];
 * Unlike get, however, the bracker operator returns a reference to the value,
 * which allows assignment:
 *  hashTable[“James”] = 1234;
 * If the key is not in the table, returning a valid reference is impossible.
 * You may choose to throw an exception in this case, but for our implementation, the situation
 * results in undefined behavior. Simply put, you do not need to address attempts
 * to access keys not in the table inside the bracket operator method.
 *
 * @param key
 * @return
 */
int& HashTable::operator[](const std::string& key)
{
    if (this->contains(key))
    {
        return int&;
    }
    else
    {
        throw std::out_of_range("Operator[] Error: Key Not Found in Table");
    }
}

/**
 * keys returns a std::vector (C++ version of ArrayList, or simply list/array)
 * with all of the keys currently in the table. The length of the vector should be
 * the same as the size of the hash table.
 *
 * @return
 */
std::vector<std::string> HashTable::keys() const
{
    std::vector<std::string> return_keys;
    for (const HashTableBucket& bucket : *(this->tableData))
    {
        return_keys.push_back(bucket.getKey());
    }
    return return_keys;
}
/**
 * alpha returns the current load factor of the table, or size/capacity. Since
 * alpha returns a double,make sure to properly cast the size and capacity, which
 * are size_t, to avoid integer division. You can cast a size_t num to a double in
 * C++ like:
 *  static_cast<double>(num)
 * The time complexity for this method must be O(1).
 *
 * @return
 */
double HashTable::alpha() const
{
    if (this->capacity() != 0)
    {
        const double size_double = static_cast<double>(this->size());
        const double capacity_double = static_cast<double>(this->capacity());
        return size_double / capacity_double;
    }
    else
    {
        throw std::runtime_error("HashTable::alpha() capacity cannot be zero");
    }
}

/**
 * capacity returns how many buckets in total are in the hash table. The time
 * complexity for this algorithm must be O(1).
 *
 * @return
 */
size_t HashTable::capacity() const
{
    return this->tableData->capacity();
}

/**
 * The size method returns how many key-value pairs are in the hash table. The
 * time complexity for this method must be O(1)
 *
 * @return
 */
size_t HashTable::size() const
{
    return this->tableData->size();
}

/**
 *
 * @param newSize
 */
void HashTable::setSize(const size_t newSize)
{
    this->tableData->resize(newSize);
    this->setProbeOffsets(newSize);
}

/**
 * Updates table size if the alpha is bad
 *
 * @return
 */
bool HashTable::checkTableSize()
{
    // When load factor exceeds 0.5, table must be resized
    if (this->alpha() >= 0.5)
    {
        // Double table size
        this->setSize(this->size() * 2);
        return true;
    }
    else
    {
        return false;
    }
}
/**
 * Get vector<size_t> of size N in a random order
 *
 * @return
 */
void HashTable::setProbeOffsets(size_t N)
{
    std::vector<size_t> offsets = std::vector<size_t>(N);
    std::iota(offsets.begin(), offsets.end(), 1);
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(offsets.begin(), offsets.end(), rng);
    this->probeOffsets = offsets;
}
/**
 * operator<< is another example of operator overloading in C++, similar to
 * operator[]. The friend keyword only needs to appear in the class declaration,
 * but not the definition. In addition, operator<< is not a method of HashTable,
 * so do not put HashTable:: before it when defining it. operator<< will allow us
 * to print the contents of our hash table using the normal syntax:
 *  cout << myHashTable << endl;
 * You should only print the buckets which are occupied,
 * and along with each item you will print which bucket (the index of the bucket)
 * the item is in. To make it easy, I suggest creating a helper method called
 * something like printMe() that returns a string of everything in the table. An
 * example which uses open addressing for collision resolution could print
 * something like:
 *  Bucket 5: <James, 4815>
 *  Bucket 2: <Juliet, 1623>
 *  Bucket 11: <Hugo, 42108>
 *
 * @param os
 * @param hashTable
 * @return
 */
std::ostream& operator<<(std::ostream& os, const HashTable& hashTable)
{
    size_t count = 0;
    for (const HashTableBucket& bucket : *(hashTable.tableData))
    {
        os << "Bucket " << count << ": " << bucket << std::endl;
        count += 1;
    }
    return os;
}