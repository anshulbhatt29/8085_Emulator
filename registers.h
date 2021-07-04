#include <iostream>
#include <map>
#include <string>
#include <stack>
using namespace std;
class Registers
{
public:
    map<string, int> labelJump;
    map<string, string> general_purpose_register;
    map<string, int> check_register; //remove it ...
    map<int, int> program_counter_next;
    map<string, int> command_address; //add all the addresses..
    map<string, string> flag_register;
    map<string, string> lower_order_rp;
    map<string, string> port_add;
    int global_line;
    stack<int> SP;
    int PC;
    string mSP;                     //for pointing to top of stack...
    stack<pair<string, string>> mS; //for storing address and its corresponding value pushed...
    Registers()                     //PCHL..
    {
        mS.push({"1500", "0"});
        mSP = mS.top().first;
        global_line = 1;
        PC = 12288; //hexadecimal address to decimal..// its hexadecimal value is 3000...
        general_purpose_register = {{"A", "-1"}, {"B", "-1"}, {"C", "-1"}, {"D", "-1"}, {"E", "-1"}, {"H", "-1"}, {"L", "-1"}};
        check_register = {{"A", 1}, {"B", 1}, {"C", 1}, {"D", 1}, {"E", 1}, {"H", 1}, {"L", 1}};
        flag_register = {{"F", "0"}, {"S", "0"}, {"P", "0"}, {"Z", "0"}, {"AC", "0"}, {"gar1", "0"}, {"gar2", "0"}, {"gar3", "0"}};
        command_address = {{"ACI", 2}, {"ADI", 2}, {"ANI", 2}, {"CALL", 3}, {"CC", 3}, {"CM", 3}, {"CNC", 3}, {"CNZ", 3}, {"CP", 3}, {"CPE", 3}, {"CPI", 2}, {"CPO", 3}, {"CZ", 3}, {"JC", 3}, {"JM", 3}, {"JMP", 3}, {"JNC", 3}, {"JNZ", 3}, {"JP", 3}, {"JPE", 3}, {"JPO", 3}, {"JZ", 3}, {"LDA", 3}, {"LHLD", 3}, {"LXI", 3}, {"MVI", 2}, {"ORI", 2}, {"SBI", 2}, {"SHLD", 3}, {"STA", 3}, {"SUI", 2}, {"XRI", 2}, {"ADC", 1}, {"ADD", 1}, {"ANA", 1}, {"CMA", 1}, {"CMC", 1}, {"CMP", 1}, {"DAA", 1}, {"DAD", 1}, {"DCR", 1}, {"DCX", 1}, {"DI", 1}, {"EI", 1}, {"HLT", 1}, {"INR", 1}, {"INX", 1}, {"LDAX", 1}, {"MOV", 1}, {"NOP", 1}, {"ORA", 1}, {"PCHL", 1}, {"POP", 1}, {"PUSH", 1}, {"RAL", 1}, {"RAR", 1}, {"RC", 1}, {"RET", 1}, {"RIM", 1}, {"RLC", 1}, {"RM", 1}, {"RNC", 1}, {"RNZ", 1}, {"RP", 1}, {"RPE", 1}, {"RPO", 1}, {"RRC", 1}, {"RST", 1}, {"RZ", 1}, {"SBB", 1}, {"SIM", 1}, {"SPHL", 1}, {"STAX", 1}, {"STC", 1}, {"SUB", 1}, {"XCHG", 1}, {"XRA", 1}, {"XTHL", 1}};
        lower_order_rp = {{"B", "C"}, {"D", "E"}, {"H", "L"}};
    }
};
Registers reobj = Registers();