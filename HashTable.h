/**
 * HashTable.h
 *
 * Grant Rynders - CS3100 - Project 4
 */
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <optional>
#include <string>
#include <ostream>
#include <vector>
class HashTable
{
    private:

    public:
        HashTable(size_t initCapacity=8);
        bool insert(std::string key, size_t value);
        bool remove(std::string key);
        bool contains(std::string key) const;
        std::optional<int> get(const std::string& key) const;
        int& operator[](const std::string& key);
        std::vector<std::string> keys() const;
        double alpha() const;
        size_t capacity() const;
        size_t size() const;
        friend std::ostream& operator<<(std::ostream& os, const HashTable& ht);
};
#endif