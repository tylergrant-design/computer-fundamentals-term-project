#pragma once
#include <string>
#include "student.h"

using std::string;

// ========== Helper Functions ==========
/**
 * @brief Checks to see if a string is a valid banner number.
 * @param s The string to check.
 * @return true if banner number.
 */
bool is_banner(string s);
/**
 * @brief Checks to see is a string is a valid barcode.
 * @param s The string to check.
 * @return true if barcode.
 */
bool is_barcode(string s);
/**
 * @brief Binary search in registered_list by barcode.
 * @param barcode The barcode to search.
 * @returns true if barcode was found.
 */
bool search_registered(string barcode);
/**
 * @brief Binary search in registered_list by barcode.
 * @param barcode The barcode to search.
 * @returns pointer to the student, or nullptr if not found.
 */
RegisteredStudent* find_registered(string barcode);
/**
 * @brief Linear search to find banner number.
 * Because we sort by barcode O(n) is best complexity.
 * @param banner The banner number to search.
 * @return true if banner was found.
 */
bool search_class_list(string banner);
/**
 * @brief Insertion sort of registered_list.
 * Sort by barcode.
 */
void sort_registered();
/**
 * @brief Removes spaces, tabs, and new lines from the front and back of a string.
 * @param s The string to trim.
 * @return The trimmed string.
 */
string trim(string s);
