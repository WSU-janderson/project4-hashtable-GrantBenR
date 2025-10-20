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
class HashTableBucket
{
    private:
        // Normal – the bucket is non-empty and currently storing a key-value pair
        // Empty Since Start (ESS) – the bucket has never had a key-value pair
        // Empty After Remove (EAR) – the bucket previously stored a key-value pair, but that pair was later removed from the table.
        enum class BucketType {NORMAL, ESS, EAR};
    public:
        HashTableBucket();
        HashTableBucket(std::string key, int value);
        void load(std::string key, int value);
        bool isEmpty() const;
        bool isNormal() const;
        bool isEmptySinceStart() const;
        bool isEmptyAfterRemove() const;
        void setNormal(bool val);
        void setEmptySinceStart(bool val);
        void setEmptyAfterRemove(bool val);
        friend std::ostream& operator<<(std::ostream& os, const HashTableBucket& bucket);
};


#endif //HASHTABLEBUCKET_H