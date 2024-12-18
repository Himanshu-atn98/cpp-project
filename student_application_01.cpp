#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
#define true 1
#define false 0
#define TRUE 1
#define FALSE 0
class TMFileMode
{
public:
static short append;
static short out;
static short in;
static short binary;
};
short TMFileMode::append=1;
short TMFileMode::out=2;
short TMFileMode::in=4;
short TMFileMode::binary=8;

class TMOutputFileStream
{
private:
FILE *f;
int failed;
public:
TMOutputFileStream(const char *fileName)
{
this->failed=false;
this->f=NULL;
this->open(fileName,TMFileMode::out);
}
TMOutputFileStream(const char *fileName, short fileMode)
{
this->failed=false;
this->f=NULL;
this->open(fileName,fileMode);
}

void open(const char *fileName,short fileMode)
{
if(this->f!=NULL)
{
this->failed=true;
return;
}
if(fileMode==TMFileMode::out)
{
this->f=fopen(fileName,"w");
}
else
{
if(fileMode==TMFileMode::append)
{
this->f=fopen(fileName,"a");
}
else
{
if(fileMode==TMFileMode::binary)
{
this->f=fopen(fileName,"wb");
}
else
{
if(fileMode==TMFileMode::append|TMFileMode::binary)
{
this->f=fopen(fileName,"ab");
}
}
}
}
if(f!=NULL) this->failed=false; else this->failed=true;
}
int hasOperationFailed()
{
return this->failed;
}
void close()
{
if(this->f==NULL) this->failed=true;
else
{
fclose(f);
this->failed=false;
}
}
void operator<<(int x)
{
if(this->f==NULL)
{
this->failed=true;
return ;
}
char data[21];
sprintf(data,"%d",x);
fputs(data,this->f);
this->failed=false;
}
void operator<<(char x)
{
if(this->f==NULL)
{
this->failed=true;
return ;
}
fputc(x,this->f);
this->failed=false;
}
void operator<<(const char *x)
{
if(this->f==NULL)
{
this->failed=true;
return;
}
fputs(x,this->f);
this->failed=false;
}
void writeBytes(const char *baseAddress,int size)
{
if(this->f==NULL)
{
this->failed=true;
return ;
}
fwrite(baseAddress,size,1,f);
this->failed=false;
}
};

class TMInputFileStream
{
private:
FILE *f;
int failed;
public:
TMInputFileStream(const char *fileName)
{
this->failed=false;
this->f=NULL;
this->open(fileName,TMFileMode::in);
}
TMInputFileStream(const char *fileName,short fileMode)
{
this->failed=false;
this->f=NULL;
this->open(fileName,fileMode);
}
void open(const char *fileName,short fileMode)
{
if(this->f!=NULL)
{
this->failed=true;
return;
}
if(fileMode==TMFileMode::in)
{
this->f=fopen(fileName,"r");
}
else
{
if(fileMode==(TMFileMode::in|TMFileMode::binary))
{
this->f=fopen(fileName,"rb");
}
}
if(f!=NULL) this->failed=false; else this->failed=true;
}
int hasOperationFailed()
{
return this->failed;
}
void close()
{
if(this->f=NULL) this->failed=true;
else
{
fclose(f);
this->failed=false;
}
}

void operator>>(int &x)
{
if(this->f==NULL)
{
this->failed=true;
return ;
}
if(feof(this->f))
{
x=0;
this->failed=true;
return ;
}
char data[21];
char m;
int i=0;
while(1)
{
m=fgetc(this->f);
if(feof(this->f)) break;
if(m==' ') break;
data[i]=m;
i++;
}
if(i==0)
{
x=0;
this->failed=true;
return;
}
data[i]='\0';
x=atoi(data);
this->failed=false;
}
void operator>>(char &x)
{
if(this->f==NULL)
{
this->failed=true;
return;
}
if(feof(this->f))
{
x=0;
this->failed=false;
return;
}
x=fgetc(this->f);
if(x==EOF)
{
x=0;
this->failed=true;
return;
}
}
void operator>>(char *x)
{
if(this->f==NULL)
{
this->failed=true;
return;
}
if(feof(this->f))
{
*x='\0';
this->failed=true;
return;
}

int i=0;
char m;
while(1)
{
m=fgetc(this->f);
if(feof(this->f)) break;
if(m=='\n') break;
*x=m;
x++;
i++;
}
*x='\0';
if(i==0)
{
this->failed=true;
return;
}
this->failed=false;

}
void readBytes(char *baseAddress,int size)
{
if(this->f=NULL)
{
this->failed=true;
return;
}
if(feof(this->f))
{
for(int x=0;x<size;x++) *(baseAddress+x)=0;
this->failed=true;
return;
}
fread(baseAddress,size,1,f);
if(feof(this->f))
{
this->failed=true;
return;
}
this->failed=false;
}
};

//*********************TESTs CODE START******************
void test1()
{
TMOutputFileStream ofs1("file1.tt");
ofs1<<101;
ofs1<<' ';
ofs1<<"Cool Fool";
ofs1<<"\n";
ofs1<<'A';
ofs1<<"Whatever";
ofs1<<"\n";
ofs1.close();
}
void test2()
{
TMInputFileStream ifs1("file1.ttt");
int x;
ifs1>>x;
char n1[101];
ifs1>>n1;
char m;
ifs1>>m;
char n2[101];
ifs1>>n2;
ifs1.close();
cout<<x<<","<<n1<<","<<m<<","<<n2<<endl;
}

class Student
{
private:
char name[21];
int rollNumber;
public:
void askInformation()
{
cout<<"Enter your name:";
cin>>name;
cin.clear();
fflush(stdin);
cout<<"Enter your roll number:";
cin>>rollNumber;
cin.clear();
fflush(stdin);
}
void printInformation()
{
cout<<"Roll number:"<<rollNumber<<endl;
cout<<"Name:"<<name<<endl;
}
};
void test3()
{
TMInputFileStream ifs2("file2.ttt",TMFileMode::in|TMFileMode::binary);
if(ifs2.hasOperationFailed())
{
cout<<"No students"<<endl;
return ;
}
ifs2.close();
}


void test4()
{
char m;
Student student;
while(1)
{
student.askInformation();
TMOutputFileStream ofs2("file2.ttt",TMFileMode::append|TMFileMode::binary);
ofs2.writeBytes((char *)&student,sizeof(Student));
ofs2.close();
cout<<"Student added."<<endl;
cout<<"Add more (Y/N):";
cin>>m;
cin.clear();
fflush(stdin);
if(m!='y' && m!='Y') break;
}
}

void test5()
{
TMInputFileStream ifs2("file2.ttt",TMFileMode::in|TMFileMode::binary);
if(ifs2.hasOperationFailed())
{
cout<<"No students"<<endl;
return;
}
Student student;
while(1)
{
ifs2.readBytes((char *)&student,sizeof(Student));
if(ifs2.hasOperationFailed()) break;
student.printInformation();
}
ifs2.close();
}


 
int main()
{
test1();
cout<<"Test 1 completed"<<endl;
test2();
cout<<"Test 2 completed"<<endl;
test3();
cout<<"Test 3 completed"<<endl;
test4();
cout<<"Test 4 completed"<<endl;
test5();
cout<<"Test 5 completed"<<endl;
return 0;
}
