#pragma once
#include <string>

using std::string;

/**
 * @brief Open camera, show live preview.
 * SPACE to save the photo. ESC to cancel.
 * @param path The path to the image.
 * @returns true if a photo was saved.
*/
bool capture(string path);
/**
 * @brief Read the photo and extract first, last, and banner.
 * @param path The path to the image.
 * @param first Saves first name.
 * @param last Saves last name.
 * @param banner Saves banner number.
 * @return true if all 3 are set.
*/
bool compile_DalCard(string path, string* first, string* last, string* banner);
