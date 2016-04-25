#ifndef CPU_H
#define CPU_H
#include <string.h>
#include <iostream>
#include <string>
#include "opcode.h"

#define MEMORY_SIZE 4096
#define VMEMORY_SIZE 2000
using namespace std;

class CPU
{
private:
    static const string regs_name[];
    char memory[MEMORY_SIZE];
    char vmemory[VMEMORY_SIZE];
    int regs_value[32];
    int pc;
    int instruction;
    int opcode;
    int rd, rs, rt;
    int func;
    int j_addr;
    int imm;
    void fetch_instruction();
    void exec_instruction();
    int pc_max;

public:
    CPU() { pc = 0; memset(regs_value, 0, sizeof(int) * 32); }
    void initCPU();
    void showState();
    void load_program(string filename);
    void load_text_file(string filename);
    void exec_program();
    void single_step();
    void show_memory(int range = 10, int offset = 0);
    void video_card_display();
};

#endif // CPU_H
