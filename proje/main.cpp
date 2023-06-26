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
    bool upassedit(string name,string trypassword,string newpassword )
    {
        if(!ufind(name))
        {
            cout<<"user not found"<<endl;
            line;
            return 0;
        }
        while(ulist[name]!=trypassword)
        {
            cout<<"the password is incorrect,try again :"<<endl;
            cin>>trypassword;
        }
        udel(name);
        uinsert(name,newpassword);
        return 1;
    }
    bool ulogin(string name,string password)
    {
        for(auto & y : ulist)
            if ((name==y.first) && (password==y.second))
                return 1;
        return 0;
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
    void fuserprint(string name)                                                               //prints the purchase log (all the factors )
    {
        ifstream fread("../proje/files/factorlog.csv");
        string tmp;
        cout<<"head of log"<<endl;
        line;
        while(getline(fread,tmp,','))
        {   if(name==tmp)
            {
                cout<<endl;
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
            else
            {
                getline(fread,tmp,',');
                getline(fread,tmp,',');
                getline(fread,tmp,',');
                getline(fread,tmp,'\n');
            }
        }
        cout<<"end of log"<<endl;

    }
    void fusernc(string name,string newname)   //changes the name of the user in the factors file
    {
        fstream fwrite;
        fwrite.open("../proje/files/factorlog1.csv", ios::out | ios::app);
        ifstream fread("../proje/files/factorlog.csv");
        string tmp;
        while(getline(fread,tmp,','))
        {   if(name==tmp)
            {
                fwrite<<newname<<",";
            }
            else
            {
                fwrite<<tmp<<",";
            }
            getline(fread,tmp,',');
            fwrite<<tmp<<",";
            getline(fread,tmp,',');
            fwrite<<tmp<<",";
            getline(fread,tmp,',');
            fwrite<<tmp<<",";
            getline(fread,tmp,'\n');
            fwrite<<tmp<<"\n";

        }
        fwrite.close();
        fread.close();
        remove("../proje/files/factorlog.csv");
        rename("../proje/files/factorlog1.csv","../proje/files/factorlog.csv");

    }
};
void buy(string name)
{
    products p;
    factors f;
    while(1)
    {
        cout<<name<<"s dashboard : shop"<<endl<<endl;
        line;
        cout<<".1 : to see all the products"<<endl;
        cout<<".2 : to view a product by its name"<<endl;
        cout<<".3 : to buy a product"<<endl;
        cout<<".4 : to go back "<<endl;
        line;
        int cs;
        cin>>cs;
        switch(cs)
        {
        case 1 :
        {
            p.pprint();
            break;
        }
        case 2 :
        {
            cout<<"enter full name of the product : "<<endl;
            string pname;
            cin>>pname;
            product tmp=p.pfind(pname);
            cout<<"product name : "<<endl;
            cout<<tmp.name<<endl;
            cout<<"products price : "<<endl;
            cout<<tmp.price<<endl;
            cout<<"stock : "<<endl;
            cout<<tmp.stock<<endl;
            line;
            break;
        }
        case 3 :
        {
            cout<<"enter full name of the product : "<<endl;
            string pname;
            cin>>pname;
            if(!p.pcheck(pname))
            {
                cout<<"item not found "<<endl;
                line;
                break;
            }
            product tmp=p.pfind(pname);
            cout<<"enter the number of items you want to buy : "<<endl;
            int pbuy;
            bool q=0;
            while(1)
            {
                cin>>pbuy;
                if(pbuy>tmp.stock)
                {cout<<"this many items are not available "<<endl<<"enter 1 to try again or 0 to go back"<<endl;
                    int c;
                    cin>>c;
                    if(c)
                        continue;
                    else
                    {
                        q=1;
                        break;
                    }
                }
                else
                    break;
            }
            if(q)
                break;
            cout<<"select your prefered currency : "<<endl;
            cout<<".1 : toman "<<endl;
            cout<<".2 : dollar "<<endl;
            cout<<".3 : euro "<<endl;
            cout<<".4 : pound "<<endl;
            int cs;
            string curr;
            double pprice=0;
            cin>>cs;
            fstream buyread("../proje/files/currency.txt");
            switch(cs)
            {
            case 1 :
            {
                pprice=tmp.price*pbuy;
                curr="toman";
                break;
            }
            case 2 :
            {   string tp;
                getline(buyread,tp);
                pprice=tmp.price/stod(tp)*pbuy;
                curr="dollar";
                break;
            }
            case 3 :
            {
                string tp;
                getline(buyread,tp);
                getline(buyread,tp);
                pprice=tmp.price/stod(tp)*pbuy;
                curr="euro";
                break;
            }
            case 4 :
            {
                string tp;
                getline(buyread,tp);
                getline(buyread,tp);
                getline(buyread,tp);
                pprice=tmp.price/stod(tp)*pbuy;
                curr="pound";
                break;
            }
            }
            cout<<"the total price is : "<<endl;
            cout<<pprice<<" "<<curr<<endl;
            cout<<"type yes to confirm your purchase,type any thing to go back"<<endl;
            string yes;
            cin>>yes;
            if(yes=="yes")
            {
                cout<<"item bought"<<endl;
                f.finsert(name,pname,pbuy,pprice,curr);
                p.pstockedit(pname,-(pbuy));
                break;
            }
            else
                break;
        }
        case 4 :
        {
            return;
        }
        }
    }
}
void sdshbrd(string adname)
{
    users s;
    factors f;
    products p;
    while(1)
    {
        line;
        cout<<"admin : "<<adname<<"s dashboard"<<endl<<endl;
        line;
        cout<<".1 : to see all purchases"<<endl;
        cout<<".2 : to see a users purchases"<<endl;
        cout<<".3 : to see all users list"<<endl;
        cout<<".4 : to ban a users account"<<endl;
        cout<<".5 : to add a new product to the shop"<<endl;
        cout<<".6 : to edit a products name"<<endl;
        cout<<".7 : to edit a products price"<<endl;
        cout<<".8 : to add to a products stock"<<endl;
        cout<<".9 : to manualy update currency price"<<endl;
        cout<<".10 : to delete a product"<<endl;
        cout<<".11 : to see all products"<<endl;
        cout<<".12 : to log out "<<endl;
        line;
        int cs;
        cin>>cs;
        switch(cs)
        {
        case 1:
        {
            f.fprint();
            line;
            break;
        }
        case 2 :
        {
            cout<<"enter the username : "<<endl;
            string uname;
            cin>>uname;
            cout<<uname<<"s previos purchases : "<<endl;
            f.fuserprint(uname);
            line;
            break;

        }
        case 3 :
        {
            s.uprint();
            line;
            break;
        }
        case 4 :
        {
            cout<<"enter the username : "<<endl;
            string uname;
            cin>>uname;
            s.udel(uname);
            cout<<uname<<"has been banned"<<endl;
            line;
            break;
        }
        case 5 :
        {  string pname;
            double price;
            int stock;
            cout<<"enter the name of the product : "<<endl;
            cin>>pname;
            cout<<"enter the number of items available : "<<endl;
            cin>>stock;
            cout<<"enter the price of the product : "<<endl;
            cin>>price;
            p.pinsert(pname,stock,price);
            cout<<"product added"<<endl;
            line;
            break;
        }
        case 6 :
        {cout<<"enter products current name : "<<endl;
            string oldname;
            cin>>oldname;
            cout<<"enter products new name : "<<endl;
            string newname;
            cin>>newname;
            p.pnameedit(oldname,newname);
            cout<<"product data edited"<<endl;
            line;
            break;
        }
        case 7 :
        {
            cout<<"enter products name : "<<endl;
            string pname;
            cin>>pname;
            cout<<"enter products new price in toman : "<<endl;
            double price;
            cin>>price;
            p.ppriceedit(pname,price);
            cout<<"product data edited"<<endl;
            line;
            break;
        }
        case 8 :
        {cout<<"enter products name : "<<endl;
            string name;
            cin>>name;
            cout<<"enter how much do you want to add to stock(negative to reduce) : "<<endl;
            int addstock;
            cin>>addstock;
            p.pstockedit(name,addstock);
            cout<<"product data edited"<<endl;
            line;
            break;
        }
        case 9 :
        { fstream cnew;
            cnew.open("../proje/files/currency1.txt",ios::out);
            double dollar;
            double euro;
            double pound;
            cout<<"enter the new price of dollar in toman : "<<endl;
            cin>>dollar;
            cout<<"enter the new price of euro in toman : "<<endl;
            cin>>euro;
            cout<<"enter the new price of pound in toman : "<<endl;
            cin>>pound;
            cnew<<dollar<<endl;
            cnew<<euro<<endl;
            cnew<<pound<<endl;
            cnew.close();
            remove("../proje/files/currency.txt");
            rename("../proje/files/currency1.txt","../proje/files/currency.txt");
            cout<<"currency price updated"<<endl;
            line;
            break;

        }
        case 10 :
        {
            cout<<"enter products name : "<<endl;
            string pname;
            cin>>pname;
            if(!p.pcheck(pname))
            {
                cout<<"product not found"<<endl;
                break;
            }
            p.pdel(pname);
            cout<<"product deleted"<<endl;
            line;
            break;
        }
        case 11 :
        {
            p.pprint();
            break;
        }
        case 12 :
        {
            return;
        }
        }

    }
}
void udshbrd(string name)
{   users s;
    factors f;
    while(1)
    {
        line;
        cout<<name<<"s dashboard"<<endl<<endl;
        line;
        cout<<".1 : to see your previous purchases"<<endl;
        cout<<".2 : to open the products menu"<<endl;
        cout<<".3 : to change your username"<<endl;
        cout<<".4 : to change your password"<<endl;
        cout<<".5 : to log out"<<endl;
        cout<<".6 : to delete your account"<<endl;
        line;
        int cs;
        cin>>cs;
        switch(cs)
        {
        case 1:
        {
            cout<<"your previos purchases : "<<endl;
            factors f;
            f.fuserprint(name);
            break;

        }
        case 2:
        {
            buy(name);
            break;
        }
        case 3:
        {
            string newname;
            cout<<"enter your new username"<<endl;
            cin>>newname;
            s.unameedit(name,newname);
            f.fusernc(name,newname);
            name=newname;
            break;

        }
        case 4:
        {
            while(1)
            {
                users s;
                string trypassword;
                string newpassword;
                cout<<"enter your current password"<<endl;
                cin>>trypassword;
                cout<<"enter your new password"<<endl;
                cin>>newpassword;
                if( s.upassedit(name,trypassword,newpassword))
                    break;
            }
            break;
        }
        case 5:
        {
            return;
        }
        case 6:
        {
            while(1)
            {
                string pass;
                cout<<"enter your current password"<<endl;
                cin>>pass;
                if(s.ulogin(name,pass))
                {
                    string tmp;
                    cout<<"type yes to confirm"<<endl;
                    cin>>tmp;
                    if(tmp=="yes")
                    {
                        s.udel(name);
                        cout<<"your account is deleted,please login or sign up with a new account "<<endl;
                        line;
                        return;
                    }
                    else{
                        cout<<"canceled deleting account"<<endl;
                        line;
                        break;
                    }
                }
            }
        }
        }
    }
}
void login()
{
    cout<<"---------------login--------------"<<endl;
    cout<<".enter 1 to login"<<endl;
    cout<<".enter 2 to sign up"<<endl;
    int cs;
    cin>>cs;
    switch(cs)
    {
    case 1:
    {
        while(1)
        {   int check=1;
            users userinf ;
            string name;
            string password;
            cout<<"enter user name :"<<endl;
            cin>>name;
            if(!userinf.ufind(name))
            {
                cout<<"username not found"<<endl;
                cout<<"enter 0 to go back, 1 to try again"<<endl;
                cin>>check;
                if(check)
                    continue;
                else
                    break;
            }
            if(!check)
                break;
            cout<<"enter password :"<<endl;
            cin>>password;
            if(userinf.ulogin(name,password))
            {udshbrd(name);
                break;
            }
            cout<<"incorrect password or username"<<endl;
        }
        break;
    }
    case 2:
    {

        while(1)
        {
            users userinf ;
            string name;
            string password;
            cout<<"enter user name :"<<endl;
            cin>>name;
            if(userinf.ufind(name))
            {
                cout<<"this username already exists"<<endl;
                continue;
            }
            cout<<"enter password :"<<endl;
            cin>>password;
            userinf.uinsert(name,password);
            cout<<"accout added,now you can log in"<<endl;
            line;
            break;
        }
        while(1)
        {
            users userinf ;
            string name;
            string password;
            cout<<"enter user name :"<<endl;
            cin>>name;
            if(!userinf.ufind(name))
            {
                cout<<"username not found"<<endl;
                continue;
            }
            cout<<"enter password :"<<endl;
            cin>>password;
            if(userinf.ulogin(name,password))
            {udshbrd(name);
                break;
            }

        }
        break;
    }
    case 3:
    {   bool q=1;
        while(q){
            cout<<"enter admin name"<<endl;
            string adname;
            cin>>adname;
            cout<<"enter your password"<<endl;
            string adpassword;
            cin>>adpassword;
            fstream ad("../proje/files/admin.txt");
            string tmp;
            while(getline(ad,tmp))
            {
                if(tmp==adname)
                {   getline(ad,tmp);
                    if(tmp==adpassword)
                    { q=0;
                        sdshbrd(adname);
                        break;

                    }

                }
            }
            if(!q)
                break;
            cout<<"wrong password or username.type 0 to go back. 1 to try again"<<endl;
            int ck;
            cin>>ck;
            if(ck)
                continue;
            else
                break;
        }
    }
    }
}
int main()
{

    while(1){
        login();
    }

}
