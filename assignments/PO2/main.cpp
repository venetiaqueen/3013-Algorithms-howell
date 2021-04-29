/*
*  Author:             Faith Howell
*    Email:            faith-howell@outlook.com
*    Label:            P02
*    Title:            P02 - Processing in Linear Time
*    Course:           CMPS 3013
*    Semester:         Spring 2021

    Description:
    This program is to load a singly linked list with dictionary words and then time how long it takes to look them up. The program will take the user's input and return the top results as well as the total number of results found. 
     

    Files:
*         main.cpp
*         animal_names.txt
*         mygetch.hpp
*         timer.txt
*
*    Usage:
*           main.cpp               : driver program
*           animal_names.txt       : Input file
*
*/

#include <iostream>
#include <time.h>
#include <chrono> 
#include "timer.hpp"
#include "mygetch.hpp"
//#include "termcolor.hpp"
#include <string>
#include <vector>
#include <fstream>

using namespace std;
/*
    Struct Name: wordNode
 
    Description:
      - Node used to hold both string and pointer
 
    Public Methods:
 	    - string word
 	    - wordNode* Next
 
    Private Methods:
        None
 
    Usage:
  	    - Creates node for a Linked List
 
 */

struct wordNode
{
    wordNode* Next;
    string word;

    wordNode()
    {
        Next = NULL;
        word = "";
    }

};

/*
    Class Name: LinkedList
 
    Description:
        - Implements a basic Linked List made up of wordNodes. 
        - Has a size variable
        - Has Head and Tail wordNode pointers
 
    Public Methods:
      - LinkedList()    : default constructor
 	    - int Get_Size()
 	    - void Insert_Data(wordNode* entry)
 	    - vector<string> Find(string typed)
 	    - void Print()
 
    Private Methods:
        - None
 
    Usage:
        - Load a linked list of wordNodes containing dictionary words.
 	      - Print the results
 */

class LinkedList
{
protected:
    wordNode* Head;
    wordNode* Tail;
    int Size;

public:

 /*
    Constructor : LinkedList
 
    Description:
    - Initialize with default values.
 
    Params:
    - None
 
    Returns:
    - None
 */
    LinkedList()
    {
        Head = NULL;
        Tail = NULL;
        Size = 0;
    }
 /*
    Public : Get_Size()
 
    Description:
    - returns size of linkedlist
 
    Params:
    - None
 
    Returns:
    - integer
 */
    int Get_Size()
    {
        return Size;
    }

/*
   Public : Insert_Data(wordNode* entry)

   Description:
      - Receives a wordNode and loads it into the linked list

   Params:
       wordNode* entry

   Returns:
       None
*/
    void Insert_Data(wordNode* entry)
    {
        if (!Head)
        {
            Head = Tail = entry;
        }

        else
        {
            Tail->Next = entry;
            Tail = entry;
        }
        Size++;
    }

/*
   Public : Print()

   Description:
    - Prints results of linkedlist

   Params:
    - None

   Returns:
    - None
*/
    void Print() {

        wordNode* Current = Head;     // Begin at the top and work your way down to the next node.
        while (Current) {
            cout << Current->word;   // Print name in node
            cout << endl;
            cout << "->";            
            Current = Current->Next; // Print next node
        }
        cout << "NULL" << endl;
    }

/*
    Public : Find(string typed)

    Description:
        - Receives the user's input
        - Compares it to the animals_names.txt data 
        - Searches for matches If a match is found
        - If found, it is added to the vector<string>Results

    Params:
        string typed

    Returns:
        vector<string> Results
*/
   vector<string> Find(string typed)
    {

       vector<string> Results;


       wordNode* Current = Head;
        
       while (Current)
       {
            string found = "";


            found = Current->word;              // Temp variable for the current stored node

            int length = typed.length();      

            if (found.substr(0, length) == typed) 
            {                            
                Results.push_back(found);
            }

            Current = Current->Next;            // Traverse to next node
       }

        return Results;                         // Return the vector of results
    }

};

int main() 
{
    LinkedList L1;                  
    vector<string> animalsWords;      // Placeholder animalsWords to read in the animals_names.txt

    ifstream op;
    op.open("animal_names.txt");


    Timer t;                  
    t.Start();                  // Starts Timer

    while (!op.eof())           // if file is NOT empty
    {
        string Temp;

        op >> Temp;

        animalsWords.push_back(Temp);
    }

    t.End();
    cout << t.Seconds() << " seconds to read in and print" << endl;


   
    Timer time2;                // Time to load the words into the Linked List

    time2.Start();

    for (int j = 0; j < animalsWords.size(); j++) 
    {
        wordNode* Temp = new wordNode;

        string item = animalsWords[j];  // allocate new memory

        Temp->word = item;

        L1.Insert_Data(Temp);
    }

    time2.End();

    cout << time2.Seconds() << "seconds to read in and print" << endl;


    char k;                 // Holder of char
    string word = "";      
    vector<string> matches; // any matches found in vector of animalsWords

    string Top_Results[10];
    int SearchResults;

    cout << endl << "Type keys and watch what happens. Type capital Z to quit." << endl;

    while ((k = getch()) != 'Z') 
    {

        // Tests for a backspace and if pressed deletes 
        if ((int)k == 127) 
        {
            if (word.size() > 0) 
            {
                word = word.substr(0, word.size() - 1);
            }
        }

        else 
        {
            // Makes sure a letter was pressed
            if (!isalpha(k)) 
            {
                cout << "Letters only!" << endl;
                continue;
            }

            if ((int)k >= 97) 
            {
                k -= 32;
            }
            word += k; // append char to word
        }

      // Timer for the amount of time it takes to return word suggestions
       Timer Auto_Suggestion;   

       Auto_Suggestion.Start();
       matches = L1.Find(word);
       Auto_Suggestion.End();

       SearchResults = matches.size();


        if ((int)k != 32) // if k is not a spacebar
        { 
            cout << "Keypressed: " << k << " = " << (int)k << endl;
            cout << "Current Substr: " << word << endl;
            cout << SearchResults << " words found in " << Auto_Suggestion.Seconds() << " seconds" << endl;

            
            if (matches.size() >= 10)     // This prints out Top Ten results
            {
                for (int i = 0; i < 10; i++)
                {
                    Top_Results[i] = matches[i];
                    cout << Top_Results[i] << " ";
                }
            }

            else
            {
                for (int j = 0; j < matches.size(); j++)
                {
                    Top_Results[j] = matches[j];
                    cout << Top_Results[j] << " ";
                }
            }

            cout << endl << endl;
        }
    }

    return 0;
}
