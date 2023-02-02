#pragma once
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <typeinfo>
#include <stdlib.h>
#include "class.h"
#include "binaryTree.h"
#include "linkedList.h"



using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

void writeToBookFile(TreeNode<Book>*, std::ofstream&);
void writeToCopyFile(TreeNode<Copy>*, std::ofstream&);
void writeToUserFile(TreeNode<User*>*, std::ofstream&);



int main()
{
    std::fstream user_file("user.txt");     // user file
    std::fstream book_file("book.txt");     // book file
    std::fstream copy_file("copy.txt");     // copy file


    // file error check
    if (user_file.fail())
    {
        cerr << "Error opening user.txt" << endl;
        user_file.close();
        exit(1);
    }
    if (book_file.fail())
    {
        cerr << "Error opening book.txt" << endl;
        book_file.close();
        exit(1);
    }

    if (copy_file.fail())
    {
        cerr << "Error opening copy.txt" << endl;
        copy_file.close();;
        exit(1);
    }

    long long int ISBN;
    string title, author, category;
    Book book_temp;
    TreeNode<Book>* book_node;
    BinaryTree<Book> book_database;

    // set first node of book binary tree
    book_file >> ISBN >> title >> author >> category;
    book_temp.setISBN(ISBN);
    book_temp.setTitle(title);
    book_temp.setAuthor(author);
    book_temp.setCategory(category);
    book_node = new TreeNode<Book>(book_temp);
    book_database.root = book_node;

    // store to book BST
    while (!book_file.eof())
    {
        book_file >> ISBN >> title >> author >> category;

        if (book_file.eof())
        {
            break;
        }

        book_temp.setISBN(ISBN);
        book_temp.setTitle(title);
        book_temp.setAuthor(author);
        book_temp.setCategory(category);
        book_database.insertTreeNode(book_node, book_temp);
    }

    book_file.seekg(0, std::ios::beg);
    book_database.inOrderTraversal(book_database.root);
    cout << endl << endl;


    int ID;
    Copy copy_temp;
    TreeNode<Copy>* copy_node;
    BinaryTree<Copy> copy_database;
    vector<Copy> copy_list_temp;

    // set first node of copy binary tree
    copy_file >> ISBN >> ID;
    copy_temp.setID(ID);
    book_node = book_database.searchByKey(book_database.root, ISBN);    // get corresponding book
    copy_temp.setBook(book_node->data);
    copy_list_temp = book_node->data.getCopyList();                     // get copy list from corresponding book
    copy_list_temp.push_back(copy_temp);                                // add current copy to copy list
    book_node->data.setCopyList(copy_list_temp);                        // update copy list 
    copy_node = new TreeNode<Copy>(copy_temp);
    copy_database.root = copy_node;

    // store to copy BST
    while (!copy_file.eof())
    {
        copy_file >> ISBN >> ID;

        if (copy_file.eof())
        {
            break;
        }

        copy_temp.setID(ID);
        book_node = book_database.searchByKey(book_database.root, ISBN);    // get corresponding book
        copy_temp.setBook(book_node->data);
        copy_list_temp = book_node->data.getCopyList();                     // get copy list from corresponding book
        copy_list_temp.push_back(copy_temp);                                // add current copy to copy list
        book_node->data.setCopyList(copy_list_temp);                        // update copy list 
        copy_database.insertTreeNode(copy_node, copy_temp);
    }

    copy_file.seekg(0, std::ios::beg);
    copy_database.inOrderTraversal(copy_database.root);
    cout << endl << endl;


    int userType;
    string username, password;
    Student* student_temp = new Student(username, password);
    Teacher* teacher_temp = new Teacher(username, password);
    Librarian* librarian_temp = new Librarian(username, password);
    TreeNode<User*>* user_node;
    BinaryTreePtr<User*> user_database;

    // set first node of user binary tree
    user_file >> userType >> username >> password;

    if (userType == 0)  // student type
    {
        student_temp = new Student(username, password);
        user_node = new TreeNode<User*>(student_temp);
        user_database.root = user_node;
    }
    else if (userType == 1) // teacher type
    {
        teacher_temp = new Teacher(username, password);
        user_node = new TreeNode<User*>(teacher_temp);
        user_database.root = user_node;
    }
    else // librarian type
    {
        librarian_temp = new Librarian(username, password);
        user_node = new TreeNode<User*>(librarian_temp);
        user_database.root = user_node;
    }

    // continue reading from user file
    while (!user_file.eof())
    {
        user_file >> userType >> username >> password;

        if (user_file.eof())
        {
            break;
        }

        if (userType == 0)
        {
            student_temp = new Student(username, password);
            user_database.insertTreeNode(user_node, student_temp);
        }
        else if (userType == 1)
        {
            teacher_temp = new Teacher(username, password);
            user_database.insertTreeNode(user_node, teacher_temp);
        }
        else
        {
            librarian_temp = new Librarian(username, password);
            user_database.insertTreeNode(user_node, librarian_temp);
        }
    }

    user_file.seekg(0, std::ios::beg);
    user_database.inOrderTraversal(user_database.root);
    cout << endl << endl;

    // close files after reading
    book_file.close();
    copy_file.close();
    user_file.close();



    // login page
    cout << "--------------------------------------" << endl;
    cout << "|        Library Database v2.0       |" << endl;
    cout << "--------------------------------------" << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Pasword: ";
    cin >> password;
    
    TreeNode<User*>* user_match = user_database.searchByKey(user_database.root, username);  //get corresponding node to username
    string class_name;

    // login fail
    if (user_match == NULL)
    {
        cerr << "Incorrect username or password!" << endl;
        exit(1);
    }
    if (user_match->data->getPassword() != password)
    {
        cerr << "Incorrect username or password!" << endl;
        exit(1);
    }

    //login success
    class_name = user_match->data->getClassName();   // get user class name if login success


    //welcome page
    cout << endl;
    cout << "--------------------------------------" << endl;
    cout << "|              Homepage              |" << endl;
    cout << "--------------------------------------" << endl;

    int option;

    // student options
    if (class_name == "Student")
    {
        student_temp = dynamic_cast<Student*>(user_match->data);

        cout << "Welcome back, Student!" << endl;
        cout << endl;

        do {
            cout << "Please select an option (0-6): " << endl;
            cout << "   1. Search for a book" << endl;
            cout << "   2. Borrow a book" << endl;
            cout << "   3. Return a book" << endl;
            cout << "   4. Renew a book" << endl;
            cout << "   5. Reserve a book" << endl;
            cout << "   6. Cancel a book reservation" << endl;
            cout << "   7. My information" << endl;
            cout << "   8. Change my password" << endl;
            cout << "   9. Popularity poll" << endl;
            cout << "   0. Log Out" << endl;
            cout << "Option: ";

            cin >> option;

            switch (option)
            {
            case 0:
                break;
            case 1:
                int search_option;
                cout << "Please choose a search option:" << endl;
                cout << "   1. Search by ISBN" << endl;
                cout << "   2. Search by title" << endl;
                cout << "   3. Search by author" << endl;
                cout << "   4. Search by category" << endl;
                cout << "Search option: ";

                cin >> search_option;

                switch (search_option)
                {
                case 1:
                    student_temp->searchByISBN(book_database);
                    break;
                case 2:
                    student_temp->searchByTitle(book_database);
                    break;
                case 3:
                    student_temp->searchByAuthor(book_database);
                    break;
                case 4:
                    student_temp->searchByCategory(book_database);
                    break;
                default:
                    cerr << "Invalid search option." << endl;
                }
                break;
            case 2:
                student_temp->borrowBook(book_database, copy_database);
                break;
            case 3:
                student_temp->returnBook(book_database, copy_database);
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                cout << student_temp;
                break;
            case 8:
                break;
            case 9:
                break;
            default:
                cerr << "Invalid option." << endl;
            }
            cout << endl << endl;
        } while (option != 0);
    }


    // teacher options
    else if (class_name == "Teacher")
    {
        teacher_temp = dynamic_cast<Teacher*>(user_match->data);

        cout << "Welcome back, Teacher!" << endl;
        cout << endl;

        do {
            cout << "Please select an option (0-6): " << endl;
            cout << "   1. Search for a book" << endl;
            cout << "   2. Borrow a book" << endl;
            cout << "   3. Return a book" << endl;
            cout << "   4. Renew a book" << endl;
            cout << "   5. Reserve a book" << endl;
            cout << "   6. Cancel a book reservation" << endl;
            cout << "   7. My information" << endl;
            cout << "   8. Change my password" << endl;
            cout << "   9. Popularity poll" << endl;
            cout << "   0. Log Out" << endl;
            cout << "Option: ";

            cin >> option;

            switch (option)
            {
            case 0:
                break;
            case 1:
                int search_option;
                cout << "Please choose a search option:" << endl;
                cout << "   1. Search by ISBN" << endl;
                cout << "   2. Search by title" << endl;
                cout << "   3. Search by author" << endl;
                cout << "   4. Search by category" << endl;
                cout << "Search option: ";

                cin >> search_option;

                switch (search_option)
                {
                case 1:
                    teacher_temp->searchByISBN(book_database);
                    break;
                case 2:
                    teacher_temp->searchByTitle(book_database);
                    break;
                case 3:
                    teacher_temp->searchByAuthor(book_database);
                    break;
                case 4:
                    teacher_temp->searchByCategory(book_database);
                    break;
                default:
                    cerr << "Invalid search option." << endl;
                }
                break;
            case 2:
                teacher_temp->borrowBook(book_database, copy_database);
                break;
            case 3:
                teacher_temp->returnBook(book_database, copy_database);
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                cout << teacher_temp;
                break;
            case 8:
                break;
            case 9:
                break;
            default:
                cerr << "Invalid option." << endl;
            }
            cout << endl << endl;
        } while (option != 0);
    }


    // librarian options
    else if(class_name == "Librarian")
    {
        librarian_temp = dynamic_cast<Librarian*>(user_match->data);

        cout << "Welcome back, Librarian!" << endl;
        cout << endl;

        do {
            cout << "Please select an option (0-7): " << endl;
            cout << "    1. Add a book copy" << endl;
            cout << "    2. Add a new book" << endl;
            cout << "    3. Delete an existing book copy" << endl;
            cout << "    4. Delete an existing book" << endl;
            cout << "    5. Search Users" << endl;
            cout << "    6. Add Users" << endl;
            cout << "    7. Delete Users" << endl;
            cout << "    8. My Information" << endl;
            cout << "    9. Change Password" << endl;
            cout << "    0. Log Out" << endl;
            cout << "Option: ";

            cin >> option;

            switch (option)
            {
            case 0:
                break;
            case 1:
                librarian_temp->addBookCopy(book_database, copy_database);
                break;
            case 2:
                librarian_temp->addBook(book_database);
                break;
            case 3:
                librarian_temp->deleteBookCopy(book_database, copy_database);
                break;
            case 4:
                librarian_temp->deleteBook(book_database, copy_database);
                break;
            case 5:
                librarian_temp->searchUser(user_database);
                break;
            case 6:
                librarian_temp->addUser(user_database);
                break;
            case 7:
                librarian_temp->deleteUser(book_database, user_database);
                break;
            case 8:
                cout << librarian_temp;
                break;
            default:
                cerr << "Invalid Option!" << endl;
            }
            cout << endl << endl;
        } while (option != 0);
    }

    //log out page
    cout << "Logging out..." << endl;

    //Declare new variables as output files and clear existing information
    std::ofstream book_file1("book.txt", std::ios::out | std::ios::trunc);
    std::ofstream copy_file1("copy.txt", std::ios::out | std::ios::trunc);
    std::ofstream user_file1("user.txt", std::ios::out | std::ios::trunc);

    //write from updated BST to txt files
    writeToBookFile(book_database.root, book_file1);
    writeToCopyFile(copy_database.root, copy_file1);
    writeToUserFile(user_database.root, user_file1);

    //close files after writing
    book_file1.close();
    copy_file1.close();
    user_file1.close();

	return 0;
}




// write from BST to book.txt 
void writeToBookFile(TreeNode<Book>* root, std::ofstream& f)
{
    TreeNode<Book>* node = root;

    // write to file using inorder traversal
    if (node)
    {
        writeToBookFile(node->left, f);
        f << node->data.getISBN() << "\t" << node->data.getTitle() << "\t" << node->data.getAuthor() << "\t" << node->data.getCategory() << endl;
        writeToBookFile(node->right, f);
    }
    return;

}


// write from BST to copy.txt 
void writeToCopyFile(TreeNode<Copy>* root, std::ofstream& f)
{
    TreeNode<Copy>* node = root;

    // write to file using inorder traversal
    if (node)
    {
        writeToCopyFile(node->left, f);
        f << node->data.getBook().getISBN() << "\t" << node->data.getID() << endl;
        writeToCopyFile(node->right, f);
    }
    return;
}

// write from BST to user.txt 
void writeToUserFile(TreeNode<User*>* root, std::ofstream& f)
{
    TreeNode<User*>* node = root;

    // write to file using inorder traversal
    if (node)
    {
        writeToUserFile(node->left, f);
        string name = node->data->getClassName();   // temporary user type to be compared in if statement
        if (name == "Student")   // compare whhether user type of current node is student
        {
            f << 0 << "\t" << node->data->getUsername() << "\t" << node->data->getPassword() << endl;
        }
        else if (name == "Teacher")  // compare whhether user type of current node is teacher
        {
            f << 1 << "\t" << node->data->getUsername() << "\t" << node->data->getPassword() << endl;
        }
        else  // user type must be librarian
        {
            f << 2 << "\t" << node->data->getUsername() << "\t" << node->data->getPassword() << endl;
        }
        writeToUserFile(node->right, f);
    }
    return;
}