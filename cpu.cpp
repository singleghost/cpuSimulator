#include "cpu.h"
#include "opcode.h"
#include <string.h>
#include <fstream>
#include <iostream>

using namespace std;

const string CPU::regs_name[] = {"$(0)zero","$(1)at","$(2)v0","$(3)v1","$(4)a0",
              "$(5)a1","$(6)a2","$(7)a3","$(8)t0","$(9)t1",
              "$(10)t2","$(11)t3","$(12)t4","$(13)t5","$(14)t6",
              "$(15)t7","$(16)s0","$(17)s1","$(18)s2","$(19)s3",
               "$(20)s4","$(21)s5","$(22)s6","$(23)s7","$(24)t8",
              "$(25)t9","$(26)k0","$(27)k1","$(28)gp","$(29)sp",
              "$(30)fp","$(31)ra"};
void CPU::load_text_file(string filename)
{
    ifstream fin;
    fin.open(filename);
    char line[40];
    int j = 0;
    int value = 0;
    while(!fin.eof()) {
        value = 0;
        fin.getline(line, 32);
        for (int i = 0; i <= 31; i++)
            value = (value << 1) + line[i] - '0';
        *((int *)memory+j) = value;
        j++;
    }
}

void CPU::load_program(string filename)
{
    ifstream fin;
    int i = 0;
    fin.open(filename, ios::binary);
    while(!fin.eof()) {
        fin.read((char *)((int *)memory + i), 4);
        i++;
    }
    fin.close();
    pc_max = (i-1) * 4;
}

void CPU::show_memory(int range, int offset)
{
    for(int m = 0; m < range; m++) {
        if(m % 16 == 0) printf("%08x: ", m);
        printf("%02x ", memory[m + offset]);
        if((m+1) % 16 == 0) printf("\n");
    }
    printf("\n");
}

void CPU::exec_program()
{
    pc = 0;
    while(true) {
        regs_value[0] = 0;

        fetch_instruction();
        exec_instruction();
        if(pc >= pc_max)
            break;
    }

}

void CPU::exec_instruction()
{
    if(opcode == 0) { // R_type
        switch(func) {
        case O_ADD:
            regs_value[rd] = regs_value[rs] + regs_value[rt];
            break;
        case O_SUB:
            regs_value[rd] = regs_value[rs] - regs_value[rt];
            break;

        }
    } else if(opcode == 2 || opcode == 3) { // J_type
        if(opcode == 2) { // J
        pc = (pc & 0x0000000) | (j_addr << 2);
        } else if(opcode == 3) { // Jal
        regs_value[31] = pc + 4;
        pc = (pc & 0x0000000) | (j_addr << 2);
        }

    } else if(((opcode >> 2) << 2) != 16) { // I_type
        switch(opcode) {
            case 4: // beq
                if (regs_value[rs] == regs_value[rt])
                    pc += j_addr << 2;
                break;
            case 8: // addi
                regs_value[rt] = regs_value[rs] + imm;
                break;
            default:
                break;
        }

    } else { //wrong instruction
    }
}

void CPU::single_step()
{
    fetch_instruction();
    exec_instruction();
}

void CPU::fetch_instruction()
{
    instruction = memory[pc] | memory[pc+1] << 8| memory[pc+2] << 16 | memory[pc+3] << 24;
    pc += 4;

    opcode = (instruction >> 26) & 63;
    rs = (instruction >> 21) & 31;
    rt = (instruction >> 16) & 31;
    rd = (instruction >> 11) & 31;
    func = (instruction) & 63;
    j_addr = (instruction << 6) >> 6;
    imm = (instruction << 16) >> 16;
}

void CPU::showState()
{
    int i;
    for(i = 0; i < 32; i++) {
        cout << regs_name[i] << " :" << regs_value[i] << '\t';
        if((i+1) % 4 == 0)
            cout << endl;
    }
    cout << "PC:" << pc << endl;
}
