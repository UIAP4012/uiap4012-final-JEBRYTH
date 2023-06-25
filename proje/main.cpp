#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <bits/stdc++.h>
#define line cout<<"------------------------------------------------"<<endl
using namespace std;
class users
{   friend class staff;
    friend class product;
    friend class products;
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
        fstream uwrite;
        uwrite.open("../proje/files/user.txt",std::ios::app);      //inserting the data in both ulist and the users file
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
class product
{   friend class products;
public:
    string name;
    double price;
    int stock;
public:
    product(string name,double price,int stock)
    {
        this->name=name;
        this->price=price;
        this->stock=stock;
    }
    product()
    {

    }
};
int operator<(const product first,const product second )
{

    if(first.name<second.name)
        return 1;
    if(first.name>second.name)
        return 0;
    if(first.price<second.price)
        return 0;
    if(first.price<second.price)
        return 1;
    if(first.stock<second.stock)
        return 1;
    if(first.stock<second.stock)
        return 0;
    else return 0;

}
class products
{
    set<product> plist;
    public:
    products(){
        fstream pread("../proje/files/product.txt");
        string tmp;
        product tp;
        while (getline (pread,tmp)) {
        tp.name=tmp;
        getline (pread,tmp);
        tp.price=stod(tmp);
        getline (pread,tmp);
        tp.stock=stod(tmp);
        plist.insert(tp);
        }
        pread.close();
    }
    void pinsert(string pname,int pstock,double pprice)
{
        if(pcheck(pname))
        {
            cout<<"product already exists"<<endl;
            line;
            return;
        }
        fstream pwrite;
        pwrite.open("../proje/files/product.txt", std::ios::app);//inserting the data in both plist and the product file
        pwrite<<pname<<endl;
        pwrite<<pprice<<endl;
        pwrite<<pstock<<endl;
        product tp;
        tp.name=pname;
        tp.price=pprice;
        tp.stock=pstock;
        plist.insert(tp);
        pwrite.close();
}
    void pnameedit(string pname,string pnewname)
    {   int ps=pfind(pname).stock;
        double p=pfind(pname).price;
        pdel(pname);
        pinsert(pnewname,ps,p);
    }
    void pstockedit(string pname,int addstock)
    {
        int ps=pfind(pname).stock;
        double p=pfind(pname).price;
        pdel(pname);
        pinsert(pname,ps+addstock,p);
    }
    void ppriceedit(string pname,double newprice)
    {
        int ps=pfind(pname).stock;
        pdel(pname);
        pinsert(pname,ps,newprice);
    }
    product  pfind(string pname)
    {
        for(auto & y :plist)
        {
            if(y.name==pname)
            {
             return y;
            }
        }
        cout<<"product not found"<<endl;
                 line;
                 product y;
                 y.name="0";
                 y.price=0;
                 y.stock=0;
                return y ;

    }
    bool pcheck(string pname)
    {
        for(auto & y : plist)
        if(pname==y.name)
            return 1;
        return 0;

    }
    void pdel(string pname)
    {
        if(!pcheck(pname))
        {
            cout<<"product not found"<<endl;
            line;
            return;
        }
        plist.erase(pfind(pname));
        remove("../proje/files/product.txt");
        fstream newpfile;
        newpfile.open("../proje/files/product.txt",ios::out);
        newpfile.close();
        fstream pwrite("../proje/files/product.txt");      //inserting the data in the product file
        for(auto & y :plist )
        {
            pwrite<<y.name<<endl;
            pwrite<<y.price<<endl;
            pwrite<<y.stock<<endl;
        }
        pwrite.close();
    }
    void pprint()
    {
        cout<<"list of products : "<<endl;
        line;
        for(auto & y : plist)
        {
            cout<<"product name : "<<y.name<<endl
               <<"price : "<<y.price<<endl
               <<"available in stock : "<<y.stock<<endl;
            line;
        }
    }
};
class factors
{ public:
 void finsert(string uname,string pname, int num ,double price ,string currency ) //adds a factor to the file
 {   fstream fwrite;
     fwrite.open("../proje/files/factorlog.csv", ios::out | ios::app);
     fwrite<<uname<<","<<pname<<","<<num<<","<<price<<","<<currency<<"\n";
     fwrite.close();
 }

 void fprint()                                                               //prints the purchase log (all the factors )
 {
     ifstream fread("../proje/files/factorlog.csv");
     string tmp;
     cout<<"head of log"<<endl;
     line;
     while(getline(fread,tmp,','))
     {   cout<<endl;
         cout<<"purchaser name : "<<endl<<tmp<<endl;
         getline(fread,tmp,',');
         cout<<"product name : "<<endl<<tmp<<endl;
         getline(fread,tmp,',');
         cout<<"number of items bought : "<<endl<<tmp<<endl;
         getline(fread,tmp,',');
         cout<<"price : "<<endl<<tmp<<endl;
         getline(fread,tmp,'\n');
         cout<<"currency : "<<endl<<tmp<<endl;
         line;
     }
     cout<<"end of log"<<endl;

 }

};
void login()
{
    cout<<"---------------login--------------"<<endl;
}
int main()
{

}
