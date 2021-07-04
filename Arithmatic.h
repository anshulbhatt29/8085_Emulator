#include "Error_handler.h" //we can't include .h file more than once in program...
#include <algorithm>
class Arithmatic
{
public:
    map<char, int> decimal_value_hex{{'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}, {'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15}};
    map<char, string> hex_to_binary{{'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"}, {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"}, {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"}, {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}};
    map<int, char> hex_value_decimal{{0, '0'}, {1, '1'}, {2, '2'}, {3, '3'}, {4, '4'}, {5, '5'}, {6, '6'}, {7, '7'}, {8, '8'}, {9, '9'}, {10, 'A'}, {11, 'B'}, {12, 'C'}, {13, 'D'}, {14, 'E'}, {15, 'F'}};

    //handle the case of H register.  INX H corresponds to memory.
    void AMC(string s)
    {
        string a = reobj.general_purpose_register["A"];
        string re = "";
        int c = 0;
        int cn = 0;
        int i = a.length() - 1, j = s.length() - 1, x, y;
        while (i >= 0 || j >= 0)
        {
            if (i >= 0)
            {
                x = decimal_value_hex[a[i]];
            }
            else
                x = 0;
            if (j >= 0)
            {
                y = decimal_value_hex[s[j]];
            }
            else
                y = 0;
            x = x + y + (reobj.flag_register["F"] == "0" ? 0 : 1);
            if (cn == 0)
                reobj.flag_register["AC"] = to_string(x / 16);
            cn++;
            reobj.flag_register["F"] = to_string(x / 16);
            x = x % 16;
            re += hex_value_decimal[x];
            i--;
            j--;
        }
        reverse(re.begin(), re.end());

        reobj.general_purpose_register["A"] = re;
        string binary = "";
        for (int i = 0; i < re.length(); i++)
        {
            binary += hex_to_binary[re[i]];
        }
        binary[0] == '0' ? reobj.flag_register["S"] = "0" : reobj.flag_register["S"] = "1";
        c = 0;
        for (int i = 0; i < binary.length(); i++)
        {
            if (binary[i] == '1')
                c++;
        }
        c % 2 == 0 ? reobj.flag_register["P"] = "1" : reobj.flag_register["P"] = "0";
        c == 0 ? reobj.flag_register["Z"] = "1" : reobj.flag_register["Z"] = "0";
    }

    /*void ACI(string s)
    {
        string a=reobj.general_purpose_register["A"];
        string re="";
        int c=0;
        int cn=0;
        int i=a.length()-1,j=s.length()-1,x,y;
            while(i>=0||j>=0){
            if(i>=0)
            {
                x=decimal_value_hex[a[i]];
            }
            else x=0;
            if(j>=0)
            {
                y=decimal_value_hex[s[j]];
            }
            else y=0;
            x=x+y+(reobj.flag_register["F"]=="0"?0:1);
            if(cn==0)
            reobj.flag_register["AC"]=to_string(x/16);
            cn++;
            reobj.flag_register["F"]=to_string(x/16);
            x=x%16;
            re+=hex_value_decimal[x];
          i--;
          j--;
        }
        reverse(re.begin(),re.end());

        reobj.general_purpose_register["A"]=re;
        string binary="";
        for(int i=0;i<re.length();i++)
        {
            binary+=hex_to_binary[re[i]];
            
        }
        binary[0]=='0'?reobj.flag_register["S"]="0":reobj.flag_register["S"]="1";
        c=0;
        for(int i=0;i<binary.length();i++)
        {
            if(binary[i]=='1')
            c++;
        }
         c%2==0?reobj.flag_register["P"]="1":reobj.flag_register["P"]="0";
         c==0?reobj.flag_register["Z"]="1":reobj.flag_register["Z"]="0";
    }
    */

    void ADM(string s) //data...
    {
        string a = reobj.general_purpose_register["A"];
        string re = "";
        int c = 0;
        int i = a.length() - 1, j = s.length() - 1, x, y;
        while (i >= 0 || j >= 0)
        {
            if (i >= 0)
            {
                x = decimal_value_hex[a[i]];
            }
            else
                x = 0;
            if (j >= 0)
            {
                y = decimal_value_hex[s[j]];
            }
            else
                y = 0;
            if (c != 0)
                x = x + y + (reobj.flag_register["F"] == "0" ? 0 : 1);
            else
                x = x + y;
            if (c == 0)
            {
                reobj.flag_register["AC"] = to_string(x / 16);
            }
            c++;
            reobj.flag_register["F"] = to_string(x / 16);
            x = x % 16;
            re += hex_value_decimal[x];
            i--;
            j--;
        }
        reverse(re.begin(), re.end());

        reobj.general_purpose_register["A"] = re;
        string binary = "";
        for (int i = 0; i < re.length(); i++)
        {
            binary += hex_to_binary[re[i]];
        }
        binary[0] == '0' ? reobj.flag_register["S"] = "0" : reobj.flag_register["S"] = "1";
        c = 0;
        for (int i = 0; i < binary.length(); i++)
        {
            if (binary[i] == '1')
                c++;
        }
        c % 2 == 0 ? reobj.flag_register["P"] = "1" : reobj.flag_register["P"] = "0";
        c == 0 ? reobj.flag_register["Z"] = "1" : reobj.flag_register["Z"] = "0";
    }
    /*
    void ADD(string s)
    {
        string a=reobj.general_purpose_register["A"];
        string re="";
        int c=0;
        s=reobj.general_purpose_register[s];
        int i=a.length()-1,j=s.length()-1,x,y;
            while(i>=0||j>=0){
            if(i>=0)
            {
                x=decimal_value_hex[a[i]];
            }
            else x=0;
            if(j>=0)
            {
                y=decimal_value_hex[s[j]];
            }
            else y=0;
            if(c!=0)
            x=x+y+(reobj.flag_register["F"]=="0"?0:1);
            else x=x+y;

            if(c==0)
            reobj.flag_register["AC"]=to_string(x/16);
            c++;
            reobj.flag_register["F"]=to_string(x/16);

            x=x%16;
            re+=hex_value_decimal[x];
          i--;
          j--;
        }
        reverse(re.begin(),re.end());

        reobj.general_purpose_register["A"]=re;
        string binary="";
        for(int i=0;i<re.length();i++)
        {
            binary+=hex_to_binary[re[i]];
            
        }
        binary[0]=='0'?reobj.flag_register["S"]="0":reobj.flag_register["S"]="1";
        c=0;
        for(int i=0;i<binary.length();i++)
        {
            if(binary[i]=='1')
            c++;
        }
         c%2==0?reobj.flag_register["P"]="1":reobj.flag_register["P"]="0";
         c==0?reobj.flag_register["Z"]="1":reobj.flag_register["Z"]="0";

    }

      void ADC(string s)
    {
         string a=reobj.general_purpose_register["A"];
        string re="";
        int c=0;
        int cn=0;
      //  s=reobj.general_purpose_register[s];
        int i=a.length()-1,j=s.length()-1,x,y;
            while(i>=0||j>=0){
            if(i>=0)
            {
                x=decimal_value_hex[a[i]];
            }
            else x=0;
            if(j>=0)
            {
                y=decimal_value_hex[s[j]];
            }
            else y=0;
            x=x+y+(reobj.flag_register["F"]=="0"?0:1);
            if(cn==0)
            reobj.flag_register["AC"]=to_string(x/16);
            cn++;
            reobj.flag_register["F"]=to_string(x/16);
            x=x%16;
            re+=hex_value_decimal[x];
          i--;
          j--;
        }
        reverse(re.begin(),re.end());

        reobj.general_purpose_register["A"]=re;
        string binary="";
        for(int i=0;i<re.length();i++)
        {
            binary+=hex_to_binary[re[i]];
            
        }
        binary[0]=='0'?reobj.flag_register["S"]="0":reobj.flag_register["S"]="1";
        c=0;
        for(int i=0;i<binary.length();i++)
        {
            if(binary[i]=='1')
            c++;
        }
         c%2==0?reobj.flag_register["P"]="1":reobj.flag_register["P"]="0";
         c==0?reobj.flag_register["Z"]="1":reobj.flag_register["Z"]="0";
    }
    */
    void DAD(string s) //only cy flag is affected...
    {
        string a = reobj.general_purpose_register["H"] + reobj.general_purpose_register["L"];
        string re = "";
        int c = 0;
        int i = a.length() - 1, j = s.length() - 1, x, y;
        while (i >= 0 || j >= 0)
        {
            if (i >= 0)
            {
                x = decimal_value_hex[a[i]];
            }
            else
                x = 0;
            if (j >= 0)
            {
                y = decimal_value_hex[s[j]];
            }
            else
                y = 0;
            if (c != 0)
                x = x + y + (reobj.flag_register["F"] == "0" ? 0 : 1);
            else
                x = x + y;
            c++;
            reobj.flag_register["F"] = to_string(x / 16);
            x = x % 16;
            re += hex_value_decimal[x];
            i--;
            j--;
        }
        reverse(re.begin(), re.end());
        reobj.general_purpose_register["H"] = re.substr(0, 2);
        reobj.general_purpose_register["L"] = re.substr(2, 4);
    }
    /*
    void SUB(string s)
    {  string a=reobj.general_purpose_register["A"];
        string re="";
        int c=0;
        int cn=0;
        s=reobj.general_purpose_register[s];
        int i=a.length()-1,j=s.length()-1,x,y;
            while(i>=0||j>=0){
            if(i>=0)
            {
                x=decimal_value_hex[a[i]];
            }
            else x=0;
            if(j>=0)
            {
                y=decimal_value_hex[s[j]];
            }
            else y=0;
            if(c!=0)
            x=x-y-(reobj.flag_register["F"]=="0"?0:1);
            else x=x-y;
            c++;
            if(cn==0)
             x<0?reobj.flag_register["AC"]="1":reobj.flag_register["AC"]="0";
            cn++;

            x<0?reobj.flag_register["F"]="1":reobj.flag_register["F"]="0";
            //reobj.flag_register["F"]=to_string(x/16);
            x=x%16;
            if(x<0) x=x+16;
            re+=hex_value_decimal[x];
          i--;
          j--;
        }
        reverse(re.begin(),re.end());

        reobj.general_purpose_register["A"]=re;
        string binary="";
        for(int i=0;i<re.length();i++)
        {
            binary+=hex_to_binary[re[i]];
            
        }
     
        binary[0]=='0'?reobj.flag_register["S"]="0":reobj.flag_register["S"]="1";
        c=0;
        for(int i=0;i<binary.length();i++)
        {
            if(binary[i]=='1')
            c++;
        }
         c%2==0?reobj.flag_register["P"]="1":reobj.flag_register["P"]="0";
         c==0?reobj.flag_register["Z"]="1":reobj.flag_register["Z"]="0";

    }
    */
    void SUI(string s)
    {
        string a = reobj.general_purpose_register["A"];
        string re = "";
        int c = 0;
        int cn = 0;
        int i = a.length() - 1, j = s.length() - 1, x, y;
        while (i >= 0 || j >= 0)
        {
            if (i >= 0)
            {
                x = decimal_value_hex[a[i]];
            }
            else
                x = 0;
            if (j >= 0)
            {
                y = decimal_value_hex[s[j]];
            }
            else
                y = 0;
            if (c != 0)
                x = x - y - (reobj.flag_register["F"] == "0" ? 0 : 1);
            else
                x = x - y;
            c++;
            if (cn == 0)
                x < 0 ? reobj.flag_register["AC"] = "1" : reobj.flag_register["AC"] = "0";
            cn++;

            x < 0 ? reobj.flag_register["F"] = "1" : reobj.flag_register["F"] = "0";
            //reobj.flag_register["F"]=to_string(x/16);
            x = x % 16;
            if (x < 0)
                x = x + 16;
            re += hex_value_decimal[x];
            i--;
            j--;
        }
        reverse(re.begin(), re.end());

        reobj.general_purpose_register["A"] = re;
        string binary = "";
        for (int i = 0; i < re.length(); i++)
        {
            binary += hex_to_binary[re[i]];
        }
        binary[0] == '0' ? reobj.flag_register["S"] = "0" : reobj.flag_register["S"] = "1";
        c = 0;
        for (int i = 0; i < binary.length(); i++)
        {
            if (binary[i] == '1')
                c++;
        }
        c % 2 == 0 ? reobj.flag_register["P"] = "1" : reobj.flag_register["P"] = "0";
        c == 0 ? reobj.flag_register["Z"] = "1" : reobj.flag_register["Z"] = "0";
    }
    void SBI(string s)
    {
        string a = reobj.general_purpose_register["A"];
        string re = "";
        int c = 0;
        int cn = 0;
        int i = a.length() - 1, j = s.length() - 1, x, y;
        while (i >= 0 || j >= 0)
        {
            if (i >= 0)
            {
                x = decimal_value_hex[a[i]];
            }
            else
                x = 0;
            if (j >= 0)
            {
                y = decimal_value_hex[s[j]];
            }
            else
                y = 0;
            x = x - y - (reobj.flag_register["F"] == "0" ? 0 : 1);
            if (cn == 0)
                x < 0 ? reobj.flag_register["AC"] = "1" : reobj.flag_register["AC"] = "0";
            cn++;

            x < 0 ? reobj.flag_register["F"] = "1" : reobj.flag_register["F"] = "0";
            //reobj.flag_register["F"]=to_string(x/16);
            x = x % 16;
            if (x < 0)
                x = x + 16;
            re += hex_value_decimal[x];
            i--;
            j--;
        }
        reverse(re.begin(), re.end());

        reobj.general_purpose_register["A"] = re;
        string binary = "";
        for (int i = 0; i < re.length(); i++)
        {
            binary += hex_to_binary[re[i]];
        }
        binary[0] == '0' ? reobj.flag_register["S"] = "0" : reobj.flag_register["S"] = "1";
        c = 0;
        for (int i = 0; i < binary.length(); i++)
        {
            if (binary[i] == '1')
                c++;
        }
        c % 2 == 0 ? reobj.flag_register["P"] = "1" : reobj.flag_register["P"] = "0";
        c == 0 ? reobj.flag_register["Z"] = "1" : reobj.flag_register["Z"] = "0";
    }
    /*
    void SBB(string s)
    {
        string a=reobj.general_purpose_register["A"];
        string re="";
        int c=0;
        int cn=0;
        //s=reobj.general_purpose_register[s];
        int i=a.length()-1,j=s.length()-1,x,y;
            while(i>=0||j>=0){
            if(i>=0)
            {
                x=decimal_value_hex[a[i]];
            }
            else x=0;
            if(j>=0)
            {
                y=decimal_value_hex[s[j]];
            }
            else y=0;
            x=x-y-(reobj.flag_register["F"]=="0"?0:1);
                if(cn==0)
               x<0?reobj.flag_register["AC"]="1":reobj.flag_register["AC"]="0";
            cn++;
            x<0?reobj.flag_register["F"]="1":reobj.flag_register["F"]="0";
            //reobj.flag_register["F"]=to_string(x/16);
            x=x%16;
            if(x<0) x=x+16;
            re+=hex_value_decimal[x];
          i--;
          j--;
        }
        reverse(re.begin(),re.end());

        reobj.general_purpose_register["A"]=re;
        string binary="";
        for(int i=0;i<re.length();i++)
        {
            binary+=hex_to_binary[re[i]];
            
        }
        binary[0]=='0'?reobj.flag_register["S"]="0":reobj.flag_register["S"]="1";
        c=0;
        for(int i=0;i<binary.length();i++)
        {
            if(binary[i]=='1')
            c++;
        }
         c%2==0?reobj.flag_register["P"]="1":reobj.flag_register["P"]="0";
         c==0?reobj.flag_register["Z"]="1":reobj.flag_register["Z"]="0";
    }
    */
    void CMP(string s) //A-(R) any register..//s is value...
    {
        string a = reobj.general_purpose_register["A"];
        string re = "";
        int c = 0;
        int cn = 0;
        int i = a.length() - 1, j = s.length() - 1, x, y;
        while (i >= 0 || j >= 0)
        {
            if (i >= 0)
            {
                x = decimal_value_hex[a[i]];
            }
            else
                x = 0;
            if (j >= 0)
            {
                y = decimal_value_hex[s[j]];
            }
            else
                y = 0;
            if (c != 0)
                x = x - y - (reobj.flag_register["F"] == "0" ? 0 : 1);
            else
                x = x - y;
            c++;
            if (cn == 0)
                x < 0 ? reobj.flag_register["AC"] = "1" : reobj.flag_register["AC"] = "0";
            cn++;
            x < 0 ? reobj.flag_register["F"] = "1" : reobj.flag_register["F"] = "0";
            //reobj.flag_register["F"]=to_string(x/16);
            x = x % 16;
            if (x < 0)
                x = x + 16;
            re += hex_value_decimal[x];
            i--;
            j--;
        }
        reverse(re.begin(), re.end());
        //reobj.general_purpose_register["A"]=re;
        string binary = "";
        for (int i = 0; i < re.length(); i++)
        {
            binary += hex_to_binary[re[i]];
        }

        binary[0] == '0' ? reobj.flag_register["S"] = "0" : reobj.flag_register["S"] = "1";
        c = 0;
        for (int i = 0; i < binary.length(); i++)
        {
            if (binary[i] == '1')
                c++;
        }
        c % 2 == 0 ? reobj.flag_register["P"] = "1" : reobj.flag_register["P"] = "0";
        c == 0 ? reobj.flag_register["Z"] = "1" : reobj.flag_register["Z"] = "0";
    }
    string INR(string s)
    {
        string a = "1";
        string re = "";
        string cy_pre = reobj.flag_register["F"];
        int c = 0;
        int cn = 0;
        int i = a.length() - 1, j = s.length() - 1, x, y;
        while (i >= 0 || j >= 0)
        {
            if (i >= 0)
            {
                x = decimal_value_hex[a[i]];
            }
            else
                x = 0;
            if (j >= 0)
            {
                y = decimal_value_hex[s[j]];
            }
            else
                y = 0;
            if (c != 0)
                x = x + y + (reobj.flag_register["F"] == "0" ? 0 : 1);
            else
                x = x + y;
            c++;
            if (cn == 0)
                reobj.flag_register["AC"] = to_string(x / 16);
            cn++;
            reobj.flag_register["F"] = to_string(x / 16);
            x = x % 16;
            re += hex_value_decimal[x];
            i--;
            j--;
        }
        reverse(re.begin(), re.end());
        string binary = "";
        for (int i = 0; i < re.length(); i++)
        {
            binary += hex_to_binary[re[i]];
        }
        binary[0] == '0' ? reobj.flag_register["S"] = "0" : reobj.flag_register["S"] = "1";
        c = 0;
        for (int i = 0; i < binary.length(); i++)
        {
            if (binary[i] == '1')
                c++;
        }
        c % 2 == 0 ? reobj.flag_register["P"] = "1" : reobj.flag_register["P"] = "0";
        c == 0 ? reobj.flag_register["Z"] = "1" : reobj.flag_register["Z"] = "0";
        reobj.flag_register["F"] = cy_pre;
        return re;
    } //INX in DATA_TRANSFER file.

    string DCR(string s)
    {
        string a = "1";
        string re = "";
        string cy_pre = reobj.flag_register["F"];
        int c = 0;
        int cn = 0;
        int i = a.length() - 1, j = s.length() - 1, x, y;
        while (i >= 0 || j >= 0)
        {
            if (i >= 0)
            {
                x = decimal_value_hex[a[i]];
            }
            else
                x = 0;
            if (j >= 0)
            {
                y = decimal_value_hex[s[j]];
            }
            else
                y = 0;
            if (c != 0)
                y = y - x - (reobj.flag_register["F"] == "0" ? 0 : 1);
            else
                y = y - x;
            c++;
            if (cn == 0)
                x < 0 ? reobj.flag_register["AC"] = "1" : reobj.flag_register["AC"] = "0";
            cn++;
            y < 0 ? reobj.flag_register["F"] = "1" : reobj.flag_register["F"] = "0";
            //reobj.flag_register["F"]=to_string(x/16);
            y = y % 16;
            if (y < 0)
                y = y + 16;
            re += hex_value_decimal[y];
            i--;
            j--;
        }
        reverse(re.begin(), re.end());
        string binary = "";
        for (int i = 0; i < re.length(); i++)
        {
            binary += hex_to_binary[re[i]];
        }
        binary[0] == '0' ? reobj.flag_register["S"] = "0" : reobj.flag_register["S"] = "1";
        c = 0;
        for (int i = 0; i < binary.length(); i++)
        {
            if (binary[i] == '1')
                c++;
        }
        c % 2 == 0 ? reobj.flag_register["P"] = "1" : reobj.flag_register["P"] = "0";
        c == 0 ? reobj.flag_register["Z"] = "1" : reobj.flag_register["Z"] = "0";
        reobj.flag_register["F"] = cy_pre;
        return re;
    }
};
Arithmatic ari_class = Arithmatic();
