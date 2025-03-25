#include <iostream>
#include <Windows.h>
#include <conio.h> // For _getch()
#include "SharedMemory.h"
#include <tchar.h>

#pragma comment(lib, "./lib/SharedMemory.lib")

using namespace std;



int main() {
    char ch;
    cout << "Press 'q' to print 'Welcome message'.\n";

    SharedMemoryHandler* sh = new SharedMemoryHandler(_T("NUTRI-IPC"), 0);
    HANDLE fullEvent = sh->getFullEvent();
    HANDLE emptyEvent = sh->getEmptyEvent();


    while (true) {
        DWORD result = WaitForSingleObject(fullEvent, INFINITE);

        SharedMemory* sm = sh->getMessage();

        int cmd = sm->cmd;
        int option = sm->option;

        cout << "SetMSG with cmd: " << cmd << ", option: " << option << endl;


        ResetEvent(fullEvent);
        SetEvent(emptyEvent);

        if (cmd == 0) {
            break;
        }

    }
    delete sh;
    return 0;
}

