#include <iostream>
#include <cstdlib>
#include <vector>
#include <time.h>

using namespace std;

struct Person{
    string name;
    int credit,
            bet;
};

Person person;
vector<int> bets{
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

vector<string> menus{"Mulai", "Lihat riwayat", "Keluar"};
vector<string> histories;

int main (){
    int player,
            enemy,
            menu,
            win = 0,
            lost = 0,
            draw = 0,
            credit = 0,
            bet;
    char repeat;
    string name;

    srand(time(0));
    begin:
    cout << "================ Lempar Dadu Haram !!! ================\n\n";

    name:
    cout << "Masukkan nama : ";
    getline(cin, name);

    if (!name.empty()) {
        person.name = name;
    } else {
        system("cls");
        goto name;
    }


    credit:
    cout << "Masukkan saldo (min Rp 100) : Rp ";
    cin >> credit;

    if (credit >= 100){
        person.credit = credit;
    } else {
        system("cls");
        goto credit;
    }

    system("cls");
    menu:
    for (int i = 0; i < menus.size(); i++) {
        cout << i + 1 << ". " << menus[i] << "\n";
    }

    cout << "\nPilih menu (1 - " << menus.size() << ") : ";
    cin >> menu;

    system("cls");

    switch (menu) {
        case 1:
            if (person.credit == 0) {
                goto credit;
            } else {
                bet:
                player = rand() % 6 + 1;
                enemy = rand() % 6 + 1;

                cout << "Daftar taruhan : ";
                for (int i = 0; i < bets.size(); i++) {
                    if (credit >= bets[i] || person.bet >= bets[i]) {
                        cout << i + 1 << ". Rp " << bets[i] << "\n";
                    }
                }

                cout << "\nPilih taruhan : ";
                cin >> bet;

                if (bet > 0 && bet <= bets.size()) {
                    person.bet = bets[bet - 1];
                } else {
                    system("cls");
                    goto bet;
                }

                system("cls");

                if (player > enemy) {
                    person.credit = person.credit + person.bet;
                    cout << "Saldo : " << person.credit << "\n\n";
                    cout << "Player : " << player << "\n";
                    cout << "Enemy : " << enemy << "\n";
                    cout << "Hasil : Menang\n\n";
                    histories.push_back("Menang");
                } else if (player < enemy) {
                    person.credit = person.credit - person.bet;
                    cout << "Saldo : " << person.credit << "\n\n";
                    cout << "Player : " << player << "\n";
                    cout << "Enemy : " << enemy << "\n";
                    cout << "Hasil : Kalah\n\n";
                    histories.push_back("Kalah");
                } else {
                    person.credit = person.credit;
                    cout << "Saldo : " << person.credit << "\n\n";
                    cout << "Player : " << player << "\n";
                    cout << "Enemy : " << enemy << "\n";
                    cout << "Hasil : Imbang\n\n";
                    histories.push_back("Imbang");
                }

                cout << "Ulangi permainan (y/t) : ";
                cin >> repeat;

                system("cls");

                if (repeat == 'y') {
                    if (person.credit == 0) {
                        goto credit;
                    } else {
                        goto bet;
                    }
                } else {
                    goto menu;
                }
            }

            break;
        case 2:
            cout << "======== Riwayat Permainan ========\n\n";

            if (histories.size() > 0){
                for (int i = 0; i < histories.size(); i++) {
                    // cout << i + 1 << ". " << histories[i] << "\n";

                    if (histories[i] == "Menang") {
                        win = 1 + win;
                    } else if (histories[i] == "Kalah") {
                        lost = 1 + lost;
                    } else {
                        draw = 1 + draw;
                    }
                }

                cout << "Menang : " << win << "\n";
                cout << "Kalah : " << lost << "\n";
                cout << "Imbang : " << draw << "\n";
            } else {
                cout << "Belum ada riwayat permainan!\n\n";
            }

            cout << "Kembali ke menu? (y/t) : ";
            cin >> repeat;

            if (repeat == 'y') goto menu;
            break;
        case 3:
            abort();
            break;
        default:
            cout << "Tidak ada pilihan menu!";
            break;
    }
}
