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
using namespace std;

enum class Mode { Attendance, Registration, Request };

enum class RegResult { WrongMode, NotInClassList, AlreadyRegistered, SaveFailed, Ok };
enum class CheckInResult { WrongMode, BadScan, NotRegistered, SaveFailed, Ok };


// ========== Data Stores ==========
Mode current_mode = Mode::Attendance;
vector<Student> class_list;
vector<RegisteredStudent> registered_list;
// Attendance log tbd

// ========== Load/Save Files ==========
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

// ========== Capture ==========
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
// ========== Save/Load Files ==========
void load_class_list() {
    ifstream file("data/class_list.csv");
    if (!file) { cout << "Cannot open class_list.csv\n"; return; }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string first, last, banner;
        getline(ss, first, ',');
        getline(ss, last, ',');
        getline(ss, banner, ',');
        class_list.push_back(Student(trim(first), trim(last), trim(banner)));
    }
}
void load_registered() {
    ifstream file("data/registered.csv");
    if (!file) { cout << "Cannot open registered.csv\n"; return; }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string first, last, banner, barcode;
        getline(ss, first, ',');
        getline(ss, last, ',');
        getline(ss, banner, ',');
        getline(ss, barcode, ',');
        registered_list.push_back(RegisteredStudent(trim(first), trim(last), trim(banner), trim(barcode)));
    }
}
bool save_registered(RegisteredStudent s) {
    ofstream file("data/registered.csv", ios::app);
    if (!file) { return false; }
    file << s.toCsv() << "\n";
    return file.good();
}
bool save_attendance(RegisteredStudent s)
{
    time_t now = time(nullptr);
    const tm* today = localtime(&now);
    char date[11];
    if(today == nullptr || strftime(date, sizeof(date), "%Y-%m-%d", today) == 0)
    {
        return false;
    }
    string filename = string("data/Attendance_") + date + ".txt";
    ofstream log(filename, ios::app);
    if(!log)
    {
        return false;
    }
    log << s.getBanner() << ", " << date <<'\n';
    log.close();
    return log.good();
}

bool mode_selection(string selection)
{
    if (selection == "Attendance" || selection == "A" || selection == "a" || selection == "attendance") 
    {
        current_mode = Mode::Attendance;
        return true;
    }
    if (selection == "Registration" || selection == "R" || selection == "r"|| selection == "registration")
    {
        current_mode = Mode::Registration;
        return true;
    }
    if (selection == "Request" || selection == "Q" || selection == "q" || selection == "request")
    {
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

// ========== Capture ==========
bool capture(string path);
bool compile_DalCard(string path, string* first, string* last, string* banner);

// ========== Helper Functions ==========
bool is_banner(string s) {
    if (s.size() != 9) { return false; }
    if (s[0] != 'B') { return false; }
    for (size_t i = 1; i < s.size(); i++) {
        if (!isdigit((unsigned char)s[i])) { return false; }
    }
    return true;
}
bool is_barcode(string s) {
    if (s.empty()) { return false; }
    for (size_t i = 0; i < s.size(); i++) {
        if (!isdigit(s[i])) { return false; }
    }
    return true;
}
bool search_registered(string barcode) {
    return find_registered(barcode) != nullptr;
}
RegisteredStudent* find_registered(string barcode) {
    int low = 0;
    int high = (int)registered_list.size() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        string mid_barcode = registered_list[mid].getBarcode();
        if (mid_barcode == barcode) return &registered_list[mid];
        if (mid_barcode < barcode) low = mid + 1;
        else high = mid - 1;
    }
    return nullptr;
}
bool search_class_list(string banner) {
    for (size_t i = 0; i < class_list.size(); i++) {
        if (banner == class_list[i].getBanner()) return true;
    }
    return false;
}
void sort_registered() {
    for (size_t i = 1; i < registered_list.size(); i++) {
        int j = i;
        while (j > 0 && registered_list[j - 1].getBarcode() > registered_list[j].getBarcode()) {
            swap(registered_list[j - 1], registered_list[j]);
            j--;
        }
    }
}
string trim(string s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = s.find_first_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}
