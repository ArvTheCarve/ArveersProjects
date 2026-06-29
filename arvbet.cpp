#include <algorithm>

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

class CasinoUser {
private:
  string name;
  double balance;

public:
  CasinoUser(string n, double b) : name(n), balance(b) {}

  double getBalance() const { return balance; }
  string getName() const { return name; }

  void updateBalance(double amount) { balance += amount; }

  bool canAfford(double amount) { return balance >= amount; }
};

struct Transaction {
  string type;
  double amount;
};

vector<Transaction> history;

void sleepMs(int milliseconds) {
#ifdef _WIN32
  Sleep(milliseconds);
#else
  usleep(milliseconds * 1000);
#endif
}

void logAction(CasinoUser &user, string type, double amount) {
  user.updateBalance(amount);
  history.push_back({type, amount});
}

double calculateLoyaltyBonus(int gamesPlayed) {
  if (gamesPlayed <= 0)
    return 0;
  if (gamesPlayed == 1)
    return 5.0;
  return 1.1 * calculateLoyaltyBonus(gamesPlayed - 1);
}

void findMaxWin() {
  if (history.empty()) {
    cout << "No transactions yet.\n";
    return;
  }

  double maxWin = -1e9;
  for (size_t i = 0; i < history.size(); i++) {
    if (history[i].amount > maxWin) {
      maxWin = history[i].amount;
    }
  }
  cout << "Your highest single transaction impact: " << maxWin << " coins."
       << endl;
}

void playHorseRacing(CasinoUser &user) {
  double bet;
  cout << "\n--- Horse Racing ---\n";
  cout << "Current Balance: " << user.getBalance() << "\n";
  cout << "Enter bet amount: ";
  cin >> bet;

  if (!user.canAfford(bet)) {
    cout << "Insufficient coins!\n";
    return;
  }

  int horse;
  cout << "Pick a horse (1-5): ";
  cin >> horse;

  cout << "\nThe race is starting!\n";
  int positions[5] = {0, 0, 0, 0, 0};
  bool finished = false;
  int winner = -1;

  while (!finished) {
    // Clear screen (simple way for many terminals) or just print new lines
    // somewhat tricky to do clean animation in standard C++ without ncurses,
    // but we can just print updates.
    // Better visual: print tracks repeatedly.

    // Simple "movement" animation
    for (int i = 0; i < 5; ++i) {
      if (positions[i] < 20) {      // Race length 20
        positions[i] += rand() % 3; // Move 0-2 steps
      }
      if (positions[i] >= 20 && winner == -1) {
        winner = i + 1;
        finished = true;
      }
    }

// Display track
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    cout << "\n--- RACE TRACK ---\n";
    for (int i = 0; i < 5; ++i) {
      cout << "Horse " << i + 1 << " |";
      for (int j = 0; j < 20; ++j) {
        if (j == positions[i])
          cout << (i + 1); // Horse number
        else
          cout << "-";
      }
      cout << "|";
      if (winner == i + 1)
        cout << " WINNER!";
      cout << "\n";
    }

    sleepMs(300);
    if (finished)
      break;
  }

  cout << "\nThe winner is Horse " << winner << "!\n";

  if (horse == winner) {
    cout << "You won! Payout: " << bet * 2 << "\n";
    logAction(user, "Horse Racing Win", bet);
  } else {
    cout << "You lost " << bet << " coins.\n";
    logAction(user, "Horse Racing Loss", -bet);
  }
}

void playRoulette(CasinoUser &user) {
  double bet;
  cout << "\n--- Roulette ---\n";
  cout << "Enter bet amount: ";
  cin >> bet;

  if (!user.canAfford(bet)) {
    cout << "Insufficient coins!\n";
    return;
  }

  int choice;
  cout << "1. Red\n2. Black\nChoose: ";
  cin >> choice;

  cout << "Spinning the wheel...\n";
  for (int i = 0; i < 10; ++i) {
    cout << (i % 2 == 0 ? "RED " : "BLACK ") << rand() % 36 << "\r";
    cout.flush();
    sleepMs(100 + i * 20);
  }

  int result =
      rand() % 2; // 0 for Red, 1 for Black roughly for this simple logic?
  // Wait, original logic: int result = rand() % 2;
  // if ((choice == 1 && result == 0) || (choice == 2 && result == 1))
  // Implies result 0 is Red (choice 1), result 1 is Black (choice 2).

  string color = (result == 0) ? "RED" : "BLACK";
  cout << "\nBall landed on: " << color << "!\n";

  if ((choice == 1 && result == 0) || (choice == 2 && result == 1)) {
    cout << "Correct! You won " << bet << " coins.\n";
    logAction(user, "Roulette Win", bet);
  } else {
    cout << "Wrong color! Lost " << bet << " coins.\n";
    logAction(user, "Roulette Loss", -bet);
  }
}

void playLuckyWheel(CasinoUser &user) {
  cout << "\n--- Lucky Wheel ---\n";
  cout << "Cost per spin: 10 coins. Spin? (y/n): ";
  char c;
  cin >> c;
  if (c != 'y' && c != 'Y')
    return;

  double cost = 10;
  if (!user.canAfford(cost)) {
    cout << "Insufficient coins!\n";
    return;
  }

  cout << "Wheel is spinning...\n";
  const char *animation = "|/-\\";
  for (int i = 0; i < 20; ++i) {
    cout << " " << animation[i % 4] << " \r";
    cout.flush();
    sleepMs(100);
  }

  int spin = rand() % 100;
  double multiplier;
  if (spin < 50)
    multiplier = 0.5;
  else if (spin < 80)
    multiplier = 1.5;
  else if (spin < 95)
    multiplier = 3.0;
  else
    multiplier = 10.0;

  double win = cost * multiplier;
  cout << "\nWheel stopped at " << multiplier << "x! You got " << win
       << " coins.\n";
  logAction(user, "Lucky Wheel", win - cost);
}

void cashOut(CasinoUser &user) {
  ofstream outFile("cheque.txt");
  if (outFile.is_open()) {
    outFile << "**********************************************************"
            << endl;
    outFile << "*                     CASINO CHEQUE                      *"
            << endl;
    outFile << "**********************************************************"
            << endl;
    outFile << "*                                                        *"
            << endl;
    outFile << "*  Pay to the order of: " << left << setw(25) << user.getName()
            << "*" << endl;
    outFile << "*                                                        *"
            << endl;
    outFile << "*  Amount: " << setw(10) << fixed << setprecision(2)
            << user.getBalance() << " coins                         *" << endl;
    outFile << "*                                                        *"
            << endl;
    outFile << "*  Signature: __________________________                 *"
            << endl;
    outFile << "*                                                        *"
            << endl;
    outFile << "**********************************************************"
            << endl;
    outFile << "\n--- Detailed Transaction History ---\n";
    for (const auto &t : history) {
      outFile << left << setw(20) << t.type << ": "
              << (t.amount >= 0 ? "+" : "") << setw(10) << t.amount << endl;
    }
    outFile.close();
    cout << "Receipt generated in cheque.txt. Thank you for playing!\n";
  } else {
    cout << "Error writing to file.\n";
  }
}

int main() {
  srand(static_cast<unsigned int>(time(0)));
  string name;
  cout << "Welcome to the Online Casino!\n";
  cout << "Enter your name: ";
  getline(cin, name);

  CasinoUser player(name, 100.0);
  int gamesCount = 0;

  int choice;
  do {
    cout << "\n===== CASINO MENU (Balance: " << player.getBalance()
         << ") =====\n";
    cout << "1. Horse Racing\n";
    cout << "2. Roulette\n";
    cout << "3. Lucky Wheel\n";
    cout << "4. View Max Win (Search Algorithm)\n";
    cout << "5. Cash Out & Exit\n";
    cout << "Choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
      playHorseRacing(player);
      gamesCount++;
      break;
    case 2:
      playRoulette(player);
      gamesCount++;
      break;
    case 3:
      playLuckyWheel(player);
      gamesCount++;
      break;
    case 4:
      findMaxWin();
      break;
    case 5: {
      double bonus = calculateLoyaltyBonus(gamesCount);
      if (bonus > 0) {
        cout << "Recursive Loyalty Bonus: " << bonus << " coins added!\n";
        player.updateBalance(bonus);
      }
      cashOut(player);
      break;
    }
    default:
      cout << "Invalid choice.\n";
    }
  } while (choice != 5);

  return 0;
}
