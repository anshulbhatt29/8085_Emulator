#include "Data_transfer.h"
#include <bits/stdc++.h> //change this header file//todo...//no space after the instruction..//BUT work for lines spaces or new lines...
using namespace std;
//make it work on empty line and nop instruction...//work on common address...//while taking input no H....
//interrupts instructions or control instructions:NOP,DI,EI,SIM,RIM.
//ambiguous instructions:PCHL,POP PSW,SPHL,RM...
int main()
{
    dataobj.put_data(); //starting address 3000....//change it use while loop....
    dataobj.program_counter_function();
    ifstream fileptr;
    string str, word;
    fileptr.open("input.txt");
    while (!fileptr.eof())
    {
        int check_for_label = 0;
        getline(fileptr, str);
        std::stringstream stream(str);
        while (stream >> word)
        {

            //Data transfer instructions.
            if (word == "LDA")
            {
                stream >> word;
                check_LDA(stream, word);
                dataobj.LDA(word);
                reobj.global_line++;
                dataobj.print();
            }
            else if (word == "MOV")
            {
                stream >> word;
                std::stringstream stream_for_move(word);
                std::stringstream copystream_for_move(word);
                //copystream_for_move << stream_for_move.rdbuf();

                check_MOV(stream, copystream_for_move);
                //stream_for_move << (copystream_for_move.str());
                string s1, s2, re;
                getline(stream_for_move, s1, ',');
                getline(stream_for_move, s2, ',');

                if (s1 == "M")
                {

                    re = reobj.general_purpose_register["H"] + reobj.general_purpose_register["L"];
                    address_obj.arr_address[re] = reobj.general_purpose_register[s2];
                }
                else if (s2 == "M") //do it..
                {
                    re = reobj.general_purpose_register["H"] + reobj.general_purpose_register["L"];
                    reobj.general_purpose_register[s1] = address_obj.get_address_value(re);
                }
                else if (reobj.check_register[s1] && reobj.check_register[s2])
                {

                    dataobj.MOV(s1, s2);
                }
                else
                {
                    print8085Error();
                }

                reobj.global_line++;
                dataobj.print();

            } //both memory instructions are missing....very very important check it.....
            else if (word == "MVI")
            {
                stream >> word;
                std::stringstream stream_for_move(word);
                std::stringstream copystream_for_move(word);
                //copystream_for_move << stream_for_move.rdbuf();
                check_MOV(stream, copystream_for_move);
                string s1, s2, re;
                getline(stream_for_move, s1, ',');
                getline(stream_for_move, s2, ',');
                if (s1 == "M") //do it..
                {
                    re = reobj.general_purpose_register["H"] + reobj.general_purpose_register["L"];
                    address_obj.arr_address[re] = s2;
                }
                else if (reobj.check_register[s1] && s2.length() == 2)
                    dataobj.MVI(s1, s2);
                else
                {
                    print8085Error();
                }
                reobj.global_line++;
                dataobj.print();
            }
            else if (word == "SHLD") //check it bro!!! ok... for address to be in hex or decimal.
            {
                stream >> word;
                check_LDA(stream, word); //same functionality..
                dataobj.SHLD(word);
                reobj.global_line++;
            }
            else if (word == "LXI") //not for SP.lxi rp,8085.??????????????????????????????????????
            {
                stream >> word;
                std::stringstream stream_for_move(word);
                std::stringstream copystream_for_move(word);
                check_LXI(stream, copystream_for_move);
                string s1, s2;
                getline(stream_for_move, s1, ','); //rp
                getline(stream_for_move, s2, ','); //address.
                dataobj.LXI(s1, s2);
                reobj.global_line++;
                dataobj.print();
            }
            else if (word == "LHLD")
            {
                stream >> word;
                check_LDA(stream, word);
                dataobj.LHLD(word);
                reobj.global_line++;
            }

            else if (word == "STA")
            {
                stream >> word;
                check_LDA(stream, word);
                dataobj.STA(word);
                reobj.global_line++;
                dataobj.print();
            }
            else if (word == "LDAX") //not accepted registers other than B,D....
            {
                stream >> word;
                check_LDAX(stream, word);
                dataobj.LDAX(word);
                reobj.global_line++;
            }
            else if (word == "XCHG")
            {
                check_XCHG(stream);
                dataobj.XCHG();
                reobj.global_line++;
            }
            else if (word == "STAX") //STAX H not valid. same as "M";;;....
            {
                stream >> word;
                check_LDAX(stream, word);
                dataobj.STAX(word);
                reobj.global_line++;
            }

            else if (word == "HLT")
            {
                dataobj.HLT();
                exit(0);
            }
            //Logical Instructions.
            else if (word == "ANA")
            {
                stream >> word;
                check_ANA(stream);
                if (word == "M")
                {
                    string re = reobj.general_purpose_register["H"] + reobj.general_purpose_register["L"];
                    dataobj.ANA(address_obj.get_address_value(re));
                }
                else if (word == "A" || word == "B" || word == "C" || word == "D" || word == "E" || word == "H" || word == "L")
                {
                    dataobj.ANA(reobj.general_purpose_register[word]);
                }
                else
                {
                    print8085Error();
                }
                reobj.global_line++;
            }
            else if (word == "ANI")
            {
                stream >> word;
                check_ANI(stream, word);
                dataobj.ANA(word);
                reobj.global_line++;
            }
            else if (word == "ORA")
            {
                stream >> word;
                check_ANA(stream);
                if (word == "M")
                {
                    string re = reobj.general_purpose_register["H"] + reobj.general_purpose_register["L"];
                    dataobj.ORA(address_obj.get_address_value(re));
                }
                else if (word == "A" || word == "B" || word == "C" || word == "D" || word == "E" || word == "H" || word == "L")
                {
                    dataobj.ORA(reobj.general_purpose_register[word]);
                }
                else
                {
                    print8085Error();
                }

                reobj.global_line++;
            }
            else if (word == "ORI")
            {
                stream >> word;
                check_ANI(stream, word);
                dataobj.ORA(word);
                reobj.global_line++;
            }
            else if (word == "XRA")
            {
                stream >> word;
                check_ANA(stream);
                if (word == "M")
                {
                    string re = reobj.general_purpose_register["H"] + reobj.general_purpose_register["L"];
                    dataobj.XRA(address_obj.get_address_value(re));
                }
                else if (word == "A" || word == "B" || word == "C" || word == "D" || word == "E" || word == "H" || word == "L")
                {
                    dataobj.XRA(reobj.general_purpose_register[word]);
                }
                else
                {
                    print8085Error();
                }
                reobj.global_line++;
                dataobj.print();
            }
            else if (word == "XRI")
            {
                stream >> word;
                check_ANI(stream, word);
                dataobj.XRA(word);
                reobj.global_line++;
            }
            else if (word == "CMA")
            {
                check_ANA(stream);
                dataobj.CMA(reobj.general_purpose_register["A"]);
                reobj.global_line++;
            }
            else if (word == "CMC")
            {
                check_ANA(stream);
                reobj.flag_register["F"] == "0" ? reobj.flag_register["F"] = "1" : reobj.flag_register["F"] = "0";
                reobj.global_line++;
                dataobj.print();
            }
            else if (word == "STC")
            {
                check_ANA(stream);
                reobj.flag_register["F"] = "1";
                reobj.global_line++;
            }
            else if (word == "RLC")
            {
                check_ANA(stream);
                dataobj.RLC();
                reobj.global_line++;
            }
            else if (word == "RAL")
            {
                check_ANA(stream);
                dataobj.RAL();
                reobj.global_line++;
            }
            else if (word == "RRC")
            {
                check_ANA(stream);
                dataobj.RRC();
                reobj.global_line++;
            }
            else if (word == "RAR")
            {

                check_ANA(stream);
                dataobj.RAR();
                reobj.global_line++;
                dataobj.print();
            }
            else if (word == "CMP") //its definition is in arithmatic file as it is similar to SUB...
            {
                stream >> word;
                check_ANA(stream);
                string s;
                if (word == "M")
                {
                    s = reobj.general_purpose_register["H"] + reobj.general_purpose_register["L"];
                    ari_class.CMP(address_obj.get_address_value(s));
                }
                else if (word == "A" || word == "B" || word == "C" || word == "D" || word == "E" || word == "H" || word == "L")
                    ari_class.CMP(reobj.general_purpose_register[word]);
                else
                {
                    print8085Error();
                }

                reobj.global_line++;
                dataobj.print();
            }
            else if (word == "CPI")
            {

                stream >> word;
                check_ANI(stream, word);
                ari_class.CMP(word);
                reobj.global_line++;
            }
            //Stack//Input/Output....
            //IN /OUT confussion....
            else if (word == "PUSH")
            {

                stream >> word;
                check_ANA(stream);
                if (word == "PSW")
                {
                    string psw;
                    psw = reobj.general_purpose_register["S"] + reobj.general_purpose_register["Z"] + reobj.general_purpose_register["gar1"] + reobj.general_purpose_register["AC"] + reobj.general_purpose_register["gar2"] + reobj.general_purpose_register["P"] + reobj.general_purpose_register["gar3"] + reobj.general_purpose_register["F"];
                    int da = dataobj.binary_to_decimal(psw);
                    psw = dataobj.decimal_hex_value(da);
                    dataobj.PUSH(reobj.general_purpose_register["A"], psw);
                }
                else if (word == "B" || word == "D" || word == "H")
                {
                    dataobj.PUSH(reobj.general_purpose_register[word], reobj.general_purpose_register[reobj.lower_order_rp[word]]);
                }
                else
                {
                    print8085Error();
                }
                reobj.global_line++;
            }
            else if (word == "POP")
            {

                stream >> word;
                check_ANA(stream);
                if (word == "PSW")
                {
                    dataobj.POP("A", "PSW");
                }
                else if (word == "B" || word == "D" || word == "H")
                {
                    dataobj.POP(word, reobj.lower_order_rp[word]);
                }
                else
                {
                    print8085Error();
                }
                reobj.global_line++;
            }
            else if (word == "XTHL")
            {

                check_ANA(stream);
                dataobj.XTHL(reobj.general_purpose_register["H"], reobj.general_purpose_register["L"]);
                reobj.global_line++;
            }
            else if (word == "SPHL")
            {
                check_ANA(stream);
                dataobj.SPHL(reobj.general_purpose_register["H"], reobj.general_purpose_register["L"]);
                reobj.global_line++;
            }
            else if (word == "IN") //programer will enter the value at run time ...at particular address..
            {
                stream >> word;
                check_ANI(stream, word);
                reobj.general_purpose_register["A"] = reobj.port_add[word];
                reobj.global_line++;
            }
            else if (word == "OUT")
            {
                stream >> word;
                check_ANI(stream, word);
                reobj.port_add[word] = reobj.general_purpose_register["A"];
                reobj.global_line++;
            }

            //Arithemetic Instructions.
            else if (word == "ADD")
            {
                stream >> word;
                check_ANA(stream);
                if (word == "M")
                {
                    ari_class.ADM(address_obj.get_address_value(reobj.general_purpose_register["H"] + reobj.general_purpose_register["L"]));
                }
                else if (word == "A" || word == "B" || word == "C" || word == "D" || word == "E" || word == "H" || word == "L") //ari_class.ADD(word);//use enum//
                    ari_class.ADM(reobj.general_purpose_register[word]);
                else
                {
                    print8085Error();
                }

                reobj.global_line++;
                dataobj.print();
            }
            else if (word == "ADI")
            {
                stream >> word; //word is data...
                check_ANI(stream, word);
                ari_class.ADM(word); //because it is handling data.
                reobj.global_line++;
            }
            else if (word == "ACI")
            {

                stream >> word;
                check_ANI(stream, word);
                // ari_class.ACI(word);
                ari_class.AMC(word);
                reobj.global_line++;
            }
            /* if (word == "AMC")
            {
                stream >> word;
                ari_class.AMC(address_obj.get_address_value(reobj.general_purpose_register["H"] + reobj.general_purpose_register["L"]));
                reobj.global_line++;
            }*/

            else if (word == "ADC")
            {
                stream >> word;
                check_ANA(stream);
                if (word == "M")
                {
                    ari_class.AMC(address_obj.get_address_value(reobj.general_purpose_register["H"] + reobj.general_purpose_register["L"]));
                }
                else if (word == "A" || word == "B" || word == "C" || word == "D" || word == "E" || word == "H" || word == "L")
                    ari_class.AMC(reobj.general_purpose_register[word]);
                else
                {
                    print8085Error();
                }
                reobj.global_line++;
                dataobj.print();
            }
            else if (word == "DAD")
            {
                string s1;
                stream >> word;
                check_ANA(stream);
                if (word == "SP") //value of SP....//2 locations of stack are used at once in any operation like push/pop...
                {
                    ari_class.DAD(reobj.mSP);
                }
                else if (word == "B" || word == "D" || word == "H")
                {
                    s1 = reobj.general_purpose_register[word] + reobj.general_purpose_register[reobj.lower_order_rp[word]];
                    ari_class.DAD(s1);
                }
                else
                {
                    print8085Error();
                }
                reobj.global_line++;
            }
            else if (word == "DAA") //adjust accumulator..
            {
                check_ANA(stream);
                dataobj.DAA();
                reobj.global_line++;
            }
            //Subtraction...
            else if (word == "SUB")
            {
                stream >> word;
                check_ANA(stream);
                if (word == "M")
                {
                    ari_class.SUI(address_obj.get_address_value(reobj.general_purpose_register["H"] + reobj.general_purpose_register["L"])); //for SUB M.
                }
                else if (word == "A" || word == "B" || word == "C" || word == "D" || word == "E" || word == "H" || word == "L")
                    ari_class.SUI(reobj.general_purpose_register[word]);
                else
                {
                    print8085Error();
                }
                reobj.global_line++;
            }
            else if (word == "SUI") //word =data..
            {
                stream >> word;
                check_ANI(stream, word);
                ari_class.SUI(word);
                reobj.global_line++;
            }
            else if (word == "SBI") //In this case word=data..
            {
                stream >> word;
                check_ANI(stream, word);
                ari_class.SBI(word);
                reobj.global_line++;
            }
            else if (word == "SBB")
            {
                stream >> word;
                check_ANA(stream);
                if (word == "M")
                {
                    ari_class.SBI(address_obj.get_address_value(reobj.general_purpose_register["H"] + reobj.general_purpose_register["L"])); //for SBB M.
                }
                else if (word == "A" || word == "B" || word == "C" || word == "D" || word == "E" || word == "H" || word == "L")
                    ari_class.SBI(reobj.general_purpose_register[word]);
                else
                {
                    print8085Error();
                }

                reobj.global_line++;
            }
            else if (word == "INR") //memory ,Register.//important!!! carry flag is not affected.okkk
            {
                string ret_val;
                stream >> word;
                check_ANA(stream);
                if (word == "M")
                {
                    string re = "";
                    re += reobj.general_purpose_register["H"] + reobj.general_purpose_register["L"];
                    ret_val = ari_class.INR(address_obj.get_address_value(re));
                    address_obj.arr_address[re] = ret_val;
                }
                else if (word == "A" || word == "B" || word == "C" || word == "D" || word == "E" || word == "H" || word == "L")
                {
                    ret_val = ari_class.INR(reobj.general_purpose_register[word]);
                    reobj.general_purpose_register[word] = ret_val;
                    // cout << reobj.general_purpose_register["A"] << endl;
                }
                else
                {
                    print8085Error();
                }
                reobj.global_line++;
                dataobj.print();
            }
            else if (word == "INX")
            {
                stream >> word;
                check_ANA(stream);
                if (word == "B" || word == "D" || word == "H" || word == "SP")
                    dataobj.INX(word);
                else
                {
                    print8085Error();
                }
                reobj.global_line++;
            }
            else if (word == "DCR") //carry flag is not affected.
            {
                string ret_val;
                stream >> word;
                check_ANA(stream);
                if (word == "M")
                {
                    string re = "";
                    re += reobj.general_purpose_register["H"] + reobj.general_purpose_register["L"];
                    ret_val = ari_class.DCR(address_obj.get_address_value(re));
                    address_obj.arr_address[re] = ret_val;
                }
                else if (word == "A" || word == "B" || word == "C" || word == "D" || word == "E" || word == "H" || word == "L")
                {
                    ret_val = ari_class.DCR(reobj.general_purpose_register[word]);
                    reobj.general_purpose_register[word] = ret_val;
                }
                else
                {
                    print8085Error();
                }
                reobj.global_line++;
            }
            else if (word == "DCX")
            {
                stream >> word;
                check_ANA(stream);
                if (word == "B" || word == "D" || word == "H" || word == "SP")
                    dataobj.DCX(word);
                else
                {
                    print8085Error();
                }
                reobj.global_line++;
            }

            //Branching instructions.
            else if (word == "JMP")
            {
                int deci_val;
                stream >> word;
                check_branch(stream, word);
                if (reobj.labelJump.find(word) == reobj.labelJump.end())
                {
                    deci_val = dataobj.hexidecimal_to_decimal(word);
                    reobj.global_line = reobj.program_counter_next[deci_val];
                }
                else
                {
                    reobj.global_line = reobj.labelJump[word];
                }
                fileptr.seekg(0);
                for (int i = 1; i < reobj.global_line; i++)
                {
                    getline(fileptr, str); //check may be..
                }

                dataobj.print();
            }
            else if (word == "JC")
            {
                stream >> word;
                check_branch(stream, word);
                if (reobj.flag_register["F"] == "1")
                {
                    int deci_val;
                    if (reobj.labelJump.find(word) == reobj.labelJump.end())
                    {
                        deci_val = dataobj.hexidecimal_to_decimal(word);
                        reobj.global_line = reobj.program_counter_next[deci_val];
                    }
                    else
                    {
                        reobj.global_line = reobj.labelJump[word];
                    }
                    fileptr.seekg(0);
                    for (int i = 1; i < reobj.global_line; i++)
                    {
                        getline(fileptr, str);
                    }
                }
                else
                    reobj.global_line++;
                dataobj.print();
            }
            else if (word == "JNC")
            {

                stream >> word;
                check_branch(stream, word);
                if (reobj.flag_register["F"] == "0")
                {
                    int deci_val;
                    if (reobj.labelJump.find(word) == reobj.labelJump.end())
                    {
                        deci_val = dataobj.hexidecimal_to_decimal(word);
                        reobj.global_line = reobj.program_counter_next[deci_val];
                    }
                    else
                    {
                        reobj.global_line = reobj.labelJump[word];
                    }
                    fileptr.seekg(0);
                    for (int i = 1; i < reobj.global_line; i++)
                    {
                        getline(fileptr, str);
                    }
                }
                else
                    reobj.global_line++;
                dataobj.print();
            }
            else if (word == "JZ")
            {

                stream >> word;
                check_branch(stream, word);
                if (reobj.flag_register["Z"] == "1")
                {
                    int deci_val;
                    if (reobj.labelJump.find(word) == reobj.labelJump.end())
                    {
                        deci_val = dataobj.hexidecimal_to_decimal(word);
                        reobj.global_line = reobj.program_counter_next[deci_val];
                    }
                    else
                    {
                        reobj.global_line = reobj.labelJump[word];
                    }
                    fileptr.seekg(0);
                    for (int i = 1; i < reobj.global_line; i++)
                    {
                        getline(fileptr, str);
                    }
                }
                else
                    reobj.global_line++;
                dataobj.print();
            }
            else if (word == "JNZ")
            {

                stream >> word;
                check_branch(stream, word);
                if (reobj.flag_register["Z"] == "0")
                {
                    int deci_val;
                    if (reobj.labelJump.find(word) == reobj.labelJump.end())
                    {
                        deci_val = dataobj.hexidecimal_to_decimal(word);
                        reobj.global_line = reobj.program_counter_next[deci_val];
                    }
                    else
                    {
                        reobj.global_line = reobj.labelJump[word];
                    }
                    fileptr.seekg(0);
                    for (int i = 1; i < reobj.global_line; i++)
                    {
                        getline(fileptr, str);
                    }
                }
                else
                    reobj.global_line++;
                dataobj.print();
            }
            else if (word == "JPE")
            {

                stream >> word;
                check_branch(stream, word);
                if (reobj.flag_register["P"] == "1")
                {
                    int deci_val;
                    if (reobj.labelJump.find(word) == reobj.labelJump.end())
                    {
                        deci_val = dataobj.hexidecimal_to_decimal(word);
                        reobj.global_line = reobj.program_counter_next[deci_val];
                    }
                    else
                    {
                        reobj.global_line = reobj.labelJump[word];
                    }
                    fileptr.seekg(0);
                    for (int i = 1; i < reobj.global_line; i++)
                    {
                        getline(fileptr, str);
                    }
                }
                else
                    reobj.global_line++;
            }
            else if (word == "JPO")
            {

                stream >> word;
                check_branch(stream, word);
                if (reobj.flag_register["P"] == "0")
                {
                    int deci_val;
                    if (reobj.labelJump.find(word) == reobj.labelJump.end())
                    {
                        deci_val = dataobj.hexidecimal_to_decimal(word);
                        reobj.global_line = reobj.program_counter_next[deci_val];
                    }
                    else
                    {
                        reobj.global_line = reobj.labelJump[word];
                    }
                    fileptr.seekg(0);
                    for (int i = 1; i < reobj.global_line; i++)
                    {
                        getline(fileptr, str);
                    }
                }
                else
                    reobj.global_line++;
            }
            else if (word == "JM")
            {

                stream >> word;
                check_branch(stream, word);
                if (reobj.flag_register["S"] == "1")
                {
                    int deci_val;
                    if (reobj.labelJump.find(word) == reobj.labelJump.end())
                    {
                        deci_val = dataobj.hexidecimal_to_decimal(word);
                        reobj.global_line = reobj.program_counter_next[deci_val];
                    }
                    else
                    {
                        reobj.global_line = reobj.labelJump[word];
                    }
                    fileptr.seekg(0);
                    for (int i = 1; i < reobj.global_line; i++)
                    {
                        getline(fileptr, str);
                    }
                }
                else
                    reobj.global_line++;
            }
            else if (word == "JP")
            {

                stream >> word;
                check_branch(stream, word);
                if (reobj.flag_register["S"] == "0")
                {
                    int deci_val;
                    if (reobj.labelJump.find(word) == reobj.labelJump.end())
                    {
                        deci_val = dataobj.hexidecimal_to_decimal(word);
                        reobj.global_line = reobj.program_counter_next[deci_val];
                    }
                    else
                    {
                        reobj.global_line = reobj.labelJump[word];
                    }
                    fileptr.seekg(0);
                    for (int i = 1; i < reobj.global_line; i++)
                    {
                        getline(fileptr, str);
                    }
                }
                else
                    reobj.global_line++;
            }
            else if (word == "CALL") //address and label..
            {

                stream >> word;
                check_branch(stream, word);
                int deci_val, line;
                if (reobj.labelJump.find(word) == reobj.labelJump.end())
                {
                    deci_val = dataobj.hexidecimal_to_decimal(word);
                    line = reobj.program_counter_next[deci_val];
                }
                else
                {
                    line = reobj.labelJump[word];
                }
                reobj.SP.push(reobj.global_line + 1);
                fileptr.seekg(0);
                for (int i = 1; i < line; i++)
                {
                    getline(fileptr, str);
                }
                reobj.global_line = line;
            }
            else if (word == "CC")
            {

                stream >> word;
                check_branch(stream, word);
                if (reobj.flag_register["F"] == "1")
                {
                    int deci_val, line;
                    if (reobj.labelJump.find(word) == reobj.labelJump.end())
                    {
                        deci_val = dataobj.hexidecimal_to_decimal(word);
                        line = reobj.program_counter_next[deci_val];
                    }
                    else
                    {
                        line = reobj.labelJump[word];
                    }
                    reobj.SP.push(reobj.global_line + 1);
                    fileptr.seekg(0);
                    for (int i = 1; i < line; i++)
                    {
                        getline(fileptr, str);
                    }
                    reobj.global_line = line;
                }
                else
                    reobj.global_line++;
            }
            else if (word == "CNC")
            {

                stream >> word;
                check_branch(stream, word);
                if (reobj.flag_register["F"] == "0")
                {
                    int deci_val, line;
                    if (reobj.labelJump.find(word) == reobj.labelJump.end())
                    {
                        deci_val = dataobj.hexidecimal_to_decimal(word);
                        line = reobj.program_counter_next[deci_val];
                    }
                    else
                    {
                        line = reobj.labelJump[word];
                    }
                    reobj.SP.push(reobj.global_line + 1);
                    fileptr.seekg(0);
                    for (int i = 1; i < line; i++)
                    {
                        getline(fileptr, str);
                    }
                    reobj.global_line = line;
                }
                else
                    reobj.global_line++;
            }
            else if (word == "CZ")
            {

                stream >> word;
                check_branch(stream, word);
                if (reobj.flag_register["Z"] == "1")
                {
                    int deci_val, line;
                    if (reobj.labelJump.find(word) == reobj.labelJump.end())
                    {
                        deci_val = dataobj.hexidecimal_to_decimal(word);
                        line = reobj.program_counter_next[deci_val];
                    }
                    else
                    {
                        line = reobj.labelJump[word];
                    }
                    reobj.SP.push(reobj.global_line + 1);
                    fileptr.seekg(0);
                    for (int i = 1; i < line; i++)
                    {
                        getline(fileptr, str);
                    }
                    reobj.global_line = line;
                }
                else
                    reobj.global_line++;
            }
            else if (word == "CNZ")
            {

                stream >> word;
                check_branch(stream, word);
                if (reobj.flag_register["Z"] == "0")
                {
                    int deci_val, line;
                    if (reobj.labelJump.find(word) == reobj.labelJump.end())
                    {
                        deci_val = dataobj.hexidecimal_to_decimal(word);
                        line = reobj.program_counter_next[deci_val];
                    }
                    else
                    {
                        line = reobj.labelJump[word];
                    }
                    reobj.SP.push(reobj.global_line + 1);
                    fileptr.seekg(0);
                    for (int i = 1; i < line; i++)
                    {
                        getline(fileptr, str);
                    }
                    reobj.global_line = line;
                }
                else
                    reobj.global_line++;
            }
            else if (word == "CPE")
            {

                stream >> word;
                check_branch(stream, word);
                if (reobj.flag_register["P"] == "1")
                {
                    int deci_val, line;
                    if (reobj.labelJump.find(word) == reobj.labelJump.end())
                    {
                        deci_val = dataobj.hexidecimal_to_decimal(word);
                        line = reobj.program_counter_next[deci_val];
                    }
                    else
                    {
                        line = reobj.labelJump[word];
                    }
                    reobj.SP.push(reobj.global_line + 1);
                    fileptr.seekg(0);
                    for (int i = 1; i < line; i++)
                    {
                        getline(fileptr, str);
                    }
                    reobj.global_line = line;
                }
                else
                    reobj.global_line++;
            }
            else if (word == "CPO")
            {

                stream >> word;
                check_branch(stream, word);
                if (reobj.flag_register["P"] == "0")
                {
                    int deci_val, line;
                    if (reobj.labelJump.find(word) == reobj.labelJump.end())
                    {
                        deci_val = dataobj.hexidecimal_to_decimal(word);
                        line = reobj.program_counter_next[deci_val];
                    }
                    else
                    {
                        line = reobj.labelJump[word];
                    }
                    reobj.SP.push(reobj.global_line + 1);
                    fileptr.seekg(0);
                    for (int i = 1; i < line; i++)
                    {
                        getline(fileptr, str);
                    }
                    reobj.global_line = line;
                }
                else
                    reobj.global_line++;
            }
            else if (word == "CM")
            {

                stream >> word;
                check_branch(stream, word);
                if (reobj.flag_register["S"] == "1")
                {
                    int deci_val, line;
                    if (reobj.labelJump.find(word) == reobj.labelJump.end())
                    {
                        deci_val = dataobj.hexidecimal_to_decimal(word);
                        line = reobj.program_counter_next[deci_val];
                    }
                    else
                    {
                        line = reobj.labelJump[word];
                    }
                    reobj.SP.push(reobj.global_line + 1);
                    fileptr.seekg(0);
                    for (int i = 1; i < line; i++)
                    {
                        getline(fileptr, str);
                    }
                    reobj.global_line = line;
                }
                else
                    reobj.global_line++;
            }
            else if (word == "CP")
            {

                stream >> word;
                check_branch(stream, word);
                if (reobj.flag_register["S"] == "0")
                {
                    int deci_val, line;
                    if (reobj.labelJump.find(word) == reobj.labelJump.end())
                    {
                        deci_val = dataobj.hexidecimal_to_decimal(word);
                        line = reobj.program_counter_next[deci_val];
                    }
                    else
                    {
                        line = reobj.labelJump[word];
                    }
                    reobj.SP.push(reobj.global_line + 1);
                    fileptr.seekg(0);
                    for (int i = 1; i < line; i++)
                    {
                        getline(fileptr, str);
                    }
                    reobj.global_line = line;
                }
                else
                    reobj.global_line++;
            }
            else if (word == "RET")
            {

                int line = reobj.SP.top();
                reobj.SP.pop();
                fileptr.seekg(0);
                for (int i = 1; i < line; i++)
                {
                    getline(fileptr, str);
                }
                reobj.global_line = line;
            }
            else if (word == "RC")
            {

                if (reobj.flag_register["F"] == "1")
                {
                    int line = reobj.SP.top();
                    reobj.SP.pop();
                    fileptr.seekg(0);
                    for (int i = 1; i < line; i++)
                    {
                        getline(fileptr, str);
                    }
                    reobj.global_line = line;
                }
                else
                    reobj.global_line++;
            }
            else if (word == "RNC")
            {

                if (reobj.flag_register["F"] == "0")
                {
                    int line = reobj.SP.top();
                    reobj.SP.pop();
                    fileptr.seekg(0);
                    for (int i = 1; i < line; i++)
                    {
                        getline(fileptr, str);
                    }
                    reobj.global_line = line;
                }
                else
                    reobj.global_line++;
            }
            else if (word == "RZ")
            {

                if (reobj.flag_register["Z"] == "1")
                {
                    int line = reobj.SP.top();
                    reobj.SP.pop();
                    fileptr.seekg(0);
                    for (int i = 1; i < line; i++)
                    {
                        getline(fileptr, str);
                    }
                    reobj.global_line = line;
                }
                else
                    reobj.global_line++;
            }
            else if (word == "RNZ")
            {

                if (reobj.flag_register["Z"] == "0")
                {
                    int line = reobj.SP.top();
                    reobj.SP.pop();
                    fileptr.seekg(0);
                    for (int i = 1; i < line; i++)
                    {
                        getline(fileptr, str);
                    }
                    reobj.global_line = line;
                }
                else
                    reobj.global_line++;
            }
            else if (word == "RPE")
            {
                if (reobj.flag_register["P"] == "1")
                {
                    int line = reobj.SP.top();
                    reobj.SP.pop();
                    fileptr.seekg(0);
                    for (int i = 1; i < line; i++)
                    {
                        getline(fileptr, str);
                    }
                    reobj.global_line = line;
                }
                else
                    reobj.global_line++;
            }
            else if (word == "RPO")
            {

                if (reobj.flag_register["P"] == "0")
                {
                    int line = reobj.SP.top();
                    reobj.SP.pop();
                    fileptr.seekg(0);
                    for (int i = 1; i < line; i++)
                    {
                        getline(fileptr, str);
                    }
                    reobj.global_line = line;
                }
                else
                    reobj.global_line++;
            }
            else if (word == "RM")
            {

                if (reobj.flag_register["S"] == "1")
                {
                    int line = reobj.SP.top();
                    reobj.SP.pop();
                    fileptr.seekg(0);
                    for (int i = 1; i < line; i++)
                    {
                        getline(fileptr, str);
                    }
                    reobj.global_line = line;
                }
                else
                    reobj.global_line++;
            }
            else if (word == "RP")
            {
                if (reobj.flag_register["S"] == "0")
                {
                    int line = reobj.SP.top();
                    reobj.SP.pop();
                    fileptr.seekg(0);
                    for (int i = 1; i < line; i++)
                    {
                        getline(fileptr, str);
                    }
                    reobj.global_line = line;
                }
                else
                    reobj.global_line++;
            }
            else
            {
                if (word[word.length() - 1] != ':' || check_for_label > 0)
                {
                    print8085Error();
                }
                check_for_label++;
            }
        }
    }
}
