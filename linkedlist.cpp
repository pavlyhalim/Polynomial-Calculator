
#include "linkedlist.h"
#include<fstream>
#include<string>
#include<iostream>
#include <cstddef>
using namespace std;

//=======================================
//constructor
LinkedList::LinkedList()
{
    head = NULL;
}
//=======================================
//destructor
LinkedList::~LinkedList()
{
    //delete all the nodes in the linked list
    removeAll();
}
//=======================================
//insert a new term of the polynomial expression into the linked list while also simplifying and sorting the polynomial expression
void LinkedList::insert(int coef,int expo)
{
    //create a new node
    Node* new_node = new Node(coef,expo);
    
    //if the list is empty
    if(head == NULL)
    {
        head = new_node;
        return;
    }
    
    //if the new node is to be inserted before the head node
    if(head->expo < expo)
    {
        new_node->next = head;
        head = new_node;
        return;
    }
    
    //if the new node is to be inserted after the head node
    Node* current = head;
    while(current->next != NULL and current->next->expo >= expo)
    {
        current = current->next;
    }
    
    //simplify the polynomial expression manually
    if (current->expo == expo)
    {
        current->coef += coef;
    }
    else
    {
        new_node->next = current->next;
        current->next = new_node;
    }
}

//=======================================
// display all nodes of a Linked List object of which it is called using exception handling
void LinkedList::display() const
{
    //if the list is empty
    if(head == NULL)
    {
        cout << "Empty List" << endl;
        return;
    }
    
    //display all the nodes in the linked list
    Node* temp = head;
    while(temp != NULL)
    {
        if(temp->coef >0)cout << "+";
        if(temp->coef==-1){
            if(temp->expo==0)cout << "-1";
            else cout << "-";
        }
        else if(temp->coef!=1) cout << temp->coef;
        if(temp->expo>0)
            cout << "x";
        if(temp->expo>1)cout << "^" << temp->expo;
        temp = temp->next;
    }
    cout << endl;
}

//=======================================
// remove all nodes of a Linked List object of which it is called
void LinkedList::removeAll()
{
    Node* current = head;
    while (current != NULL)
    {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    head = NULL;
}
