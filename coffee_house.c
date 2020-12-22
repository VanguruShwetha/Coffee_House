#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
int order_count=0;
struct item
{
	int sno;
	float price;
	char item_name[50];
	int quantity;
	char ingredients[1000];
};
struct item list[100];
int num=1;
float total_bill;
int  login()
{
	int type=0,i;
    	char username[10],ch=' ';
    	char password[10];
    	char user[10]="coffee";
    	char pass[10]="house";
    	do
	{
		printf(" \n\n                  ENTER USERNAME:-");
		scanf("%s", &username);
		printf(" \n\n                  ENTER PASSWORD:-");
		i=0;
		while(i<10)//for password  not to appear on screen
		{
			 password[i]=getch();
	    		ch=password[i];
	    		if(ch==13) break;
	   		 else printf("*");//* appears when we type password
	    		i++;
		}
		password[i]='\0';
		i=0;
		if(strcmp(username,"coffee")==0 && strcmp(password,"house")==0)
		{
			printf("  \n\n\n        LOGIN IS SUCCESSFUL!!");
			return 1;
			break;
		}
		else
		{
			printf("\n        SORRY, LOGIN IS UNSUCESSFUL!!\nEnter again");
			type++;
			getch();//holds the screen
		}
	}
	while(type<=2);
	if (type>2)
	{
		printf("\nSorry you have entered the wrong username and password for four times!!!");
		return 2;
	}
		system("cls");//It clears the output screen of the program
}
void insert(char name[50],float rate,int number,char lists[1000])
{
	list[num].sno=num;
	list[num].price=rate;
	strcpy(list[num].item_name,name);
	strcpy(list[num].ingredients,lists);
	list[num].quantity=number;
	num++;
	
}
void edit_name(int sno,char name[50])
{
	strcpy(list[sno].item_name,name);
	return ;
}
void edit_price(int sno,float rate)
{
	list[sno].price=rate;
	return ;
}
void edit_quantity(int sno, int number)
{
	list[sno].quantity=number;
	return ;
}
void display()
{
	system("cls");
	printf("\n\n\n\n\n\n\t\t\tTHE COFFEE HOUSE");
	printf("\n\n      TODAYS MENU...");
	int i=1;
	printf("\n\n\n------------------------------------------------------------\n");
	printf("| SNO. |   NAME                        |  PRICE  | QUANTITY  |\n");
	for(i=1;i<num;i++)
	{
		printf("---------------------------------------------------------\n");
		printf("|  %d   |",i);
		//char temp[50];
		//temp=list[i].item_name;
		int j=0;
		j=20-(strlen(list[i].item_name));
		printf("  %s",list[i].item_name);
		for(j;j<=20;j++)
			printf(" ");
		printf("    |  %0.2f  |",list[i].price);
		printf("    %d     |\n",list[i].quantity);
	}
	printf("---------------------------------------------------------\n");
}
void delete(int sno)
{
	int i=1;
	for(i=1;i<num;i++)
	{
		if(i==sno||i>sno)
		{
			list[i+1].sno=i;
			list[i]=list[i+1];
		}
	}
	num--;
}
void admin()
{
	int result=login();
	if(result==2)
		return ;
	int ch1,ch2;
	//system("cls");
	ch1=ch2=0;
	int number;
	int edit;
	float rate=0.0;
	char  name[50];
	char lists[1000];
	while(ch1!=5)
	{
		start:system("cls");
		printf("\n\n\n\n\n\n\t\t\tTHE COFFEE HOUSE");
		printf("\n\n\n\n\t\t\t");
		printf("1.Display Menu\n");
		printf("\t\t\t2.Add Item\n");
		printf("\t\t\t3.Edit menu\n");
		printf("\t\t\t4.Delete Item\n");
		printf("\t\t\t5.Go back....\n");
		printf("\t\t\tEnter your choice:");
		scanf("%d",&ch1);
		switch(ch1)
		{
			case 1:display();
			       	printf("\npress 1 to go back");
			       	int key;
			        scanf("%d",&key);
			        break;
			case 2:system("cls");
			        	printf("\n\n\n\t");
				display();
			        	printf("Enter the name of the coffee: ");
			 	scanf("%s",name);
			 	printf("\tEnter the Quantity available");
			  	scanf("%d",&number);
				printf("\tEnter the price of the coffee:");
				scanf("%f",&rate);
				printf("\tEnter the ingredients");
				scanf("%[^\n]",lists);
				insert(name,rate,number,lists);
				goto start;
			case 3: start1:system("cls");
				printf("\n\n\n\n\n\n\t\tTHE COFFEE HOUSE");
				printf("\n\n\n\t");
				display();
				printf("1.Edit name\n");
				printf("\t2.Edit price\n");
				printf("\t3.Edit quantity\n");
				printf("\t4.goback");
				scanf("%d",&ch2);
				if(ch2==4)
					goto start;
				else if(ch2==1)
				{
					printf("Enter the sno. of coffee:");
					scanf("%d",&edit);
					printf("Enter the new name of the coffee:");
					scanf("%s",name);
					edit_name(edit,name);
				}
				else if(ch2==2)
				{
					printf("Enter the sno. of coffee:");
					scanf("%d",&edit);
					printf("Enter the new price of coffee:");
					scanf("%f",&rate);
					edit_price(edit,rate);
				}
				else if(ch2==3)
				{
					printf("Enter the sno. of coffee:");
					scanf("%d",&edit);
					printf("Enter the new Quantity of coffee:");
					scanf("%d",&number);
					edit_quantity(edit,number);
				}
				else
				{
					printf("please enter valid choice");
					goto start1;
				}
				break;
			 case 4:display();
			 	printf("enter the sno. to delete:");
			       	scanf("%d",&edit);
			       	delete(edit);
			       	break;
			case 5:break;
			default:printf("please enter valid option");
		}
	}
	return ;
}
float calculate_bill(int number,int quant)
{
	float rate_of_item=list[number].price;
	return (rate_of_item*quant);
}
void reduce_quantity(int a[][2],int temp)
{
	for(int i=0;i<temp;i++)
	{
		list[a[i][0]].quantity=list[a[i][0]].quantity-a[i][1];
	}
	return ;
}
void backup(float bill)
{
	char date[30]=__DATE__;
	FILE *bills;
	time_t now;
	struct tm *time=localtime(&now);
	strcat(date,".txt");
	bills=fopen(date,"a");
	fprintf(bills,"Bill:%0.2f\n",bill);
	fclose(bills);
}
void preference()
{
	char temp;
	char extra[500];
	printf("ANY THING ELSE SIR/MADAM:");
	scanf("%c",&temp);
	scanf("%[^\n]",extra);
	//printf("%s",extra);
	printf("\t\tWOULD YOU LIKE US TO ADD SOMETHING IN THE MENU\n\t\tIF YES PLEASE ENTER THE NAME OF THE ITEM ELSE ENTER NO:  ");
	char prefer[200];
	scanf("%c",&temp);
	scanf("%[^\n]",prefer);
	char date[30]=__DATE__;
	FILE *PREFER;
	time_t now;
	struct tm *time=localtime(&now);
	strcat(date,"._preferences");
	strcat(date,".txt");
	PREFER=fopen(date,"a");
	char ch=getc(PREFER);
	while(ch!=EOF)
	{
		ch=getc(PREFER);
	}
	fprintf(PREFER,"Order number: %d\t",order_count);
	fprintf(PREFER,"Extras: %s",extra);
	if(strcmp("no",prefer)!=0)
	{
		char answer[3];
		printf("\n\t THE ITEM ENTERED BY THE  CUSTOMER IN THE MENU OR NOT:");
		scanf("%s",answer);
		fprintf(PREFER,"\t\tPreference:  %s\n",prefer);
		fclose(PREFER);
	}
	system("pause");
}
int serve ()
{
    	printf ("\n\n\t\tORDER NO. %d IS READY\t\t", order_count);
    	printf ("\n\n\t\tENJOY YOUR COFFEE......\n\t\tTHANK YOU\n\t\tPLEASE VISIT AGAIN.......!!\n\n");
}
void customer()
{
	int ch,number;
	ch=0;
	int n,a[10][2],temp;
	int quantity;
	float bill=0.0;
	system("cls");
	printf("\n\n\n\n\n\n\t\t\tWELCOME TO THE COFFEE HOUSE");
	printf("\n\n\n\n\t\t1.See the menu\n\t\t2.Go back\n\t\t");
	scanf("%d",&ch);
	if(ch==1)
	{
		int choice=0;
		while(choice!=1)
		{
			display();
			printf("\n\n\tPLEASE ENTER NUMBER OF ITEMS REQUIRED:");
			scanf("%d",&n);
			temp=n;
			int i=0;
			int a[n][2];
			while(n!=0)
			{
				printf("\n\n\tPLEASE ENTER YOUR CHOICE: ");
				scanf("%d",&number);
				printf("\t\t%s",list[number].ingredients);
				a[i][0]=number;
				printf("\n\tENTER THE QUANTITY REQUIRED: ");
				scanf("%d",&quantity);
				a[i][1]=quantity;
				bill=bill+calculate_bill(number,quantity);
				i++;
				n--;
			}
			printf("\n\tYOUR TOTAL BILL IS: %0.2f",bill);
			printf("\n\n\tPLEASE ENTER 1 TO CONFIRM YOUR BILL\n\t\t\t2 TO GO BACK TO MENU\t\t");
			scanf("%d",&choice);
			if(choice==1)
			{
				order_count++;
				printf("\n\n\t\tYOUR ORDER NUMBER IS: %d \n\t\tYOU WILL SOON RECIEVE YOUR ORDER PLEASE WAIT........",order_count);
				reduce_quantity(a,temp);
				backup(bill);
				total_bill=total_bill+bill;
				preference();
				serve();
				return ;
			}
		}
	}
	return ;
}
int main()
{
	system("cls");
	system("color B0");
	FILE *end;
	int ch;
	ch=0;
	insert(" Americano  ",30.0,12,"Expresso and Slow brew");
	insert(" Cappuchino ",50.0,15,"Espresso, steamed milk");
	insert(" Cafe Latte ",45.0,15,"Espresso,steamed milk, foam");
	insert(" CafeChoco  ",50.0,15,"creamy chocloates, steamed milk");
	insert(" Cafe Mocha ",40.0,15,"Espresso,steamed milk, foam, creamy chocolate");
	insert(" House Tea  ",60.0,15,"Spicy nutty indian Tea");
	insert("VanillaLatte",70.0,15,"Espresso,foam,sweet Vanilla");
	insert(" Frappucino ",80.0,15,"frozen blended espresso");
	while(ch!=3)
	{
		system("cls");
		printf("\n\n\n\n\n\n\t\t\tWELCOME TO THE COFFEE HOUSE");
		printf("\n\n\n\n\n\n\t\t1.CUSTOMER\n\t\t2.ADMIN\n\t\t3.EXIT\n\t\t");
		scanf("%d",&ch);
		if(ch==1)
		{
			customer();
		}
		else if(ch==2)
		{
			admin();
		}
		else if(ch==3)
		{
			break;
		}
		else
		{
			printf("\n\t\t\Enter valid option");
		}
	}
	char date[30]=__DATE__;
	time_t now;
	struct tm *time=localtime(&now);
	strcat(date,".txt");
	end=fopen(date,"a");
	fprintf(end,"\n\n\t\t\t\t\t\tTotal Bill:%0.2f\n",total_bill);
	fclose(end);
	return 0;
}
