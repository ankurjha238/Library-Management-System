#include<stdio.h>
#include<string.h>

typedef struct book
{
    char bookname[50];
	int bno;
	int issue;
	char authname[20];
	int edition;
}book;

typedef struct student
{
    int admno;
	char name[20];
	int stbno[3][6];
	int token;
	int fine;
}student;

void createbook(book *t)
{
    printf("\n\nNew book entry \n\n");
    printf("Enter book number ");
    scanf("%d",&t->bno);
    printf("Enter book name ");
    scanf("%s",t->bookname);
    printf("Enter author name ");
    scanf("%s",t->authname);
    printf("Enter the book edition");
    scanf("%d",&t->edition);
    t->issue = 0;
    printf("\nBook created \n\n");
}

void showbook(book t)
{
    printf("\n\nBook number %d \n",t.bno);
    printf("Book name %s\n",t.bookname);
    printf("Author name %s\n",t.authname);
    printf("Edition %d\n\n",t.edition);
}

void modifybook(book *t)
{
    printf("\n\nBook number is  %d\n",t->bno);
    printf("Book name ");
    scanf("%s",t->bookname);
    printf("Author name ");
    scanf("%s",t->authname);
    printf("Enter the edition");
    scanf("%d\n",&t->edition);
}

void createstudent(student *s)
{
    printf("\n\nNew student entry \n\n");
    printf("Enter admission no  ");
    scanf("%d",&s->admno);
    printf("Enter name  ");
    scanf("%s",s->name);
    s->token = 0;
    s->fine = 0;
    int i,j;
    for(i=0;i<3;i++)
        for(j=0;j<6;j++)
            s->stbno[i][j]=-1;
}

void showstudent(student s)
{
    printf("\n\nStudent's admission no is  %d\n",s.admno);
    printf("Student's name  ");
    printf("%s",s.name);
    printf("\nNo. of books issued %d\n",s.token);
    int i,j;
    for(i=0;i<s.token;i++)
    {
        printf("\nBook No.  :");
        for(j=0;j<6;j++)
        {
            if(s.stbno[i][j]!=-1)
            printf("%d",s.stbno[i][j]);
        }
    }
    printf("\nFine is :%d\n\n",s.fine);
}

void modifystudent(student *s)
{
    printf("\n\nAdmission no  %d\n",s->admno);
    printf("Enter name  ");
    scanf("%s",s->name);
}

void writebook()
{
	char ch;
	FILE *fp;
	fp = fopen("book.dat","a+");
	do
	{
	    book bo;
		createbook(&bo);
		fwrite(&bo, sizeof(book), 1, fp);
		printf("Add more book ");
		scanf(" %c",&ch);
	}while (ch == 'Y' || ch == 'y');
	fclose(fp);
}

void writestudent()
{
	char ch;
    FILE *fp;
	fp = fopen("student.dat","a+");
	do
	{
		student stu;
		createstudent(&stu);
		fwrite(&stu, sizeof(student), 1, fp);
		printf("Add more student ");
		scanf(" %c",&ch);
	}while (ch == 'Y' || ch == 'y');
	fclose(fp);
}

void displayspb(int n)
{
	printf("\n\nBook details \n");
	int flag=0;
	FILE *fp;
	fp = fopen("book.dat","r");
	book b;
	while(fread(&b, sizeof(book), 1, fp))
    {
		if(b.bno == n)
		{
			showbook(b);
			flag=1;
		}
    }
	fclose(fp);
	if (flag==0)
		printf("\nBook does not exist \n\n\n");
}

void displaysps(int n)
{
	printf("\n\nStudent details \n\n");
	int flag=0;
	FILE *fp;
	fp = fopen("student.dat","r");
	student s;
	while(fread(&s, sizeof(student), 1, fp))
    {
		if(s.admno == n)
		{
			showstudent(s);
			flag=1;
		}
    }
	fclose(fp);
	if (flag==0)
		printf("\nStudent does not exist \n\n");
}

void modibook()
{
	int n;
	int found=0;
	printf("\n\nModify book \n");
	printf("Enter book no  ");
	scanf("%d",&n);
	book b;
	FILE *fp;
	fp = fopen("book.dat","r+");
	while(fread(&b, sizeof(book), 1, fp) && found==0)
	{
		if(b.bno == n)
		{
			showbook(b);
			printf("Enter new details \n");
			modifybook(&b);
			int pos = -1*sizeof(book);
			fseek(fp,pos,1);
			fwrite(&b,sizeof(book),1,fp);
			found=1;
		}
	}
	fclose(fp);
	if (found==0)
		printf("\nBook not found\n\n");
}

void modistudent()
{
	int n;
	int found=0;
	printf("\n\nModify student \n\n");
	printf("Enter admission no  ");
	scanf("%d",&n);
	FILE *fp;
	student s;
	fp = fopen("student.dat","r+");
	while(fread(&s, sizeof(student), 1, fp) && found==0)
	{
		if(s.admno == n)
		{
			showstudent(s);
			printf("\n Enter new details \n");
			modifystudent(&s);
			int pos = -1*sizeof(student);
			fseek(fp,pos,1);
			fwrite(&s,sizeof(student),1,fp);
			found=1;
		}
	}
	fclose(fp);
	if (found==0)
		printf("\nStudent not found\n\n");
}

void deletebook()
{
    int n;
	printf("\n\nDelete book \n");
	printf("Enter book no  ");
	scanf("%d",&n);
	FILE *f1;
	book b;
	f1 = fopen("book.dat","r+");
	FILE *f2;
	f2 = fopen("temp.dat","r+");
	while(fread(&b, sizeof(book), 1, f1))
		if(b.bno != n)
			fwrite(&b,sizeof(book),1,f2);
	fclose(f2);
	fclose(f1);
	remove("book.dat");
	rename("temp.dat","book.dat");
}

void deletestudent()
{
	int n;
	printf("\n\nDelete student \n");
	printf("Enter admission no  ");
	scanf("%d",&n);
	FILE *f1,*f2;
	student s;
	f1 = fopen("student.dat","r+");
	f2= fopen("temp.dat","r+");
	while(fread(&s, sizeof(student), 1, f1))
		if(s.admno != n)
			fwrite(&s,sizeof(student),1,f2);
	fclose(f2);
	fclose(f1);
	remove("student.dat");
	rename("temp.dat","student.dat");
}

void displayalls()
{
    FILE *fp;
    student s;
	fp = fopen("student.dat","r");
	printf("\n\nStudent list \n");
	printf("==================================================================== \n");
	printf("Admn no.\t\t\tName\t\t\tBook \n");
	printf("==================================================================== \n");
	while(fread(&s, sizeof(student), 1, fp))
    {
        printf("\n");
        printf("%d\t\t\t",s.admno);
        printf("%s\t\t\t\t\t%d",s.name,s.token);
    }
	fclose(fp);
}

void displayallb()
{
    FILE *fp;
    book b;
	fp = fopen("book.dat","r+");
	printf("\n\nBooks list \n");
	printf("==================================================================== \n");
	printf("Book no.\t\t\tName\t\t\tAuthor \n");
	printf("==================================================================== \n");
	while(fread(&b, sizeof(book), 1, fp))
    {
        printf("%d\t\t\t\t%s\t\t\t\t%s",b.bno,b.bookname,b.authname);
    }
	fclose(fp);
}

void bookissue()
{
	int sn,bn;
	int found=0;
	int flag=0,ff=0;
	student s;
	book b;
	printf("\n\nBook issue \n\n");
	printf("Enter admission no  :");
	scanf("%d",&sn);
	FILE *f,*f1;
	f = fopen("student.dat","r+");
	f1 = fopen("book.dat","r+");
	while(fread(&s, sizeof(student), 1, f) && found==0)
	{
		if(s.admno == sn)
		{
			found=1;
			if(s.fine == 0)
            {
                ff = 1;
                if(s.token <=3)
                {
                    printf("Enter book no  :");
                    scanf("%d",&bn);
                    while(fread(&b, sizeof(book), 1, f1) && flag==0)
                    {
                        if(b.bno == bn && b.issue == 0)
                        {
                            int bh;
                            bh = b.bno;
                            displayallb();
                            flag=1;
                            int i,j;
                            int t[6];
                            for(j=0;j<6;j++)
                            {
                                t[j] = bh%10;
                                bh = bh/10;
                            }
                            j = 6;
                            for(i=0;i<6;i++)
                            {
                                s.stbno[s.token][i] = t[j--];
                            }
                            s.token = s.token + 1;
                            b.issue = 1;
                            int pos= -1*sizeof(student);
                            int pos1 = -1*sizeof(book);
                            fseek(f1,pos,1);
                            fseek(f,pos,1);
                            fwrite(&b, sizeof(book), 1, f1);
                            fwrite(&s, sizeof(student), 1, f);
                            printf("Book issued for 15 days \n");
                        }
                    }
                    if (flag==0)
                    printf("\nBook does not exist \n");
                }
                else
                    printf("\nYou have not returned the previously issued book");
            }
        else if(ff==0)
            printf("\nYou have not paid the fine");
    }
    }

        if(found==0)
            printf("\nStudent does not exist \n");

        fclose(f);
        fclose(f1);

}

void deposit()
{
	int sn,bn;
	int found=0;
	student s;
	book b;
	int day,fne=0,flag=0;
	printf("\n\nBook deposit \n");
	printf("Enter admission no  ");
	scanf("%d",&sn);
	FILE *f,*f1;
	f = fopen("student.dat","r+");
	f1 = fopen("book.dat","r+");
	while(fread(&s, sizeof(student), 1, f) && found==0)
	{
		if(s.admno == sn)
		{
		    int ste,i;
		    for(i=0;i<6;i++)
                ste = (ste*10) + s.stbno[s.token][i];
			found=1;
			if(s.token > 0)
            {
			while(fread(&b, sizeof(book), 1, f1) && flag==0)
			{
				if(b.bno == ste && b.issue == 1)
				{
					showbook(b);
					flag=1;
					b.issue = 0;
					printf("Enter no. of days kept ");
					scanf("%d",&day);
					if (day>15)
					{
						fne=(day-15)*10;
						printf("Fine is %d ",&s.fine);
                        s.fine = fne;
					}

					s.token = s.token - 1;
					int pos=-1*sizeof(student);
					fseek(f,pos,1);
					fwrite(&s, sizeof(student), 1, f);
					int pos1=-1*sizeof(book);
					fseek(f1,pos1,1);
					fwrite(&b, sizeof(book), 1, f1);
					printf("\n Book deposited \n");
				}
			}
			if(flag==0)
				printf("\nBook does not exist \n\n");
		}
			else
				printf("\nNo book issued \n\n");
		}
	}
	if (found==0)
		printf("\nStudent does not exist \n\n");
	fclose(f);
	fclose(f1);
}

void finecollect(int n)
{
	printf("\n\nStudent details \n\n");
	int flag=0;
	FILE *fp;
	fp = fopen("student.dat","r");
	student s;
	while(fread(&s, sizeof(student), 1, fp))
    {
		if(s.admno == n)
		{
			showstudent(s);
			s.fine = 0;
			flag=1;
		}
    }
	fclose(fp);
	if (flag==0)
		printf("\nStudent does not exist \n\n");
}

void adminmenu()
{
    char pass[10];
A:  printf("\n");
	strcpy(pass,"ankur");
	char pasw[20],cd;
	printf("You need to enter the password \n\n");
	printf("enter the password: ");
	scanf("%s",pasw);
	int num;
	int opt,num1;
	if(strcmp(pass,pasw)==0)
	{
B:  printf("\n");
	printf("Admin menu \n");
	printf("1. Create Student\n");
	printf("2. Display all student\n");
	printf("3. Display specific student info\n");
	printf("4. Modify student info\n");
	printf("5. Delete student info\n");
	printf("6. Create book\n");
	printf("7. Display all books\n");
	printf("8. Display specific book info\n");
	printf("9. Modify book info\n");
	printf("10. Delete book \n");
	printf("11. Collect Fine \n");
	printf("12. Main menu\n");
	printf("Enter your choice  \n");
	scanf("%d",&opt);
	switch(opt)
	{
		case 1: writestudent();
                break;
		case 2: displayalls();
                break;
		case 3: printf("\n\nEnter admn no. ");
                scanf("%d",&num);
                printf("\n");
                displaysps(num);
                break;
		case 4: modistudent();
                break;
		case 5: deletestudent();
                break;
		case 6: writebook();
                break;
		case 7: displayallb();
                break;
		case 8: printf("\n\nenter book no. ");
                scanf("%d",&num1);
                printf("\n");
                displayspb(num1);
                break;
		case 9: modibook();
                break;
		case 10: deletebook();
                 break;
        case 11: printf("\n\nEnter admn no. ");
                 scanf("%d",&num);
                 printf("\n");
                 finecollect(num);
                 break;
	}
		if (opt<12)
			goto B;
	}

	else
	{
		printf("Password is wrong\n");
		printf("Try more... \nEnter y or n :");
		scanf(" %c",&cd);
		if (cd=='Y' || cd=='y')
			goto A;
	}
}

void main()
{
	int opt;
ABC:printf("\n");
	printf("Library Management System \n\n");
	printf("Main Menu \n\n");
	printf("1. Book issue\n");
	printf("2. Book deposit\n");
	printf("3. Administrator menu\n");
	printf("4. Display all books\n");
	printf("5. EXIT\n");
	printf("Enter your choice  ");
	scanf("%d",&opt);
	switch(opt)
	{
		case 1: bookissue();
                break;
		case 2: deposit();
                break;
		case 3: adminmenu();
                break;
        case 4: displayallb();
                break;
	}
	if (opt<5)
	{
		goto ABC;
	}
}
