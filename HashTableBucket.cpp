/**
* HashTableBucket.cpp
 *
 * Author: Grant Rynders
 * Class: CS3100
 * Professor: James Anderson
 * Assignment: Project 4
 * Date Created 10/20/25
 *
 */

#include "HashTableBucket.h"
#include <string>

/**
 * The default constructor can simply set the bucket type to ESS.
 */
HashTableBucket::HashTableBucket()
{

}
/**
 * A parameterized constructor could initialize the key and value, as
 * well as set the bucket type to NORMAL.
 *
 * @param key
 * @param value
 */
HashTableBucket::HashTableBucket(std::string key, int value)
{

}
/**
 * A load method could load the key-value pair into the bucket, which
 * should then also mark the bucket as NORMAL.
 *
 * @param key
 * @param value
 */
void HashTableBucket::load(std::string key, int value)
{

}
/**
 * This method would return whether the bucket is empty, regardless of
 * if it has had data placed in it or not.
 *
 * @return
 */
bool HashTableBucket::isEmpty() const
{
    return false;
}

/**
 *
 * @return
 */
bool HashTableBucket::isNormal() const
{
    return false;
}
/**
 *
 * @return
 */
bool HashTableBucket::isEmptySinceStart() const
{
    return false;
}
/**
 *
 * @return
 */
bool HashTableBucket::isEmptyAfterRemove() const
{
    return false;
}
/**
 *
 * @param val
 */
void HashTableBucket::setNormal(const bool val)
{

}
/**
 *
 * @param val
 */
void HashTableBucket::setEmptySinceStart(const bool val)
{

}
/**
 *
 * @param val
 */
void HashTableBucket::setEmptyAfterRemove(const bool val)
{

}
/**
 * The stream insertion operator could be overloaded to print the
 * bucket's contents. Or if preferred, you could write a print method
 * instead.
 *
 * @param os
 * @param bucket
 * @return
 */
std::ostream& operator<<(std::ostream& os, const HashTableBucket& bucket)
{
    return os;
}