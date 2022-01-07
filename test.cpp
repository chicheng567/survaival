#include<iostream>
using namespace std;
class motherClass {
public:
    int a;
    int b;
    void motherFunc() {
        cout << "This is func for all son" << endl;
    }
};
class sonClass_1st : public motherClass {
    int c;
public:
    void func() {
        cout << "this is first son" << endl;
    }
};
class sonClass_2st : public motherClass {
    int d;
    public:
    void func() {
        cout << "this is second son" << endl;
    }
};

void testFunc(motherClass input) {
    ;
}