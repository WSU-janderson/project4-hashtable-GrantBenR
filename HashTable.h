/**
 * HashTable.h
 *
 * Author: Grant Rynders
 * Class: CS3100
 * Professor: James Anderson
 * Assignment: Project 4
 * Date Created 10/20/25
 *
 */
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <optional>
#include <string>
#include <ostream>
#include <vector>

#include "HashTableBucket.h"

class HashTable
{
    private:
        std::vector<std::vector<HashTableBucket>>* tableData;
        std::vector<size_t> probeOffsets;
        size_t numElements;
        static const std::hash<std::string> hasher;
        static const std::vector<HashTableBucket> BucketGroupDefault;
        bool rehash_table(size_t new_capacity);
        bool resize_table();
        void set_probe_offsets(size_t N=8);
        size_t hash(const std::string& str) const;
        size_t get_index(const std::string& key, size_t modulo) const;
        std::vector<HashTableBucket>& get_bucket_group(const std::string& key);
        std::vector<HashTableBucket>& get_bucket_group(const std::string& key) const;
        std::optional<std::reference_wrapper<HashTableBucket>> get_bucket(const std::string& key);
        std::optional<std::reference_wrapper<HashTableBucket>> get_bucket(const std::string& key) const;
    public:
        HashTable(size_t initCapacity=8);
        bool insert(std::string key, size_t value);
        bool update(const std::string& key, size_t value);
        bool remove(std::string key);
        bool contains(std::string key) const;
        std::optional<size_t> get(const std::string& key) const;
        size_t& operator[](const std::string& key);
        std::vector<std::string> keys() const;
        double alpha() const;
        size_t capacity() const;
        size_t size() const;
        void set_size(size_t new_num_elements);
        size_t vector_size() const;
        friend std::ostream& operator<<(std::ostream& os, const HashTable& hashTable);
};
#endif