#include <iostream>
using namespace std;

int main() {
    int secretNumber = 7;
    int guess;
    int tries = 0;
    
    cout << "Guess the number (1-10): ";
    
    while (tries < 3) {
        cin >> guess;
        tries++;
        
        if (guess == secretNumber) {
            cout << "You won!" << endl;
            return 0;
        }
        
        if (guess < secretNumber) {
            cout << "Too low! ";
        } else {
            cout << "Too high! ";
        }
        
        if (tries < 3) {
            cout << "Try again: ";
        }
    }
    
    cout << "\nGame over! The number was " << secretNumber << endl;
    return 0;
}
