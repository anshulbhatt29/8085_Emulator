#include "registers.h"
#include <sstream>
using namespace std;
void print8085Error()
{
    printf("Error in line\n");
    printf("%d\n", reobj.global_line);
    exit(0);
}
void print8085ErrorPC(int line)
{
    printf("Error in line\n");
    printf("%d\n", line);
    exit(0);
}
void check_LDA(stringstream &st, string &s)
{
    if (s.length() != 4 || st.rdbuf()->in_avail())
    {
        print8085Error();
    }
}
void check_MOV(stringstream &st, stringstream &st1)
{
    string s1, s2;
    try
    {
        getline(st1, s1, ',');
        getline(st1, s2, ',');
    }
    catch (exception e)
    {
        print8085Error();
    }
    if (st.rdbuf()->in_avail() || st1.rdbuf()->in_avail())
    {
        print8085Error();
    }
}
void check_LXI(stringstream &st, stringstream &st1)
{
    string s1, s2;
    try
    {
        getline(st1, s1, ',');
        getline(st1, s2, ',');
    }
    catch (exception e)
    {
        print8085Error();
    }
    if (st.rdbuf()->in_avail() || st1.rdbuf()->in_avail() || s2.length() != 4 || !(s1 == "B" || s1 == "D" || s1 == "H" || s1 == "SP"))
    {
        print8085Error();
    }
}
void check_LDAX(stringstream &st, string &s)
{
    if ((s != "B" && s != "D") || st.rdbuf()->in_avail())
    {
        print8085Error();
    }
}
void check_XCHG(stringstream &st)
{
    if (st.rdbuf()->in_avail())
    {
        print8085Error();
    }
}
void check_ANA(stringstream &st)
{
    if (st.rdbuf()->in_avail())
    {
        print8085Error();
    }
}
void check_ANI(stringstream &st, string &s)
{
    if (s.length() != 2 || st.rdbuf()->in_avail())
    {
        print8085Error();
    }
}
/*
void check_IN(stringstream &st, string &s)
{
    if (s.length() != 2 || st.rdbuf()->in_avail())
    {
        print8085Error();
    }
}*/

void check_branch(stringstream &st, string &s)
{
    if (st.rdbuf()->in_avail() || (reobj.labelJump.find(s) == reobj.labelJump.end() && s.length() != 4))
    {
        print8085Error();
    }
}