#include <cctype>
#include "helpers.h"
#include "globals.h"
using namespace std;


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
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}
