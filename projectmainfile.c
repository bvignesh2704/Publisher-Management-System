#include<stdio.h>
#include<string.h>
#include<project.h>			//userdefined header file

void main()
{
	int n;
	do						//printing the menu
	{
		start:	
		printf("\n\n                    							PUBLISHER MANAGEMENT SYSTEM");
		printf("\n                    							~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		printf("\n");
		printf("\n									1 . Stock Updating for Head Office");
		printf("\n  									2 . Branches Purchasing Platform");
		printf("\n									3 . Customer Registration");
		printf("\n									4 . Display Authorlist");
		printf("\n									5 . Find bestseller book");
		printf("\n									6 . Releasing new book to market");
		printf("\n									7 . Display details of book/stock in head office");
		printf("\n									8 . Display branch 1 stock");																												
		printf("\n									9 . Display branch 2 stock");
		printf("\n									10. Display branch 3 stock");
		printf("\n									11. Customer Purchase portal");
		printf("\n									12. Display particular Customer Records");
		printf("\n									13. Display all Customer Records");	
		printf("\n 									14. Highesh Revenue generating branch");
		printf("\n									15. Calculate Royalty of books in HO");
		printf("\n									16. Royalty of Authors");
		printf("\n									17. Overall turnover");
		printf("\n									18. Reset all files");
		printf("\n									19.exit!");
		printf("\n									Enter your choice:");
		scanf("%d",&n);
		
		//function calls
		if(n==1)
		{
			stockalter();
		}

		else if(n==2)
		{
			headtobranch();
		}

		else if(n==3)
		{
			customerregister();
		}

		else if(n==4)
		{
			authordisplay();
		}

		else if(n==5)
		{
			bestseller();
		}

		else if(n==6)
		{
		struct book s,*t=&s;
		struct author a,*u=&a;
	
		printf("enter title,author,genre,ISBN,pages,stock,edition,price: \n");
		scanf(" %[^\n]",t->title);
		scanf(" %[^\n]",t->author);
		scanf(" %[^\n]",t->genre);
		scanf("%li",&t->ISBN);
		scanf("%d",&t->pages);
		scanf("%d",&t->stock);
		scanf("%d",&t->edition);
		scanf("%f",&t->price);
		t->royalty=100;
		t->copies=100;	
		appendabook(t,u);			
	
		}

		else if(n==7)
		{
			booksdisplay();
		}

		else if(n==8)
		{
			displaybranch1();
		}

		else if(n==9)
		{
			displaybranch2();
		}

		else if(n==10)
		{
			displaybranch3();
		}

		else if(n==11)
		{
			customerpurchaseportal();
		}

		else if(n==12)
		{
			displayacustomerrecord();
		}

		else if(n==13)
		{
			displayallcustomerrecord();
		}	

		else if(n==14)
		{
			highrevenuebranch();
		}

		else if(n==15)
		{
			royaltycalc();
		}

		else if(n==16)
		{
			authorroyalty();
		}

		else if(n==17)
		{
			overallturnover();
		}

		else if(n==18)
		{
			createauthorfile();
			createbookfile();
			createbranch1file();
			createbranch2file();
			createbranch3file();
			createcustomerfile();
		}

		else if(n==19)
		{
			break;			//do while loop terminates
		}

		else
		{
			goto start;		//miscellaneous choice prints menu again 
		}
	
	}
	while(n<=18);		

}