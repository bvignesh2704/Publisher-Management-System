#include<stdio.h>
#include<string.h>
#include<math.h>

//structure definitions
struct author
{
	char author[80];
	int noofbooks;
	int royalty;
	char nameofbooks[10][80];
};


struct customer
{
	char name[30],add[30],password[30],books[10][80];
	long int id,phone;
	int ct,quantity[10];
};


struct book
{
	char title[80];
	char author[80];
	char genre[20];
	long int ISBN;
	int pages,royalty,stock,copies,edition;
	float price;
};

//function to register a new customer's details
void customerregister()
{
	FILE *f;
	//open file containing details of all customers
	f=fopen("customer.dat","rb+");

	struct customer a;
	char ch;
	int i,flag=0;

	//input customer details
	printf("enter name:");
	scanf(" %[^\n]",a.name);
	printf("enter address:");
	scanf(" %[^\n]",a.add);
	printf("enter id:");
	scanf("%li",&a.id);
	printf("enter phone no:");
	scanf("%li",&a.phone);
	printf("enter password:");
	scanf("%s",a.password);
	
	a.ct=0;										//initialising number of books purchased by customer to be zero
	
	fseek(f,0,2);								//positioning pointer at the end of the file
	fwrite(&a,sizeof(struct customer),1,f);		//writing one customer's details into file
	
	//close file
	fclose(f);
}

//function to write a binary file containing details of authors
void createauthorfile()
{
	//initialising a structure object with details of exisiting books'author details
	struct author b[25]={{"jk rowling",3,10,{"harry potter-chamber of secrets","harry potter-goblet of fire","harry potter-order of phoenix"}},{"antoine",1,5,{"le petit prince"}},{"jrr tolkien",1,5,{"the hobbit"}},{"hrider",2,4,{"she","invisible man"}},{"cslewis",1,6,{"lion"}},{"dan brown",2,10,{"da vinci code","mixed demolitions"}},{"paulo coelho",2,7,{"alchemist","mirror"}},{"vladimir",2,5,{"lolita","aremon"}},{"johanna",1,7,{"common sense"}},{"chetan bhagat",2,8,{"one indian girl","revolution"}},{"rd sharma",1,5,{"play with math"}},{"sl arora",1,6,{"play with physics"}},{"reema thareja",1,5,{"coding in c"}},{"hc verma",1,15,{"concepts of physics"}},{"susritha verma",1,10,{"nights of life"}},{"bishal raj",1,5,{"experiences sold"}},{"v bignesh",1,7,{"morals extended"}}};
	
	//opening file containing details of authors of all books at headoffice
	FILE *fp=fopen("author.dat","wb+");
	
	int i;
	for(i=0;i<17;i++)
	{
		fwrite(&b[i],sizeof(b[i]),1,fp);		//writing record by record into the file
	}
	//close file
	fclose(fp);
}

//function to print the details of authors
void authordisplay()
{
	struct author s;
	
	//opening file containing details of authors of all books at headoffice
	FILE *fp1=fopen("author.dat","rb+");
	int i;
	
	//displaying all author details
	while(fread(&s,sizeof(s),1,fp1))
	{
		printf("\n\nname:%s      noofbooks:%d    royalty:%d",s.author,s.noofbooks,s.royalty);
		for(i=0;i<s.noofbooks;i++)
			printf("\nbook%d:%s   ",i+1,s.nameofbooks[i]);
	}
	//close file
	fclose(fp1);
}

//function to determine the bestseller book
void bestseller()
{
	int i,big;
	FILE *fp;
	struct book b;
	
	//open file containing details of al books at head office
	fp=fopen("books.dat","rb");
	fread(&b,sizeof(b),1,fp);
	//checking for highest number of copies sold
	big=b.copies;
	
	while(fread(&b,sizeof(b),1,fp))
	{	
		if(big<b.copies)
			{
				big=b.copies;
			}
	}
	fclose(fp);
	
	fp=fopen("books.dat","rb");
	while(fread(&b,sizeof(b),1,fp))
	{
		if(big==b.copies)
			printf("%s is bestseller\n",b.title);
	}
	
	//close file
	fclose(fp);
}
/*
//function to add a new book in the market to the headoffice
void appendabook()
{
	FILE *fp=fopen("books.dat","ab");
	FILE *f=fopen("author.dat","rb+");
	struct book s;
	struct author a;
	
	printf("enter title,author,genre,ISBN,pages,stock,edition,price: \n");
	scanf(" %[^\n]",s.title);
	scanf(" %[^\n]",s.author);
	scanf(" %[^\n]",s.genre);
	scanf("%li",&s.ISBN);
	scanf("%d",&s.pages);
	scanf("%d",&s.stock);
	scanf("%d",&s.edition);
	scanf("%f",&s.price);
	s.royalty=100;
	s.copies=100;
	
	fwrite(&s,sizeof(s),1,fp);						//writing new record's book details
	int c=0;
	
	while(fread(&a,sizeof(a),1,f))
	{
		//updating author details file accordingly
		if(strcmp(s.author,a.author)==0)
		{	c++;
			strcpy(a.nameofbooks[a.noofbooks],s.title);
			a.noofbooks++;
			fseek(f,-sizeof(a),1);
			fwrite(&a,sizeof(a),1,f);
			break;
		}
	}
	fclose(f);
	
	if(c==0)										//if new author
		{
			FILE *fq=fopen("author.dat","ab+");		//open authors file in append mode
			strcpy(a.author,s.author);
			a.noofbooks=1;
			a.royalty=3;
			strcpy(a.nameofbooks[0],s.title);
			fwrite(&a,sizeof(a),1,f);
			fclose(fq);
		}
	
			
	fclose(fp);
}
*/

void appendabook(struct book *t,struct author *u)
{
	FILE *fp=fopen("books.dat","ab");
	FILE *f=fopen("author.dat","rb+");
	
	
	fwrite(t,sizeof(struct book),1,fp);						//writing new record's book details
	int c=0;
	
	while(fread(u,sizeof(struct author),1,f))
	{
		//updating author details file accordingly
		if(strcmp(t->author,u->author)==0)
		{	c++;
			strcpy(u->nameofbooks[u->noofbooks],t->title);
			u->noofbooks++;
			fseek(f,-sizeof(struct author),1);
			fwrite(u,sizeof(struct author),1,f);
			break;
		}
	}
	fclose(f);
	
	if(c==0)										//if new author
		{
			FILE *fq=fopen("author.dat","ab+");		//open authors file in append mode
			strcpy(u->author,t->author);
			u->noofbooks=1;
			u->royalty=3;
			strcpy(u->nameofbooks[0],t->title);
			fwrite(u,sizeof(struct author),1,f);
			fclose(fq);
		}
	
			
	fclose(fp);
}
//function to write a binary file containing details of all books in the headoffice
void createbookfile()
{
	struct book b[25]={{"harry potter-chamber of secrets","jk rowling","fiction",600001,300,100,500,1000,1,150},
{"harry potter-goblet of fire","jk rowling","fiction",600002,350,100,600,2000,1,150},
{"harry potter-order of phoenix","jk rowling","fiction",600003,400,100,700,2000,1,150},
{"le petit prince","antoine","fiction",600004,700,100,500,1000,1,180},
{"the hobbit","jrr tolkien","fiction",600005,450,100,500,1000,1,800},
{"lord of rings","jrr tolkien","fiction",600006,900,100,500,1000,1,120},
{"she","hrider","fiction",600007,400,100,500,2000,1,350},
{"lion","cslewis","fiction",600008,300,100,400,3000,1,1000},
{"da vinci code","dan brown","fiction",600009,300,100,600,4000,1,600},
{"alchemist","paulo coelho","science fiction",600010,300,100,500,1000,1,700},
{"mirror","paulo coelho","fiction",600011,300,100,500,1000,1,430},
{"invisible man","hrider","fiction",600012,300,100,500,1000,1,210},
{"lolita","vladimir","fiction",600013,300,100,200,1000,1,900},
{"common sense","johanna","fiction",600014,300,100,500,1000,1,450},
{"one indian girl","chetan bhagat","fiction",600015,300,100,500,1500,1,190},
{"mixed demolitions","dan brown","fiction",600016,300,100,500,1000,1,210},
{"revolution","chetan bhagat","fiction",600017,300,100,500,1000,1,210},
{"play with math","rd sharma","reference",600018,300,100,500,1020,1,310},
{"play with physics","sl arora","reference",600019,300,100,500,1200,1,310},
{"coding in c","reema thareja","reference",600020,300,100,100,1300,1,410},
{"aremon","vladimir","fiction",600021,300,100,400,1400,1,210},
{"concepts of physics","hc verma","reference",600022,300,100,500,1500,1,310},
{"nights of life","susritha verma","fiction",600023,300,100,700,1050,1,210},
{"experiences sold","bishal raj","fiction",600024,300,100,300,2050,1,210},
{"morals extended","v bignesh","fiction",600025,300,100,300,1700,1,210}};
	FILE *fp;
	int i;
	fp=fopen("books.dat","wb+");
	for(i=0;i<25;i++)
		fwrite(&b[i],sizeof(b[i]),1,fp);
	fclose(fp);
}

//function to display details of all books in the headoffice
void booksdisplay()
{
		struct book s;
	FILE *fp1=fopen("books.dat","rb+");
	int i;
	printf("\n            title                    author               genre              isbn      pages     royalty   stock       copies      edition      price\n");      
	while(fread(&s,sizeof(s),1,fp1))
	{
		printf("\n%-35s %-20s %-15s    %li    %6d    %6d    %6d      %6d      %6d      %6f",s.title,s.author,s.genre,s.ISBN,s.pages,s.royalty,s.stock,s.copies,s.edition,s.price);

	}
	fclose(fp1);
}

//function to write a binary file containing details of books in BRANCH I
void createbranch1file()
{
	FILE *f;
	f=fopen("branch1.dat","wb+");
	struct book p[6]={{"harry potter-chamber of secrets","jk rowling","fiction",600001,300,100,500,100,1,150},
{"harry potter-goblet of fire","jk rowling","fiction",600002,350,100,600,200,1,150},
{"harry potter-order of phoenix","jk rowling","fiction",600003,400,100,700,200,1,150},
{"le petit prince","antoine","fiction",600004,700,100,500,100,1,180},
{"the hobbit","jrr tolkien","fiction",600005,450,100,500,100,1,800},
{"lord of rings","jrr tolkien","fiction",600006,900,100,500,100,1,120}};
	int i;
	for(i=0;i<6;i++)	
		fwrite(&p[i],sizeof(p[i]),1,f);
	fclose(f);
}


//function to write a binary file containing details of books in BRANCH II
void createbranch2file()
{
	FILE *f;
	f=fopen("branch2.dat","wb+");
	struct book q[5]={{"she","hrider","fiction",600007,400,100,500,200,1,350},
{"lion","cslewis","fiction",600008,300,100,400,300,1,1000},
{"da vinci code","dan brown","fiction",600009,300,100,600,400,1,600},
{"alchemist","paulo coelho","science fiction",600010,300,100,500,100,1,700},
{"mirror","paulo coelho","fiction",600011,300,100,500,100,1,430}};
	int i;
	for(i=0;i<5;i++)
		fwrite(&q[i],sizeof(q[i]),1,f);
	fclose(f);
}


//function to write a binary file containing details of books in BRANCH III
void createbranch3file()
{
	FILE *f;
	f=fopen("branch3.dat","wb+");
	struct book r[6]={{"invisible man","hrider","fiction",600012,300,100,500,100,1,210},
{"lolita","vladimir","fiction",600013,300,100,200,100,1,900},
{"common sense","johanna","fiction",600014,300,100,500,100,1,450},
{"one indian girl","chetan bhagat","fiction",600015,300,100,500,100,1,190},
{"mixed demolitions","dan brown","fiction",600016,300,100,500,100,1,210},
{"revolution","chetan bhagat","fiction",600017,300,100,500,100,1,210}};
	int i;
	for(i=0;i<6;i++)
	fwrite(&r[i],sizeof(r[i]),1,f);
	fclose(f);
}	

//function to display details of all books present in BRANCH I
void displaybranch1()
{
	struct book s;
	FILE *fp1=fopen("branch1.dat","rb+");
	int i;
	printf("\n            title                    author               genre              isbn      pages     royalty   stock       copies      edition      price\n");      
	while(fread(&s,sizeof(s),1,fp1))
	{
		printf("\n%-35s %-20s %-15s    %li    %6d    %6d    %6d      %6d      %6d      %6f",s.title,s.author,s.genre,s.ISBN,s.pages,s.royalty,s.stock,s.copies,s.edition,s.price);

	}
	fclose(fp1);
}

//function to display details of all books present in BRANCH II
void displaybranch2()
{
	struct book s;
	FILE *fp1=fopen("branch2.dat","rb+");
	int i;
      
	printf("\n            title                    author               genre              isbn      pages     royalty   stock       copies      edition      price\n");      
	while(fread(&s,sizeof(s),1,fp1))
	{
		printf("\n%-35s %-20s %-15s    %li    %6d    %6d    %6d      %6d      %6d      %6f",s.title,s.author,s.genre,s.ISBN,s.pages,s.royalty,s.stock,s.copies,s.edition,s.price);

	}
	fclose(fp1);
}

//function to display details of all books present in BRANCH III
void displaybranch3()
{
	struct book s;
	FILE *fp1=fopen("branch3.dat","rb+");
	int i;
	printf("\n            title                    author               genre              isbn      pages     royalty   stock       copies      edition      price\n");      
	while(fread(&s,sizeof(s),1,fp1))
	{
		printf("\n%-35s %-20s %-15s    %li    %6d    %6d    %6d      %6d      %6d      %6f",s.title,s.author,s.genre,s.ISBN,s.pages,s.royalty,s.stock,s.copies,s.edition,s.price);

	}
	fclose(fp1);
}


//function to display a working portal for already registered customers to buy books
void customerpurchaseportal()
{
	FILE *f;
	//opening file containing details of all customers
	f=fopen("customer.dat","rb+");
	struct customer a;
	char name[30],password[30];

	printf("\nenter name:");
	scanf(" %[^\n]",name);
	printf("\nenter password:");
	scanf(" %[^\n]",password);

	int co=0;

	while(fread(&a,sizeof(a),1,f))		
	{
		if(strcmp(a.name,name)==0&&strcmp(a.password,password)==0)		//matching with customer details in file
		{
			co++;
			printf("\nlogin successful!!!");	
			break;
		}
		
	}

	if(co==0)
	{
		printf("\ninvalid login!");
		
	}
	else
	{
		
	printf("\nBook list:\n");
	
	struct book s;
	
	//opening file containing details of all books at headoffice
	FILE *fp1=fopen("books.dat","rb+");
	int i;
	
	printf("\n            title                    author                genre              isbn     price\n");      
	//displays all book details
	while(fread(&s,sizeof(s),1,fp1))
	{
		printf("\n%-35s %-20s %-15s     %d    %f  ",s.title,s.author,s.genre,s.ISBN,s.price);
	}
	
	fclose(fp1);
	
	//input details of desired book
	int n,q;
	long int isbn;
	printf("\nenter the isbn of the book you want to purchase:");
	scanf("%li",&isbn);
	printf("\nenter no of books you want:");
	scanf("%d",&q);
	printf("\nenter the branch from where you should get your book(1/2/3):");
	scanf("%d",&n);
	
	
	if(n==1)		//branch 1
	{
		int pres=0;
		struct book s,temp;
		FILE *fp1=fopen("branch1.dat","rb+");
		while(fread(&s,sizeof(struct book),1,fp1))
		{
			if(s.ISBN==isbn)
			{
				if(s.stock>q)							//checking for stock
				{
					pres++;
					temp=s;								//copying details from one abject to a temporary object
					s.stock-=q;							//decrementing stock accordingly
					s.copies+=q;						//incrementing number of copies sold accordingly
					fseek(fp1,-sizeof(s),1);			//positioning pointer to write record with updated stock
					fwrite(&s,sizeof(s),1,fp1);

					//updating customer's book purchase records
					strcpy(a.books[a.ct],s.title);		
					a.quantity[a.ct]=q;
					a.ct+=1;
					fseek(f,-sizeof(a),1);
					fwrite(&a,sizeof(a),1,f);
					break;
				}
			}
		}
				
		if(pres==0)
			printf("\n\nBook out of stock in the given branch!Try in a different branch!");		
			
		fclose(fp1);

	
	}
	
	if(n==2)		//branch 2
	{
		int pres=0;
		struct book s,temp;
		FILE *fp1=fopen("branch2.dat","rb+");
		while(fread(&s,sizeof(struct book),1,fp1))
		{
			if(s.ISBN==isbn)													//checking for stock
			{
				if(s.stock>q)
				{
					pres++;
					temp=s;														//copying details from one abject to a temporary object
					s.stock-=q;													//decrementing stock accordinly
			
					s.copies+=q;										
					fseek(fp1,-sizeof(s),1);
					fwrite(&s,sizeof(s),1,fp1);
					//updating customer's book purchase records
					strcpy(a.books[a.ct],s.title);
					a.quantity[a.ct]=q;
					a.ct+=1;
					fseek(f,-sizeof(a),1);
					fwrite(&a,sizeof(a),1,f);
					break;
				}
			}
		}
				
		if(pres==0)
			printf("\n\nBook out of stock in the given branch!Try in a different branch!");		
			
		fclose(fp1);
						
	}
	
	if(n==3)		//branch 3
	{
		int pres=0;
		struct book s,temp;
		FILE *fp1=fopen("branch3.dat","rb+");
		while(fread(&s,sizeof(struct book),1,fp1))
		{
			if(s.ISBN==isbn)
			{
				if(s.stock>q)
				{
					pres++;
					temp=s;
					s.stock-=q;
					s.copies+=q;
					fseek(fp1,-sizeof(s),1);
					fwrite(&s,sizeof(s),1,fp1);
					strcpy(a.books[a.ct],s.title);
					a.quantity[a.ct]=q;
					a.ct+=1;
					fseek(f,-sizeof(a),1);
					fwrite(&a,sizeof(a),1,f);
					break;
				}
			}
		}
				
		if(pres==0)
			printf("\n\nBook out of stock in the given branch!Try in a different branch!");		
		
		fclose(fp1);					
	}
	}
	fclose(f);	

}

//function to display all registered customers' records
void displayallcustomerrecord()
{
	int i;
	struct customer a;
	FILE *f;
	
	//opening file containing details of all customers
	f=fopen("customer.dat","rb");
	
	char name[30],password[30];	
	printf("\nenter name:");
	scanf(" %[^\n]",name);
	printf("\nenter password:");
	scanf(" %[^\n]",password);
	
	if(strcmp(name,"admin")==0&&strcmp(password,"admin")==0)		//only admin can access all customers' details
	{
		while(fread(&a,sizeof(a),1,f))
		{
		
			printf("\n\nName:%s\n",a.name);
			printf("Address:%s\n",a.add);
			printf("Phone:%li\n",a.phone);
			if(a.ct==0)
				printf("No purchase records found");
			else
			{
				printf("Books                             quantity\n");
				for(i=0;i<a.ct;i++)     
					printf("%-40s%d\n",a.books[i],a.quantity[i]);
			}       			
		}
	}
	
	//close file
	fclose(f);
}


//function to dispay a particular customer's records
void displayacustomerrecord()
{
	int i;
	FILE *f;
	
	//opening file containing details of all customers
	f=fopen("customer.dat","rb+");
	struct customer a;
	char name[30],password[30];
	
	//input name and password of customer whose details to be displayed
	printf("\nenter name:");
	scanf(" %[^\n]",name);
	printf("\nenter password:");
	scanf(" %[^\n]",password);
	
	while(fread(&a,sizeof(a),1,f))
	{
		if(strcmp(a.name,name)==0&&strcmp(a.password,password)==0)		//matching name and password with customer details in file
		{
			printf("\n\nName:%s\n",a.name);
			printf("Address:%s\n",a.add);
			printf("Phone:%li\n",a.phone);
			if(a.ct==0)
				printf("No purchase records found");
			else
			{
				printf("Books                             quantity\n");
				for(i=0;i<a.ct;i++)     
					printf("%-40s%d\n",a.books[i],a.quantity[i]);
			}
			break;
		}
	}
	//closes file
	fclose(f);
}	

//function to write a binary file containing details of customers
void createcustomerfile()
{
	FILE *f;
	int i;
	//opening file containing details of all customers
	f=fopen("customer.dat","wb+");	
	struct customer a[6]={{"vignesh","mogappair 24","qwerty123",{"0"},18593,98411,0,{0}},{"susmithaa","virugambakkam 13","brocolli 123",{"0"},18181,87545,0,{0}},{"suraj","nungambakkam 17","susmithaa 77",{"0"},18177,10987,0,{0}},{"vishal","nungambakkam 34","everything123",{"0"},18598,73387,0,{0}},{"srihari","nungambakkam 14","doll 12345",{"0"},18164,87423,0,{0}},{"prasanna","nungambakkam 7","shadowdraconium 7",{"0"},18500,87544,0,{0}}};
	
	//writing record by record into file
	for(i=0;i<6;i++)
		fwrite(&a[i],sizeof(a[i]),1,f);

	//close file
	fclose(f);
}

//function to display a working portal for branch owners to purchase books from the headoffice
void headtobranch()
{
	printf("\nEnter from which branch you are(1/2/3):");
	struct book s,b;
	int n;
	scanf("%d",&n);
	
	if(n==1)			//BRANCH I is purchasing books from headoffice
	{
		long int isbn;
		int copy;
	
		printf("\nenter the isbn of book you want to purchase:");
		scanf("%li",&isbn);
		
		printf("\nenter the no of copies you want:");
		scanf("%d",&copy);
		
		//opening file containing details of all books at headoffice
		FILE *fp1=fopen("books.dat","rb+");
		while(fread(&s,sizeof(struct book),1,fp1))
		{
			if(s.ISBN==isbn)			//matching ISBN of book requested (by branch) and books in headoffice
			{
				int copytr;
				if(s.stock>copy)		//checking if requested number of copies present
				{
					s.stock-=copy;		//decrementing stock of headoffice of that book by number of copies
					s.copies+=copy;		//incrementing number of copies of said book sold at headoffice by number of copies requested
					copytr=copy;
				}
				
				else					//if stock is less than number of copies requested
				{
					copytr=s.stock;		//branch buys whatever stock present
					s.copies+=copytr;
					s.stock=0;
				}

				//opening file containing details of books in branch1
				FILE *fp2=fopen("branch1.dat","rb+");
				int count=0;
				while(fread(&b,sizeof(struct book),1,fp2))
				{
					if(b.ISBN==isbn)
					{	
						count++;
						b.stock+=copytr;			//updating stock at branch
						fseek(fp2,-sizeof(b),1);	//positioning pointer to write record with updated stock
						fwrite(&b,sizeof(b),1,fp2);
					}
				}
				fclose(fp2);

				if(count==0)								//new book with zero existing stock bought by branch from headoffice
				{
					FILE *fp3=fopen("branch1.dat","ab");	//appending details of new book
					b=s;									//copying book details from one object to another
					b.stock=copytr;							//updated stock of new book
					b.copies=0;								
					fwrite(&b,sizeof(b),1,fp3);
					fclose(fp3);
		
				}

				fseek(fp1,-sizeof(s),1);		//positioning pointer in books.dat file to write record with decremented stock
				fwrite(&s,sizeof(s),1,fp1);
			}
		}
		fclose(fp1);
	}

	else if(n==2)			//BRANCH II is purchasing books from headoffice
	{
		long int isbn;
		int copy;
		printf("\nenter the isbn of book you want to purchase:");
		scanf("%li",&isbn);
		printf("\nenter the no of copies you want:");
		scanf("%d",&copy);
		FILE *fp1=fopen("books.dat","rb+");
		while(fread(&s,sizeof(struct book),1,fp1))
		{
			if(s.ISBN==isbn)
			{
				int copytr;
				if(s.stock>copy)
				{
					s.stock-=copy;
					s.copies+=copy;
					copytr=copy;
				}
			
				else
				{
					copytr=s.stock;
					s.copies+=copytr;
					s.stock=0;
				}

				FILE *fp2=fopen("branch2.dat","rb+");
				int count=0;
				
				while(fread(&b,sizeof(struct book),1,fp2))
				{
					if(b.ISBN==isbn)
					{	
						count++;
						b.stock+=copytr;
						fseek(fp2,-sizeof(b),1);
						fwrite(&b,sizeof(b),1,fp2);
					}
				}
				
				fclose(fp2);

				if(count==0)
				{
					FILE *fp3=fopen("branch2.dat","ab");
					b=s;
					b.stock=copytr;
					b.copies=0;
					fwrite(&b,sizeof(b),1,fp3);
					fclose(fp3);
					
				}
				fseek(fp1,-sizeof(s),1);
				fwrite(&s,sizeof(s),1,fp1);
			}
		}
		fclose(fp1);
	}
	
	if(n==3)
	{
		long int isbn;
		int copy;
		printf("\nenter the isbn of book you want to purchase:");
		scanf("%li",&isbn);
		printf("\nenter the no of copies you want:");
		scanf("%d",&copy);
		FILE *fp1=fopen("books.dat","rb+");
		while(fread(&s,sizeof(struct book),1,fp1))
		{
			if(s.ISBN==isbn)
			{
				int copytr;
				if(s.stock>copy)
				{
					s.stock-=copy;
					s.copies+=copy;
					copytr=copy;
				}
				else
				{
					copytr=s.stock;
					s.copies+=copytr;
					s.stock=0;
				}

				FILE *fp2=fopen("branch3.dat","rb+");
				int count=0;
				while(fread(&b,sizeof(struct book),1,fp2))
				{
					if(b.ISBN==isbn)
					{	
						count++;
						b.stock+=copytr;
						fseek(fp2,-sizeof(b),1);
						fwrite(&b,sizeof(b),1,fp2);
					}
				}
				fclose(fp2);

				if(count==0)
				{
					FILE *fp3=fopen("branch3.dat","ab");
					b=s;
					b.stock=copytr;
					b.copies=0;
					fwrite(&b,sizeof(b),1,fp3);
					fclose(fp3);
				}
				
				fseek(fp1,-sizeof(s),1);
				fwrite(&s,sizeof(s),1,fp1);
			}
		}
		fclose(fp1);
	
	}

}

//function to determine the highest revenue generating branch
void highrevenuebranch()
{
	int p,q,r;
	FILE *a,*b,*c;
	struct book A,B,C;
	
	//a,b,c are pointers of files containing dtails of Branches 1,2 and 3 respectively
	a=fopen("branch1.dat","rb");
	b=fopen("branch2.dat","rb");
	c=fopen("branch3.dat","rb");

	//calculating yearly turnovers of each branch
	while(fread(&A,sizeof(A),1,a))
		p+=A.copies*A.price;
	while(fread(&B,sizeof(A),1,b))
		q+=B.copies*B.price;
	while(fread(&C,sizeof(A),1,c))
		r+=C.copies*C.price;

	//comparison of yearly turnovers of each branch
	if((p>q)&&(p>r))
		printf("Branch 1 is the highest revenue generating branch\n");
	else if(q>r&&q>p)
		printf("Branch 2 is the highest revenue generating branch\n");
	else 
		printf("Branch 3 is the highest revenue generating branch\n");
	
	//closing files of all branches
	fclose(a);
	fclose(b);
	fclose(c);
}


//function to calculate the royalty of a book given the royalty percent of the author,number of copies sold and its price
void royaltycalc()
{
	struct author a;
	struct book b;
	
	//opening file containing details of all books at headoffice
	FILE *fp1=fopen("books.dat","rb+");
	
	while(fread(&b,sizeof(struct book),1,fp1))
	{
		//opening file containing details of all authors
		FILE *fp2=fopen("author.dat","rb");
		
		while(fread(&a,sizeof(struct author),1,fp2))
		{
		//matching a book with its author using author name
		if(strcmp(b.author,a.author)==0)
			{
			b.royalty=a.royalty*b.price*b.copies/100;
			fseek(fp1,-sizeof(b),1);			//positioning the pointer one record behind to alter the royalty to calculated value
			fwrite(&b,sizeof(struct book),1,fp1);
			}
		}
		fclose(fp2);
	}	
	fclose(fp1);
}

//function that calculates and displays the royalty amount to be paid to each author
void authorroyalty()
{
	struct author s;
	
	//opening file containing details of all books at headoffice
	FILE *fp1=fopen("author.dat","rb+");
	int i;

	printf("\nAuthor name                   Royalty\n");

	while(fread(&s,sizeof(s),1,fp1))
	{
		int sum=0;
		struct book b;
		
		//opening file containing details of all books at headoffice
		FILE *fp2=fopen("books.dat","rb+");

		while(fread(&b,sizeof(struct book),1,fp2))
		{	
			if(strcmp(b.author,s.author)==0)
				sum+=b.royalty;			//adding the royalty contribution of every book the author has written to calculate author's total royalty to be paid
		}
	
		//displaying author's royalty to be paid
		printf("\n%-30s%d",s.author,sum);
		
		fclose(fp2);
	}	
	fclose(fp1);
}


//function to update stock of existing books
void stockalter()
{
	//opening file containing details of all books at headoffice
	FILE *fp=fopen("books.dat","rb+");
	struct book s;
	printf("\nenter the quantity of each book:\n");
	
	while(fread(&s,sizeof(s),1,fp))
	{
		int n;
		printf("%-40s :",s.title);
		scanf("%d",&n);			//reads additional stock of said book
		s.stock+=n;				//updates existing stock
	
		fseek(fp,-sizeof(s),1); //positions pointer one record behind to write with updated stock
		fwrite(&s,sizeof(s),1,fp);
	}
	
	fclose(fp);	
}


//function to calculate overall yearly turnover of the company(headoffice) with inflow of cash being the price of the books sold to branches and outflow of cash being the royalty paid to the authors 
void overallturnover()
{
	float royalty=0,turnover=0,sold=0,pur=0;
	struct book b;
	FILE *fp;
	
	//opening file containing details of all books at headoffice
	fp=fopen("books.dat","rb+");
	
	while(fread(&b,sizeof(b),1,fp))
	{
		royalty+=b.royalty;			//outflow of cash due to the sum of royalties paid off
		pur+=b.stock*b.price/2;		//outflow of cash due to purchased stock
		sold+=b.copies*b.price;		//total inflow of cash is the cost of the books bought from headoffice
	}
	
	fclose(fp);
	
	turnover=sold-pur-royalty;		//total turnover calculation
	printf("%f is the yearly turnover\n",turnover);
}

