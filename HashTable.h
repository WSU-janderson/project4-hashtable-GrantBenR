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
        void setSize(size_t newSize);
        bool checkTableSize();
        void setProbeOffsets(size_t N=8);
        size_t hash(const std::string& str) const;
        bool push_back(const std::vector<HashTableBucket>& newBuckets);
        static const std::hash<std::string> hasher;
    public:
        HashTable(size_t initCapacity=8);
        bool insert(std::string key, size_t value);
        bool remove(std::string key);
        bool contains(std::string key) const;
        std::optional<size_t> get(const std::string& key) const;
        size_t& operator[](const std::string& key);
        std::vector<std::string> keys() const;
        double alpha() const;
        size_t capacity() const;
        size_t size() const;
        friend std::ostream& operator<<(std::ostream& os, const HashTable& hashTable);
};
#endif