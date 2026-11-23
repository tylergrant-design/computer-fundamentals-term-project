// Tyler Grant B01097745
// Brady Buffet B01000126

#pragma once

#include <iostream>
#include <string>
#include <vector>
using std::string;

class Student {
    private:
        string first;
        string last;
        string banner;
        static int count;
    
    public:
        Student(string first, string last, string banner) : 
            first(first), last(last), banner(banner) { count++; }

        string getFirst() const { return first; }
        string getLast() const { return last; }
        string getBanner() const { return banner; }
        int getCount() { return count; }

        virtual string toCsv() const { return first + "," + last + "," + banner; }
        virtual ~Student() = default;
};

class RegisteredStudent : public Student {
    private:
        string barcode;
        static int count;
    
    public:
        // Register Student from scratch
        RegisteredStudent(string first, string last, string banner, string barcode) :
            Student(first, last, banner), barcode(barcode) { count++; }
        
        // Register Student in class_list
        RegisteredStudent(const Student& s, string barcode) :
            Student(s), barcode(barcode) {}
        
        string getBarcode() const { return barcode; }
        int getCount() { return count; }

        string toCsv() const { return Student::toCsv() + "," + barcode; }
};

int Student::count = 0;
int RegisteredStudent::count = 0;