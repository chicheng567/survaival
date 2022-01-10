#include<iostream>
#include<windows.h>
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

int main() {
    while(1) {
        cout << GetAsyncKeyState(VK_SPACE) << endl;
    }
}