#include<iostream>
#include<iomanip>
using namespace std;


class account
{
   int acno;
   char name[50];
   int deposit;
   char type;


public:
   void create_account();
   void show_account() const;
   void modify();
   void dep(int);
   void draw(int);
   void report() const;
   int retacno() const;
   int retdeposit() const;
   char rettype() const;
};


account *accounts = nullptr; // Dynamic array to store accounts
int numAccounts = 0;


void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);
void intro();
void account::create_account()
{
   cout<<"\nEnter The account No. :";
   cin>>acno;
   cout<<"\n\nEnter The Name of The account Holder : ";
   cin.ignore();
   cin.getline(name,50);
   cout<<"\nEnter Type of The account (C/S) : ";
   cin>>type;
   type=toupper(type);
   cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
   cin>>deposit;
   cout<<"\n\n\nAccount Created..";
}


void account::show_account() const
{
   cout<<"\nAccount No. : "<<acno;
   cout<<"\nAccount Holder Name : ";
   cout<<name;
   cout<<"\nType of Account : "<<type;
   cout<<"\nBalance amount : "<<deposit;
}




void account::modify()
{
   cout<<"\nAccount No. : "<<acno;
   cout<<"\nModify Account Holder Name : ";
   cin.ignore();
   cin.getline(name,50);
   cout<<"\nModify Type of Account : ";
   cin>>type;
   type=toupper(type);
   cout<<"\nModify Balance amount : ";
   cin>>deposit;
}


  
void account::dep(int x)
{
   deposit+=x;
}
  
void account::draw(int x)
{
   deposit-=x;
}
  
void account::report() const
{
   cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}


  
int account::retacno() const
{
   return acno;
}


int account::retdeposit() const
{
   return deposit;
}


char account::rettype() const
{
   return type;
}


int main()
{
   char ch;
   int num;


   cout<<"\n\n Welcome to BANK  MANAGEMENT SYSTEM\n\n";
   cout<<"Press ENTER to start!\n";
   //cin.get();
   do
   {
       cout << "\n\n\n\tMAIN MENU";
       cout << "\n\n\t01. NEW ACCOUNT";
       cout << "\n\n\t02. DEPOSIT AMOUNT";
       cout << "\n\n\t03. WITHDRAW AMOUNT";
       cout << "\n\n\t04. BALANCE ENQUIRY";
       cout << "\n\n\t05. ALL ACCOUNT HOLDER LIST";
       cout << "\n\n\t06. CLOSE AN ACCOUNT";
       cout << "\n\n\t07. MODIFY AN ACCOUNT";
       cout << "\n\n\t08. EXIT";
       cout << "\n\n\tSelect Your Option (1-8) ";
       cin >> ch;


       switch (ch)
       {
       case '1':
           write_account();
           break;
       case '2':
           cout << "\n\n\tEnter The account No. : ";
           cin >> num;
           deposit_withdraw(num, 1);
           break;
       case '3':
           cout << "\n\n\tEnter The account No. : ";
           cin >> num;
           deposit_withdraw(num, 2);
           break;
       case '4':
           cout << "\n\n\tEnter The account No. : ";
           cin >> num;
           display_sp(num);
           break;
       case '5':
           display_all();
           break;
       case '6':
           cout << "\n\n\tEnter The account No. : ";
           cin >> num;
           delete_account(num);
           break;
       case '7':
           cout << "\n\n\tEnter The account No. : ";
           cin >> num;
           modify_account(num);
           break;
       case '8':
           cout << "\n\n\tThanks for using bank management system";
           break;
       default:
           cout << "\a";
       }


       cin.ignore();
       cin.get();
   } while (ch != '8');


   // Clean up dynamic memory before exiting
   delete[] accounts;


   return 0;
}


// Implementation of account class remains the same


void write_account()
{
   account ac;
   ac.create_account();


   // Allocate memory for new account
   account *temp = new account[numAccounts + 1];


   // Copy existing accounts to the new memory block
   for (int i = 0; i < numAccounts; ++i)
   {
       temp[i] = accounts[i];
   }


   // Add the new account to the end
   temp[numAccounts] = ac;


   // Increment the number of accounts
   ++numAccounts;


   // Release the old memory block and update the pointer
   delete[] accounts;
   accounts = temp;
}


void display_sp(int n)
{
   bool found = false;
   for (int i = 0; i < numAccounts; ++i)
   {
       if (accounts[i].retacno() == n)
       {
           accounts[i].show_account();
           found = true;
           break;
       }
   }
   if (!found)
       cout << "\n\nAccount number does not exist";
}


void modify_account(int n)
{
   bool found = false;
   for (int i = 0; i < numAccounts; ++i)
   {
       if (accounts[i].retacno() == n)
       {
           accounts[i].show_account();
           cout << "\n\nEnter The New Details of account" << endl;
           accounts[i].modify();
           cout << "\n\n\t Record Updated";
           found = true;
           break;
       }
   }
   if (!found)
       cout << "\n\n Record Not Found ";
}


void delete_account(int n)
{
   bool found = false;
   for (int i = 0; i < numAccounts; ++i)
   {
       if (accounts[i].retacno() == n)
       {
           // Create a new array to hold accounts excluding the one to be deleted
           account *temp = new account[numAccounts - 1];
          
           // Copy accounts before the deleted one
           for (int j = 0; j < i; ++j)
               temp[j] = accounts[j];


           // Copy accounts after the deleted one
           for (int j = i + 1; j < numAccounts; ++j)
               temp[j - 1] = accounts[j];


           // Decrement the number of accounts
           --numAccounts;


           // Release the old memory block and update the pointer
           delete[] accounts;
           accounts = temp;


           cout << "\n\n\tRecord Deleted ..";
           found = true;
           break;
       }
   }
   if (!found)
       cout << "\n\n Record Not Found ";
}


void display_all()
{
   cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
   cout << "====================================================\n";
   cout << "A/c no.      NAME           Type  Balance\n";
   cout << "====================================================\n";
   for (int i = 0; i < numAccounts; ++i)
   {
       accounts[i].report();
   }
}


void deposit_withdraw(int n, int option)
{
   int amt;
   bool found = false;
   for (int i = 0; i < numAccounts; ++i)
   {
       if (accounts[i].retacno() == n)
       {
           accounts[i].show_account();
           if (option == 1)
           {
               cout << "\n\n\tTO DEPOSIT AMOUNT ";
               cout << "\n\nEnter The amount to be deposited";
               cin >> amt;
               accounts[i].dep(amt);
           }
           if (option == 2)
           {
               cout << "\n\n\tTO WITHDRAW AMOUNT ";
               cout << "\n\nEnter The amount to be withdrawn";
               cin >> amt;
               int bal = accounts[i].retdeposit() - amt;
               if ((bal < 500 && accounts[i].rettype() == 'S') || (bal < 1000 && accounts[i].rettype() == 'C'))
                   cout << "Insufficient balance";
               else
                   accounts[i].draw(amt);
           }
           cout << "\n\n\t Record Updated";
           found = true;
           break;
       }
   }
   if (!found)
       cout << "\n\n Record Not Found ";
}
