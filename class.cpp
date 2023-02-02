#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <typeinfo>
#include "class.h"

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::setw;
using std::setfill;
using std::left;
using std::string;
using std::vector;

Book::Book() 
{
	ISBN = 0;
	title = "";
	author = "";
	category = "";
	copy_list;
	reserver_list;
	favor = 0;
	main_search_key = ISBN;
}

Book::Book(long long int ISBN, string title, string author, string category, std::vector<Copy> copy_list, ReserverList<Reader*> reserver_list, int favor) 
{
	this->ISBN = ISBN;
	this->title = title;
	this->author = author;
	this->category = category;
	this->copy_list = copy_list;
	this->reserver_list = reserver_list;
	this->favor = favor;
	this->main_search_key = ISBN;
}

long long int Book::getISBN()
{
	return ISBN;
}

string Book::getTitle()
{
	return title;
}

string Book::getAuthor()
{
	return author;
}

string Book::getCategory()
{
	return category;
}

std::vector<Copy> Book::getCopyList()
{
	return copy_list;
}

ReserverList<Reader*> Book::getReserverList()
{
	return reserver_list;
}

int Book::getFavor()
{
	return favor;
}

void Book::setISBN(long long int ISBN)
{
	this->ISBN = ISBN;
	this->main_search_key = ISBN;
}

void Book::setTitle(string title)
{
	this->title = title;
}

void Book::setAuthor(string author)
{
	this->author = author;
}

void Book::setCategory(string category)
{
	this->category = category;
}

void Book::setCopyList(std::vector<Copy> copy_list)
{
	this->copy_list = copy_list;
}

void Book::setReserverList(ReserverList<Reader*> reserver_list)
{
	this->reserver_list = reserver_list;
}

void Book::setFavor(int favor)
{
	this->favor = favor;
}

std::ostream& operator << (std::ostream& out, Book& b)
{
	string borrow, reserve;

	for (int i = 0; i < b.copy_list.size(); i++)
	{
		if (b.copy_list[i].getBorrowerName() == "" && b.copy_list[i].getReserverName() == "")
		{
			borrow = "Available";
			reserve = "Open for reservation";
		}
		else if (b.copy_list[i].getBorrowerName() == "" && b.copy_list[i].getReserverName() != "")
		{
			borrow = "Waiting for reserver";
			reserve = "Reserved";
		}
		else if (b.copy_list[i].getBorrowerName() != "" && b.copy_list[i].getReserverName() == "")
		{
			borrow = "Borrowed";
			reserve = "Open for reservation";
		}
		else
		{
			borrow = "Borrowed";
			reserve = "Open for reservation";
		}
		out << setw(20) << left << b.ISBN << setw(45) << left << b.title << setw(25) << 
			left << b.author << setw(25) << left << b.category << setw(10) << left << 
			b.copy_list[i].getID() << setw(25) << left << borrow << reserve <<endl;
	}

	return out;
}

std::istream& operator >> (std::istream& in, Book& b)
{
	in >> b.ISBN >> b.title >> b.author >> b.category;
	return in;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------
Copy::Copy()
{
	ID = 0;
	book;
	borrower_name = "";
	reserver_name = "";
	reserve_start_date = "";
	reserve_exp_date = "";
	borrow_start_date = "";
	borrow_exp_date = "";
	main_search_key = ID;
}

Copy::Copy(int ID, Book book, string borrower_name, string reserver_name, string reserve_start_date, string reserve_exp_date, string borrow_start_date, string borrow_exp_date)
{
	this->ID = ID;
	this->book = book;
	this->borrower_name = borrower_name;
	this->reserver_name = reserver_name;
	this->reserve_start_date = reserve_start_date;
	this->reserve_exp_date = reserve_exp_date;
	this->borrow_start_date = borrow_start_date;
	this->borrow_exp_date = borrow_exp_date;
	this->main_search_key = ID;
}

int Copy::getID()
{
	return ID;
}

Book Copy::getBook()
{
	return book;
}

string Copy::getBorrowerName()
{
	return borrower_name;
}

string Copy::getReserverName()
{
	return reserver_name;
}

string Copy::getReserveStartDate()
{
	return reserve_start_date;
}

string Copy::getReserveExpDate()
{
	return reserve_exp_date;
}

string Copy::getBorrowStartDate()
{
	return borrow_start_date;
}

string Copy::getBorrowExpDate()
{
	return borrow_exp_date;
}

void Copy::setID(int ID)
{
	this->ID = ID;
	this->main_search_key = ID;
}

void Copy::setBook(Book book)
{
	this->book = book;
}

void Copy::setBorrowerName(string borrower_name)
{
	this->borrower_name = borrower_name;
}

void Copy::setReserverName(string reserver_name)
{
	this->reserver_name = reserver_name;
}

void Copy::setReserveStartDate(string start_date)
{
	this->reserve_start_date = start_date;
}

void Copy::setReserveExpDate(string exp_date)
{
	this->reserve_exp_date = exp_date;
}

void Copy::setBorrowStartDate(string start_date)
{
	this->borrow_start_date = start_date;
}

void Copy::setBorrowExpDate(string exp_date)
{
	this->borrow_exp_date = exp_date;
}

std::ostream& operator << (std::ostream& out, Copy& c)
{
	out << setw(20) << left << c.getBook().getISBN() << setw(45) << left << c.getBook().getTitle() << setw(25) <<
		left << c.getBook().getAuthor() << setw(25) << left << c.getBook().getCategory() << setw(10) << left << c.getID();

	return out;
}

std::istream& operator >> (std::istream& in, Copy& c)
{
	return in;
}


//--------------------------------------------------------------------------------------------------------------------------------------------------------
User::User()
{
	username = "";
	password = "";
	main_search_key = username;
}

User::User(string username, string password)
{
	this->username = username;
	this->password = password;
	this->main_search_key = username;
}

string User::getUsername()
{
	return username;
}

string User::getPassword()
{
	return password;
}

void User::setUsername(string username)
{
	this->username = username;
	this->main_search_key = username;
}

void User::setPassword(string password)
{
	this->password = password;
}

std::ostream& operator << (std::ostream& out, User* u)
{
	if (u->getClassName() == "Student")
	{
		Student* s = dynamic_cast<Student*>(u);
		vector<Copy> borrowed_copies = s->getBorrowedCopies();
		vector<Copy> reserved_copies = s->getReservedCopies();

		out << endl;
		out << setw(15) << left << "User Type" << setw(15) << left << "Username" << setw(15) << left << "Password" << endl;
		out << "--------------------------------------" << endl;
		out << setw(15) << left << s->getClassName() << setw(15) << left << s->username << setw(15) << left << s->password << endl;

		out << "List of borrowed copies: " << endl;
		for (int i = 0; i < borrowed_copies.size(); i++)
		{
			out << borrowed_copies[i] << endl;
		}

		out << "List of reserved copies: " << endl;
		for (int i = 0; i < reserved_copies.size(); i++)
		{
			out << reserved_copies[i] << endl;
		}
	}

	else if (u->getClassName() == "Teacher")
	{
		Teacher* t = dynamic_cast<Teacher*>(u);
		vector<Copy> borrowed_copies = t->getBorrowedCopies();
		vector<Copy> reserved_copies = t->getReservedCopies();

		out << endl;
		out << setw(15) << left << "User Type" << setw(15) << left << "Username" << setw(15) << left << "Password" << endl;
		out << "--------------------------------------" << endl;
		out << setw(15) << left << t->getClassName() << setw(15) << left << t->username << setw(15) << left << t->password << endl;
		out << endl;

		if (borrowed_copies.empty())
		{
			out << "List of borrowed copies: N/A" << endl;
		}
		else
		{
			out << "List of borrowed copies: N/A" << endl;
			out << setw(20) << left << "ISBN" << setw(45) << left << "Title" << setw(25) << left
				<< "Author" << setw(25) << left << "Category" << setw(10) << left << "ID" << setw(15) << left << "Start Date" << "Expiration Date" << endl;
			out << "-----------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
			for (int i = 0; i < borrowed_copies.size(); i++)
			{
				out << borrowed_copies[i] << setw(15) << left << borrowed_copies[i].getBorrowStartDate() << borrowed_copies[i].getBorrowExpDate() << endl;
			}
			out << endl;
		}

		if (reserved_copies.empty())
		{
			out << "List of reserved copies: N/A" << endl;
		}
		else
		{
			out << "List of reserved copies: " << endl;
			out << setw(20) << left << "ISBN" << setw(45) << left << "Title" << setw(25) << left
				<< "Author" << setw(25) << left << "Category" << setw(10) << left << "ID" << setw(15) << left << "Start Date" << "Expiration Date" << endl;
			out << "-----------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
			for (int i = 0; i < reserved_copies.size(); i++)
			{
				out << reserved_copies[i] << setw(15) << left << reserved_copies[i].getReserveStartDate() << reserved_copies[i].getReserveExpDate() << endl;
			}
		}
	}
	else
	{
		out << endl;
		out << setw(15) << left << "User Type" << setw(15) << left << "Username" << setw(15) << left << "Password" << endl;
		out << "--------------------------------------" << endl;
		out << setw(15) << left << u->getClassName() << setw(15) << left << u->username << setw(15) << left << u->password << endl;
	}

	return out;
}

std::istream& operator >> (std::istream& in, User* l)
{
	in >> l->username >> l->password;

	return in;
}

string User::getClassName()
{
	return "User";
}


//--------------------------------------------------------------------------------------------------------------------------------------------------------
Librarian::Librarian(string username, string password) : User(username, password)
{

}
void Librarian::addBook(BinaryTree<Book>& book_database)
{
	Book book_temp;

	cout << "Please enter details of the book in the format (ISBN, title, author, category): ";
	cin >> book_temp;

	book_database.root = book_database.insertTreeNode(book_database.root, book_temp);
}

void Librarian::addBookCopy(BinaryTree<Book>& book_database, BinaryTree<Copy>& copy_database)
{

	int ID;
	long long int ISBN;
	Copy copy_temp;
	TreeNode<Book>* book_node;
	vector<Copy> copy_list_temp;

	// get ISBN from keyboard input
	cout << "Please enter the ISBN: ";
	cin >> ISBN;
	
	book_node = book_database.searchByKey(book_database.root, ISBN);    // get corresponding book

	// check if corresponding book exists
	// corresponding book does not exist
	if (book_node == NULL)
	{
		cerr << "No matching book found in the library." << endl;
		return;
	}

	ID = copy_database.findMaxID() + 1;	// generate new ID
	copy_temp.setID(ID);	// set ID in new copy

	copy_temp.setBook(book_node->data);				// set corresponding book details in new copy
	copy_list_temp = book_node->data.getCopyList();	// get copy list from corresponding book
	copy_list_temp.push_back(copy_temp);			// add new copy to copy list
	book_node->data.setCopyList(copy_list_temp);	// update copy list    
	book_database.updateTreeByNode(book_database.root, book_node);	// update book database
	copy_database.root = copy_database.insertTreeNode(copy_database.root, copy_temp);	//add new copy to copy database

	cout << "Successfully added this book copy to the library." << endl;
}

void Librarian::deleteBook(BinaryTree<Book>& book_database, BinaryTree<Copy>& copy_database)
{
	int ID;
	long long int ISBN;
	Copy copy_temp;
	TreeNode<Book>* book_node;
	vector<Copy> copy_list_temp;

	// get ISBN from keyboard input
	cout << "Please enter the ISBN: ";
	cin >> ISBN;

	book_node = book_database.searchByKey(book_database.root, ISBN);    // get corresponding book

	// check if corresponding book exists
	// corresponding book does not exist
	if (book_node == NULL)
	{
		cerr << "No matching book found in the library." << endl;
		return;
	}

	copy_list_temp = book_node->data.getCopyList();	// get copy list from corresponding book

	bool borrow = 0;	// borrow flag

	// iterate through copy list and check if any copies are being borrowed
	for (int i = 0; i < copy_list_temp.size(); i++)
	{
		if (copy_list_temp[i].getBorrowerName() != "")
		{
			borrow = 1;
		}
	}
	if (borrow == 1)
	{
		cerr << "There are users currently borrowing copies of this book. Failed to delete this book." << endl;
		return;
	}

	// delete all copies
	for (int i = 0; i < copy_list_temp.size(); i++)	
	{
		ID = copy_list_temp[i].getID();
		copy_database.root = copy_database.deleteTreeNode(copy_database.root, ID);
	}

	book_database.root = book_database.deleteTreeNode(book_database.root, ISBN);	// delete book from book database

	cout << "Successfully deleted this book from the library." << endl;
}

void Librarian::deleteBookCopy(BinaryTree<Book>& book_database, BinaryTree<Copy>& copy_database)
{
	int ID;
	long long int ISBN;
	Book book_temp;
	TreeNode<Copy>* copy_node;
	TreeNode<Book>* book_node;
	vector<Copy> copy_list;

	// get ID from keyboard input
	cout << "Please enter the ID: ";
	cin >> ID;

	copy_node = copy_database.searchByKey(copy_database.root, ID);    // get corresponding copy

	// check if corresponding copy exists
	if (copy_node == NULL)
	{
		cerr << "No matching copy found in the library." << endl;
		return;
	}

	// check if copy is being borrowed
	// copy is being borrowed
	if (copy_node->data.getBorrowerName() != "")
	{
		cerr << "This book is currently borrowed. Failed to delete this book copy." << endl;
		return;
	}

	ISBN = copy_node->data.getBook().getISBN();	// get corresponding book's ISBN
	book_node = book_database.searchByKey(book_database.root, ISBN);	// get corresponding book from book database
	copy_list = book_node->data.getCopyList();	// get corresponding book's copy list

	// delete copy from corresponding book's copy list
	for (int i = 0; i < copy_list.size(); i++)
	{
		if (copy_list[i].getID() == ID)
		{
			copy_list.erase(copy_list.begin() + i);
			book_node->data.setCopyList(copy_list);	// update corresponding book's copy list
			book_database.updateTreeByNode(book_database.root, book_node);	// update book database
			break;
		}
	}

	copy_database.root = copy_database.deleteTreeNode(copy_database.root, ID);	// delete copy from copy database

	cout << "Successfully deleted this book copy from the library." << endl;
}

void Librarian::searchUser(BinaryTreePtr<User*>& user_database)
{
	string username;
	TreeNode<User*>* user_temp;

	// get username from keyboard input
	cout << "Pleaee enter the username: ";
	cin >> username;

	user_temp = user_database.searchByKey(user_database.root, username);	// get corresponding user 

	// check if corresponding user exists
	if (user_temp == NULL)
	{
		cerr << "No matching user found." << endl;
		return;
	}

	cout << user_temp->data;	// print search results
}

void Librarian::addUser(BinaryTreePtr<User*>& user_database)
{
	char userType;
	string username;
	string password;
	TreeNode<User*>* match;
	Student* student_temp;
	Teacher* teacher_temp;
	Librarian* librarian_temp;

	do
	{
		// get username from keyboard input
		cout << "Enter username: ";
		cin >> username;

		match = user_database.searchByKey(user_database.root, username);	// get corresponding user

		// check if username is taken
		if (match == NULL)
		{
			break;
		}

		cout << "That username has been taken!" << endl;

	} while (match != NULL);

	// get password from keyboard input
	cout << "Enter password: ";
	cin >> password;
	
	do 
	{
		// get usertype from keyboard input
		cout << "Please enter the user type (s/t/l): ";
		cin >> userType;

		switch (userType)
		{
		case 's':
			student_temp = new Student(username, password);	// create new user with type student
			user_database.root = user_database.insertTreeNode(user_database.root, student_temp);	// add new user to user database
			break;
		case 't':
			teacher_temp = new Teacher(username, password);	// create new user with type teacher
			user_database.root = user_database.insertTreeNode(user_database.root, teacher_temp);	// add new user to user database
			break;
		case 'l':
			librarian_temp = new Librarian(username, password);	// create new user with type librarian
			user_database.root = user_database.insertTreeNode(user_database.root, librarian_temp);	// add new user to user database
			break;
		default:
			cerr << "Invalid user type!" << endl;
			continue;
		}

		break;

	} while (1);
	
	cout << "Successfully added new user to the database." << endl;
}

void Librarian::deleteUser(BinaryTree<Book>& book_database, BinaryTreePtr<User*>& user_database)
{
	long long int ISBN;
	string username;
	vector<Copy> borrow_list;
	vector<Copy> reserve_list;
	ReserverList<Reader*> reserver_list;
	TreeNode<Book>* book_node;
	User* user_temp;
	Reader* reader_temp;

	// get username from keyboard input
	cout << "Enter username: ";
	cin >> username;

	user_temp = user_database.searchByKey(user_database.root, username)->data;	// get corresponding user

	// check if corresponding user exists
	if (user_temp == NULL)
	{
		cerr << "No matching user found." << endl;
		return;
	}

	reader_temp = dynamic_cast<Reader*>(user_temp);	// cast matching user into reader type

	borrow_list = reader_temp->getBorrowedCopies();	// get user's borrow list
	reserve_list = reader_temp->getReservedCopies();	// get user's reserve list

	// check if user has any borrowed copies
	// user has 1 or more borrowed copies
	if (!borrow_list.empty())
	{
		cerr << "Unable to delete user because he/she has borrowed copies." << endl;
		return;
	}

	// iterate through reserve list and delete user from corresponding book's reserver list
	for (int i = 0; i < reserve_list.size(); i++)
	{
		ISBN = reserve_list[i].getBook().getISBN();	// get ISBN of the current reserved copy
		book_node = book_database.searchByKey(book_database.root, ISBN);	// get corresponding book
		reserver_list = book_node->data.getReserverList();	// get book's reserver list
		reserver_list.deleteNode(user_temp->username);	// delete user from book's reserver list

		// update current copy's reserver
		if (reserver_list.head == NULL)
		{
			reserve_list[i].setReserverName("");
		}
		else
		{
			reserve_list[i].setReserverName(reserver_list.head->data->getUsername());
		}
		book_node->data.setReserverList(reserver_list);	// update book's reserver list
		book_database.updateTreeByNode(book_database.root, book_node);	// update book database
	}

	user_database.root = user_database.deleteTreeNode(user_database.root, username);	// delete user from database

	cout << "Successfully deleted this user from the database." << endl;
}

string Librarian::getClassName()
{
	return "Librarian";
}


//--------------------------------------------------------------------------------------------------------------------------------------------------------
Reader::Reader(string username, string password) : User(username, password)
{
	max_copies = 0;
	max_borrowing_periods = 0;
	penalties = 0;
}

Reader::Reader(int max_copies, int max_borrowing_periods, string username, string password) : User(username, password)
{
	this->max_copies = max_copies;
	this->max_borrowing_periods = max_borrowing_periods;
	penalties = 0;
}

int Reader::getMaxCopies()
{
	return max_copies;
}

int Reader::getMaxBorrowingPeriods()
{
	return max_borrowing_periods;
}

std::vector<Copy> Reader::getBorrowedCopies()
{
	return borrowed_copies;
}

std::vector<Copy> Reader::getReservedCopies()
{
	return reserved_copies;
}

int Reader::getPenalties()
{
	return penalties;
}

void Reader::setBorrowedCopies(std::vector<Copy> borrowed_copies)
{
	this->borrowed_copies = borrowed_copies;
}
void Reader::setReservedCopies(std::vector<Copy> reserved_copies)
{
	this->reserved_copies = reserved_copies;
}

void Reader::setPenalties(int penalties)
{
	this->penalties = penalties;
}

string Reader::getClassName()
{
	return "Reader";
}

void Reader::searchByISBN(BinaryTree<Book>& book_database)
{
	long long int ISBN;

	// get ISBN from keyboard input
	cout << "Please enter the ISBN: ";
	cin >> ISBN;

	TreeNode<Book>* book_node = book_database.searchByKey(book_database.root, ISBN);	// get corresponding book

	// check if corresponding book exists
	// corresponding book does not exist
	if (book_node == NULL)
	{
		cerr << "No matching book found in library." << endl;
		return;
	}

	cout << endl;
	cout << setw(20) << left << "ISBN" << setw(45) << left << "Title" << setw(25) << left
		<< "Author" << setw(25) << left << "Category" << setw(10) << left << "ID" << setw(25) << left << "Borrow Status" << "Reserve Status" << endl;

	cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

	cout << book_node->data;	// print search results
}

void Reader::searchByAuthor(BinaryTree<Book>& book_database)
{
	book_database.setBookKey(book_database.root, "author");	// set book search key as author in book database

	string author;

	// get author name from keyboard input
	cout << "Please enter the author name: ";
	cin >> author;

	vector<TreeNode<Book>*> book_vect = book_database.searchByBookKey(book_database.root, author);	// get corresponding book

	// check if corresponding book exists
	// corresponding book does not exist
	if (book_vect.empty())
	{
		cerr << "No matching book found in library." << endl;
		return;
	}


	// print search results
	cout << endl;
	cout << setw(20) << left << "ISBN" << setw(45) << left << "Title" << setw(25) << left
		<< "Author" << setw(25) << left << "Category" << setw(10) << left << "ID" << setw(25) << left << "Borrow Status" << "Reserve Status" << endl;

	cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

	for (int i = 0; i < book_vect.size(); i++)
	{
		cout << book_vect[i]->data;
	}
}

void Reader::searchByTitle(BinaryTree<Book>& book_database)
{
	book_database.setBookKey(book_database.root, "title");	// set book search key as title in book database

	string title;

	// get title name from keyboard input
	cout << "Please enter the title name: ";
	cin >> title;

	vector<TreeNode<Book>*> book_vect = book_database.searchByBookKey(book_database.root, title);	// get corresponding book

	// check if corresponding book exists
	// corresponding book does not exist
	if (book_vect.empty())
	{
		cerr << "No matching book found in library." << endl;
		return;
	}

	// print search results
	cout << endl;
	cout << setw(20) << left << "ISBN" << setw(45) << left << "Title" << setw(25) << left
		<< "Author" << setw(25) << left << "Category" << setw(10) << left << "ID" << setw(25) << left << "Borrow Status" << "Reserve Status" << endl;

	cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

	for (int i = 0; i < book_vect.size(); i++)
	{
		cout << book_vect[i]->data;
	}
}

void Reader::searchByCategory(BinaryTree<Book>& book_database)
{
	book_database.setBookKey(book_database.root, "category");	// set book search key as category in book database

	string category;

	// get category name from keyboard input
	cout << "Please enter the category: ";
	cin >> category;

	vector<TreeNode<Book>*> book_vect = book_database.searchByBookKey(book_database.root, category);	// get corresponding book

	// check if corresponding book exists
	// corresponding book does not exist
	if (book_vect.empty())
	{
		cerr << "No matching book found in library." << endl;
		return;
	}

	// print search results
	cout << endl;
	cout << setw(20) << left << "ISBN" << setw(45) << left << "Title" << setw(25) << left
		<< "Author" << setw(25) << left << "Category" << setw(10) << left << "ID" << setw(25) << left << "Borrow Status" << "Reserve Status" << endl;

	cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

	for (int i = 0; i < book_vect.size(); i++)
	{
		cout << book_vect[i]->data;
	}
}

void Reader::borrowBook(BinaryTree<Book>& book_database, BinaryTree<Copy>& copy_database)
{
	bool overdue = 0;	// overdue flag for borrowed copies

	// check if user has any overdue copies
	for (int i = 0; i < this->borrowed_copies.size(); i++)
	{
		clock_t curr = clock();							// mark current clock time
		int currInt = curr / CLOCKS_PER_SEC;				// convert clock time to seconds
		string currDate = std::to_string(currInt);				// convert to string
		if (currDate > this->borrowed_copies[i].getBorrowExpDate())
		{
			cerr << "You have an overdue copy with ID: " << this->borrowed_copies[i].getID() << endl;
			overdue = 1;
			this->penalties++; // increment penalty
		}
	}
	// user has 1 or more overdue copies
	if (overdue == 1)
	{
		cerr << "Please return overdue copies before borrowing a new one." << endl;
		return;
	}

	// check if user's number of borrowed copies exceeds max copies for his/her user type
	if (this->borrowed_copies.size() == this->getMaxCopies())
	{
		cerr << "You have reached the max number of borrowed copies. Please return a copy before borrowing a new one." << endl;
		this->penalties++;
		return;
	}

	int ID;	// ID to store keyboard input

	// get ID from keyboard input
	cout << "Please enter the book copy ID: ";
	cin >> ID;

	TreeNode<Copy>* copy_node = copy_database.searchByKey(copy_database.root, ID);	// find corresponding copy

	// check if corresponding copy exists
	// corresponding copy does not exist
	if (copy_node == NULL)
	{
		cerr << "No corresponding book copy found." << endl;
		return;
	}
	// check if copy is being borrowed
	// copy is being borrowed
	else if (copy_node->data.getBorrowerName() != "")
	{
		if (copy_node->data.getBorrowerName() == this->getUsername())
			cerr << "You are already borrowing this book." << endl;
		else
			cerr << "This book copy is currently borrowed." << endl;
		return;
	}
	// update copy's details
	else
	{
		clock_t c_start = clock();							// mark current clock time
		int start = c_start / CLOCKS_PER_SEC;				// convert clock time to seconds
		int end = start + this->getMaxBorrowingPeriods();	// expiration date
		string sDate = std::to_string(start);				// convert to string
		string eDate = std::to_string(end);					// convert to string

		copy_node->data.setBorrowStartDate(sDate);				// set copy's borrow start date
		copy_node->data.setBorrowExpDate(eDate);				// set copy's borrow exp date
		copy_node->data.setBorrowerName(this->getUsername());	// set copy's borrower to user's name
		this->borrowed_copies.push_back(copy_node->data);		// update user's borrowed list

		TreeNode<Book>* book_node = book_database.searchByKey(book_database.root, copy_node->data.getBook().getISBN());	// find corresponding book
		vector<Copy> copy_list = book_node->data.getCopyList();	// get book's copy list

		// iterate through book's copy list and find matching book
		for (int i = 0; i < copy_list.size(); i++)
		{
			if (copy_list[i].getID() == copy_node->data.getID())
			{
				copy_list[i] = copy_node->data;	// update copy details
				book_node->data.setCopyList(copy_list);	// update copy list
				break;
			}
		}
		book_database.updateTreeByNode(book_database.root, book_node);	// update book database
		cout << "Successfully borrowed this book copy." << endl;

		return;
	}
}

void Reader::returnBook(BinaryTree<Book>& book_database, BinaryTree<Copy>& copy_database)
{
	int ID;

	// get book ID to be borrowwed
	cout << "Please enter the book ID: ";
	cin >> ID;

	TreeNode<Copy>* copy_node = copy_database.searchByKey(copy_database.root, ID);	// corresponding book copy
	
	// book copy does not exist
	if (copy_node == NULL)
	{
		cerr << "No matching book copy found in the library." << endl;
		return;
	}

	// book copy not being borrowed
	if (copy_node->data.getBorrowerName() != this->getUsername())
	{
		cerr << "You are currently not borrowing this book." << endl;
		return;
	}

	// book copy exists
	else
	{
		copy_node->data.setBorrowStartDate("");	// reset copy's borrow start date
		copy_node->data.setBorrowExpDate("");	// reset copy's borrow exp date
		copy_node->data.setBorrowerName("");	// set borrower to blank

		// iterate through user's borrowed list and delete corresponding copy by ID
		for (int i = 0; i < this->borrowed_copies.size(); i++)
		{
			if (this->borrowed_copies[i].getID() == ID)
			{
				this->borrowed_copies.erase(this->borrowed_copies.begin() + i);
				break;
			}
		}

		clock_t c_start = clock();							// mark current clock time
		int start = c_start / CLOCKS_PER_SEC;				// convert clock time to seconds
		int end = start + 5;								// expiration date
		string sDate = std::to_string(start);				//convert to string
		string eDate = std::to_string(end);					// convert to string

		ReserverList<Reader*> reserver_list = copy_node->data.getBook().getReserverList();	// get corresponding book's reserver list

		// update copy's reserver
		// check if copy has a reserver
		if (copy_node->data.getReserverName() == "")
		{
			// reserver list is empty
			if (reserver_list.head == NULL)
			{
				copy_node->data.setReserveStartDate("");	// reset reserve start date
				copy_node->data.setReserveExpDate("");		// reset reserve exp date
			}
			// reserver list not empty
			else
			{
				copy_node->data.setReserverName(reserver_list.head->data->getUsername());	// set reserver to first reserver in line
				reserver_list.deleteNode(reserver_list.head->data->getUsername());	// delete reserver from reserver list
				copy_node->data.getBook().setReserverList(reserver_list);	// update reserver list
				copy_node->data.setReserveStartDate(sDate);	// set reserve start date to current time
				copy_node->data.setReserveExpDate(eDate);	// set reserve exp date to current time + 5
			}
		}
		else
		{
			copy_node->data.setReserveStartDate(sDate);	// set reserve start date to current time
			copy_node->data.setReserveExpDate(eDate);	// set reserve exp date to current time + 5
		}
	}

	TreeNode<Book>* book_node = book_database.searchByKey(book_database.root, copy_node->data.getBook().getISBN());	// find corresponding book
	vector<Copy> copy_list = book_node->data.getCopyList();	// get book's copy list

	// iterate through book's copy list and find matching book
	for (int i = 0; i < copy_list.size(); i++)
	{
		if (copy_list[i].getID() == copy_node->data.getID())
		{
			copy_list[i] = copy_node->data;	// update copy details
			book_node->data.setCopyList(copy_list);	// update copy list
			break;
		}
	}
	book_database.updateTreeByNode(book_database.root, book_node);	// update book database

	cout << "Successfully returned this book copy." << endl;
}

void Reader::renewBook(BinaryTree<Book>& book_database, BinaryTree<Copy>& copy_database)
{
	int ID;

	// get book ID to be renewed
	cout << "Please enter the book ID: ";
	cin >> ID;

	TreeNode<Copy>* copy_node = copy_database.searchByKey(copy_database.root, ID);	// corresponding book copy

	// book does not exist
	if (copy_node == NULL)
	{
		cerr << "No matching book copy found in the library." << endl;
		return;
	}

	// book copy not being borrowed
	if (copy_node->data.getBorrowerName() != this->getUsername())
	{
		cerr << "You are currently not borrowing this book." << endl;
		return;
	}

	// book copy exists
	else
	{
		clock_t c_start = clock();							// mark current clock time
		int start = c_start / CLOCKS_PER_SEC;				// convert clock time to seconds
		int end = start + this->getMaxBorrowingPeriods();	// expiration date
		string sDate = std::to_string(start);				//convert to string
		string eDate = std::to_string(end);					// convert to string

		copy_node->data.setReserveStartDate(sDate);	// set reserve start date to current time
		copy_node->data.setReserveExpDate(eDate);	// set reserve exp date to current time + 5

		// iterate through user's borrowed list and update copy
		for (int i = 0; i < this->borrowed_copies.size(); i++)
		{
			if (this->borrowed_copies[i].getID() == ID)
			{
				this->borrowed_copies[i] = copy_node->data;
				break;
			}
		}
	}

	TreeNode<Book>* book_node = book_database.searchByKey(book_database.root, copy_node->data.getBook().getISBN());	// find corresponding book
	vector<Copy> copy_list = book_node->data.getCopyList();	// get book's copy list

	// iterate through book's copy list and find matching book
	for (int i = 0; i < copy_list.size(); i++)
	{
		if (copy_list[i].getID() == copy_node->data.getID())
		{
			copy_list[i] = copy_node->data;	// update copy details
			book_node->data.setCopyList(copy_list);	// update copy list
			break;
		}
	}
	book_database.updateTreeByNode(book_database.root, book_node);	// update book database

	cout << "Successfully renewed this book copy." << endl;
}

void Reader::reserveBook(BinaryTree<Book>& book_database)
{
	long long ISBN;

	// get book ISBN to be reserved
	cout << "Please enter the ISBN: ";
	cin >> ISBN;

	TreeNode<Book>* book_node = book_database.searchByKey(book_database.root, ISBN);	// corresponding book

	// book does not exist
	if (book_node == NULL)
	{
		cerr << "No matching book found in the library." << endl;
		return;
	}

	// book exists
	else
	{
		ReserverList<Reader*> reserver_list = book_node->data.getReserverList();	// get book's reserver list
		reserver_list.insertNode(this);	// add reserver to end of linked list
		book_node->data.setReserverList(reserver_list);	// update reserver list
	}

	book_database.updateTreeByNode(book_database.root, book_node);	// update book database

	cout << "Successfully reserved this book." << endl;
}

void Reader::cancelReservation(BinaryTree<Book>& book_database, BinaryTree<Copy>& copy_database)
{
	long long int ISBN;

	// get book ISBN to be reserved
	cout << "Please enter the book ISBN: ";
	cin >> ISBN;

	TreeNode<Book>* book_node = book_database.searchByKey(book_database.root, ISBN);	// corresponding book

	// book does not exist
	if (book_node == NULL)
	{
		cerr << "No matching book found in the library." << endl;
		return;
	}

	ReserverList<Reader*> reserver_list = book_node->data.getReserverList();	// get book's reserver list

	// book not being reserved
	if (reserver_list.searchReserver(this->getUsername()) == NULL)
	{
		cerr << "You are currently not borrowing this book." << endl;
		return;
	}

	vector<Copy> copy_list = book_node->data.getCopyList();	// get book's copy list

	// book is reserved
	reserver_list.deleteNode(this->username);	// delete reserver from reserver list
	book_node->data.setReserverList(reserver_list);	// update reserver list

	// iterate through copy list and find reserved copy
	for (int i = 0; i < copy_list.size(); i++)
	{
		// copy with reserver exists
		if (copy_list[i].getReserverName() == this->username)
		{
			TreeNode<Copy>* copy_node = copy_database.searchByKey(copy_database.root, copy_list[i].getID());	// get corresponding copy in database
			vector<Copy> reserved_copies = this->getReservedCopies();	// get user's reserved copies

			// iterate through user's reserve list and find reserved copy
			for (int j = 0; j < reserved_copies.size(); j++)
			{
				if (reserved_copies[j].getID() == copy_node->data.getID())
				{
					reserved_copies.erase(reserved_copies.begin() + j);
					this->setReservedCopies(reserved_copies);
					break;
				}
			}

			// if reserver list is empty
			if (reserver_list.head == NULL)
				copy_node->data.setReserverName("");	// set reserver to blank
			// if reserver list is not empty
			else
			{
				clock_t c_start = clock();							// mark current clock time
				int start = c_start / CLOCKS_PER_SEC;				// convert clock time to seconds
				int end = start + 5;								// expiration date
				string sDate = std::to_string(start);				//convert to string
				string eDate = std::to_string(end);					// convert to string

				copy_node->data.setReserverName(reserver_list.head->data->getUsername());	// set reserver to first in line
				reserver_list.deleteNode(reserver_list.head->data->getUsername());			// delete head from linked list
				copy_node->data.setReserveStartDate(sDate);				// set reserve start state
				copy_node->data.setReserveExpDate(eDate);				// set reserve exp date
			}

			// update copy_database
			copy_database.updateTreeByNode(copy_database.root, copy_node);

			break;
		}
	}

	// update book_database
	book_database.updateTreeByNode(book_database.root, book_node);	// update book database

	cout << "Successfully canceled this reservation." << endl;
}


//--------------------------------------------------------------------------------------------------------------------------------------------------------
Student::Student(string username, string password) : Reader(5, 100, username, password)
{

}

string Student::getClassName()
{
	return "Student";
}

int Student::getMaxCopies()
{
	return max_copies;
}

int Student::getMaxBorrowingPeriods()
{
	return max_borrowing_periods;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------
Teacher::Teacher(string username, string password) : Reader(10, 150, username, password)
{

}

string Teacher::getClassName()
{
	return "Teacher";
}

int Teacher::getMaxCopies()
{
	return max_copies;
}

int Teacher::getMaxBorrowingPeriods()
{
	return max_borrowing_periods;
}