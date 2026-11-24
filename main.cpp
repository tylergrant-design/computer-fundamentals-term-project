// Tyler Grant B01097745
// Brady Buffet B01000126

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <boost/algorithm/string.hpp>
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
        class_list.push_back(Student(first, last, banner));
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
        registered_list.push_back(RegisteredStudent(first, last, banner, barcode));
    }
}
bool save_registered(RegisteredStudent s) {
    ofstream file("data/registered.csv");
    if (!file) { return false; }
    file << s.toCsv() << "\n";
    return file.good();
}
bool save_attendance(RegisteredStudent s);

// ========== Set Operating Mode ==========
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
RegResult register_student(Student s, string barcode, Mode current_mode) {
    // WrongMode error check
    if (current_mode != Mode::Registration) { return RegResult::WrongMode; }
    // NotInClassList error check
    if (!search_class_list_banner(s.getBanner())) { return RegResult::NotInClassList; }
    // AlreadyRegistered error check
    if (search_registered_barcode(barcode)) { return RegResult::AlreadyRegistered; }
    
    // Append an entry to the registered.csv
    RegisteredStudent newReg(s, barcode);
    // Save and error check
    if (!save_registered(newReg)) { return RegResult::SaveFailed; }
    // Successful registration
    return RegResult::Ok;
}

// ========== Check-in Student ==========
CheckInResult check_in(string barcode)
{
    if(current_mode != Mode::Attendance)
    {
        return CheckInResult::WrongMode;
    }
    if(barcode.empty())
    {
        return CheckInResult::BadScan;
    }
    for(int i = 0; i < registered_list.size(); i++)
    {
        if(RegisteredStudent[i].getBarcode() == barcode)
        {
            if(save_attendance(student))
            {
                return CheckInResult::Ok;
            }
            return CheckInResult::SaveFailed;
        }
    }
    return CheckInResult::NotRegistered;
}

// ========== Request Attendance ==========
void request_attendance();

// ========== Capture ==========
Student compile_DalCard();
void capture();

// ========== Helper Functions ==========
bool is_banner(string s) {
    if (s.size() != 9) { return false; }
    if (s[0] != 'B') { return false; }
    for (int i = 1; i < s.size(); i++) {
        if (!isdigit(s[i])) { return false; }
    }
    return true;
}
bool is_barcode(string s) {
    for (int i = 0; i < s.size(); i++) {
        if (!isdigit(s[i])) { return false; }
    }
    return true;
}
// Binary search in registered_list by barcode
bool search_registered_barcode(string barcode) {
    int low = 0;
    int high = (int)registered_list.size() - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        string mid_banner = registered_list[mid].getBarcode();

        if (mid_banner == barcode) return true;
        if (mid_banner < barcode) low = mid + 1;
        if (mid_banner > barcode) high = mid -1;
    }
    return false;
}
// Linear search to find banner number, because we sort by barcode O(n) is best
bool search_class_list_banner(string banner) {
    for (int i = 0; i < class_list.size(); i++) {
        if (banner == class_list[i].getBanner()) return true;
    }
    return false;
}
// Insertion sort of registered_list by barcode
void sort_registered() {
    for (int i = 1; i < registered_list.size(); i++) {
        int j = i;
        while (j > 0 && registered_list[j - 1].getBarcode() > registered_list[j].getBarcode()) {
            swap(registered_list[j - 1], registered_list[j]);
            j--;
        }
    }
}

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
        else cout << "Unkown input\n";

        // Notes:
        // must load the new registered file when exiting the registration mode
        // barcode when a terminal line starts with isdigit(line[0])
        // must validate barcode
    }
}
