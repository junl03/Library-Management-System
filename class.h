#pragma once
#include <cstdio>
#include <string>
#include <vector>
#include "linkedList.h"
#include "binaryTree.h"

using std::string;

class Book;
class Copy;
class Reader;

class Book {
private:
	long long int ISBN;
	string title;
	string author;
	string category;
	std::vector<Copy> copy_list;
	ReserverList<Reader*> reserver_list;
	int favor;
public:
	long long int main_search_key;
	string book_search_key;

	Book();
	Book(long long int, string, string, string, std::vector<Copy>, ReserverList<Reader*>, int favor);
	long long int getISBN();
	string getTitle();
	string getAuthor();
	string getCategory();
	std::vector<Copy> getCopyList();
	ReserverList<Reader*> getReserverList();
	int getFavor();
	void setISBN(long long int);
	void setTitle(string);
	void setAuthor(string);
	void setCategory(string);
	void setCopyList(std::vector<Copy>);
	void setReserverList(ReserverList<Reader*>);
	void setFavor(int);
	friend std::ostream& operator << (std::ostream&, Book&);
	friend std::istream& operator >> (std::istream&, Book&);
};


class Copy {
private:
	int ID;
	Book book;
	string borrower_name;
	string reserver_name;
	string reserve_start_date;
	string reserve_exp_date;
	string borrow_start_date;
	string borrow_exp_date;
public:
	int main_search_key;

	Copy();
	Copy(int, Book, string, string, string, string, string, string);
	int getID();
	Book getBook();
	string getBorrowerName();
	string getReserverName();
	string getReserveStartDate();
	string getReserveExpDate();
	string getBorrowStartDate();
	string getBorrowExpDate();
	void setID(int);
	void setBook(Book);
	void setBorrowerName(string);
	void setReserverName(string);
	void setReserveStartDate(string);
	void setReserveExpDate(string);
	void setBorrowStartDate(string);
	void setBorrowExpDate(string);
	friend std::ostream& operator << (std::ostream&, Copy&);
	friend std::istream& operator >> (std::istream&, Copy&);
};


class User {
public:
	string username;
	string password;
	string main_search_key;

	User();
	User(string, string);
	string getUsername();
	string getPassword();
	void setUsername(string);
	void setPassword(string);
	friend std::ostream& operator << (std::ostream&, User*);
	friend std::istream& operator >> (std::istream&, User*);
	virtual string getClassName();
};


class Librarian : public User {
public:
	Librarian(string, string);
	void addBook(BinaryTree<Book>&);
	void addBookCopy(BinaryTree<Book>&, BinaryTree<Copy>&);
	void deleteBook(BinaryTree<Book>&, BinaryTree<Copy>&);
	void deleteBookCopy(BinaryTree<Book>&, BinaryTree<Copy>&);
	void searchUser(BinaryTreePtr<User*>&);
	void addUser(BinaryTreePtr<User*>&);
	void deleteUser(BinaryTree<Book>&, BinaryTreePtr<User*>&);
	virtual string getClassName();
};


class Reader : public User {
public:
	int max_copies;
	int max_borrowing_periods;
	std::vector<Copy> borrowed_copies;
	std::vector<Copy> reserved_copies;
	int penalties;

	Reader(string, string);
	Reader(int, int, string, string);
	virtual int getMaxCopies();
	virtual int getMaxBorrowingPeriods();
	std::vector<Copy> getBorrowedCopies();
	std::vector<Copy> getReservedCopies();
	int getPenalties();
	void setBorrowedCopies(std::vector<Copy>);
	void setReservedCopies(std::vector<Copy>);
	void setPenalties(int);
	void searchByISBN(BinaryTree<Book>&);
	void searchByAuthor(BinaryTree<Book>&);
	void searchByTitle(BinaryTree<Book>&);
	void searchByCategory(BinaryTree<Book>&);
	void borrowBook(BinaryTree<Book>&, BinaryTree<Copy>&);
	void returnBook(BinaryTree<Book>&, BinaryTree<Copy>&);
	void renewBook(BinaryTree<Book>&, BinaryTree<Copy>&);
	void reserveBook(BinaryTree<Book>& book_database);
	void cancelReservation(BinaryTree<Book>&, BinaryTree<Copy>&);
	virtual string getClassName();
};


class Student : public Reader {
public:
	Student(string, string);
	virtual int getMaxCopies();
	virtual int getMaxBorrowingPeriods();
	virtual string getClassName();
};


class Teacher : public Reader {
public:
	Teacher(string, string);
	virtual int getMaxCopies();
	virtual int getMaxBorrowingPeriods();
	virtual string getClassName();
};