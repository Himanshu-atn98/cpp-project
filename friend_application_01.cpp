#include<iostream>
#include<stdio.h>
#include<fstream>
using namespace std;
void addFriend()
{
char name[21];
int age;
char contactNumber[101];
cout<<"Enter name:";
cin.getline(name,21); // user might feed space.
cin.clear();
fflush(stdin);
cout<<"Enter age:";
cin>>age;
cin.clear();
fflush(stdin);
cout<<"Enter contact number:";
cin.getline(contactNumber,21);
cin.clear();
fflush(stdin);
ofstream k;
k.open("friends.frn",ios::app);
k<<name;
k<<"\n";
k<<age;
k<<" ";
k<<contactNumber;
k<<"\n";
k.close();
cout<<"Friend added"<<endl;
}
void displayListOfFriends()
{
char n[21];
char c[101];
int a;
ifstream g;
g.open("friends.frn");
if(g.fail())
{
cout<<"No contacts"<<endl;
return;
}
while(1)
{
g.getline(n,22);
if(g.fail()) break;
g>>a;
g.getline(c,102);
cout<<"Name:"<<n<<", Age:"<<a<<endl;
cout<<"Contact Number:"<<c<<endl;
}
g.close();
}
int main()
{
int ch;
while(1)
{
cout<<"1. Add friend"<<endl;
cout<<"2. Display list of friend"<<endl;
cout<<"3. Exit"<<endl;
cout<<"Enter your choice:";
cin>>ch;
cin.clear();
fflush(stdin);
if(ch==1) addFriend();
if(ch==2) displayListOfFriends();
if(ch==3) break;
}
return 0;
}