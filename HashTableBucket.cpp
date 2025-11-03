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
HashTableBucket::HashTableBucket() : bucket_type(BucketType::ESS), bucket_value(0){}
/**
 * A parameterized constructor could initialize the key and value, as
 * well as set the bucket type to NORMAL.
 *
 * @param key (std::string)
 * @param value (size_t)
 */
HashTableBucket::HashTableBucket(std::string key, size_t value) : bucket_type(BucketType::NORMAL), bucket_key(key), bucket_value(value){}
/**
 * A load method could load the key-value pair into the bucket, which
 * should then also mark the bucket as NORMAL.
 *
 * @param key (std::string)
 * @param value (size_t)
 */
void HashTableBucket::load(std::string key, size_t value)
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
    return this->bucket_type;
}
/**
 * Getter for this->bucket_key
 *
 * @return
 */
std::string HashTableBucket::getKey() const
{
    return this->bucket_key;
}
/**
 * Getter for this->bucket_value
 *
 * @return
 */
size_t HashTableBucket::getValue() const
{
    return this->bucket_value;
}
/**
 * Getter for reference to this->bucket_value
 *
 * @return
 */
size_t& HashTableBucket::getValueRef()
{
    return this->bucket_value;
}
/**
 * Sets bucket_type to normal
 */
void HashTableBucket::setNormal()
{
    this->bucket_type = BucketType::NORMAL;
}
/**
 * Sets bucket_type to empty since start
 */
void HashTableBucket::setEmptySinceStart()
{
    this->bucket_type = BucketType::ESS;
}

/**
 * Sets bucket_type to empty after removal
 */
void HashTableBucket::setEmptyAfterRemove()
{
    this->bucket_type = BucketType::EAR;
}
/**
 * Setter for bucket key
 * @param key_value
 */
void HashTableBucket::setKey(std::string key_value)
{
    this->bucket_key = std::move(key_value);
}
/**
 * Setter for bucket value
 * @param input_value
 */
void HashTableBucket::setValue(const size_t input_value)
{
    this->bucket_value = input_value;
}
/**
 * Equals operator for bucket. Simply sets bucket_type, key, and value
 *
 * @param bucket
 * @return
 */
HashTableBucket& HashTableBucket::operator=(const HashTableBucket& bucket)
{
    this->bucket_type = bucket.getBucketType();
    this->bucket_key = bucket.getKey();
    this->bucket_value = bucket.getValue();
    return *this;
}
/**
 * Boolean == operator. Checks bucket_type, key, and value
 *
 * @param bucket
 * @return
 */
bool HashTableBucket::operator==(const HashTableBucket& bucket) const
{
    const bool areBucketTypesEqual = (this->getBucketType() == bucket.getBucketType());
    const bool areKeysEqual = (this->getKey() == bucket.getKey());
    const bool areValuesEqual = (this->getValue() == bucket.getValue());
    return (areBucketTypesEqual && areKeysEqual && areValuesEqual);
}
/**
 * Boolean != operator. Checks bucket_type, key, and value
 *
 * @param bucket
 * @return
 */
bool HashTableBucket::operator!=(const HashTableBucket& bucket) const
{
    const bool areBucketTypesEqual = (this->getBucketType() == bucket.getBucketType());
    const bool areKeysEqual = (this->getKey() == bucket.getKey());
    const bool areValuesEqual = (this->getValue() == bucket.getValue());
    return !(areBucketTypesEqual && areKeysEqual && areValuesEqual);
}
/**
 * Compares values of two buckets: less than
 *
 * @param bucket
 * @return
 */
bool HashTableBucket::operator<(const HashTableBucket& bucket) const
{
    return (this->getValue() < bucket.getValue());
}
/**
 * Compares values of two buckets: greater than
 *
 * @param bucket
 * @return
 */
bool HashTableBucket::operator>(const HashTableBucket& bucket) const
{
    return (this->getValue() > bucket.getValue());
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
    os << "<";
    if (bucket.getBucketType() == BucketType::NORMAL)
    {
        os << "\"" << bucket.getKey() << "\"," << bucket.getValue();
    }
    else if (bucket.getBucketType() == BucketType::ESS)
    {
        os << "EES";
    }
    else if (bucket.getBucketType() == BucketType::EAR)
    {
        os << "EAR";
    }
    else
    {
        throw std::runtime_error("Operator<<: Bucket type is not supported");
    }
    os << ">";
    return os;
}