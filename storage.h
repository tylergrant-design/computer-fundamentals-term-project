#pragma once
#include "student.h"


/**
 * @brief Load class_list.csv into a vector array.
*/
void load_class_list();
/** 
 * @brief Load registered.csv into a vector array.
*/
void load_registered();
/** 
 * @brief Append another row in registered.csv.
 * @param s The student to save.
 * @return false if failed to append.
 */
bool save_registered(RegisteredStudent s);
/**
 * @brief Append a registered student to the attendance log.
 * @param s The student to save.
 * @return false if failed to append.
 */
bool save_attendance(RegisteredStudent s);
