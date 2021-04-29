/*****************************************************************************
*  Author:             Faith Howell
*    Email:            faith-howell@outlook.com
*    Label:            P01
*    Title:            P01 - Resizing the Stack
*    Course:           CMPS 3013
*    Semester:         Spring 2021
*    Description: 
*           This program is used to resize an array. To do so, the program 
*           will read the values from the file nums.dat. The program then 
*           checks if each value is even or odd. If even, the value will be
*           pushed and if odd, the program *will remove the last EVEN value 
*           from the stack.

    Usage:
*           - $ ./ main.cpp
*           - $ ./ nums_test.dat
*           - $ ./ output.txt
*
*    Files:
*           main.cpp          : driver program
*           nums_test.dat     : Input file
*           output.txt        : Output file   
 ******************************************************************/


#include <iostream>
#include <fstream>

using namespace std;


class ArrayStack{
  private:
    int *A;                     // Pointer
    int Top;                    // Top of Stack
    int size;                   // Stack size
    int numofResizes;           // Num of times stack resizes
    int mSize;                  // maximum size of stack
    
public:
 

 


/**
 *  Public :  ArrayStack
 *
 * Description:
 *            Default Constructor
 *
 * Params:
 *          - None
 *
 * Returns:
 *          - NULL
 */

ArrayStack(){
 size = 10;
 A = new int[size];
 Top = -1;
 mSize = size;
 numofResizes = 0;
}

/**
 * Stack constructor
 * Description:
 *    Inits an array of ints to a specified size and sets our top
 * Params:
 *    int s : integer size
 */
ArrayStack(int s){

 size = s;
 A = new int[s];
 Top = -1;
 mSize = size;
 numofResizes = 0;

}

/**
 * Empty
 * Description:
 *    Is stack empty
 * Params:
 *    void
 * Returns:
 *    bool : true = empty
 */
bool Empty(){
  return Top <= -1;
}

/**
 * Full
 * Description:
 *    Is stack full
 * Params:
 *    void
 * Returns:
 *    bool : true = full
 */
bool Full(){
  return (Top >= size - 1);
}

//Faith Howell
/**
 * Pop
 * Description:
 *    Removes top of stack and returns it
 * Params:
 *    void
 * Returns:
 *     int : item on stack
 */
int Pop(){


 if (!Empty())
    {
        checkResize();
        return A[Top--];
    }

    return -99; // sentinel value
  }
    
    /**
 * Print
 * Description:
 *    Prints data to output file in order
 * Params:
 *    int lrgest = largest size
 * Returns:
 *     void
 */
    void Print()
  {

      for (int i = 0; i <= Top; i++) 
        {
            cout << A[i] << " ";
        }

        cout << endl;
    
    
  }


/**
 * Push
 * Description:
 *    Adds item to top of stack
 * Params:
 *    int val : integer size
 * Returns:
 *     bool : true = success
 */
bool Push(int x){

    A[++Top] = x;
    checkResize();
    return true;

  }


/**
	 * getnumOfResizes
	 * Description:
	 *   Displays amount of time the Stack resizes
	 * Params:
	 *    void
	 * Returns:
	 *    void
*/
  double getnumOfResizes()
	{
		 return numofResizes;
	}


/**
	 * ContainerGrow
	 * Description:
	 *   Resizes stack by 1.5 times
	 * Params:
	 *    void
	 * Returns:
	 *    void
*/
void ContainerGrow()
  {
    int new_size = size * 1.5; 
		int *B = new int[new_size]; 
		for (int i = 0; i < size; i++)
		{
			B[i] = A[i];
		}

    delete[] A;                         

    size = new_size;                        

    A = B;  

      if (size > mSize)
        {
            mSize = size;
        }
	
  }

	/**
	 * ContainerShrink
	 * Description:
	 *            Resizes stack by 0.5 times
	 * Params:
	 *             void
	 * Returns:
	 *             void
	 */
void ContainerShrink()
	{
    int newSize = size / 2;                // halves size of original
    if (newSize < 10)
    {
        newSize = 10;
    }
    int* B = new int[newSize];             // allocate new memory

    for (int i = 0; i <= Top; i++)
    {                                      // copy values to new array
        B[i] = A[i];
    }

    delete[] A;                            // delete old array

    size = newSize;                        // save new size

    A = B;                                 // reset array pointer
  }

 /**
	 * checkResize
	 * Description:
	 *   Checks if stack needs to be resized
	 * Params:
	 *    void
	 * Returns:
	 *    void
	 */
  void checkResize()
	{
    if (Full())
    {
        ContainerGrow();                   // Call this function to make it shrinks
        numofResizes++;                    // increments times resized
    }
    else if (Top < (size / 2) && size > 10)
    {
        ContainerShrink();                 // Call this function to make it grows
        numofResizes++;                    // increments times resized
    }

	}

// Retrieve the current Stack Size
int get_stackSize()
    {
        return size;
    }


// Retrieve the Maximum Stack Size variable
int get_maxSize()
    {
        return mSize;
    }


// Retrieve the # of times Resizing occured
int get_Resize()
    {
        return numofResizes;
    }


// Retrieve the top of the stack
int get_Top()
    {
        return Top;
    }

};

int main() {
   
  ArrayStack S1; 

  ifstream fin;
  ofstream outfile;


	fin.open("input_data.txt");

   outfile.open ("stack_out.dat");
	
   

	int nums;
	
	while (!(fin.eof()))
	{
    fin>> nums;

		if ( nums % 2 == 0 )
		{
			S1.Push(nums);
			
		}
		else 
		{
			S1.Pop();
			
		}

	}


	     
   

    outfile <<"################################################################\n";
    outfile << "Program 1 - Resizing the Stack\n";
    outfile << "CMPS 3013\n";
    outfile << "Faith Howell\n";

    outfile <<endl;
   
    outfile << "Max Stack size: " << S1.get_maxSize() << endl;
    outfile << "End Stack size: " << S1.get_stackSize() << endl;
    outfile << "Stack Resized:  " <<S1.get_Resize()<<" "<< "times"<<endl;
    outfile <<"################################################################\n";

    fin.close();
    outfile.close();

	
	
	return 0;
}
