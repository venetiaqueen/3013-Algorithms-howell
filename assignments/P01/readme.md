
## Program 1 - Resizing the Stack

### Faith Howell

### Overview

- The stack implementation  has a `Resize` method that ONLY will make the stack larger as we add items. 
- This means that the stack will never shrink if we remove many items. 
- We should probably remedy this issue.

#### Stack Resizing

- Full and Empty are determined by number of items in stack vs current stack size.
- This obviously gives us a ratio. So if I have a stack of size `50` and it has `17` items in it, then its `0.34` percent full. 
- You will resize your stack when it gets too full, or too empty. But what is `too full` or `too empty` and how much do we resize it by??
- Those parameters are determined by command line parameters entered when you run your program. 
- For testing, and to get up and running (if you don't know about `argc` and `argv`) simply use the following thresholds to resize your stack:
  - Too Full = 100% meaning no extra slots available in your array. 
  - Too Empty = 15% meaning in a stack of 100, if you get down to 15 items you need to shrink your stack.
  - Enlarging = Double the size of the stack.
  - Shrinking - Cut the size of the stack in half. 
- When you do use command line params, your program should expect 0 (which implies use defaults) or 4 params (in this order):
  - Too Full Threshold : a real number like .85, .77,  or 1.0  (threshold to grow)
  - Too Empty Threshold: a real number like .15, .20, or 0.0  (threshold to shrink)
  - Enlarging Threshold: a real number like 2.0 (double size), or 1.5 or 1.75 (how much to grow)
  - Shrinking Threshold: a real number like .5 or .75 or .25  (how much to shrink)
- If you want to handle a param count of other than 0 or 4, that would be a nice touch. 
- One hard rule: Never let your stack get below **size 10**.
- Rename `Resize` method to be `ContainerGrow`.
- Add a `ContainerShrink` method.
- A third method: `CheckResize` could be a good addition. This method would calculate the ratios then call appropriated resize method if necessary. 
- Make sure you comment your code.

#### Testing Your Code

- You will read numbers from the file [nums_test.dat](./nums_test.dat).
- If a number is even, push it onto the stack. 
- If a number is odd, perform a pop operation removing the last even value from the stack. 
- Don't let your stack get smaller than **10** (our starting stack size).
- You need to keep track of the following:
  - the **max size** the stack ever reached
  - **how many times** the stack was resized (grown or reduced)
  - **final size** of stack when program completed


### Files

|  #  | File                           | Description                          |
| :-: | ------------------------------ | ------------------------------------ |
|  1  | [main.cpp](https://github.com/venetiaqueen/3013-Algorithms-howell/blob/master/assignments/P01/main.cpp)           | The main cpp             |
|  2  | [input.data](https://github.com/venetiaqueen/3013-Algorithms-howell/blob/master/assignments/P01/input.data) | Input file to test the code          |
|  5  | [stack_out.dat](https://github.com/venetiaqueen/3013-Algorithms-howell/blob/master/assignments/P01/stack_out.dat)       | The output file to print the results |
|  6  | [Banner](https://github.com/venetiaqueen/3013-Algorithms-howell/blob/master/assignments/P01/P01%20Banner)               | Banner for Assignment                |
```
