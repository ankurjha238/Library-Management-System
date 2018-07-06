//#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
//#include<iomanip.h>

using namespace std;

class book
{
	char bookname[50];
	char bno[6];
	char authname[20];
	public:
	void createbook()
	{
		cout<<"New book entry \n\n";
		cout<<"Enter book number ";
		cin>>bno;
		cout<<endl<<"Enter book name ";
		gets(bookname);
		cout<<"Enter author name ";
		gets(authname);
		cout<<"Book created \n";
	}
	void showbook()
	{
		cout<<"Book number "<<bno<<endl;
		cout<<"Book name "<<bookname<<endl;
		cout<<"Author name "<<authname<<endl;
	}
	void modifybook()
	{
		cout<<"Book number is  "<<bno;
		cout<<"Book name ";
		gets(bookname);
		cout<<"Author name  ";
		gets(authname);
	}
	char* retbno()
	{	return bno;	}
	void report()
	{
		cout<<bno<<setw(20)<<bookname<<setw(20);
		cout<<authname<<endl;
	}
};

class student
{
	char admno[6];
	char name[20];
	char stbno[6];
	int token;
	public:
	void createstudent()
	{
		clrscr();
		cout<<"New student entry \n\n";
		cout<<"Enter admission no  ";
		cin>>admno;
		cout<<endl<<"Enter name  ";
		gets(name);
		token = 0;
		stbno[0] = '/0';
	}
	void showstudent()
	{
		cout<<"Student's admission no is  "<<admno<<endl;
		cout<<"Student's name  ";
		puts(name);
		cout<<"No. of books issued "<<token;
		if (token==1)
			cout<<endl<<"Book no  "<<stbno;
	}
	void modifystudent()
	{
		cout<<"Admission no  "<<admno<<endl;
		cout<<"Enter name  ";
		gets(name);
	}
	char* retadmno()
	{	return admno;	}
	char* retstbno()
	{	return stbno;	}
	int retoken()
	{	return token;	}
	void addtoken()
	{	token=1;	}
	void resetoken()
	{	token=0;	}
	void getstbno(char t[])
	{	strcpy(stbno,t);	}
    void report()
	{
		cout<<admno<<setw(20);
		cout<<name<<setw(13)<<token<<endl;
	}
};

fstream f,f1;
book b;
student s;

void writebook()
{
	char ch;
	f.open("book.dat",ios::out|ios::app);
	do
	{
		clrscr();
		b.createbook();
		f.write((char*)&b, sizeof(book));
		cout<<"Add more book ";
		cin>>ch;
	}while (ch == 'Y' || ch == 'y');
	f.close();
}

void writestudent()
{
	char ch;
	f.open("student.dat",ios::out|ios::app);
	do
	{
		clrscr();
		s.createstudent();
		f.write((char*)&s, sizeof(student));
		cout<<"Add more student ";
		cin>>ch;
	}while (ch == 'Y' || ch == 'y');
	f.close();
}

void displayspb(char n[])
{
	cout<<"Book details \n";
	int flag=0;
	f.open("book.dat",ios::in);
	while(f.read((char*)&b, sizeof(b)))
		if(strcmp(b.retbno(),n)==0)
		{
			b.showbook();
			flag=1;
		}
	f.close();
	if (flag==0)
		cout<<"Book does not exist \n";
	getch();
}

void displaysps(char n[])
{
	cout<<"Student details \n\n";
	int flag=0;
	f.open("student.dat",ios::in);
	while(f.read((char*)&s, sizeof(s)))
		if(strcmp(s.retadmno(),n)==0)
		{
			s.showstudent();
			flag=1;
		}
	f.close();
	if (flag==0)
		cout<<"Student does not exist \n";
	getch();
}

void modifybook()
{
	char n[6];
	int found=0;
	clrscr();
	cout<<"Modify book \n";
	cout<<"Enter book no  ";
	gets(n);
	f.open("book.dat",ios::in|ios::out);
	while(f.read((char*)&b, sizeof(b)) && found==0)
	{
		if(strcmp(b.retbno(),n)==0)
		{
			b.showbook();
			cout<<"Enter new details \n";
			b.modifybook();
			int pos = -1*sizeof(b);
			f.seekp(pos,ios::cur);
			f.write((char*)&b, sizeof(b));
			found=1;
		}
	}
	f.close();
	if (found==0)
		cout<<"Book not found";
	getch();
}

void modifystudent()
{
	char n[6];
	int found=0;
	clrscr();
	cout<<"Modify student \n\n";
	cout<<"Enter admission no  ";
	gets(n);
	f.open("student.dat",ios::in|ios::out);
	while(f.read((char*)&s, sizeof(s)) && found==0)
	{
		if(strcmp(s.retadmno(),n)==0)
		{
			s.showstudent();
			cout<<"\n Enter new details \n";
			s.modifystudent();
			int pos = -1*sizeof(s);
			f.seekp(pos,ios::cur);
			f.write((char*)&s, sizeof(s));
			found=1;
		}
	}
	f.close();
	if (found==0)
		cout<<"Student not found";
	getch();
}

void deletebook()
{
	char n[6];
	clrscr();
	cout<<"Delete book \n";
	cout<<"enter book no  ";
	cin>>n;
	f.open("book.dat",ios::in|ios::out);
	fstream f2;
	f2.open("temp.dat",ios::in|ios::out);
	f.seekg(0,ios::beg);
	while(f.read((char*)&b, sizeof(b)))
		if(strcmp(b.retbno(),n)!=0)
			f2.write((char*)&b, sizeof(b));
	f2.close();
	f.close();
	remove("book.dat");
	rename("temp.dat","book.dat");
	getch();
}

void deletestudent()
{
	char n[6];
	clrscr();
	cout<<"Delete student \n";
	cout<<"enter admission no  ";
	cin>>n;
	f.open("student.dat",ios::in|ios::out);
	fstream f2;
	f2.open("temp.dat",ios::in|ios::out);
	f.seekg(0,ios::beg);
	while(f.read((char*)&s, sizeof(s)))
		if(strcmp(s.retadmno(),n)!=0)
			f2.write((char*)&s, sizeof(s));
	f2.close();
	f.close();
	remove("student.dat");
	rename("temp.dat","student.dat");
	getch();
}

void displayalls()
{
	clrscr();
	f.open("student.dat",ios::in|ios::out);
	cout<<"Student list \n";
	cout<<"=============================================== \n";
	cout<<"Admn no."<<setw(10)<<"Name"<<setw(20)<<"Book \n";
	cout<<"=============================================== \n";
	while(f.read((char*)&s, sizeof(s)))
		s.report();
	f.close();
	getch();
}

void displayallb()
{
	clrscr();
	f.open("book.dat",ios::in|ios::out);
	cout<<"Books list \n";
	cout<<"=============================================== \n";
	cout<<"Book no."<<setw(10)<<"Name"<<setw(20)<<"Author \n";
	cout<<"=============================================== \n";
	while(f.read((char*)&b, sizeof(b)))
		b.report();
	f.close();
	getch();
}

void bookissue()
{
	char sn[6], bn[6];
	int found=0;
	int flag=0;
	clrscr();
	cout<<"Book issue \n\n";
	cout<<"Enter admission no  ";
	cin>>sn;
	f.open("student.dat",ios::in|ios::out);
	f1.open("book.dat",ios::in|ios::out);
	while(f.read((char*)&s, sizeof(s)) && found==0)
	{
		if(strcmp(s.retadmno(),sn)==0)
		{
			found=1;
			if(s.retoken()==0)
			{
				cout<<"Enter book no  ";
				cin>>bn;
		while(f1.read((char*)&b, sizeof(b)) && flag==0)
		{
			if(strcmp(b.retbno(),bn)==0)
			{
				b.showbook();
				flag=1;
				s.addtoken();
				s.getstbno(b.retbno());
				int pos= -1*sizeof(s);
				f.seekp(pos,ios::cur);
				f.write((char*)&s,sizeof(s));
				cout<<"Book issued for 7 days \n";
			}
		}
		if (flag==0)
			cout<<"Book does not exist \n";
	}
		else
			cout<<"You have not returned the book";
		}
	}
	if(found==0)
		cout<<"Student does not exist \n";
	getch();
	f.close();
	f1.close();
}

void deposit()
{
	char sn[6],bn[6];
	int found=0;
	int day,fine,flag=0;
	clrscr();
	cout<<"Book deposit \n";
	cout<<"Enter admission no  ";
	cin>>sn;
	f.open("student.dat",ios::in|ios::out);
	f1.open("book.dat",ios::in|ios::out);
	while(f.read((char*)&s, sizeof(s)) && found==0)
	{
		if(strcmp(s.retadmno(),sn)==0)
		{
			found=1;
			if(s.retoken()==1)
		{
			while(f1.read((char*)&b, sizeof(b)) && flag==0)
			{
				if(strcmp(b.retbno(),s.retstbno())==0)
				{
					b.showbook();
					flag=1;
					cout<<"Enter no. of days kept ";
					cin>>day;
					if (day>7)
					{
						fine=(day-7)*1;
						cout<<"fine "<<fine;
					}

					s.resetoken();
					int pos=-1*sizeof(s);
					f.seekp(pos,ios::cur);
					f.write((char*)&s,sizeof(s));
					cout<<"\n Book deposited \n";
				}
			}
			if(flag==0)
				cout<<"Book does not exist \n";
		}
			else
				cout<<"No book issued \n";
		}
	}
	if (found==0)
		cout<<"Student does not exist \n";
	f.close();
	f1.close();
	getch();
}

void adminmenu()
{
XY:	clrscr();
	char pass[10] = "ankur";
	char pasw[20] , cd;
	cout<<"You need to enter the password \n\n";
	cout<<"enter the password: ";
	gets(pasw);
	if(strcmp(pass,pasw)==0)
	{
ZX:     clrscr();
	int opt;
	cout<<"Admin menu \n"<<endl;
	cout<<"1. Create Student"<<endl;
	cout<<"2. Display all student"<<endl;
	cout<<"3. Display specific student info"<<endl;
	cout<<"4. Modify student info"<<endl;
	cout<<"5. Delete student info"<<endl;
	cout<<"6. Create book"<<endl;
	cout<<"7. Display all books"<<endl;
	cout<<"8. Display specific book info"<<endl;
	cout<<"9. Modify book info"<<endl;
	cout<<"10. Delete book "<<endl;
	cout<<"11. Main menu"<<endl;
	cout<<"Enter your choice  ";
	cin>>opt;
	switch(opt)
	{
		case 1: clrscr();
			writestudent();
			break;
		case 2: displayalls();
			break;
		case 3: char num[6];
			clrscr();
			cout<<"Enter admn no. ";
			gets(num);
			cout<<endl<<endl;
			displaysps(num);
			break;
		case 4: modifystudent();
			break;
		case 5: deletestudent();
			break;
		case 6: clrscr();
			writebook();
			break;
		case 7: displayallb();
			break;
		case 8: char num1[6];
			clrscr();
			cout<<"enter book no. ";
			cin>>num1;
			cout<<endl<<endl;
			displayspb(num1);
			break;
		case 9: modifybook();
			break;
		case 10: deletebook();
			break;
	}
		if (opt<11)
			goto ZX;
		getch();
	}

	else
	{
		cout<<"Password is wrong\n";
		cout<<"Try more... ";
		cin>>cd;
		if (cd=='Y' || cd=='y')
			goto XY;
	}
}

void main()
{
	int opt;
ABC:    clrscr();
	gotoxy(25,2);
	cout<<"Library Management System \n\n";
	cout<<"Main Menu \n\n";
	cout<<"1. Book issue"<<endl;
	cout<<"2. Book deposit"<<endl;
	cout<<"3. Administrator menu"<<endl;
	cout<<"4. EXIT"<<endl;
	cout<<"Enter your choice  ";
	cin>>opt;
	switch(opt)
	{
		case 1: clrscr();
			bookissue();
			break;
		case 2: deposit();
			break;
		case 3: adminmenu();
			break;
	}
	if (opt<4)
	{
		goto ABC;
	}

	getch();
}







