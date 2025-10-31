#include<iostream>
#include<fstream>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
using namespace std;
int i,n,j;
ifstream fin;
ofstream fout;
fstream fio;
void disp();

class stock
{
    char name[20], pass[10];
    float pr;
    int quant;

public:
    void get();
    void get2();
    void show();
    int stchk(char nm[30]);
    void withd(int qty);
    void refill(int qty);
}st;

void stock::withd(int qty)
{
    if(quant>=qty)
    {
        quant-=qty;
        cout<<"\n\n Stock updated.\n";
        cout<<"\n\n Total price to be paid: "<<pr*qty;
    }
    else
       {
           cout<<"\n\n Insufficient stock";
       }
    getch();
}

void stock::refill(int qty)
{
    quant+=qty;
    cout<<"\n\nStock updated.";
    getch();
}
int stock::stchk(char nm[30])
    {
        if(strcmp(nm,name)==0)
            return 0;
        else
            return 1;
    }
void stock::get()
{
    cin>>name>>pr>>quant;
}
void stock::get2()
{
    cin>>name>>quant;
}
void stock::show()
{
    cout<<"\n"<<name<<"\t\t\t"<<quant<<"\t\t\t"<<pr;
}
void addnew()
{
    system("cls");
    disp();
    getch();
    system("cls");
    cout<<"\n Enter the No. of Products that you wish to add:";
    cin>>n;
    if(n!=0)
    {
        fout.open("shop.dat",ios::binary|ios::app);
        for(i=0;i<n;i++)
        {
            cout<<"\n\n Input the name,price and the quantity of item respectively\n\n";
            st.get();
            fout.write((char*)&st,sizeof(st));
            cin.get();
        }
        cout<<"\n\n Stock Updated!!";
        fout.close();
        cin.get();
        system("cls");
        disp();
    }
    else
    {
        fout.close();
        cin.get();
        system("cls");
        cout<<"\n\n No items to be added";
    }
}
void withdraw()
{
    system("cls");
    char temp[100];
    int qty;
    int i=0;
    long pos=0;
    disp();
    cout<<"\n\n Enter the product's name \n"<<endl;
    cin>>temp;
    cout<<"\n\n Enter quantity: \n"<<endl;
    cin>>qty;
    fio.open("shop.dat",ios::binary|ios::out|ios::in);
    while(fio)
    {
        pos=fio.tellg();
        fio.read((char*)&st,sizeof(st));
        if(st.stchk(temp)==0)
        {
            st.withd(qty);
            fio.seekp(pos);
            fio.write((char*)&st,sizeof(st));
            i++;
            break;
        }
    }
    if(i!=1)
      {
            cout<<"\n\n!!Record not found!!";
            fio.close();
            cin.get();
            system("cls");
            disp();
            getch();
      }
}
void disp()
{
    int i=1;
    cout<<"\n=====================================================================================================";
    cout<<"\n\n========================================\t THE STOCK ITEMS ARE\t=============================";
    cout<<"\n\n=====================================================================================================\n";
    cout<<"\n\n PARTICULARS \t STOCK AVAILABLE\t\t\t PRICE";
    cout<<"\n\n=====================================================================================================\n";
    fin.open("shop.dat",ios::binary);
    while(!fin.eof())
    {
        fin.read((char*)&st,sizeof(st));
        if(!fin.eof())
        {
            if(fin.tellg()<0)
            {
                i=0;
                break;

            }
            st.show();
        }
    }
    if(i==0)
    {
        cout<<"\n\n\t\t!!Empty record room!!";
        getch();
    }
    fin.close();

}
void refill()
{
    system("cls");
    char temp[100];int qty;
    int i=0;
    long pos=0;
    disp();
    cout<<"\n\n Enter the products name \n"<<endl;
    cin>>temp;
    cout<<"\n\n Enter quantity: \n"<<endl;
    cin>>qty;
    fio.open("shop.dat",ios::binary|ios::out|ios::in);
    while(fio)
    {
        pos=fio.tellg();
        fio.read((char*)&st,sizeof(st));
        if(st.stchk(temp)==0)
        {
            st.refill(qty);
            fio.seekp(pos);
            fio.write((char*)&st,sizeof(st));
            i++;
            break;
        }
    }
    if(i!=1)
       {
            cout<<"\n\n!Record not found !!";
            fio.close();
            system("cls");
            cin.get();
            disp();
        cin.get();
       }
}
void deleteRecord()
{
    system("cls");
    int i=0;
    char temp[30];
    cout<<"\n\t\t\t\t Delete Record";
    cout<<"\n\n Enter the name of the product: ";
    cin>>temp;
    fin.open("shop.dat",ios::binary);
    fout.open("temp.dat",ios::binary);
    while(!fin.eof())
    {
        fin.read((char*)&st,sizeof(st));
        if(!fin.eof())
            if(st.stchk(temp)==0)
        {
            st.show();
            cout<<"\n\n\n\t\t Record deleted";
            i++;

        }
        else
           {
             fout.write((char*)&st,sizeof(st));
           }
    }
    if(i==0)
        cout<<"\n\n!!Record not found!!";
    fin.close();
    fout.close();
    remove("shop.dat");
    rename("temp.dat","shop.dat");
}

int main()
{
    char pass[10],pass2[10];
    int i,j;
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t|============================= WELCOME TO STORE MANAGEMENT ==============================|";
    getch();
    system("cls");
    cout<<"\n\t\t STORE MANAGEMENT SYSTEM\n";
    cout<<"======================================================================";
    cout<<"\n\t\t 1. Dealer Menu\n\n\t\t 2. Customer Menu\n\n\t\t 3. Employee Menu";
    cout<<"\n======================================================================";
    cout<<"\n\n Enter your Choice: ";
    cin>>j;
    if(j==1)
    {
        system("cls");

        system("cls");
        cout<<"\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tEnter the password letter by letter:";

        for(int z=0;z<6;z++)
        {
            pass[z]=getch();
            system("cls");
            cout<<"\n\n\n\n\n\n\n\t\t\t\t\t Enter the password letter by letter:";
            for(i=1;i<=(z+1);i++)
            {
                cout<<"*";
            }
        }
        if(strcmp(pass,"123456")==1)
        {
            system("cls");
            dealermenu:
            cout<<"\n=====================================================================================================";
            cout<<"\n\n\t\t\t DEALER MENU\n 1. Add new product\n 2. Display stock\n 3. Refill\n 4. Remove an item\n 5. Exit:";
            cout<<"\n\n\n======================================== END OF MENU ===============================================";
            cout<<"\n\n Enter your Choice: \t";
            cin>>i;
            if(i==1)
            {
                addnew();
                getch();
                goto dealermenu;
            }
            else
                if(i==2)
            {
                system("cls");
                disp();
                getch();
                goto
                dealermenu;
            }
            else
                if(i==3)
            {
                refill();
                goto
                dealermenu;

            }
            else
                if(i==4)
            {
                deleteRecord();
                getch();
                goto
                dealermenu;
            }
            else
            {
                system("cls");
                getch();
                exit(0);

            }
        }
        else
        {
            cout<<"\n\n\n Authorized Personnel Only\n\n";
            getch();
            getch();
            getch();
            getch();
            getch();
            getch();
            exit(0);
        }
    }
    if(j==2)
    {
        custmenu:
            system("cls");
            cout<<"====================================================================================";
            cout<<"\n\n\t\t\t CUSTOMER MENU\n 1. Purchase\n 2. Display stock\n 3. Exit:";
            cout<<"\n\n\n=============================== END OF MENU ========================================";
            cout<<"\n\n Enter your Choice :\t";
            cin>>i;

            if(i==1)
            {
                withdraw();
                getch();
                goto
                custmenu;
            }
            else
                if(i==2)
            {
                system("cls");
                disp();
                getch();
                goto
                custmenu;
            }
            else
            {
                system("cls");
                getch();
                exit(0);

            }
    }
    if(j==3)
    {
        system("cls");
        cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t Enter the password letter by letter: ";

        for(int z=0;z<3;z++)
        {
            pass2[z]=getch();
            system("cls");
            cout<<"\n\n\n\n\n\t\t\t\t Enter the password letter by letter: ";
            for(i=1;i<=(z+1);i++)
            {
                cout<<"*";

            }
        }
        if(strcmp(pass2,"123")==1)
           {
               empmenu:
                   system("cls");
                   cout<<"=====================================================================";
                   cout<<"\n\n\t\t\t EMPLOYEE MENU\n 1. Display stock\n 2. Refill\n 3. Exit: ";
                   cout<<"\n\n\n========================== END OF MENU ===============================";
                   cout<<"\n\n enter your Choice: \t";
                   cin>>i;
                   if(i==1)

                    {
                        system("cls");
                        disp();
                        getch();
                        goto empmenu;

                    }
                    else
                        if(i==2)
                    {
                        refill();
                        goto empmenu;

                    }
                    else
                    {
                        system("cls");
                        cout<<"\n\n\n\t\t\t THANK YOU!! SHOPPING FROM US!!";
                        getch();
                        exit(0);

                    }
           }
           else
           {
               cout<<"\n\n Sorry!! Access Denied..'n'n";
               getch();
               getch();
               exit(0);
           }
    }
    getch();
}
