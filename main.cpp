// Garrett, Brunsch
// Lab #2 Recursion S25
// CS_136_14728SP25P
// Due 3/2/25

#include <iostream>
#include <iomanip>
using namespace std;

enum MenuChoice { RECURSIVE_ADD = 1, RECURSIVE_MULTIPLY, QUIT };

void calcRecursiveAdd(int n, int current, double& total);
void calcRecursiveMultiply(int n, int current, int& total);
void displayMenu();
void clearInputError();
void processSeriesCalculation(MenuChoice choice);

int main()
{
    cout << fixed << setprecision(6); // 6 used to match the sample formatting from classroom module "...=1.787302"

    /* NOTE: As a consequence of only using manipulators here:
    * Trailing zeroes will be present with whole numbers in the ADD case, but not MULTIPLY
    * This is because case "ADD" uses a double while case "MULTIPLY" uses an int and setprecision only targets floating points
    * This trade-off is intentional because it avoids the extra computational expenses noted in previous feedback
    */ 
        
    int userChoice = 0;
    int n = 0;

    do
    {
        displayMenu();
        cin >> userChoice;

        switch (userChoice)
        {
            //Fall-through preferred to avoid repeating logic for prompting and processing user responses
        case RECURSIVE_ADD:
        case RECURSIVE_MULTIPLY:
            processSeriesCalculation(static_cast<MenuChoice>(userChoice));
            break;
        case QUIT:
            cout << "Now exiting program...\n\n";
            break;
        default:
            clearInputError();
        }
    } while (userChoice != QUIT);

    return 0;
}

void displayMenu()
{
    cout << "\n\n --- Main Menu ---\n"
        "1. Recursive Add Series\n"
        "2. Recursive Multiply Series\n"
        "3. Quit\n"
        "Choice: ";
}

void clearInputError()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Invalid entry. Please double check the input and try again\n";
}

// Recursive function to add first n terms of series
// eg: 1 + 1/(1+2) + ... + 1/((n-1)+n)
void calcRecursiveAdd(int n, int current, double& total)
{
    if (current == 1)
    {
        cout << "1"; // 1 directly used instead of "current" to avoid re-calling cout manipulators
        total = 1.0;
    }
    else
    {
        calcRecursiveAdd(n, current - 1, total);
        cout << "+1/(" << (current - 1) << "+" << current << ")"; // Based on provided formula of 1/((n-1)+n)
        total += 1.0 / ((current - 1) + current);
    }

    if (current == n)
    {
        cout << "=" << total << "\n";
    }
}

// Recursive function to produce sum of the first n terms of series
// eg: (n*n) + ((n-1)*(n-1)) + ... + 1
void calcRecursiveMultiply(int n, int current, int& total)
{
    if (current == 1)
    {
        cout << "1";
        total = 1;
    }
    else
    {
        cout << "(" << current << "*" << current << ")";

        // Course example showed extra space only on last term. This if/else block is to emulate that formatting
        if (current == 2)
        {
            cout << " +";
        }
        else
        {
            cout << "+";
        }
        calcRecursiveMultiply(n, current - 1, total);
        total += current * current;
    }
    if (current == n)
    {
        cout << " =" << total << "\n";
    }
}

void processSeriesCalculation(MenuChoice choice)
{
    int n = 0;
    cout << "Enter the number of terms: ";
    cin >> n;

    if (cin.fail())
    {
        clearInputError();
    }

    if (n > 0) 
    {
        if (choice == RECURSIVE_ADD) 
        {
            double sum = 0.0;
            calcRecursiveAdd(n, n, sum);
        }
        else if (choice == RECURSIVE_MULTIPLY)
        {
            int product = 0;
            calcRecursiveMultiply(n, n, product);
        }
    }
    else 
    {
        cout << "Entered value must be a number > 0\n";
    }
}

/*
TEST CASE 1: Valid menu (1) + Valid positive input
 --- Main Menu ---
1. Recursive Add Series
2. Recursive Multiply Series
3. Quit
Choice: 1
Enter the number of terms: 5
1+1/(1+2)+1/(2+3)+1/(3+4)+1/(4+5)=1.787302

TEST CASE 2: Valid menu (1) + Valid non-positive input
 --- Main Menu ---
1. Recursive Add Series
2. Recursive Multiply Series
3. Quit
Choice: 1
Enter the number of terms: 0
Entered value must be a number > 0

TEST CASE 3: Valid menu (1) + Invalid input
 --- Main Menu ---
1. Recursive Add Series
2. Recursive Multiply Series
3. Quit
Choice: 1
Enter the number of terms: abc
Invalid entry. Please double check the input and try again
Entered value must be a number > 0

TEST CASE 4: Valid menu (2) + Valid positive input
 --- Main Menu ---
1. Recursive Add Series
2. Recursive Multiply Series
3. Quit
Choice: 2
Enter the number of terms: 3
(3*3)+(2*2) +1 =14

TEST CASE 5: Valid menu (2) + Valid non-positive input
 --- Main Menu ---
1. Recursive Add Series
2. Recursive Multiply Series
3. Quit
Choice: 2
Enter the number of terms: 0
Entered value must be a number > 0

TEST CASE 6: Valid menu (2) + Invalid input
 --- Main Menu ---
1. Recursive Add Series
2. Recursive Multiply Series
3. Quit
Choice: 2
Enter the number of terms: def
Invalid entry. Please double check the input and try again
Entered value must be a number > 0

TEST CASE 7: Valid menu (3) - Quit
 --- Main Menu ---
1. Recursive Add Series
2. Recursive Multiply Series
3. Quit
Choice: 3
Now exiting program...

TEST CASE 8: Invalid menu
 --- Main Menu ---
1. Recursive Add Series
2. Recursive Multiply Series
3. Quit
Choice: xyz
Invalid entry. Please double check the input and try again
*/
