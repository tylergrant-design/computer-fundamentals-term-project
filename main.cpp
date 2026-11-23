// Tyler Grant B01097745
// Brady Buffet B01000126

// Start coding brainstorm
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <boost/algorithm/string.hpp>
#include <algorithm>
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
void load_class_list();
void load_registered();
bool save_registered(RegisteredStudent s);
bool save_attendance(RegisteredStudent s)
{
    time_t now = time(nullptr);
    const tm* today = localtime(&now);
    cha date[11];
    if(today == nullptr || strftime(date, sizeof(date), "%Y-%m-%d", today) == 0)
    {
        return false;
    }
    String filename = string("Attendance_") + date + ".txt";
    ofstream log(filename,ios::app);
    if(!log)
    {
        return false;
    }
    log << student.getBannerNumber() << ", " << date <<'\n';
    log.close();
    return !log.fail();
}

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
RegResult register_student(string banner, string barcode);

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

// Binary search in registered_list by banner number
bool student_found(string banner) {
    int low = 0;
    int high = registered_list.size() -1;

    while (low <= high) {
        int mid = (low + high) / 2;
        string mid_banner = registered_list[mid].getBanner();

        if (mid_banner == banner) return true;
        if (mid_banner < banner) low = mid + 1;
        if (mid_banner > banner) high = mid -1;
    }
    return false;
}

// Insertion sort of registered_list by banner number
void sort_registered() {
    for (int i = 1; i < registered_list.size(); i++) {
        int j = i;
        while (j > 0 && registered_list[j - 1].getBanner() > registered_list[j].getBanner()) {
            swap(registered_list[j - 1], registered_list[j]);
            j--;
        }
    }
}

// ========== Main ==========
int main() {
    load_class_list();
    load_registered();

    // get terminal input
    string line;
    while(cout << "> ", getline(cin, line)) {
        line = trim(line);
        if (line.empty()) continue;
        // handle command
        // handle barcode
        else cout << "Unkown input\n";
    }
}
