#include<iostream>
#include<map>
#include<string>
#include<stack>
using namespace std;
class Registers{
    public:

    map<string,string> general_purpose_register;
    map<int,int>program_counter_next;
    map<string,int> command_address;
    map<string,string> flag_register;
    map<string,string> lower_order_rp;
    map<string,string> port_add;
    int global_line;
    stack<int> SP;
    int PC;
    string mSP;//for pointing to top of stack...
    stack<pair<string,string> > mS;//for storing address and its corresponding value pushed...
    Registers()
    {
        mS.push({"1500","0"});
        mSP=mS.top().first;
        global_line=1;
        PC=32768;
        general_purpose_register={{"A","-1"},{"B","-1"},{"C","-1"},{"D","-1"},{"E","-1"},{"H","-1"},{"L","-1"}};
        flag_register={{"F","0"},{"S","0"},{"P","0"},{"Z","0" },{"AC","0"},{"gar1","0"},{"gar2","0"},{"gar3","0"}};
        command_address={{"ACI",2},{"ADI",2},{"ANI",2},{"CALL",3},{"CC",3},{"CM",3},{"CNC",3},{"CNZ",3},{"CP",3},{"CPE",3},{"CPI",2},{"CPO",3},{"CZ",3},{"JC",3},{"JM",3},{"JMP",3},{"JNC",3},{"JNZ",3},{"JP",3},{"JPE",3},{"JPO",3},{"JZ",3},{"LDA",3},
        {"LHLD",3},{"LXI",3},{"MVI",2},{"ORI",2},{"SBI",2},{"SHLD",3},{"STA",3},{"SUI",2},{"XRI",2}};
        lower_order_rp={{"B","C"},{"D","E"},{"H","L"}};


    }
};
Registers reobj=Registers();