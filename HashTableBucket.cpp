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
#include <utility>

/**
 * The default constructor can simply set the bucket type to ESS.
 */
HashTableBucket::HashTableBucket()
{
    this->bucketType = BucketType::ESS;
}
/**
 * A parameterized constructor could initialize the key and value, as
 * well as set the bucket type to NORMAL.
 *
 * @param key (std::string)
 * @param value (int)
 */
HashTableBucket::HashTableBucket(std::string key, int value)
{
    // This is just a wrapper for load essentially
    // It will fill the bucket and set to NORMAL
    this->load(std::move(key), value);
}
/**
 * A load method could load the key-value pair into the bucket, which
 * should then also mark the bucket as NORMAL.
 *
 * @param key (std::string)
 * @param value (int)
 */
void HashTableBucket::load(std::string key, int value)
{
    this->setKey(std::move(key));
    this->setValue(value);
    // Set bucket to normal
    this->setNormal();
}
/**
 * This method would return whether the bucket is empty, regardless of
 * if it has had data placed in it or not.
 *
 * @return
 */
bool HashTableBucket::isEmpty() const
{
    // If the bucket is not normal, then it must be empty or broken for whatever reason
    return (this->getBucketType() != BucketType::NORMAL);
}

/**
 * Is bucketType == BucketType::Normal
 *
 * @return
 */
bool HashTableBucket::isNormal() const
{
    return (this->getBucketType() == BucketType::NORMAL);
}
/**
 * Is bucketType == BucketType::ESS
 *
 * @return
 */
bool HashTableBucket::isEmptySinceStart() const
{
    return (this->getBucketType() == BucketType::ESS);
}
/**
 * Is bucketType == BucketType::Normal
 *
 * @return
 */
bool HashTableBucket::isEmptyAfterRemove() const
{
    return (this->getBucketType() == BucketType::EAR);
}
/**
 * Getter for bucketType enum variable
 *
 * @return
 */
BucketType HashTableBucket::getBucketType() const
{
    return this->bucketType;
}
/**
 *
 * @return
 */
std::string HashTableBucket::getKey() const
{
    return this->key;
}
/**
 *
 * @return
 */
size_t HashTableBucket::getValue() const
{
    return this->value;
}
/**
 *
 * @param val
 */
void HashTableBucket::setNormal()
{
    this->bucketType = BucketType::NORMAL;
}
/**
 *
 * @param val
 */
void HashTableBucket::setEmptySinceStart()
{
    this->bucketType = BucketType::ESS;
}

/**
 *
 * @param val
 */
void HashTableBucket::setEmptyAfterRemove()
{
    this->bucketType = BucketType::EAR;
}
/**
 *
 * @param key_value
 */
void HashTableBucket::setKey(std::string key_value)
{
    this->key = std::move(key_value);
}
/**
 *
 * @param input_value
 */
void HashTableBucket::setValue(const size_t input_value)
{
    this->value = input_value;
}
/**
 *
 * @param bucket
 * @return
 */
HashTableBucket& HashTableBucket::operator=(const HashTableBucket& bucket)
{
    this->bucketType = bucket.bucketType;
    this->key = bucket.key;
    this->value = bucket.value;
    return *this;
}
bool HashTableBucket::operator==(const HashTableBucket& bucket) const
{
    const bool areBucketTypesEqual = (this->bucketType == bucket.bucketType);
    const bool areKeysEqual = (this->key == bucket.key);
    const bool areValuesEqual = (this->value == bucket.value);
    return (areBucketTypesEqual && areKeysEqual && areValuesEqual);
}
bool HashTableBucket::operator!=(const HashTableBucket& bucket) const
{
    const bool areBucketTypesEqual = (this->bucketType == bucket.bucketType);
    const bool areKeysEqual = (this->key == bucket.key);
    const bool areValuesEqual = (this->value == bucket.value);
    return !(areBucketTypesEqual && areKeysEqual && areValuesEqual);
}
bool HashTableBucket::operator<(const HashTableBucket& bucket) const
{
    return (this->value < bucket.value);
}
bool HashTableBucket::operator>(const HashTableBucket& bucket) const
{
    return (this->value > bucket.value);
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