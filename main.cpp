// Tyler Grant B01097745
// Brady Buffet B01000126

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <cctype>
#include "student.h"
#include "globals.h"
#include "helpers.h"
#include "storage.h"
#include "capture.h"

using namespace std;

enum class Mode { Attendance, Registration, Request };
enum class RegResult { WrongMode, NotInClassList, AlreadyRegistered, SaveFailed, Ok };
enum class CheckInResult { WrongMode, BadScan, NotRegistered, SaveFailed, Ok };


// ========== Data Stores ==========
Mode current_mode = Mode::Attendance;
vector<Student> class_list;
vector<RegisteredStudent> registered_list;
// Attendance log tbd

// ========== Set Operating Mode ==========
/**
 * @brief Updates current_mode.
 * @param selection The desired mode.
 * @return false if selection is not in Mode.
 */
bool mode_selection(string selection);

// ========== Register Student ==========
/**
 * @brief Registers a student on the class list.
 * @param s The student to register.
 * @param barcode The scanned barcode.
 * @return RegResult status.
 */
RegResult register_student(Student s, string barcode);

// ========== Check-in Student ==========
/**
 * @brief Logs the attendance of a student who scanned their barcode.
 * Student must be registered.
 * @param barcode The scanned barcode.
 * @return CheckInResult status.
 */
CheckInResult check_in(string barcode);

// ========== Request Attendance ==========
/**
 * @brief Request the attendance log.
 */
void request_attendance();


// ========== Main ==========
int main() {
    load_class_list();
    load_registered();
    sort_registered();

    // get terminal input
    string line;
    while(cout << "> ", getline(cin, line)) {
        line = trim(line);
        if (line.empty()) continue;
        // handle command
        // handle barcode
        else cout << "Unknown input\n";

        // Notes:
        // must load the new registered file when exiting the registration mode
        // barcode when a terminal line starts with isdigit(line[0])
        // must validate barcode
    }
}


// ========== Set Operating Mode ==========
bool mode_selection(string selection)
{
    if (selection == "Attendance" || selection == "A" || selection == "a" || selection == "attendance") {
        current_mode = Mode::Attendance;
        return true;
    }
    if (selection == "Registration" || selection == "R" || selection == "r"|| selection == "registration") {
        current_mode = Mode::Registration;
        return true;
    }
    if (selection == "Request" || selection == "Q" || selection == "q" || selection == "request") {
        current_mode = Mode::Request;
        return true;
    }
    return false;
}

// ========== Register Student ==========
RegResult register_student(Student s, string barcode) {
    // WrongMode error check
    if (current_mode != Mode::Registration) { return RegResult::WrongMode; }
    // NotInClassList error check
    if (!search_class_list(s.getBanner())) { return RegResult::NotInClassList; }
    // AlreadyRegistered error check
    if (search_registered(barcode)) { return RegResult::AlreadyRegistered; }
    
    // Append an entry to the registered.csv
    RegisteredStudent newReg(s, barcode);
    // Save and error check
    if (!save_registered(newReg)) { return RegResult::SaveFailed; }
    // Successful registration
    registered_list.push_back(newReg);
    sort_registered();
    return RegResult::Ok;
}

// ========== Check-in Student ==========
CheckInResult check_in(string barcode)
{
    if (current_mode != Mode::Attendance) {
        return CheckInResult::WrongMode;
    }
    if (!is_barcode(barcode)) {
        return CheckInResult::BadScan;
    }
    RegisteredStudent* s = find_registered(barcode);
    if (s == nullptr) return CheckInResult::NotRegistered;
    if (save_attendance(*s)) return CheckInResult::Ok;
    return CheckInResult::SaveFailed;

}

// ========== Request Attendance ==========
void request_attendance();
