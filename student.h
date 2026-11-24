// Tyler Grant B01097745
// Brady Buffet B01000126

#pragma once

#include <string>
using std::string;

class Student {
    private:
        string first;
        string last;
        string banner;
    
    public:
        Student(string first, string last, string banner) : 
            first(first), last(last), banner(banner) {}

        string getFirst() const { return first; }
        string getLast() const { return last; }
        string getBanner() const { return banner; }

        virtual string toCsv() const { return first + "," + last + "," + banner; }
        virtual ~Student() = default;
};

class RegisteredStudent : public Student {
    private:
        string barcode;
    
    public:
        // Register Student from scratch
        RegisteredStudent(string first, string last, string banner, string barcode) :
            Student(first, last, banner), barcode(barcode) {}
        
        // Register Student in class_list
        RegisteredStudent(const Student& s, string barcode) :
            Student(s), barcode(barcode) {}
        
        string getBarcode() const { return barcode; }

        string toCsv() const override { return Student::toCsv() + "," + barcode; }
};
