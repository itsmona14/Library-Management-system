#include <iostream>
#include <ctime>
using namespace std;
#include <string.h>
#include <cstring>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdio.h>

struct node{
	string book_id;
	string book_name;
	string author;
	string publisher;
	string category;
	string year;
	string rent_price;
	string no_of_copies;
	struct node *left;
	struct node *right;
	int height;
};
node *root;

class Library{
	public:
		void mainmenu();
		void mainmenu1();
		void mainmenu2();
		void display_books();
		void booksEntryAvl();
		int height(node* t);
		node* RightRotate(node* &t);
		node* LeftRotate(node* &t);
		node* LeftRightRotate(node* &t);
		node* RightLeftRotate(node* &t);
		void entry_avl(string, string, string, string, string, string, string, string);
		node* entry_avl(string , string, string, string, string, string, string, string, node* t);
		void search_name(node *, string);
		void search_author(node *, string);
		void search_category(node *, string);
		void search1();
		void search2();
		void inOrderAvl(node *);
		void display(node *ptr, int level);
		void display(int level);
		void take_order();
		void suggestions();
		void donate();
};

int Library::height(node* t){
	return (t == NULL ? -1 : t->height);
}

node* Library::RightRotate(node* &t){
    node* u = t->left;
    t->left = u->right;
    u->right = t;
    t->height = max(height(t->left), height(t->right))+1;
    u->height = max(height(u->left), t->height)+1;
    return u;
}

node* Library::LeftRotate(node* &t)
{
    node* u = t->right;
    t->right = u->left;
    u->left = t;
    t->height = max(height(t->left), height(t->right))+1;
    u->height = max(height(t->right), t->height)+1 ;
    return u;
}

node* Library::RightLeftRotate(node* &t)
{
    t->right = RightRotate(t->right);
    return LeftRotate(t);
}

node* Library::LeftRightRotate(node* &t)
{
    t->left = LeftRotate(t->left);
    return RightRotate(t);
}

node* Library::entry_avl(string ID, string Book_name, string Author, string Publisher, string Category, string Year_published, string Rent_price, string No_of_copies, node *t)
{
    if(t == NULL)
    {
        t = new node;
        t->book_id = ID;
        t->book_name = Book_name;
        t->author = Author;
        t->publisher = Publisher;
        t->category = Category;
        t->year = Year_published;
        t->rent_price = Rent_price;
        t->no_of_copies = No_of_copies;
        t->height = 0;
        t->left = t->right = NULL;
    }
   
    else if(Book_name < t->book_name)
    {
        t->left = entry_avl(ID, Book_name, Author, Publisher, Category, Year_published, Rent_price, No_of_copies, t->left);
        if(height(t->left) - height(t->right) == 2)
        {
            if(Book_name < t->left->book_name)
                t = RightRotate(t);
            else
                t = LeftRightRotate(t);
        }
    }
    else if(Book_name > t->book_name)
    {
        t->right = entry_avl(ID, Book_name, Author, Publisher, Category, Year_published, Rent_price, No_of_copies, t->right);
        if(height(t->right) - height(t->left) == 2)
        {
            if(Book_name > t->right->book_name)
                t = LeftRotate(t);
            else
                t = RightLeftRotate(t);
        }
    }

    t->height = max(height(t->left), height(t->right))+1;
    return t;
}

void Library::entry_avl(string ID, string Book_name, string Author, string Publisher, string Category, string Year_published, string Rent_price, string No_of_copies)
{
	root = entry_avl(ID, Book_name, Author, Publisher, Category, Year_published, Rent_price, No_of_copies, root);
}

void Library::booksEntryAvl()
{
	ifstream F("book_list1.txt");
	if (F.is_open())
	{
		string line;
		while(getline(F,line))
		{
			stringstream ss(line);
			string ID, Book_name, Author, Publisher, Category, Year_published, Rent_price, No_of_copies;
			getline(ss, ID, '|');
			getline(ss, Book_name, '|');
			getline(ss, Author, '|');
			getline(ss, Publisher, '|');
			getline(ss, Category, '|');
			getline(ss, Year_published, '|');
			getline(ss, Rent_price, '|');
			getline(ss, No_of_copies, '|');
			entry_avl(ID, Book_name, Author, Publisher, Category, Year_published, Rent_price, No_of_copies);
		}
	}
}

void Library::inOrderAvl(node *t)
{
	if (t == NULL)
	        return;
	inOrderAvl (t->left);
	cout << " || " << setw(2) << t->book_id <<  " || " << setw(25) << t->book_name << " || " << setw(20) << t->author  << " || " << setw(25) << t->publisher << " || " << setw(16) << t->category << " || " << setw(18) << t->year << " || " << setw(10) << t->rent_price << " || " << setw(13) << t->no_of_copies << " || " << endl;
	inOrderAvl (t->right);
}

void Library::search_name(node *t, string key)
{
	while (t != NULL)
	{
        if (t->book_name == key) 
		{
            cout << "Author name : " << t->author << endl;
            cout << "Publisher: " << t->publisher << endl;
            cout << "Rent price: " << t->rent_price << endl;
            cout << "No. of copies: " << t->no_of_copies << endl;
            break;
        }
        t = t->book_name < key ? t->right : t->left;
    }
}

void Library::search_author(node *t, string key)
{
    if (t == NULL)
        return;
    search_author(t->left,key);
    if (t->author == key)
        cout << "\t-> " << t->book_name << endl;
    search_author(t->right,key);
}

void Library::search_category(node *t, string key)
{
    if (t == NULL)
        return;
    search_category(t->left,key);
    if (t->category == key)
        cout << "\t->" << t->book_name << endl;
    search_category(t->right,key);
}

void Library::search1()
{
	cout << "***************************************************************" << endl;
	cout << "\t\t\t SEARCHING BOOKS \t\t\t" << endl;
	cout << "***************************************************************" << endl;
	cout << "  1. BASED ON NAME--> \n\n  2. BASED ON AUTHOR--> \n\n  3. BASED ON CATEGORY--> \n\n  4. EXIT--> " << endl;
	cout << "***************************************************************" << endl;
	
	int c;
	string item;
	do
	{
		cout << "Enter choice: ";
		cin >> c;
		switch(c)
		{
            case 1:
                cout << "Enter book name to search: ";
                cin.ignore();
                getline(cin,item);
                search_name(root, item);
                break;
            case 2:
                cout << "Enter author name to search: ";
                cin.ignore();
                getline(cin,item);
                cout << "Names of Books: " << endl;
                search_author(root, item);
                break;
            case 3:
                cout << "Enter category to search: ";
                cin.ignore();
                getline(cin,item);
                cout << "Books available: " << endl;
                search_category(root, item);
                break;
            case 4:
                cout << "\tBack to main menu..." << endl;
                mainmenu1();
                break;
            default:
                cout << "Enter valid choice" << endl;
		}
		cout << endl;
	}while(c!=5);
}

void Library::search2()
{
	cout << "***************************************************************" << endl;
	cout << "\t\t\t SEARCHING BOOKS \t\t\t" << endl;
	cout << "***************************************************************" << endl;
	cout << "  1. BASED ON NAME--> \n\n  2. BASED ON AUTHOR--> \n\n  3. BASED ON CATEGORY--> \n\n  4. EXIT--> " << endl;
	cout << "***************************************************************" << endl;
	
	int c;
	string item;
	do
	{
		cout << "Enter choice: ";
		cin >> c;
		switch(c)
		{
            case 1:
                cout << "Enter book name to search: ";
                cin.ignore();
                getline(cin,item);
                search_name(root, item);
                break;
            case 2:
                cout << "Enter author name to search: ";
                cin.ignore();
                getline(cin,item);
                cout << "Names of Books: " << endl;
                search_author(root, item);
                break;
            case 3:
                cout << "Enter category to search: ";
                cin.ignore();
                getline(cin,item);
                cout << "Books available: " << endl;
                search_category(root, item);
                break;
            case 4:
                cout << "\tBack to main menu..." << endl;
                mainmenu2();
                break;
            default:
                cout << "Enter valid choice" << endl;
		}
	cout << endl;
	}while(c!=5);
}

void Library::donate()
{
	int n;
	ofstream myfile;
	myfile.open("book_list1.txt",ios::app);
	
	string id,name,author,publisher,price,category,year,copies;
	cout<<"How many books you want to donate? ";
	cin>>n;
	for(int i = 0; i < n; i++)
	{
		cout<<"\nBook "<<i+1<<" details :\n";
		cout<<"->Enter Book Id : ";
		cin>>id;
		cout<<"->Enter Book name : ";
		cin>>name;
		cout<<"->Enter Author name : ";
		cin>>author;
		cout<<"->Enter Publisher name : ";
		cin>>publisher;
		cout<<"->Enter Category : ";
		cin>>category;
		cout<<"->Enter year : ";
		cin>>year;
		cout<<"->Enter price : ";
		cin>>price;
		cout<<"->Enter no. of copies : ";
		cin>>copies;
		myfile << id << "|" << name << "|" << author << "|" << publisher << "|" << category << "|" << year << "|" << price << "|" << copies << endl;
		entry_avl(id,name,author,publisher,category,year,price ,copies);
	}
}

void Library::suggestions()
{
    string line,str;
    ofstream myfile1;
    myfile1.open("suggestions.txt",ios::app);
    str = "";
    cout<<"Enter feedback : \n";
    cin.ignore();
    while(getline(cin,line) && !line.empty())
	{
        str += line + " ";
    }
    myfile1 << str<<endl;
}

void Library::take_order()
{
	node *t = root;
	string item;
	ofstream myfile;
	
	int d,m,y;
	time_t now = time(0);
	tm *ltm = localtime(&now);
	
	cout << "Today's date : "<< ltm->tm_mday<<"-"<<1+ltm->tm_mon<<"-"<<1900 + ltm->tm_year << endl;
	d = ltm->tm_mday;
	m = 1+ltm->tm_mon;
	y = 1900 + ltm->tm_year;
	d += 15;
	if(m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
	{
		if(d >= 31){
		   m += 1;
		   if(m > 12)
		       y += 1;
		   d -= 31;
		}
	}
	else
	{
		if(d >= 30){
		   m += 1;
		   if(m > 12)
		       y += 1;
		   d -= 30;
		}
	}
	myfile.open("books_input.txt",ios::app);
	if (1)
	{
		int copies;
		cout << "Enter book name: ";
		cin.ignore();
		getline(cin,item);
		
		cout << "Enter no. of copies: ";
		cin >> copies;
		while (t != NULL)
		{
			if (t->book_name == item) 
			{
				myfile << t->book_id << "|" << t->book_name << "|" << t->author << "|" << t->rent_price << "|" << copies << "|" << ltm->tm_mday << "-" << 1+ltm->tm_mon << "-" << 1900 + ltm->tm_year << "|" << d << "-" << m<< "-" << y << endl;
				break;
			}
			t = t->book_name < item ? t->right : t->left;
		}
	}
	else
		cout << "Unable to open file" << endl;
}


void display_order()
{
	ifstream myfile("books_input.txt");
	if (myfile.is_open())
	{
		string line;
		cout<<" || " << "ID" << setw(5) << "  || " << "BOOK NAME"  << setw(20) << " || " << "AUTHOR"  << setw(16) << " || " << "RENT PRICE"  << " || "  << "NO. OF COPIES"  << " || " << "TODAY'S DATE" << " || "<< "DUE DATE" << setw(5) << " || " << endl;
		cout<<"--------------------------------------------------------------------------------------------------------------------------" << endl;
		while(getline(myfile,line))
		{
			stringstream ss(line);
			string ID, Book_name, Author, Publisher, Category, Year_published, Rent_price, No_of_copies, Today_date, Due_date;
			getline(ss, ID, '|');
			getline(ss, Book_name, '|');
			getline(ss, Author, '|');
			getline(ss, Rent_price, '|');
			getline(ss, No_of_copies, '|');
			getline(ss, Today_date, '|');
			getline(ss, Due_date, '|');
					
			cout << " || " << setw(2) << ID <<  " || " << setw(25) << Book_name << " || " << setw(18) << Author  << " || " << setw(10) << Rent_price << " || " << setw(13) << No_of_copies << " || " << setw(12) << Today_date << " || " << Due_date << " || " << endl;
		}
	}
}

void show_stock()
{
	int flag = 0;
	ifstream F("book_list1.txt");
	if (F.is_open())
	{
		string line;
		cout<<" || " << "ID" << setw(5) << "  || " << "BOOK NAME"  << setw(20) << " || " << "AUTHOR"  << setw(16) << " || " << "RENT PRICE"  << " || "  << "ORIGINAL COPIES"  << " || " << "CURRENT STOCK" << " || " << endl;
		cout<<"-----------------------------------------------------------------------------------------------------------------" << endl;
		while(getline(F,line))
		{
			stringstream ss(line);
			string ID, Book_name, Author, Publisher, Category, Year_published, Rent_price, No_of_copies;
			getline(ss, ID, '|');
			getline(ss, Book_name, '|');
			getline(ss, Author, '|');
			getline(ss, Publisher, '|');
			getline(ss, Category, '|');
			getline(ss, Year_published, '|');
			getline(ss, Rent_price, '|');
			getline(ss, No_of_copies, '|');
			
			istringstream iss_n(No_of_copies);
			stringstream iss_i(ID);
			int num,id;
			iss_n >> num;
			iss_i >> id;
			
			ifstream myfile("books_input.txt");
			if (F.is_open())
			{
				string line1;
				while(getline(myfile, line1))
				{
					stringstream ss1(line1);
					string ID1, Book_name1, Author1, Rent_price1, No_of_copies1;
					getline(ss1, ID1, '|');
					getline(ss1, Book_name1, '|');
					getline(ss1, Author1, '|');
					getline(ss1, Rent_price1, '|');
					getline(ss1, No_of_copies1, '|');
					
					istringstream iss_n1(No_of_copies1);
					istringstream iss_i1(ID1);
					int num1,id1;
					iss_n1 >> num1;
					iss_i1 >> id1;
					
					if (id1 == id)
					{
						cout << " || " << setw(2) << ID <<  " || " << setw(25) << Book_name << " || " << setw(18) << Author  << " || " << setw(10) << Rent_price << " || " << setw(15) << No_of_copies << " || " << setw(13) << num-num1 << " || " << endl;
						flag = 1;
						break;
					}
					else
					{
						flag = 0;
						//cout << " || " << setw(2) << ID <<  " || " << setw(25) << Book_name << " || " << setw(18) << Author  << " || " << setw(10) << Rent_price << " || " << setw(15) << No_of_copies << " || " << setw(13) << No_of_copies << " || " << endl;
					}
					flag = 0;
				}
			}
			if (flag == 1){
				continue;
			}
			else{
				cout << " || " << setw(2) << ID <<  " || " << setw(25) << Book_name << " || " << setw(18) << Author  << " || " << setw(10) << Rent_price << " || " << setw(15) << No_of_copies << " || " << setw(13) << No_of_copies  << " || " << endl;
			}
		}
	}
}

void feedback(){
	int i = 1;
	ifstream F("suggestions.txt");
	if (F.is_open())
	{
		string line;
		while(getline(F,line))
		{
		    cout<<"\nFeedback "<<i++<< " : \n";
			stringstream ss(line);
			string str;
			getline(ss, str, '\n'); 
			cout<<str<<endl;
		}
	}
}

void Library::mainmenu1()
{
	printf("\n\n***************************************************************\n");
	cout << "\tWELCOME DEAR CUSTOMER! WHAT WOULD YOU LIKE TO DO? " << endl;
	printf("***************************************************************\n");
	printf("  1. DISPLAY BOOKS--> \n\n");
	printf("  2. SEARCH BOOKS--> \n\n  3. DONATE BOOK--> \n\n  4. SUGGESTIONS--> \n\n  5. EXIT--> \n");
	printf("***************************************************************\n");
	
	while(1)
	{
		int choice;double price1;
		printf("\nEnter your choice : ");
		scanf("%d",&choice);
		
		switch(choice)
		{
			//break;
			case 1:
				booksEntryAvl();
				cout<<" || " << "ID" << setw(6) << "  || " << "BOOK NAME"  << setw(20) << " || " << "AUTHOR"  << setw(18) << " || " << "PUBLISHER" << setw(20) << " || " << "CATEGORY" << setw(12) << " || " << "YEAR OF PUBLISHING" << setw(1) << " || " << "RENT PRICE"  << " || "  << "NO. OF COPIES"  << " || " << endl;
				cout<<"------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
				inOrderAvl(root);
				break;
			case 2:
				search1();
				break;
			case 3:
				donate();
				break;
			case 4:
				suggestions();
				break;
			case 5:
				mainmenu();
				break;
			default:
				printf("\nEnter valid choice!!!");
		}
	}
}

void Library::mainmenu2()
{
	printf("\n\n***************************************************************\n");
	printf("              WELCOME TO LIBRARY MANAGEMENT SYSTEM\n");
	printf("***************************************************************\n");
	printf("  1. DISPLAY BOOKS--> \n\n");
	printf("  2. SEARCH BOOKS--> \n\n  3. LEND BOOKS--> \n\n  4. DISPLAY ORDER--> \n\n  5. STOCK OF BOOKS--> \n\n  6.Feedback--> \n\n  7. EXIT--> \n");
	printf("***************************************************************\n");
	
	while(1)
	{
		int choice;double price1;
		printf("\nEnter your choice : ");
		scanf("%d",&choice);
		
		switch(choice)
		{
			case 1:
				booksEntryAvl();
				cout<<" || " << "ID" << setw(6) << "  || " << "BOOK NAME"  << setw(20) << " || " << "AUTHOR"  << setw(18) << " || " << "PUBLISHER" << setw(20) << " || " << "CATEGORY" << setw(12) << " || " << "YEAR OF PUBLISHING" << setw(1) << " || " << "RENT PRICE"  << " || "  << "NO. OF COPIES"  << " || " << endl;
				cout<<"------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
				inOrderAvl(root);
				break;
			case 2:
				search2();
				break;
			case 3:
				take_order();
				break;
			case 4:
				display_order();
				break;
			case 5:
				show_stock();
				break;
			case 6:
				feedback();
				break;
			case 7:
				mainmenu();
				exit(0);
			default:
				printf("\nEnter valid choice!!!");
		}
	}
}

void Library::mainmenu()
{
	int ch;
	printf("\n***************************************************************\n");
	printf("              WELCOME TO LIBRARY MANAGEMENT SYSTEM\n");
	printf("***************************************************************\n");
	cout<<"  1. Customer \n  2. Librarian \n  3. Exit\n";
	printf("***************************************************************\n");
	cout<<"Enter choice : ";
	cin>>ch;
	switch(ch){
		case 1:
			mainmenu1();
			break;
		case 2:
			mainmenu2();
			break;
		case 3:
			printf("\n");
			printf("**************************THANK YOU****************************\n\n");
			exit(0);
			break;
		default:
			cout<<"Enter valid choice !!!\n";
	}
}

int main()
{
	Library L;
	L.mainmenu();
	return 0;
}
