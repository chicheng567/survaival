#include<iostream>
#include<conio.h>
#include<windows.h>
using namespace std;
int main()
{
    while(1)
    {
        if(GetAsyncKeyState(0x41)) {
            cout << "1" << endl;
        }
    }
}