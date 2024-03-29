# Binary Tree
Ericsson Schroeter
March 17, 2018

This program populates a binary search tree with a given file of integer data.
It then finds if the numbers within given ranges (provided in another file) are
even or not.

## How to compile 'evenSumRange.c' and 'balancedEvenSumRange.c':

There is a Makefile included in the submitted file.  Enter the command `make` in
while in the same directory of the source code file.  Two executables named
*evenSumRange* and *balancedEvenSumRange* will be created in the current directory.

If you would only like to compile one of the two files you can enter the command
`make unbalanced` to compile *evenSumRange.c* or `make balanced` to compile
*balancedEvenSumRange.c*.

## How to run evenSumRange executable:

Run `./evenSumRange <data-file> <range-file>` in the terminal after compiling.

## For the balancedEvenSumRange:

Run `./balancedEvenSumRange <data-file> <range-file>` in the terminal after
compiling.

`<data-file>`: The file containing the data to populate the BST.
`<range-file>`: The file containing the ranges to query the BST with.

## How to check results:

I used *diff* to compare my results with the test results to check if there were
any differences.  If you would like to do so yourself, send the printed results
to a text file like this: `./evenSumRange dataX rangeX > output.txt`.  Then
upon completion of the program you can run `diff evenSumX output.txt`.  If
nothing is printed to the screen when running this it means your results match
the *evenSumX* file.

*******************************************************************************
