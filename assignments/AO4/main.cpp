/*****************************************************************************
*
*    Author:           Faith Howell
*    Email:            faith-howell@outlook.com
*    Label:            3013 Commenting C++ code
*    Title:            Linked List Comments
*    Course:           CMPS 3013
*    Semester:         Spring 2021
*    Description:      
*     This program implements a class that allows a linked list to be 
*     used just like  an array. It overloads the "[]"(square brackets) 
*     to simulate accessing seperate array elements, but really it
*     traverses the list to find the specified node using an index value. 
*     It also overloads the "+" and "-" signs allowing a user to "add" or 
*     "push" items onto the end of the list, as well as "pop" items off 
*     the end of our array. This class is not meant to replace the STL vector  
*     library, its simply a project to introduce the beginnings of creating 
*     complex / abstract data types.
*        
*    Usage:
*        - $ ./main filename
*        - This will read in a file containing whatever values to be read
*          into our list/array. 
*
*    Files:
*         3013 main.cpp    : driver program
******************************************************************************/

#include <iostream>
#include <string>

using namespace std;

int A[100];


struct Node
{
    int x;
    Node *next;
    Node()
    {
        x = -1;
        next = NULL;
    }
    Node(int n)
    {
        x = n;
        next = NULL;
    }
};

/*
*    Class Name: List
*    Description:
*        This class implements a linked list with various methods
*        such as push and pop to add or remove nodes from the list.
*
*    Public Methods:
*        - List() - default constructor
*        - void Push(int val)
*        - void Insert(int val)
*        - void PrintTail()
*        - string Print()
*        - int Pop()
*        - List operator+(const List& Rhs)
*        - int operator[](int index)
*        - friend ostream& operator<<(ostream& os, List L)
*    Private Methods:
*       
*    Usage:
*        - Create a class object of a Linked List
*        - insert or delete nodes from the Linked List
*        - Print output
*        - Print and read output onto another file
*/
class List
{
private:
    Node *Head;
    Node *Tail;
    int Size;

public:
   
    List()                          // Constructor
    {
        Head = Tail = NULL;
        Size = 0;
    }



    /**
     * Public: Push
     * 
     * Description:
     *      This function is used to allocate new memory.
     *      It then checks if list is empty or not. 
     * 
     * Params:
     *      - int val
     * 
     * Returns:
     *      void
     */

    void Push(int val)
    {
       
        Node *Temp = new Node(val);         // Allocates new memory

        
        if (!Head && !Tail)                // If list is empty
        {
            Head = Tail = Temp;           // It points to new node.
        }
        
        else
        {
            Tail->next = Temp;
            Tail = Temp;
        }
        Size++;
    }

    /**
     * Public : Insert
     * 
     * Description:
     *      This function allocates new memory.
     * 
     * Params:
     *      - int val
     * 
     * Returns:
     *      void
     */

    void Insert(int val)
    {
       
        Node *Temp = new Node(val);     // Allocates new memory

        Temp->next = Head;              
        Head = Temp;
        if (!Tail)
        {
            Tail = Head;
        }
        Size++;
    }

    /**
     * Public : PrintTail
     * 
     * Description:
     *      This function prints the result in tail.
     * 
     * Params:
     *      - None
     * 
     * Returns:
     *      void
     */

    void PrintTail()
    {
        cout << Tail->x << endl;
    }

    /**
     * Public : Print
     * 
     * Description:
     *      This function prints the list
     * 
     * Params:
     *      - None
     * 
     * Returns:
     *      [string] list
     */

    string Print()
    {
        Node *Temp = Head;
        string list;

        while (Temp != NULL)
        {
            list += to_string(Temp->x) + "->";
            Temp = Temp->next;
        }

        return list;
    }

    /**
     * Public : Pop
     * 
     * Description:
     *      This function is used to pop/remove a node
     * 
     * Params:
     * 
     * Returns:
     *      int
     */

    int Pop()
    {
        Size--;       // Pop/remove
        return 0;
    }

    /**
     * Public : Print
     * 
     * Description:
     *          This function prints the new list
     * 
     * Params:
     *          - const List &Rhs
     * 
     * Returns:
     *          newList
     */

    List operator+(const List &Rhs)
    {
       
        List NewList;                 // New List

        
        Node *Temp = Head;            // Points to the start/head of list

        
        while (Temp != NULL)
        {
            NewList.Push(Temp->x);    // Push values in list
            Temp = Temp->next;
        }

        
        Temp = Rhs.Head;

        while (Temp != NULL)
        {
            NewList.Push(Temp->x);    //Push values in list
            Temp = Temp->next;
        }

        
        return NewList;               // Returns a new list
    }

    /**
     * Public : operator
     * 
     * Description:
     *      Formats
     * 
     * Params:
     *      - int index
     * 
     * Returns:
     *      [int] list
     */

    int operator[](int index)
    {
        Node *Temp = Head;

        
        if (index >= Size)
        {
            cout << "Index out of bounds, exiting";
            exit(0);
        }
        else
        {

            for (int i = 0; i < index; i++)
            {
                Temp = Temp->next;
            }
            return Temp->x;
        }
    }

    /**
     * Public : ostream
     * 
     * Description:
     *      Prints and reads list into os
     * 
     * Params:
     *      - ostream &os, List L
     * 
     * Returns:
     *      [friend] os
     */

    friend ostream &operator<<(ostream &os, List L)
    {
        os << L.Print();
        return os;
    }
};


int main(int argc, char **argv)
{
    
    List L1;
    List L2;

    for (int i = 0; i < 25; i++)
    {
        L1.Push(i); 
    }

    for (int i = 50; i < 100; i++)
    {
        L2.Push(i);
    }

    
    L1.PrintTail();                 
    L2.PrintTail();                 

    
    List L3 = L1 + L2;
    cout << L3 << endl;

    
    cout << L3[5] << endl;        //Prints 
    return 0;
}
