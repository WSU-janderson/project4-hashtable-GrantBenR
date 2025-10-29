/**
 * HashTableBucket.h
 *
 * Author: Grant Rynders
 * Class: CS3100
 * Professor: James Anderson
 * Assignment: Project 4
 * Date Created 10/20/25
 *
 */

#ifndef HASHTABLEBUCKET_H
#define HASHTABLEBUCKET_H

#include <string>
#include <ostream>


/**
 * Normal – the bucket is non-empty and currently storing a key-value pair
 * Empty Since Start (ESS) – the bucket has never had a key-value pair
 * Empty After Remove (EAR) – the bucket previously stored a key-value pair, but that pair was later removed from the table.
 */
enum class BucketType {NORMAL, ESS, EAR};

class HashTableBucket
{
    private:
        BucketType bucket_type;
        std::string bucket_key;
        size_t bucket_value;
    public:
        // CONSTRUCTORS
        HashTableBucket();
        HashTableBucket(std::string key, size_t value);
        // METHODS
        void load(std::string key, size_t value);
        // GETTERS
        BucketType getBucketType() const;
        std::string getKey() const;
        bool isEmpty() const;
        bool isNormal() const;
        bool isEmptySinceStart() const;
        bool isEmptyAfterRemove() const;
        size_t getValue() const;
        size_t& getValueRef();
        // SETTERS
        void setNormal();
        void setEmptySinceStart();
        void setEmptyAfterRemove();
        void setKey(std::string key_value);
        void setValue(size_t input_value);
        // EQUALITY OPERATORS
        HashTableBucket& operator=(const HashTableBucket& bucket);
        // BOOLEAN OPERATORS
        bool operator==(const HashTableBucket& bucket) const;
        bool operator!=(const HashTableBucket& bucket) const;
        bool operator<(const HashTableBucket& bucket) const;
        bool operator>(const HashTableBucket& bucket) const;
        // OSTREAM OPERATORS
        friend std::ostream& operator<<(std::ostream& os, const HashTableBucket& bucket);
};


#endif //HASHTABLEBUCKET_H