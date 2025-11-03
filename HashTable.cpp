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
#include <algorithm>
#include <iostream>

// STATIC HASHER OBJECT FOR STRINGS
const std::hash<std::string> HashTable::hasher = std::hash<std::string>{};
// Static default bucket group configuration: vector with size 1 with an ESS bucket with key "" and value 0
const std::vector<HashTableBucket> HashTable::BucketGroupDefault = std::vector<HashTableBucket>(1, HashTableBucket());
/**
 * If the alpha is greater than 0.5, we need to double the capacity of the table without modding the size.
 * Old code that completely reindexed the table commented out since it is not necessary.
 *
 * @param new_capacity
 * @return
 */
bool HashTable::rehash_table(size_t new_capacity)
{
    const size_t new_size = this->vector_size() * 2;
    //Create a new table with our new capacity
    std::vector<std::vector<HashTableBucket>> new_table(new_size, BucketGroupDefault);
    // Because the index of our keys relies on capacity, when we resize the table we need to reindex everything

    // Iterate over groups of buckets
    for (std::vector<HashTableBucket> &bucket_group : *(this->tableData))
    {
        // Check each bucket
        for (const HashTableBucket& bucket : bucket_group)
        {
            std::string bucket_key = bucket.getKey();
            if (!bucket_key.empty())
            {
                const size_t index = get_index(bucket_key, new_size);
                if (new_table[index].front().isEmptySinceStart())
                {
                    new_table[index].front() = bucket;
                }
                else
                {
                    new_table[index].emplace_back(bucket);
                }
            }
        }
    }
    // Set tableData to our new table
    this->tableData->swap(new_table);
    // Double new_capacity
    new_capacity *= 2;
    this->tableData->reserve(new_capacity);
    if (this->capacity() == new_capacity)
    {
        return true;
    }
    else
    {
        return false;
    }
}
/**
 * Updates table size if the alpha is greater than 0.5
 *
 * @return
 */
bool HashTable::resize_table()
{
    // When load factor exceeds 0.5, table must be resized
    const double current_alpha = this->alpha();
    if (current_alpha > 0.5)
    {
        // Get current capacity
        const size_t new_capacity = this->capacity();
        // Double table capacity and rehash the whole table
        return rehash_table(new_capacity);
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
void HashTable::set_probe_offsets(const size_t N)
{
    std::vector<size_t> offsets = std::vector<size_t>(N);
    std::iota(offsets.begin(), offsets.end(), 1);
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(offsets.begin(), offsets.end(), rng);
    this->probeOffsets = offsets;
}
/**
 * Hash a string using the builtin static hasher defined above
 *
 * @param str
 * @return
 */
size_t HashTable::hash(const std::string& str) const
{
    return hasher(str);
}
/**
 * Gets the index value for a given string key using the hash() function and modulo input value
 *
 * @param key
 * @param modulo
 * @return
 */
size_t HashTable::get_index(const std::string& key, const size_t modulo) const
{
    return (this->hash(key) % modulo);
}
/**
 * Gets reference to the vector group of buckets at the key's index in the hashtable
 *
 * @param key
 * @return
 */
std::vector<HashTableBucket>& HashTable::get_bucket_group(const std::string& key)
{
    const size_t index = this->get_index(key, this->vector_size());
    std::vector<HashTableBucket>& bucket_group = this->tableData->at(index);
    return bucket_group;
}
/**
 * Gets const reference to the vector group of buckets at the key's index in the hashtable
 *
 * @param key
 * @return
 */
std::vector<HashTableBucket>& HashTable::get_bucket_group(const std::string& key) const
{
    const size_t index = this->get_index(key, this->vector_size());
    std::vector<HashTableBucket>& bucket_group = this->tableData->at(index);
    return bucket_group;
}
/**
 * Returns optional reference to a bucket with key at bucket group at an index defined by key
 *
 * @param key
 * @return
 */
std::optional<std::reference_wrapper<HashTableBucket>> HashTable::get_bucket(const std::string& key)
{
    // Check if key already exists
    std::vector<HashTableBucket>& bucket_group = this->get_bucket_group(key);
    std::optional<std::reference_wrapper<HashTableBucket>> valid_empty_bucket;
    // Iterate through all the buckets and try and find the bucket with our string key
    for (HashTableBucket& bucket : bucket_group)
    {
        if (!bucket.isNormal())
        {
            // Record any empty buckets we find, if we don't find the bucket with our string key, we want to return an empty one to plop it into.
            valid_empty_bucket = bucket;
        }
        else
        {
            if (bucket.getKey() == key)
            {
                return bucket;
            }
        }
    }
    // If no buckets were found with our string key, return an empty bucket if there is one
    if (valid_empty_bucket != std::nullopt)
    {
        return valid_empty_bucket.value();
    }
    else // if there is no string key and no empty bucket, then add a new empty bucket and return it
    {
        bucket_group.emplace_back(HashTableBucket());
        return bucket_group.back();
    }
}
/**
 * Returns const optional reference to a bucket with key at bucket group at an index defined by key
 * @param key
 * @return
 */
std::optional<std::reference_wrapper<HashTableBucket>> HashTable::get_bucket(const std::string& key) const
{
    std::vector<HashTableBucket>& bucket_group = this->get_bucket_group(key);
    // Check if key already exists
    for (HashTableBucket& bucket : bucket_group)
    {
        if (bucket.getKey() == key)
        {
            return bucket;
        }
    }
    return std::nullopt;
}
/**
 * Add new bucket group to the end of tableData
 *
 * @param newBuckets
 * @return
 */
bool HashTable::push_back(const std::vector<HashTableBucket>& newBuckets)
{
    std::string new_key = newBuckets.front().getKey();
    this->tableData->push_back(newBuckets);
    this->set_size(this->size() + 1);
    bool wasTableResized = this->resize_table();
    return true;
}
/**
 * Only a single constructor that takes an initial capacity for the table is
 * necessary. If no capacity is given, it defaults to 8 initially
 *
 * @param initCapacity
 * @return void
 */
HashTable::HashTable(const size_t initCapacity) : numElements(0)
{
    this->tableData = new std::vector<std::vector<HashTableBucket>>(initCapacity, BucketGroupDefault);
    this->tableData->reserve(initCapacity * 2);
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
    // Check if key already exists
    auto bucket = get_bucket(key);
    if (bucket != std::nullopt)
    {
        if (!bucket->get().isNormal())
        {
            bucket->get().setKey(key);
            //Update value of bucket
            bucket->get().setValue(value);
            // Set bucket type to normal
            bucket->get().setNormal();
            this->set_size(this->size() + 1);
            bool wasTableResized = this->resize_table();
            return true;
        }
        else
        {
            return false;
        }
    }
}

/**
 * Similar to Insert except if bucket exists at key it updates the value and returns true. Does not add to table if not found.
 * @param key
 * @param value
 * @return
 */
bool HashTable::update(const std::string& key, const size_t value)
{
    // Check if key already exists
    auto bucket = get_bucket(key);
    if (bucket != std::nullopt)
    {
        // Update value of bucket
        bucket->get().setValue(value);
        // Set bucket type to normal
        bucket->get().setNormal();
        return true;
    }
    else
    {
        return false;
    }
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
    // Check if key already exists
    auto bucket = get_bucket(key);
    if (bucket != std::nullopt)
    {
        if (bucket->get().isNormal())
        {
            // Update value to default 0
            bucket->get().setValue(0);
            // Update bucketType to EAR
            bucket->get().setEmptyAfterRemove();
            this->set_size(this->size() - 1);
            return true;
        }
        else
        {
            return false;
        }
    }
    // If key does not already exist
    return false;
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
    std::vector<HashTableBucket> bucket_group = this->get_bucket_group(key);
    // Search the bucket group for a bucket with the given key
    for (HashTableBucket &bucket : bucket_group)
    {
        if (bucket.getKey() == key)
        {
            // if the bucket has the key but is empty, then return false
            if (bucket.isNormal())
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    // If key does not already exist
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
    auto bucket = get_bucket(key);
    if (bucket != std::nullopt)
    {
        if (bucket->get().isNormal())
        {
            return bucket->get().getValue();
        }
    }
    return std::nullopt;
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
size_t& HashTable::operator[](const std::string& key)
{
    // Check if key already exists
    auto bucket = get_bucket(key);
    if (bucket != std::nullopt)
    {
        return bucket->get().getValueRef();
    }
    else
    {
        throw std::runtime_error("Operator[]: Table[Key] not found");
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
    for (std::vector<HashTableBucket> &bucket_group : *(this->tableData))
    {
        for (const HashTableBucket& bucket : bucket_group)
        {
            return_keys.push_back(bucket.getKey());
        }
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
        const auto size_double = static_cast<double>(this->size());
        const auto capacity_double = static_cast<double>(this->capacity());
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
    return this->numElements;
}
/**
 * Change the number of elements if we add or remove from the table
 *
 * @param new_num_elements
 */
void HashTable::set_size(const size_t new_num_elements)
{
    this->numElements = new_num_elements;
}
/**
 * Size returns the number of key-value pairs in the vector, vector_size returns the actual TableData.size() including all the empty buckets
 *
 * @return
 */
size_t HashTable::vector_size() const
{
    return this->tableData->size();
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
    const size_t init_size = hashTable.vector_size();
    for (size_t i = 0; i < init_size; i++)
    {

        os << "Bucket " << i << ": ";
        for (const HashTableBucket& bucket : hashTable.tableData->at(i))
        {
            os << bucket << " ";
        }
        os << std::endl;
    }
    return os;
}
