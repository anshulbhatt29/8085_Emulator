#include<map>
#include<string>
using namespace std;
class Address{
    public:
   // vector<string> arr_address;
    map<string,string> arr_address;
    Address()
    {  //arr_address.resize(4000);
    }
    string get_address_value(string addre_data)
    {
        //int addre_int_data=stoi(addre_data);
        return arr_address[addre_data];
    }

};
Address address_obj=Address();