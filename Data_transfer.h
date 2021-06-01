#include"Address.h"
#include"Arithmatic.h"
#include<sstream>
#include<fstream>
#include<cmath>
using namespace std;
class datatransfer{
    public:
    int hexidecimal_to_decimal(string hexadecimal)
    {
        int decimal_value;
        stringstream ss(hexadecimal);
        //ss<<hexadecimal;
        ss>>hex>>decimal_value;
       return decimal_value;

    }
    string decimal_hex_value(int d)
    {
        //string hex_v;
        stringstream ss;
        ss<<hex<<d;
        string hex_v(ss.str());
        return hex_v;

    }
    int binary_to_decimal(string s)
    {
        int x=0,sum=0;
        int i=s.length()-1;
        while(i>=0)
        {
            if(s[i]=='1')
               sum+=pow(2,x);
            i--;
            x++;
        }
        return sum;

    }
    void DAA()//check it...
    {
        string s=reobj.general_purpose_register["A"];
        int j=s.length()-1;
            if((s[j]=='A'||s[j]=='B'||s[j]=='C'||s[j]=='D'||s[j]=='E'||s[j]=='F')||reobj.flag_register["AC"]=="1")
            {
                ari_class.ADM("06");
            }
            --j;
            if((s[j]=='A'||s[j]=='B'||s[j]=='C'||s[j]=='D'||s[j]=='E'||s[j]=='F')||reobj.flag_register["F"]=="1")
            ari_class.ADM("60");

            reobj.global_line++;
    }
    //stack operations...
    void PUSH(string s1,string s2)
    {
        string s;int da;
        da=hexidecimal_to_decimal(reobj.mSP);
        --da;
        s=decimal_hex_value(da);
        reobj.mSP=s;
        reobj.mS.push({s,s1});//address,value...
        da=hexidecimal_to_decimal(reobj.mSP);
        --da;
        s=decimal_hex_value(da);
        reobj.mSP=s;
        reobj.mS.push({s,s2});

    }
    void POP(string s1,string s2)//s1=higher,s2=lower...
    {
        if(s2=="PSW")
        {
            string re="";
            s2=reobj.mS.top().second;
            for(int i=0;i<s2.length();i++)
            {
                re+=ari_class.hex_to_binary[s2[i]];
            }
            reobj.flag_register["S"]=re[0];
            reobj.flag_register["Z"]=re[1];
            reobj.flag_register["gar1"]=re[2];
            reobj.flag_register["AC"]=re[3];
            reobj.flag_register["gar2"]=re[4];
            reobj.flag_register["P"]=re[5];
            reobj.flag_register["gar3"]=re[6];
            reobj.flag_register["F"]=re[7];
        }
        else{
            reobj.general_purpose_register[s2]=reobj.mS.top().second;
        }
        reobj.mS.pop();
        reobj.general_purpose_register[s1]=reobj.mS.top().second;
        reobj.mS.pop();
        reobj.mSP=reobj.mS.top().first;
    }
    void XTHL(string s1,string s2)//s1=higher,s2=lower...
    {
        reobj.general_purpose_register["L"]=reobj.mS.top().second;
        pair<string,string> p;
        p=reobj.mS.top();
        reobj.mS.pop();
        reobj.general_purpose_register["H"]=reobj.mS.top().second;
        reobj.mS.top().second=s1;
        reobj.mS.push({p.first,s2});
    }
    void SPHL(string s1,string s2)
    {
        s1+=s2;
        reobj.mSP=s1;
    }
    //
    void ANA(string s)//s is value..//AC flag always 1...//cy=0...
    {
        int da=hexidecimal_to_decimal(s);
        int da1=hexidecimal_to_decimal(reobj.general_purpose_register["A"]);
        da1=(da1&da);
        s=decimal_hex_value(da1);
        reobj.general_purpose_register["A"]=s;
        reobj.general_purpose_register["F"]="0";
        string binary="";
        for(int i=0;i<s.length();i++)
        {
            binary+=ari_class.hex_to_binary[s[i]];
        }
           binary[0]=='0'?reobj.flag_register["S"]="0":reobj.flag_register["S"]="1";
       int c=0;
        for(int i=0;i<binary.length();i++)
        {
            if(binary[i]=='1')
            c++;
        }
         c%2==0?reobj.flag_register["P"]="1":reobj.flag_register["P"]="0";
         c==0?reobj.flag_register["Z"]="1":reobj.flag_register["Z"]="0";
         reobj.flag_register["AC"]="1";


    }
    void ORA(string s)//s is value...//cy=0,Ac=0....//
    {
        int da=hexidecimal_to_decimal(s);
        int da1=hexidecimal_to_decimal(reobj.general_purpose_register["A"]);
        da1=(da1|da);
        s=decimal_hex_value(da1);
        reobj.general_purpose_register["A"]=s;
        reobj.general_purpose_register["F"]="0";
        reobj.general_purpose_register["AC"]="0";
        string binary="";
        for(int i=0;i<s.length();i++)
        {
            binary+=ari_class.hex_to_binary[s[i]];
        }
           binary[0]=='0'?reobj.flag_register["S"]="0":reobj.flag_register["S"]="1";
       int c=0;
        for(int i=0;i<binary.length();i++)
        {
            if(binary[i]=='1')
            c++;
        }
         c%2==0?reobj.flag_register["P"]="1":reobj.flag_register["P"]="0";
         c==0?reobj.flag_register["Z"]="1":reobj.flag_register["Z"]="0";

    }
    void XRA(string s)//s is value...//cy=0,Ac=0...
    {
        int da=hexidecimal_to_decimal(s);
        int da1=hexidecimal_to_decimal(reobj.general_purpose_register["A"]);
        da1=(da1^da);
        s=decimal_hex_value(da1);
        reobj.general_purpose_register["A"]=s;
        reobj.general_purpose_register["F"]="0";
        reobj.general_purpose_register["AC"]="0";
        string binary="";
        for(int i=0;i<s.length();i++)
        {
            binary+=ari_class.hex_to_binary[s[i]];
        }
           binary[0]=='0'?reobj.flag_register["S"]="0":reobj.flag_register["S"]="1";
       int c=0;
        for(int i=0;i<binary.length();i++)
        {
            if(binary[i]=='1')
            c++;
        }
         c%2==0?reobj.flag_register["P"]="1":reobj.flag_register["P"]="0";
         c==0?reobj.flag_register["Z"]="1":reobj.flag_register["Z"]="0";


    }
    void CMA(string s)//s is value...//no flag is affected.
    {
        int da=hexidecimal_to_decimal(s);
        da=(~da);
        s=decimal_hex_value(da);
        reobj.general_purpose_register["A"]=s;

    }
    void RLC()//if MSB is 1 then no double than previous value...
    {
        string s=reobj.general_purpose_register["A"];
        string binary="";
        for(int i=0;i<s.length();i++)
        {
            binary+=ari_class.hex_to_binary[s[i]];

        }
         if(binary.length()==4)
        {
            binary="0000"+binary;
        }
        if(binary[0]=='0')
        {
            reobj.flag_register["F"]="0";
        }
        else 
        reobj.flag_register["F"]="1";
        int i=binary.length()-2;
        char x=binary[i+1],y;
        while(i>=0)
        {
            y=binary[i];
            binary[i]=x;
            x=y;
            i--;
        }
        binary[binary.length()-1]=x;
        int b_t_d=binary_to_decimal(binary);
        binary=decimal_hex_value(b_t_d);
        reobj.general_purpose_register["A"]=binary;

    }
    void RAL()//with carry..//binary to hexa too....
    {
        string s=reobj.general_purpose_register["A"];
        string binary="",pre_flag;
        for(int i=0;i<s.length();i++)
        {
            binary+=ari_class.hex_to_binary[s[i]];

        }
         if(binary.length()==4)
        {
            binary="0000"+binary;
        }
        pre_flag=reobj.flag_register["F"];
        if(binary[0]=='0')
        {
            reobj.flag_register["F"]="0";//it takes string only...
        }
        else 
        reobj.flag_register["F"]="1";
        int i=binary.length()-2;
        char x=binary[i+1],y;
        while(i>=0)
        {
            y=binary[i];
            binary[i]=x;
            x=y;
            i--;
        }
        binary[binary.length()-1]=pre_flag[0];
        int b_t_d=binary_to_decimal(binary);
        binary=decimal_hex_value(b_t_d);
        reobj.general_purpose_register["A"]=binary;

    }
    void RRC()//check for single digit or multidigit...//
    {
        string s=reobj.general_purpose_register["A"];
        string binary="";
        int size;
        for(int i=0;i<s.length();i++)
        {
            binary+=ari_class.hex_to_binary[s[i]];

        }
        if(binary.length()==4)
        {
            binary="0000"+binary;
        }
        size=binary.length()-1;
        if(binary[size]=='0')
        {
            reobj.flag_register["F"]="0";
        }
        else 
        reobj.flag_register["F"]="1";
        int i=1;
        char x=binary[0],y;
        while(i<=size)
        {
            y=binary[i];
            binary[i]=x;
            x=y;
            i++;
        }
        binary[0]=x;
        int b_t_d=binary_to_decimal(binary);
        binary=decimal_hex_value(b_t_d);
        reobj.general_purpose_register["A"]=binary;

    }
    void RAR()
    {
        string s=reobj.general_purpose_register["A"];
        string binary="",pre_flag;
        int size;
        for(int i=0;i<s.length();i++)
        {
            binary+=ari_class.hex_to_binary[s[i]];

        }
        if(binary.length()==4)
        {
            binary="0000"+binary;
        }
        pre_flag=reobj.flag_register["F"];
        size=binary.length()-1;
        if(binary[size]=='0')
        {
            reobj.flag_register["F"]="0";
        }
        else 
        reobj.flag_register["F"]="1";
        int i=1;
        char x=binary[0],y;
        while(i<=size)
        {
            y=binary[i];
            binary[i]=x;
            x=y;
            i++;
        }
        binary[0]=pre_flag[0];
        int b_t_d=binary_to_decimal(binary);
        binary=decimal_hex_value(b_t_d);
        reobj.general_purpose_register["A"]=binary;

    }
        void INX(string s)//exception..
    {
        int da;
        string re="",rh,rl;
        if(s=="SP")
        {
            s=reobj.mSP;
            da=hexidecimal_to_decimal(s);
            da++;
            s=decimal_hex_value(da);
            reobj.mSP=s;
        }
        else{
        rh=s;
        re+=reobj.general_purpose_register[rh];
        rl=reobj.lower_order_rp[s];
        re+=reobj.general_purpose_register[rl];
        int da=hexidecimal_to_decimal(re);
        da++;
        s=decimal_hex_value(da);
        reobj.general_purpose_register[rh]=s.substr(0,2);
        reobj.general_purpose_register[rl]=s.substr(2,4);
        }

    }
    void DCX(string s)//exception..
    {
        string re="",rh,rl;int da;
        if(s=="SP")
        {
            s=reobj.mSP;
            da=hexidecimal_to_decimal(s);
            --da;
            s=decimal_hex_value(da);
            reobj.mSP=s;
        }
        else{
        rh=s;
        re+=reobj.general_purpose_register[rh];
        rl=reobj.lower_order_rp[s];
        re+=reobj.general_purpose_register[rl];
        da=hexidecimal_to_decimal(re);
        da--;
        s=decimal_hex_value(da);
        reobj.general_purpose_register[rh]=s.substr(0,2);
        reobj.general_purpose_register[rl]=s.substr(2,4);
        }

    }
    void LXI(string s1,string s2)
    {
        if(s1=="SP")
        {
            reobj.mSP=s2;
        }
        else{
        reobj.general_purpose_register[s1]=s2.substr(0,2);
        s1=reobj.lower_order_rp[s1];
        reobj.general_purpose_register[s1]=s2.substr(2,4);}

    }
    void LHLD(string s)
    {
        reobj.general_purpose_register["L"]=address_obj.get_address_value(s);
        int da=hexidecimal_to_decimal(s);
        da++;
        s=decimal_hex_value(da);
        reobj.general_purpose_register["H"]=address_obj.get_address_value(s);
    }
    void STA(string s)
    {
        address_obj.arr_address[s]=reobj.general_purpose_register["A"];

    }
    void program_counter_function()
    {
      int x,line=1;
      ifstream fileptr;
      string str,word;
      fileptr.open("input.txt");
      while(!fileptr.eof()){
        //  x=fileptr.tellg();
          reobj.program_counter_next.insert({reobj.PC,line});
          getline(fileptr,str);
        std::stringstream stream (str);
        stream>> word;
        if(reobj.command_address.find(word)==reobj.command_address.end())
        {
          reobj.PC+=1;
        }
        else reobj.PC+=reobj.command_address[word];
        line++;
       
      }
   
      fileptr.close();
    }
    void put_data()
    {
        string x;
        cout<<"Enter ...";
        cin>>x;
         address_obj.arr_address["8200"]=x;
         cin>>x;
        address_obj.arr_address["8201"]=x;
          cin>>x;
         address_obj.arr_address["8202"]=x;
         cin>>x;
        address_obj.arr_address["8203"]=x;

    }
    void LDA(string ldas)
    {

        reobj.general_purpose_register["A"]=address_obj.get_address_value(ldas);

    }
    void MOV(string s1,string s2)//it might change..
    {
        reobj.general_purpose_register[s1]=reobj.general_purpose_register[s2];
    }
    void MVI(string s1,string data)
    {

        reobj.general_purpose_register[s1]=data;
    }
    void SHLD(string data)
    {
        address_obj.arr_address[data]=reobj.general_purpose_register["L"];
        int da=hexidecimal_to_decimal(data);
        da++;
        data=decimal_hex_value(da);
        address_obj.arr_address[data]=reobj.general_purpose_register["H"];
    }
    void LDAX(string s)
    {
        string re="";
        re+=reobj.general_purpose_register[s];
        s=reobj.lower_order_rp[s];
       /* int da=hexidecimal_to_decimal(s);
        da++;
        s=decimal_hex_value(da);*/
        re+=reobj.general_purpose_register[s];
        reobj.general_purpose_register["A"]=address_obj.get_address_value(re);
    }
    void STAX(string s)
    {
        string re="";
        re+=reobj.general_purpose_register[s];
        s=reobj.lower_order_rp[s];
        re+=reobj.general_purpose_register[s];
        address_obj.arr_address[re]=reobj.general_purpose_register["A"];
    }
    void XCHG()
    {
        string s;
        s=reobj.general_purpose_register["H"];
        reobj.general_purpose_register["H"]=reobj.general_purpose_register["D"];
        reobj.general_purpose_register["D"]=s;
        s=reobj.general_purpose_register["L"];
        reobj.general_purpose_register["L"]=reobj.general_purpose_register["E"];
        reobj.general_purpose_register["E"]=s;
        
    }
  
    void HLT()
    {
        cout<<"flag register carry"<<" "<<reobj.flag_register["F"]<<endl;
          cout<<"flag register auxillary carry"<<" "<<reobj.flag_register["AC"]<<endl;
         cout<<"flag register sign"<<" "<<reobj.flag_register["S"]<<endl;
          cout<<"flag register parity"<<" "<<reobj.flag_register["P"]<<endl;
         cout<<"flag register zero"<<" "<<reobj.flag_register["Z"]<<endl;
         cout<<"ans"<<endl;
        cout<<address_obj.arr_address["8204"]<<endl<<address_obj.arr_address["8205"];
    }
    int gv=0;
    void print()
    {
       

    }
};
datatransfer dataobj= datatransfer();