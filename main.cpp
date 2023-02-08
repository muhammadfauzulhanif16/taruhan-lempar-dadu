#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <time.h>

using namespace std;

struct Player{
  string name;
  int credit,
    diceGuess,
    win,
    bet;
};

vector<Player> players;

vector<int> moneys{
  100,
  200,
  500,
  1000,
  2000,
  5000,
  10000,
  20000,
  50000,
  75000,
  100000,
};

vector<string> menus{
  "Mulai", "Riwayat", "Keluar",
};

int main() {
  string menuNumber, playerAmount, playerName, creditAmount, diceGuess, betAmount;
  int betTotal = 0, diceEye = 0;
  char repeat;

  srand(time(0));

  menu:
    cout << "================ Taruhan Lempar Dadu ================\n\n";

    for (int i = 0; i < menus.size(); i++) {
      cout << i + 1 << ". " << menus[i] << "\n";
    }
      
    cout << "\nPilih menu (1 - " << menus.size() << ") : ";
    getline(cin, menuNumber);

    system("cls");

    if (!menuNumber.empty() && 
      stoi(menuNumber) > 0 && 
      stoi(menuNumber) <= menus.size()
    ) {
      switch (stoi(menuNumber)) {
        case 1:
          data:
            cout << "======== Data Pemain ========\n\n";

            cout << "==== Pemain ====\n";
            cout << "Masukkan jumlah pemain (1 - 6) : ";
            cin >> playerAmount;

            system("cls");

            if (!playerAmount.empty() && 
              stoi(playerAmount) > 0 && 
              stoi(playerAmount) <= 6
            ) {
              for (int i = 1; i <= stoi(playerAmount); i++) {
                name:
                  cout << "Masukkan nama pemain ke-" << i << " : ";
                  getline(cin, playerName);

                  if (playerName.empty()) {
                    system("cls");
                    goto name;
                  }
                    
                  players.push_back({playerName, 0, 0, 0, 0});

                  // cin.get();
                  // system("cls");
              }
            } else {
              system("cls");
              goto data;
            }

          system("cls");

          credit:
            for (int i = 0; i < players.size(); i++) {
              cout << "==== Saldo ====\n";
              for (int j = 0; j < moneys.size(); j++) {
                cout << j + 1 << ". Rp " << moneys[j] << "\n";
              }

              cout << "\nMasukkan saldo pemain ke-" << i + 1 << " (" << players[i].name << ") : Rp ";
              cin >> creditAmount;

              system("cls");

              if (!creditAmount.empty() && 
                stoi(creditAmount) >= moneys.front() && 
                stoi(creditAmount) <= moneys.back() && 
                stoi(creditAmount) % moneys.front() == 0
              ) {
                players[i].credit = stoi(creditAmount);
              } else {
                system("cls");
                goto credit; 
              }
            }

          bet:
            for (int i = 0; i < players.size(); i++) {
              cout << "==== Taruhan ====\n";
              for (int j = 0; j < moneys.size(); j++) {
                if (moneys[j] <= players[i].credit) {
                  cout << j + 1 << ". Rp " << moneys[j] << "\n";
                }              
              }

              cout << "\nMasukkan taruhan pemain ke-" << i + 1 << " (" << players[i].name << " | Rp " << players[i].credit << ") : Rp ";
              cin >> betAmount;

              system("cls");

              if (!betAmount.empty() && 
                stoi(betAmount) >= moneys.front() &&  
                stoi(betAmount) <= players[i].credit && 
                stoi(betAmount) % moneys.front() == 0
              ) {
                players[i].bet = stoi(betAmount);
                players[i].credit = players[i].credit - stoi(betAmount);                
              } else {
                system("cls");
                goto bet; 
              }
            }

          // play:  
            cout << "======== Mulai Permainan ========\n";
            cout << "Nama | Saldo | Taruhan | Menang : Tebak mata dadu\n\n";

            guess:
              for (int i = 0; i < players.size(); i++) {
                cout << "→ " << players[i].name << "\t|\tRp " << players[i].credit << "\t|\tRp " << players[i].bet << "\t|\t" << players[i].win << "\t:\t";
                cin >> diceGuess;

                if (diceGuess.empty() && 
                  stoi(diceGuess) < 1 &&
                  stoi(diceGuess) > 6
                ) {
                  system("cls");
                  goto guess;
                }

                players[i].diceGuess = stoi(diceGuess);
              }

            for (int i = 0; i < players.size(); i++) {
              betTotal = players[i].bet + betTotal;
            }

            diceEye = rand() % 6 + 1;
            cout << "\nHasil mata dadu : " << diceEye;

            for (int i = 0; i < players.size(); i++) {
              if (players[i].diceGuess == diceEye) {
                cout << "\n\nSelamat! " << players[i].name << " mendapatkan Rp " << betTotal;
                players[i].credit = players[i].credit + betTotal;
                players[i].bet = 0;
                players[i].win = players[i].win + 1;
                betTotal = 0;
              }
            }

          cout << "\n\nMulai permainan kembali? (y/t) : ";
          cin >> repeat;

          system("cls");

          if (repeat == 'y') goto bet;
          else goto menu;

          break;
        default:
          break;
      }
    }
    else
    {
      system("cls");
      goto menu;
    }
}
