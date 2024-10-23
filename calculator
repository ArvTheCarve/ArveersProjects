#include <iostream>

using namespace std;


int main() {

    int operation;

    float num1, num2;


    cout << "=== CALCULATOR ===\n";

    cout << "Menu:\n";

    cout << "1) Add\n";

    cout << "2) Subtract\n";

    cout << "3) Multiply\n";

    cout << "4) Divide\n";

    cout << "> Your choice: ";

    cin >> operation;


    cout << "Please enter the first number: ";

    cin >> num1;

    cout << "Please enter the second number: ";

    cin >> num2;


    switch (operation) {

    case 1:

        cout << "a + b equals " << (num1 + num2);
        break;

    case 2:

        cout << "a - b equals " << (num1 - num2);
        break;

    case 3:

        cout << "a * b equals " << (num1 * num2);
        break;
    case 4:

        if (num2 != 0)
            cout << "a / b equals " << (num1 / num2);
        else
            cout << "Cannot divide by 0! ";
        break;

    default:
        cout << "Invalid option: " << operation;
    }


    return 0;

}
