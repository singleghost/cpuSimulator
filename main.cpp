#include <iostream>
#include "cpu.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;
    char c;
    CPU my_cpu;
    my_cpu.load_program("instruct.bin");
    my_cpu.show_memory(20, 0);
    my_cpu.showState();
    cout << endl << ">";
    while(true) {
        c = getchar();
        switch(c) {
            case 's':
                my_cpu.single_step();
                my_cpu.showState();
                cout << endl << ">";
                break;
            case 'r':
                my_cpu.exec_program();
                my_cpu.showState();
                cout << endl << ">";
                break;
            case 'q':
                abort();
            default:
                break;
        }
        while((c = getchar()) != '\n');
    }
    return 0;
}
