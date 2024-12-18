#include<iostream>
#include<string.h>
#include<stdio.h>
#include<fstream>
using namespace std;
class Employee
{
private:
int id;
char name[21];
int age;
public:
Employee()
{
int id=0;
int age=0;
name[0]='\0';
}
Employee(const Employee &other)
{
this->id=id;
strcpy(this->name,other.name);
this->age=age;
}
Employee & operator=(Employee other)
{
this->id=other.id;
strcpy(this->name,other.name);
this->age=other.age;
return *this;
}
void setId(int id)
{
this->id=id;
}
int getId()
{
return id;
}
void setName(const char *name)
{
strcpy(this->name,name);
}
void getName(char *name)
{
strcpy(name,this->name);
}
void setAge(int age)
{
this->age=age;
}
int getAge()
{
return this->age;
}
int operator==(Employee &other)
{
return this->id=other.id;
}
int operator<(Employee &other)
{
return strcmp(this->name,other.name)<0;
}
int operator>(Employee &other)
{
return strcmp(this->name,other.name)>0;
}
int operator<=(Employee &other)
{
return strcmp(this->name,other.name)<=0;
}
int operator>=(Employee &other)
{
return strcmp(this->name,other.name)>=0;
}
int operator!=(Employee &other)
{
return strcmp(this->name,other.name)!=0;
}
};


void addEmployee()
{
int id;
cout<<"Enter employee id:";
cin>>id;
cin.clear();
fflush(stdin);
if(id<=0)
{
cout<<"Invalid Id."<<endl;
return ;
}
ifstream fin;
fin.open("employees.data");
if(!fin.fail())
{
Employee employee;
while(1)
{
fin.read((char *)&employee, sizeof(employee));
if(fin.fail()) break;
if(id==employee.getId())
{
fin.close();
char name[21];
employee.getName(name);
cout<<"That id is alloted to "<<name<<endl;
return ;
}
}
fin.close();
}
 char name[21];
 int age;
cout<<"Enter name:";
cin.getline(name,21);
cin.clear();
fflush(stdin);
cout<<"Enter age:";
cin>>age;
cin.clear();
fflush(stdin);
char m;
cout<<"Save (Y/N):";
cin>>m;
cin.clear();
fflush(stdin);
if(m!='y' && m!='Y')
{
cout<<"Employee not added"<<endl;
return ;
}
Employee employee;
employee.setId(id);
employee.setName(name);
employee.setAge(age);
ofstream file("employees.data",ios::app| ios::binary);
file.write((char*)&employee,sizeof(Employee));
file.close();
cout<<"Employee added."<<endl;
}

void displayListOfEmployees()
{
ifstream file;
file.open("employees.data",ios::binary);
if(file.fail())
{
cout<<"No records"<<endl;
return;
}
Employee employee;
int id,age;
char name[21];
while(1)
{
file.read((char*)&employee,sizeof(employee));
if(file.fail()) break;
id=employee.getId();
age=employee.getAge();
employee.getName(name);
cout<<"Employee Id:"<<id<<endl;
cout<<"Name:"<<name<<endl;
cout<<"Age:"<<age<<endl;
}
file.close();
}
int main()
{
int ch;
while(1)
{
cout<<"1.Add employee"<<endl;
cout<<"2.Display list of employees"<<endl;
cout<<"3.Exit"<<endl;
cout<<"Enter your choice:";
cin>>ch;
cin.clear();
fflush(stdin);
if(ch<=0||ch>3)
{
cout<<"Please select correct option!"<<endl;
continue;
}
else
{
if(ch==1) addEmployee();
if(ch==2) displayListOfEmployees();
if(ch==3) break;
}
}
return 0;
}