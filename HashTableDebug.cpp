/**
 * HashTableDebug.cpp
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
#include <iostream>
#include <vector>
#include <string>
#include <optional>


int main()
{
    HashTable hash_table = HashTable(10);
    std::cout << "Initial Table: " << std::endl;
    std::cout << hash_table << std::endl;
    hash_table.insert("FOOBAR", 67);
    hash_table.insert("WUMBO", 41);
    hash_table.insert("BAT", 21);
    std::cout << "Table after insert: " << std::endl;
    std::cout << hash_table << std::endl;
    auto index = hash_table.get_index("FOOBAR", hash_table.capacity());
    std::cout << "Index: " << index << std::endl;
    auto bucket = hash_table.get("FOOBAR");
    std::cout << "Get response: ";
    if (bucket != std::nullopt)
    {
         std::cout << bucket.value();
    }
    else
    {
        std::cout << "NOT FOUND";
    }
    std::cout << std::endl;
    hash_table.remove("FOOBAR");

    std::cout << "Table after remove: " << std::endl;

    std::cout << hash_table << std::endl;



    return 0;
}