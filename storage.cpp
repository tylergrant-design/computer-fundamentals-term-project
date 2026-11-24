#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include "storage.h"
#include "helpers.h"
#include "globals.h"
using namespace std;


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
