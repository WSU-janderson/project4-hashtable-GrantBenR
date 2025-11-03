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
#include <variant>


int main()
{
    // I was really busy the last couple weeks and I am not writing test cases for all the functions again lmao
    // These should cover 99% of realistic cases

    std::cout << "- - - - - - - - - -" << " BASIC INSERT " << "- - - - - - - - - -" << std::endl;
    HashTable hash_table = HashTable(10);
    std::cout << "Initial Table: " << std::endl;
    std::cout << hash_table << std::endl;
    double alpha = hash_table.alpha();
    hash_table.insert("FOOBAR", 67);
    hash_table.insert("WUMBO", 41);
    hash_table.insert("BAT", 21);
    std::cout << "Table after insert: " << std::endl;
    std::cout << hash_table << std::endl;

    std::cout << "- - - - - - - - - -" << " BASIC GET " << "- - - - - - - - - -" << std::endl;
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

    std::cout << "- - - - - - - - - -" << " BASIC REMOVE " << "- - - - - - - - - -" << std::endl;

    hash_table.remove("FOOBAR");

    std::cout << "Table after removing \"FOOBAR\": " << std::endl;

    std::cout << hash_table << std::endl;

    std::cout << "- - - - - - - - - -" << " BASIC RESIZE (A LOT OF INSERTS) " << "- - - - - - - - - -" << std::endl;

    hash_table.insert("KANGAROO", 23);
    hash_table.insert("FEIFONGWONG", 56);
    hash_table.insert("XENOGEARS", 123);
    hash_table.insert("ELHAYM", 456);
    hash_table.insert("AGNES", 789);
    hash_table.insert("KEVES", 701);
    std::cout << "Table after insert 1: " << std::endl;
    std::cout << hash_table << std::endl;

    hash_table.insert("CAT", 27);
    hash_table.insert("RAT", 29);
    hash_table.insert("TAC", 20);
    hash_table.insert("CTB", 23);
    hash_table.insert("PATRICK STAR", 19);

    std::cout << "Table after insert 2: " << std::endl;
    std::cout << hash_table << std::endl;

    std::cout << "- - - - - - - - - -" << " REMOVE FROM RESIZED TABLE " << "- - - - - - - - - -" << std::endl;
    hash_table.remove("ELHAYM");

    std::cout << "Table after removing \"ELHAYM\": " << std::endl;
    std::cout << hash_table << std::endl;

    std::cout << "- - - - - - - - - -" << " BASIC CONTAINS " << "- - - - - - - - - -" << std::endl;
    std::cout << "Does table contain \"CAT\"?: " << hash_table.contains("CAT") << std::endl;
    std::cout << "Does table contain \"ELHAYM\"?: " << hash_table.contains("ELHAYM") << std::endl;
    return 0;
}
