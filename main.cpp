#include"Data_transfer.h"
#include<bits/stdc++.h>
using namespace std;
int main()
{
    dataobj.put_data();//starting address 3000....
    dataobj.program_counter_function();
    ifstream fileptr;
    string str,word;
    fileptr.open("input.txt");
    while(!fileptr.eof()){
    getline(fileptr,str);
    std::stringstream stream (str);
    while(stream>> word)
    {
        //Data transfer instructions.
       if(word=="LDA")
       {
           stream>>word;
           dataobj.LDA(word);
           reobj.global_line++;
           dataobj.print();

       }
       if(word=="MOV")
       {
           stream>>word;
           std::stringstream stream_for_move(word);
           string s1,s2,re;
           getline(stream_for_move,s1,',');
           getline(stream_for_move,s2,',');
           if(s1=="M")
           {
              
               re=reobj.general_purpose_register["H"]+reobj.general_purpose_register["L"];
               address_obj.arr_address[re]=reobj.general_purpose_register[s2];

           }
          else if(s2=="M")//do it..
           {
               re=reobj.general_purpose_register["H"]+reobj.general_purpose_register["L"];
               reobj.general_purpose_register[s1]=address_obj.get_address_value(re);
           }
           else{
           dataobj.MOV(s1,s2);
           }

            reobj.global_line++;
            dataobj.print();

       }                      //both memory instructions are missing....very very important check it.....
           if(word=="MVI")
       {
           stream>>word;
           std::stringstream stream_for_move(word);
           string s1,s2,re;
           getline(stream_for_move,s1,',');
           getline(stream_for_move,s2,',');
             if(s1=="M")//do it..
           {
               re=reobj.general_purpose_register["H"]+reobj.general_purpose_register["L"];
               address_obj.arr_address[re]=s2;
           }
           else
              dataobj.MVI(s1,s2);
           reobj.global_line++;
           dataobj.print();

       }
         if(word=="SHLD")//check it bro!!! ok... for address to be in hex or decimal.
       {
           stream>>word;
           dataobj.SHLD(word);
            reobj.global_line++;

       }
       if(word=="LXI")//not for SP.lxi rp,8085.
       {
           stream>>word;
           std::stringstream stream_for_move(word);
           string s1,s2;
           getline(stream_for_move,s1,',');//rp
           getline(stream_for_move,s2,',');//address.
           dataobj.LXI(s1,s2);
           reobj.global_line++;
           dataobj.print();

       }
       if(word=="LHLD")
       {
           stream>>word;
           dataobj.LHLD(word);
           reobj.global_line++;
       }
     
       if(word=="STA")
       {
           stream>>word;
           dataobj.STA(word);
           reobj.global_line++;
           dataobj.print();
       }
       if(word=="LDAX")//not accepted registers other than B,D....
       {
           stream>>word;
           dataobj.LDAX(word);
           reobj.global_line++;
       }
       if(word=="XCHG")
       {
           dataobj.XCHG();
           reobj.global_line++;

       }
       if(word=="STAX")//STAX H not valid. same as "M";;;....
       {
           stream>>word;
           dataobj.STAX(word);
           reobj.global_line++;
       }

       if(word=="HLT")
       {
           dataobj.HLT();
           exit(0);
       }
       //Logical Instructions.
       if(word=="ANA")
       {
           stream>>word;
           if(word=="M")
           {
               string re=reobj.general_purpose_register["H"]+reobj.general_purpose_register["L"];
               dataobj.ANA(address_obj.get_address_value(re));

           }
           else{
               dataobj.ANA(reobj.general_purpose_register[word]);
           }
             reobj.global_line++;
       }
       if(word=="ANI")
       {
           stream>>word;
           dataobj.ANA(word);
           reobj.global_line++;
       }
       if(word=="ORA")
       {
           stream>>word;
           if(word=="M")
           {
               string re=reobj.general_purpose_register["H"]+reobj.general_purpose_register["L"];
               dataobj.ORA(address_obj.get_address_value(re));

           }
           else{
               dataobj.ORA(reobj.general_purpose_register[word]);
           }
             reobj.global_line++;

       }
       if(word=="ORI")
       {
           stream>>word;
           dataobj.ORA(word);
           reobj.global_line++;

       }
       if(word=="XRA")
       {
           stream>>word;
           if(word=="M")
           {
               string re=reobj.general_purpose_register["H"]+reobj.general_purpose_register["L"];
               dataobj.XRA(address_obj.get_address_value(re));

           }
           else{
               dataobj.XRA(reobj.general_purpose_register[word]);
           }
             reobj.global_line++;
             dataobj.print();
       }
       if(word=="XRI")
       {
           stream>>word;
           dataobj.XRA(word);
           reobj.global_line++;

       }
       if(word=="CMA")
       {
           dataobj.CMA(reobj.general_purpose_register["A"]);
           reobj.global_line++;
       }
       if(word=="CMC")
       {
             reobj.flag_register["F"]=="0"?reobj.flag_register["F"]="1":reobj.flag_register["F"]="0";
             reobj.global_line++;
             dataobj.print();
       }
       if(word=="STC")
       {
           reobj.flag_register["F"]="1";
           reobj.global_line++;
       }
       if(word=="RLC")
       {
           dataobj.RLC();
           reobj.global_line++;
       }
       if(word=="RAL")
       {
           dataobj.RAL();
           reobj.global_line++;
       }
       if(word=="RRC")
       {
           dataobj.RRC();
           reobj.global_line++;
       }
       if(word=="RAR")
       {
           dataobj.RAR();
           reobj.global_line++;
           dataobj.print();
       }
       if(word=="CMP")//it is in arithmatic file as it is similar to SUB...
       {
           stream>>word;
           string s;
           if(word=="M")
           {
               s=reobj.general_purpose_register["H"]+reobj.general_purpose_register["L"];
               ari_class.CMP(address_obj.get_address_value(s));
           }
           else 
           ari_class.CMP(reobj.general_purpose_register[word]);
           reobj.global_line++;
           dataobj.print();
           
       }
       if(word=="CPI")
       {
           stream>>word;
            ari_class.CMP(word);
           reobj.global_line++;

       }
       //Stack//Input/Output....
       //IN /OUT confussion....
       if(word=="PUSH")
       {
           stream>>word;
           if(word=="PSW")
           {
               string psw;
               psw=reobj.general_purpose_register["S"]+reobj.general_purpose_register["Z"]+reobj.general_purpose_register["gar1"]+reobj.general_purpose_register["AC"]+reobj.general_purpose_register["gar2"]+reobj.general_purpose_register["P"]+reobj.general_purpose_register["gar3"]+reobj.general_purpose_register["F"];
               int da=dataobj.binary_to_decimal(psw);
               psw=dataobj.decimal_hex_value(da);
               dataobj.PUSH(reobj.general_purpose_register["A"],psw);

           }
           else{
              dataobj.PUSH(reobj.general_purpose_register[word],reobj.general_purpose_register[reobj.lower_order_rp[word]]);
           }
           reobj.global_line++;
       }
       if(word=="POP")
       {
           stream>>word;
           if(word=="PSW")
           {
               dataobj.POP("A","PSW");

           }
           else{
               dataobj.POP(word,reobj.lower_order_rp[word]);
           }
            reobj.global_line++;
       }
       if(word=="XTHL")
       {
           dataobj.XTHL(reobj.general_purpose_register["H"],reobj.general_purpose_register["L"]);
            reobj.global_line++;
       }
       if(word=="SPHL")
       {
           dataobj.SPHL(reobj.general_purpose_register["H"],reobj.general_purpose_register["L"]);
           reobj.global_line++;
       }
       if(word=="IN")
       {
           stream>>word;
           reobj.general_purpose_register["A"]=reobj.port_add[word];
           reobj.global_line++;
       }
       if(word=="OUT")
       {
           stream>>word;
           reobj.port_add[word]=reobj.general_purpose_register["A"];
           reobj.global_line++;
       }


       //Arithemetic Instructions.
       if(word=="ADD")
       {
           stream>>word;
           if(word=="M"){
              ari_class.ADM(address_obj.get_address_value(reobj.general_purpose_register["H"]+reobj.general_purpose_register["L"]));
           }
              else
           ari_class.ADD(word);

            reobj.global_line++;
            dataobj.print();

       }
       if(word=="ADI")
       {
           stream>>word;
           ari_class.ADM(word);//because it is handling data.
            reobj.global_line++;

       }
       if(word=="ACI")
       {
           stream>>word;
           ari_class.ACI(word);
          reobj.global_line++;
       }
       if(word=="AMC")
       {
           stream>>word;
           ari_class.AMC(address_obj.get_address_value(reobj.general_purpose_register["H"]+reobj.general_purpose_register["L"]));
           reobj.global_line++;
       }
       if(word=="DAD")
       {
           string s1;
           stream>>word;
           if(word=="SP")//value of SP....
           {
               ari_class.DAD(reobj.mSP);
           }
           else{
               s1=reobj.general_purpose_register[word]+reobj.general_purpose_register[reobj.lower_order_rp[word]];
               ari_class.DAD(s1);
           }
           reobj.global_line++;
       }
       if(word=="ADC")
       {
           stream>>word;
           if(word=="M")
           {
               ari_class.ADC(address_obj.get_address_value(reobj.general_purpose_register["H"]+reobj.general_purpose_register["L"]));
           }
           else
           ari_class.ADC(reobj.general_purpose_register[word]);
           reobj.global_line++;
           dataobj.print();
       }
       if(word=="DAA")//adjust accumulator..
       {
           dataobj.DAA();
           reobj.global_line++;
       }
       //Subtraction...
       if(word=="SUB")
       {
           stream>>word;
             if(word=="M"){
              ari_class.SUI(address_obj.get_address_value(reobj.general_purpose_register["H"]+reobj.general_purpose_register["L"]));//for SUB M.
             }
             else 
               ari_class.SUB(word);
            reobj.global_line++;

       }
       if(word=="SUI")
       {
           stream>>word;
           ari_class.SUI(word);
           reobj.global_line++;
       }
       if(word=="SBI")
       {
           stream>>word;
           ari_class.SBI(word);
           reobj.global_line++;

       }
       if(word=="SBB")
       {
             stream>>word;
             if(word=="M"){
              ari_class.SBB(address_obj.get_address_value(reobj.general_purpose_register["H"]+reobj.general_purpose_register["L"]));//for SBB M.
             }
             else 
               ari_class.SBB(reobj.general_purpose_register[word]);
            reobj.global_line++;
       }
       if(word=="INR")//memory ,Register.//important!!! carry flag is not affected.okkk
       {

           string ret_val;
           stream>>word;
           if(word=="M")
           {
               string re="";
               re+=reobj.general_purpose_register["H"]+reobj.general_purpose_register["L"];
               ret_val=ari_class.INR(address_obj.get_address_value(re));
               address_obj.arr_address[re]=ret_val;

           }
           else{
               ret_val=ari_class.INR(reobj.general_purpose_register[word]);
               reobj.general_purpose_register[word]=ret_val;
               cout<<reobj.general_purpose_register["A"]<<endl;
           }
           reobj.global_line++;
           dataobj.print();
       }
       if(word=="INX")
       {
           stream>>word;
           dataobj.INX(word);
           reobj.global_line++;
       }
       if(word=="DCR")//carry flag is not affected.
       {
           string ret_val;
           stream>>word;
           if(word=="M")
           {
               string re="";
               re+=reobj.general_purpose_register["H"]+reobj.general_purpose_register["L"];
               ret_val=ari_class.DCR(address_obj.get_address_value(re));
               address_obj.arr_address[re]=ret_val;

           }
           else{
               ret_val=ari_class.DCR(reobj.general_purpose_register[word]);
               reobj.general_purpose_register[word]=ret_val;
           }
           reobj.global_line++;
       }
       if(word=="DCX")
       {
           stream>>word;
           dataobj.DCX(word);
           reobj.global_line++;
       }
     
       //Branching instructions.
       if(word=="JMP")
       {
           int deci_val,line;
           stream>>word;
           deci_val=dataobj.hexidecimal_to_decimal(word);
           line=reobj.program_counter_next[deci_val];
           fileptr.seekg(0);
           for(int i=1;i<line;i++)
           {
                getline(fileptr,str);//check may be..
           }
            reobj.global_line=line;
            dataobj.print();

       }
       if(word=="JC")
       {
            stream>>word;
            if(reobj.flag_register["F"]=="1"){
           int deci_val,line;
           deci_val=dataobj.hexidecimal_to_decimal(word);
           line=reobj.program_counter_next[deci_val];
           fileptr.seekg(0);
           for(int i=1;i<line;i++)
           {
                getline(fileptr,str);
           }
            reobj.global_line=line;
         
            }
            else reobj.global_line++;
                 dataobj.print();
             

       }
       if(word=="JNC")
       {
             stream>>word;
            if(reobj.flag_register["F"]=="0"){
           int deci_val,line;
           deci_val=dataobj.hexidecimal_to_decimal(word);
           line=reobj.program_counter_next[deci_val];
           fileptr.seekg(0);
           for(int i=1;i<line;i++)
           {
                getline(fileptr,str);
           }
            reobj.global_line=line;
            }
          else   reobj.global_line++;
          dataobj.print();
             
       }
       if(word=="JZ")
       {  stream>>word;
            if(reobj.flag_register["Z"]=="1"){
           int deci_val,line;
           deci_val=dataobj.hexidecimal_to_decimal(word);
           line=reobj.program_counter_next[deci_val];
           fileptr.seekg(0);
           for(int i=1;i<line;i++)
           {
                getline(fileptr,str);
           }
            reobj.global_line=line;

            }
          else   reobj.global_line++;
          dataobj.print();
  
       }
       if(word=="JNZ")
       {
           stream>>word;
            if(reobj.flag_register["Z"]=="0"){
           int deci_val,line;
           deci_val=dataobj.hexidecimal_to_decimal(word);
           line=reobj.program_counter_next[deci_val];
           fileptr.seekg(0);
           for(int i=1;i<line;i++)
           {
                getline(fileptr,str);
           }
            reobj.global_line=line;
            }
          else  reobj.global_line++;
          dataobj.print();
       }
       if(word=="JPE")
       {
             stream>>word;
            if(reobj.flag_register["P"]=="1"){
           int deci_val,line;
           deci_val=dataobj.hexidecimal_to_decimal(word);
           line=reobj.program_counter_next[deci_val];
           fileptr.seekg(0);
           for(int i=1;i<line;i++)
           {
                getline(fileptr,str);
           }
            reobj.global_line=line;
            }
          else  reobj.global_line++;
       }
       if(word=="JPO")
       {
             stream>>word;
            if(reobj.flag_register["P"]=="0"){
           int deci_val,line;
           deci_val=dataobj.hexidecimal_to_decimal(word);
           line=reobj.program_counter_next[deci_val];
           fileptr.seekg(0);
           for(int i=1;i<line;i++)
           {
                getline(fileptr,str);
           }
           reobj.global_line=line;
            }
           else reobj.global_line++;
       }
       if(word=="JM")
       {
             stream>>word;
            if(reobj.flag_register["S"]=="1"){
           int deci_val,line;
           deci_val=dataobj.hexidecimal_to_decimal(word);
           line=reobj.program_counter_next[deci_val];
           fileptr.seekg(0);
           for(int i=1;i<line;i++)
           {
                getline(fileptr,str);
           }
            reobj.global_line=line;
            }
           else  reobj.global_line++;

       }
       if(word=="JP")
       {
           stream>>word;
            if(reobj.flag_register["S"]=="0"){
           int deci_val,line;
           deci_val=dataobj.hexidecimal_to_decimal(word);
           line=reobj.program_counter_next[deci_val];
           fileptr.seekg(0);
           for(int i=1;i<line;i++)
           {
                getline(fileptr,str);
           }
            reobj.global_line=line;
            }
           else  reobj.global_line++;
       }
       if(word=="CALL")
       {
           stream>>word;
           int deci_val,line;
           deci_val=dataobj.hexidecimal_to_decimal(word);
           line=reobj.program_counter_next[deci_val];
           reobj.SP.push(reobj.global_line+1);
           fileptr.seekg(0);
           for(int i=1;i<line;i++)
           {
                getline(fileptr,str);
           }
            reobj.global_line=line;
       }
       if(word=="CC")
       {
           stream>>word;
           if(reobj.flag_register["F"]=="1")
           {
                 int deci_val,line;
           deci_val=dataobj.hexidecimal_to_decimal(word);
           line=reobj.program_counter_next[deci_val];
           reobj.SP.push(reobj.global_line+1);
           fileptr.seekg(0);
           for(int i=1;i<line;i++)
           {
                getline(fileptr,str);
           }
            reobj.global_line=line;

           }
           else reobj.global_line++;
       }
        if(word=="CNC")
       {
           stream>>word;
           if(reobj.flag_register["F"]=="0")
           {
                 int deci_val,line;
           deci_val=dataobj.hexidecimal_to_decimal(word);
           line=reobj.program_counter_next[deci_val];
           reobj.SP.push(reobj.global_line+1);
           fileptr.seekg(0);
           for(int i=1;i<line;i++)
           {
                getline(fileptr,str);
           }
            reobj.global_line=line;

           }
           else reobj.global_line++;
       }
        if(word=="CZ")
       {
           stream>>word;
           if(reobj.flag_register["Z"]=="1")
           {
                 int deci_val,line;
           deci_val=dataobj.hexidecimal_to_decimal(word);
           line=reobj.program_counter_next[deci_val];
           reobj.SP.push(reobj.global_line+1);
           fileptr.seekg(0);
           for(int i=1;i<line;i++)
           {
                getline(fileptr,str);
           }
            reobj.global_line=line;

           }
           else reobj.global_line++;
       }
        if(word=="CNZ")
       {
           stream>>word;
           if(reobj.flag_register["Z"]=="0")
           {
                 int deci_val,line;
           deci_val=dataobj.hexidecimal_to_decimal(word);
           line=reobj.program_counter_next[deci_val];
           reobj.SP.push(reobj.global_line+1);
           fileptr.seekg(0);
           for(int i=1;i<line;i++)
           {
                getline(fileptr,str);
           }
            reobj.global_line=line;

           }
           else reobj.global_line++;
       }
        if(word=="CPE")
       {
           stream>>word;
           if(reobj.flag_register["P"]=="1")
           {
                 int deci_val,line;
           deci_val=dataobj.hexidecimal_to_decimal(word);
           line=reobj.program_counter_next[deci_val];
           reobj.SP.push(reobj.global_line+1);
           fileptr.seekg(0);
           for(int i=1;i<line;i++)
           {
                getline(fileptr,str);
           }
            reobj.global_line=line;

           }
           else reobj.global_line++;
       }
        if(word=="CPO")
       {
           stream>>word;
           if(reobj.flag_register["P"]=="0")
           {
                 int deci_val,line;
           deci_val=dataobj.hexidecimal_to_decimal(word);
           line=reobj.program_counter_next[deci_val];
           reobj.SP.push(reobj.global_line+1);
           fileptr.seekg(0);
           for(int i=1;i<line;i++)
           {
                getline(fileptr,str);
           }
            reobj.global_line=line;

           }
           else reobj.global_line++;
       }
        if(word=="CM")
       {
           stream>>word;
           if(reobj.flag_register["S"]=="1")
           {
                 int deci_val,line;
           deci_val=dataobj.hexidecimal_to_decimal(word);
           line=reobj.program_counter_next[deci_val];
           reobj.SP.push(reobj.global_line+1);
           fileptr.seekg(0);
           for(int i=1;i<line;i++)
           {
                getline(fileptr,str);
           }
            reobj.global_line=line;

           }
           else reobj.global_line++;
       }
        if(word=="CP")
       {
           stream>>word;
           if(reobj.flag_register["S"]=="0")
           {
                 int deci_val,line;
           deci_val=dataobj.hexidecimal_to_decimal(word);
           line=reobj.program_counter_next[deci_val];
           reobj.SP.push(reobj.global_line+1);
           fileptr.seekg(0);
           for(int i=1;i<line;i++)
           {
                getline(fileptr,str);
           }
            reobj.global_line=line;

           }
           else reobj.global_line++;
       }
       if(word=="RET")
       {
        int line=reobj.SP.top();
        reobj.SP.pop();
        fileptr.seekg(0);
          for(int i=1;i<line;i++)
           {
                getline(fileptr,str);
           }
           reobj.global_line=line;

       }
       if(word=="RC")
       {
           if(reobj.flag_register["F"]=="1")
           {
                int line=reobj.SP.top();
        reobj.SP.pop();
        fileptr.seekg(0);
          for(int i=1;i<line;i++)
           {
                getline(fileptr,str);
           }
           reobj.global_line=line;

           }
           else reobj.global_line++;
       }
        if(word=="RNC")
       {
           if(reobj.flag_register["F"]=="0")
           {
                int line=reobj.SP.top();
        reobj.SP.pop();
        fileptr.seekg(0);
          for(int i=1;i<line;i++)
           {
                getline(fileptr,str);
           }
           reobj.global_line=line;

           }
           else reobj.global_line++;
       }
        if(word=="RZ")
       {
           if(reobj.flag_register["Z"]=="1")
           {
                int line=reobj.SP.top();
        reobj.SP.pop();
        fileptr.seekg(0);
          for(int i=1;i<line;i++)
           {
                getline(fileptr,str);
           }
           reobj.global_line=line;

           }
           else reobj.global_line++;
       }
        if(word=="RNZ")
       {
           if(reobj.flag_register["Z"]=="0")
           {
                int line=reobj.SP.top();
        reobj.SP.pop();
        fileptr.seekg(0);
          for(int i=1;i<line;i++)
           {
                getline(fileptr,str);
           }
           reobj.global_line=line;

           }
           else reobj.global_line++;
       }
        if(word=="RPE")
       {
           if(reobj.flag_register["P"]=="1")
           {
                int line=reobj.SP.top();
        reobj.SP.pop();
        fileptr.seekg(0);
          for(int i=1;i<line;i++)
           {
                getline(fileptr,str);
           }
           reobj.global_line=line;

           }
           else reobj.global_line++;
       }
        if(word=="RPO")
       {
           if(reobj.flag_register["P"]=="0")
           {
                int line=reobj.SP.top();
        reobj.SP.pop();
        fileptr.seekg(0);
          for(int i=1;i<line;i++)
           {
                getline(fileptr,str);
           }
           reobj.global_line=line;

           }
           else reobj.global_line++;
       }
        if(word=="RM")
       {
           if(reobj.flag_register["S"]=="1")
           {
                int line=reobj.SP.top();
        reobj.SP.pop();
        fileptr.seekg(0);
          for(int i=1;i<line;i++)
           {
                getline(fileptr,str);
           }
           reobj.global_line=line;

           }
           else reobj.global_line++;
       }
        if(word=="RP")
       {
           if(reobj.flag_register["S"]=="0")
           {
                int line=reobj.SP.top();
        reobj.SP.pop();
        fileptr.seekg(0);
          for(int i=1;i<line;i++)
           {
                getline(fileptr,str);
           }
           reobj.global_line=line;

           }
           else reobj.global_line++;
       }
    }
}
}
