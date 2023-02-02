#pragma once
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::string;

template<typename T>
class Node {
public:
	T data;
	Node* next;

	Node() { next = NULL; };
	Node(T data) { this->data = data; next = NULL; };
};

template<typename T>
class ReserverList {
public:
	Node<T>* head;

	ReserverList() { head = NULL; };

	void insertNode(T data)
	{
		// Create the new Node.
		Node<T>* newNode = new Node<T>(data);

		// Assign to head
		if (head == NULL) {
			head = newNode;
			return;
		}

		// Traverse till end of list
		Node<T>* temp = head;
		while (temp->next != NULL) {

			// Update temp
			temp = temp->next;
		}

		// Insert at the last.
		temp->next = newNode;
	}

	void deleteNode(string name)
	{
		Node<T>* temp1 = head;
		Node<T>* temp2 = NULL;
		int ListLen = 0;

		if (head == NULL) {
			cout << "List empty." << endl;
			return;
		}

		// Deleting the head.
		if (head->data->username == name) {

			// Update head
			head = head->next;
			delete temp1;
			return;
		}

		// Traverse the list to find the node to be deleted.
		while (temp1 != NULL) {

			// Update temp2
			temp2 = temp1;

			if (temp1->data->username == name)
				break;

			// Update temp1
			temp1 = temp1->next;
		}

		if (temp1 == NULL)
		{
			cout << "Node does not exist" << endl;
			return;
		}

		// Change the next pointer of the previous node.
		temp2->next = temp1->next;

		// Delete the node
		delete temp1;
	}

	void printList()
	{
		Node<T>* temp = head;

		// Check for empty list.
		if (head == NULL) {
			cout << "List empty." << endl;
			return;
		}

		// Traverse the list.
		while (temp != NULL) {
			cout << temp->data->username << " ";
			temp = temp->next;
		}
	}

	Node<T>* searchReserver(string n)
	{
		Node<T>* temp = head;

		// Check for empty list.
		if (head == NULL) {
			return head;
		}

		// Traverse the list.
		while (temp != NULL) {
			if (temp->data->getUsername() == n)
			{
				return temp;
			}
			temp = temp->next;
		}
		return NULL;
	}
};


