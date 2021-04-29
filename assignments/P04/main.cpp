/*
*  Author:             Faith Howell
*    Email:            faith-howell@outlook.com
*    Label:            P04
*    Title:            P04 - Processing in Trie Tree Time
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
#include<algorithm>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

 #define CHAR_SIZE 26     //defining character size
/*
    Struct Name: TrieNode
 
    Description:
      - Node used to hold both string and pointer
 
    Public Methods:
 	    - bool leaf
 	    - TrieNode* Next
 
    Private Methods:
        None
 
    Usage:
  	    - Creates node for a Linked List
 
 */



struct TrieNode
{
    bool leaf;
    TrieNode* C[CHAR_SIZE];
    string word;

    TrieNode()
    {
        //leaf = NULL;
        word = "";
           for (int i = 0; i < CHAR_SIZE; i++)
        {
            this->C[i] = nullptr;
        }

    }

};

/*
    Class Name: Trie
 
    Description:
        - Implements a  Tree made up of TrieNodes. 
        - Has a root variable
     
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

class Trie
{
protected:
   TrieNode* root;
   vector<string> Results;

public:

    Trie()
    {
       
        root = new TrieNode();
    }

/*
   Public : Insert_Data(Trie* w)

   Description:
      - Receives a wordNode and loads it into the linked list

   Params:
       TrieNode* w

   Returns:
       None
*/
    void Insert_Data(string w)
    {
        TrieNode* current = root;

        for (int i = 0; i < w.size(); i++)
        {
            if (current->C[w[i] - 65] == nullptr)
            {
                current->C[w[i] - 65] = new TrieNode();
            }

            current = current->C[w[i] - 65];
        }

        current->leaf = true;
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


       TrieNode* current = root;
        
       if (Results.size()!=0)
       {                
                Results.clear();
            }
      for (int i = 0; i < typed.length(); i++)
        {
            current = current->C[typed[i] - 65];          
       }

        return Results;                      
    }



 /*
    Constructor : Trie()
 
    Description:
    - Initialize with default values.
 
    Params:
    - None
 
    Returns:
    - None
 */
};

int main() 
{
    Trie L1;
    vector<string> animalsWords;      // Placeholder Dictionary to read in the words.txt data


    char k;                                 // Hold the character being typed.
    string word = "";                       // Use to Concatenate letters.
    vector<string> Matches;                 // Any matches found in vector of animals_names data.

    string Top_Results[10];                 // Initializing 10 words to print.
    int SearchResults;                      // integer SearchResults.

    cout << "Type keys and watch what happens. Type capital"<< " Z to quit." ;
         cout << endl;

    while ((k = getch()) != 'Z')            
    {
        if ((int)k == 127)         
        {
            if (word.size() > 0)
            {
                word = word.substr(0, word.size() - 1);
            }
        }

        else
        {
            if (!isalpha(k))                // Making sure  letter was pressed.
            {
                cout << "Letters only!\n";
                continue;
            }

            if ((int)k >= 97)               // Making sure its lowercase.
            {
                k -= 32;                    // Make the input word  capital letters.
            }
        }
        word += k;                          // Append character to word.

        Timer Auto_Suggestion;              // Timer for word suggestions
        Auto_Suggestion.Start();
        Matches = L1.Find(word);
        Auto_Suggestion.End();

        SearchResults = Matches.size();

        if ((int)k != 32)                  
        {
            cout << "Keypressed: "<< k << " = "
              << (int)k << endl;
            cout << "Current Substr: "       << word  << endl;
            cout<< SearchResults << " words found in "  << 
            Auto_Suggestion.Seconds() << " Seconds"  << endl;

            if (Matches.size() >= 10)       // Prints out the top 10 results.
            {
                for (int i = 0; i < 10; i++)
                {
                    Top_Results[i] = Matches[i];
                    cout << Top_Results[i] << " ";
                }
            }
            else
            {
                for (int j = 0; j < Matches.size(); j++)
                {
                    Top_Results[j] = Matches[j];
                    cout << Top_Results[j] << " ";
                }
            }

            cout<< endl
                 << endl;
        }
    }

    return 0;
}
