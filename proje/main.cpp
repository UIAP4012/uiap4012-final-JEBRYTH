#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <bits/stdc++.h>
#define line cout<<"------------------------------------------------"<<endl
using namespace std;
class users
{   friend class staff;
    map<string,string> ulist;
public:
    users()
    {
        fstream uread("../proje/files/user.txt");
        string tmp;
        int i=0;
        while (getline (uread,tmp)) {
            string p1=tmp;
            getline (uread,tmp);
            string p2=tmp;
            ulist[p1]=p2;
            i++;
        }
        uread.close();

    }
    void uprint()
    {
        for(auto & y : ulist)
        {cout<<"name : "<<endl<<y.first<<endl;
            cout<<"password : "<<endl<<y.second<<endl;
            line;
        }
    }
    bool ufind(string name)
    {
        for(auto & y : ulist)
            if (name==y.first)
                return 1;
        return 0;

    }
    void uinsert(string name,string password)
    {
        if(ufind(name))
        { cout<<"this username is already taken"<<endl;
            line;
            return;}
        fstream uwrite("../proje/files/user.txt");      //inserting the data in both ulist and the users file
        uwrite<<name<<endl;
        uwrite<<password<<endl;
        ulist[name]=password;
        uwrite.close();
    }
    void udel(string name)                             //deleting method by name
    {
        if(!ufind(name))
        {
            cout<<"user not found"<<endl;
            line;
            return;
        }
        ulist.erase(name);
        remove("../proje/files/user.txt");
        fstream newufile;
        newufile.open("../proje/files/user.txt",ios::out);
        newufile.close();
        fstream uwrite("../proje/files/user.txt");      //inserting the data in the users file
        for(auto & y :ulist )
        {
        uwrite<<y.first<<endl;
        uwrite<<y.second<<endl;
        }
        uwrite.close();
        if(!ufind(name))
        cout<<"account deleted"<<endl;
        line;

    }
    void unameedit(string name,string newname)
   {   if(!ufind(name))
        {
            cout<<"user not found"<<endl;
            line;
            return;
        }
        string tmp=ulist[name];
       this->udel(name);
       uinsert(newname,tmp);
   }
   void upassedit(string name,string trypassword,string newpassword )
   {
       if(!ufind(name))
              {
                  cout<<"user not found"<<endl;
                  line;
                  return;
              }
       while(ulist[name]!=trypassword)
       {
           cout<<"the password is incorrect,try again :"<<endl;
           cin>>trypassword;
       }
       udel(name);
       ulist[name]=newpassword;
       uinsert(name,newpassword);
   }
};
class staff
{
};
int main()
{
    users s;
    line;
    line;
    s.uprint();
    s.uinsert("choochar","injahameare");
    s.upassedit("hamid","sdfsff","goh");
    s.unameedit("choochar","sosk");

}
