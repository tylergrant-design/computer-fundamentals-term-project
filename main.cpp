// Tyler Grant B01097745
// Brady Buffet B01000126

// Start coding brainstorm
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
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
bool save_attendance(RegisteredStudent s);

// ========== Set Operating Mode ==========
bool mode_selection(string selection);

// ========== Register Student ==========
RegResult register_student(string banner, string barcode);

// ========== Check-in Student ==========
CheckInResult check_in(string barcode);

// ========== Request Attendance ==========
void request_attendance();

// ========== Main ==========
int main() {
    load_class_list();
    load_registered();

    // get terminal input
    string line;
    while(getline(cin, line)){
        // do shit
    }
}