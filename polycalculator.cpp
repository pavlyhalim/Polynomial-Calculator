
#include "polycalculator.h"
#include "linkedlist.h"
#include<fstream>
#include<string>
#include<iostream>
using namespace std;

//display the contents of the linked list
void PolyCalculator::display()
{
    cout<<"Exp1: ";
    list1.display();
    cout<<"Exp2: ";
    list2.display();
}
//=======================================

void PolyCalculator::input()
{
    //ask for the first polynomial expression
    cout << "Enter the first polynomial expression: ";
    string str1;
    
    getline(cin, str1);
    
    //ask for the second polynomial expression
    cout << "Enter the second polynomial expression: ";
    string str2;
    getline(cin, str2);
    
    //parse the first polynomial expression and store it in the first linked list
    list1.removeAll();
    parse(str1, list1);
    
    //parse the second polynomial expression and store it in the second linked list
    list2.removeAll();
    parse(str2, list2);
}

//=======================================
//take as argument a polynomial expression to parse and store the expression in a linked list with validation
void PolyCalculator::parse(string str, LinkedList& list)
{
    if(str.size()==0)
    {
        cout << "Invalid polynomial expeerssion : empty exp\n";
        return;;
    }
    if(str[0]=='^')
    {
        cout << "Invalid polynomial expeerssion\n";
        return;
    }
    if(str[str.size()-1]=='^' or str[str.size()-1]=='+' or str[str.size()-1]=='-')
    {
        cout << "Invalid polynomial expeerssion\n";
        return;
    }
    for(int i = 0 ; i < str.size() ;i++)
    {
        if( isdigit(str[i]) )
        {
            if(i-1>=0&& str[i-1]=='x')
            {
                cout << "Invalid polynomial expeerssion\n";
                return;;
            }
        }
        if (str[i] == '+' or str[i] == '-')
        {
            if (str[i]=='-')
            {
                if (i-1>=0&& (str[i-1]=='^'))
                {
                    cout << "Invalid polynomial expeerssion\n";
                    return;
                }
            }
            if(i-1>=0&& (str[i-1]=='+' or str[i-1] == '-') )
            {
                cout << "Invalid polynomial expeerssion\n";
                return;
            }
        }
        if(str[i]=='^')
        {
            if(i-1>=0&& (str[i-1]=='+' or str[i-1] == '-' or str[i-1] =='^' or isdigit(str[i-1])) )
            {
                cout << "Invalid polynomial expeerssion\n";
                return;
            }
        }
        if(str[i]=='x')
        {
            if(i-1>=0&& (str[i-1] =='^' or str[i-1] =='x' ) )
            {
                cout << "Invalid polynomial expeerssion\n";
                return;
            }
        }
    }
        //parse the polynomial expression
        int i = 0;
        int coef = 0;
        int expo = 0;
        int signCoef = 1 , signExpo=1 , notConst=0;
        int takeexpo=0;
        while (i < str.length())
        {
            //if the character is a digit
            if (isdigit(str[i]))
            {
                if(!takeexpo)coef = coef * 10 + (str[i] - '0');
                else expo = expo * 10 + (str[i] - '0');
            }
            //if the character is a sign
            else if (str[i] == '+' or str[i] == '-')
            {
                if(i-1>=0&&str[i-1]=='^')
                {
                    //if the character is a sign of the exponent
                    if (str[i] == '-')
                    {
                        signExpo = -1;
                    }
                    else signExpo=1;
                }
                else
                {
                    if (coef == 0)
                    {
                        coef=1;
                    }
                    if (expo == 0)
                    {
                        if(notConst)expo=1;
                    }
                    //insert the term into the linked list
                    list.insert(coef * signCoef, expo*signExpo);
                    coef = 0;
                    expo = 0;
                    signCoef = 1;
                    if(str[i]=='-')signCoef=-1;
                    notConst=0;
                    takeexpo=0;
                }
                //if the character is a sign of the coefficient
                
                
            }

            //so check for the character is an exponent
            else if (str[i] == 'x')
            {
                notConst=1;
                takeexpo=0;
            }
            else
            {
                takeexpo=1;
            }
            i++;

            
        }
        //insert the last term into the linked list
        if (coef == 0)
        {
            coef=1;
        }
        if (expo == 0)
        {
            if(notConst)expo=1;
        }
        //insert the term into the linked list
        list.insert(coef * signCoef, expo*signExpo);
}
//==================================
//add the two polynomial expressions
void PolyCalculator::add()
{
    //add the two polynomial expressions and store the result in the third linked list
    Node* current1 = list1.head;
    Node* current2 = list2.head;
     list3.~LinkedList();
    while (current1 != NULL and current2 != NULL)
    {
        if (current1->expo == current2->expo)
        {
            list3.insert(current1->coef + current2->coef, current1->expo);
            current1 = current1->next;
            current2 = current2->next;
        }
        else if (current1->expo > current2->expo)
        {
            list3.insert(current1->coef, current1->expo);
            current1 = current1->next;
        }
        else
        {
            list3.insert(current2->coef, current2->expo);
            current2 = current2->next;
        }
    }
    while (current1 != NULL)
    {
        list3.insert(current1->coef, current1->expo);
        current1 = current1->next;
    }
    while (current2 != NULL)
    {
        list3.insert(current2->coef, current2->expo);
        current2 = current2->next;
    }
    
    //print the result
    cout << "Exp1 + Expr2 = ";
    list3.display();
   
}

//=======================================
//subtract the two polynomial expressions
void PolyCalculator::sub(){
    //subtract the two polynomial expressions and store the result in the third linked list
    Node* current1 = list1.head;
    Node* current2 = list2.head;
    list3.~LinkedList();
    while (current1 != NULL and current2 != NULL)
    {
        if (current1->expo == current2->expo)
        {
            if(current1->coef - current2->coef != 0) list3.insert(current1->coef - current2->coef, current1->expo);
            current1 = current1->next;
            current2 = current2->next;
        }
        else if (current1->expo > current2->expo)
        {
            list3.insert(current1->coef, current1->expo);
            current1 = current1->next;
        }
        else
        {
            list3.insert(-current2->coef, current2->expo);
            current2 = current2->next;
        }
    }
    while (current1 != NULL)
    {
        list3.insert(current1->coef, current1->expo);
        current1 = current1->next;
    }
    while (current2 != NULL)
    {
        list3.insert(-current2->coef, current2->expo);
        current2 = current2->next;
    }
    
    //print the result
    cout << "Exp1 - Expr2 = ";
    list3.display();
    
}

//=======================================
// multiply the two polynomial expressions
void PolyCalculator::mul()
{
    //multiply the two polynomial expressions and store the result in the third linked list
    Node* current1 = list1.head;
    Node* current2 = list2.head;
    list3.~LinkedList();
    while (current1 != NULL)
    {
        while (current2 != NULL)
        {
            list3.insert(current1->coef * current2->coef, current1->expo + current2->expo );
            current2 = current2->next;
        }
        current1 = current1->next;
        current2 = list2.head;
    }
    
    //print the result
    cout << "Exp1 * Expr2 = ";
    list3.display();
    
}

//=======================================
//rewrite the readDate function to check if the file is opened successfully
void PolyCalculator::readData(string filename) {
    ifstream infile(filename);
    if (infile.is_open())
    {
        string str;
        getline(infile, str);
        list1.removeAll();
        parse(str, list1);
        infile >> str;
        list2.removeAll();
        parse(str, list2);
        infile.close();
    }
    else
    {
        cout << "Unable to open file"<<endl;
    }
}
//=======================================
//Optional helper function to write a polynomial expression (List) to a file;
//Optional helper function to write a polynomial expression (List) to a file get the definition of the function from the PolyCalculator.h file
void PolyCalculator::write(LinkedList& list ,ofstream& outfile)
{
    //write the polynomial expression to the file
    Node* current = list.head;
    while (current != NULL)
    {
        if (current->coef != 0)
        {
            if (current->coef > 0)
            {
                if (current->expo == 0)
                {
                    outfile << current->coef;
                }
                else if (current->expo == 1)
                {
                    outfile << current->coef << "x";
                }
                else
                {
                    outfile << current->coef << "x^" << current->expo;
                }
            }
            else
            {
                if (current->expo == 0)
                {
                    outfile << current->coef;
                }
                else if (current->expo == 1)
                {
                    outfile << current->coef << "x";
                }
                else
                {
                    outfile << current->coef << "x^" << current->expo;
                }
            }
            if (current->next != NULL)
            {
                outfile << " + ";
            }
        }
        current = current->next;
    }
}

//=======================================
//write the result of the operations to a file
void PolyCalculator::writeData(string filename) {
    ofstream outfile(filename);
    //outfile.open(filename);
    outfile << " exp1: ";
    write(list1, outfile);
      outfile << " exp2: ";
    write(list2, outfile);
    outfile << " \n";
    add();
    write(list3, outfile);
     outfile << " \n";
    sub();
    write(list3, outfile);
     outfile << " \n";
    mul();
    write(list3, outfile);
    outfile << endl;
    outfile.close();
}