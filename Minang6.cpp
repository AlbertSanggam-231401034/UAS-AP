#include <iostream>
#include <map>
#include <string>
#include <iomanip> // Untuk pengaturan format keluaran
#include <vector>  // Untuk penggunaan vector

using namespace std;

struct MenuItem {
    string name;
    double price;
};

class Restaurant {
private:
    const int menuSize = 10;
    MenuItem menu[10] = {
        {"Nasi + Ayam (Goreng/Bakar/Gulai)", 15000},
        {"Nasi + Lele (Goreng/Bakar)", 12000},
        {"Nasi + Nila (Goreng/Bakar/Gulai)", 18000},
        {"Nasi + Pari (Goreng/Bakar)", 18000},
        {"Nasi + Rendang *Best Seller*", 20000},
        {"Nasi + Dadar", 10000},
        {"Nasi + Cumi Sambal", 15000},
        {"Nasi + Udang Sambal", 15000},
        {"Nasi + Kepala Ikan *Best Seller*", 20000},
        {"Nasi Putih", 5000}
    };
    map<string, int> orders;
    double total_spent;

public:
    Restaurant() : total_spent(0) {}

    void showMenu() {
        cout << "====================Menu Makanan======================" << endl;
        for (int i = 0; i < menuSize; ++i) {
            cout << setw(2) << i + 1 << ". " << setw(40) << left << menu[i].name
                 << "Rp." << setw(6) << right << fixed << setprecision(0) << menu[i].price << endl;
        }
    }

    void addOrder(int choice, int quantity) {
        if (choice < 1 || choice > menuSize) {
            cout << "Makanan Tidak Ada di Menu" << endl;
            return;
        }
        orders[menu[choice - 1].name] += quantity;
        total_spent += menu[choice - 1].price * quantity;
    }

    void addExtra(char type, int quantity) {
        string extra;
        double price = 0;
        if (type == 'D' || type == 'd') {
            extra = "Dadar";
            price = 3000;
        } else if (type == 'P' || type == 'p') {
            extra = "Perkedel";
            price = 2000;
        } else {
            cout << "Pilihan tidak valid." << endl;
            return;
        }
        orders[extra] += quantity;
        total_spent += price * quantity;
    }

    void showTotal() {
        cout << "=======================================" << endl;
        cout << "           TOTAL BAYAR                 " << endl;
        cout << "=======================================" << endl;
        cout << "         #RIWAYAT PESANAN#            " << endl;
        cout << "=======================================" << endl;

        for (const auto& pair : orders) {
            double itemPrice = findPrice(pair.first);
            cout << pair.first << " (" << pair.second << "x) - Rp." << pair.second * itemPrice << endl;
        }

        cout << "---------------------------------------" << endl;
        cout << "Total Bayar: Rp." << total_spent << endl;
        cout << "Terima kasih! Silakan datang kembali." << endl;
    }

    double findPrice(const string& itemName) {
        for (int i = 0; i < menuSize; ++i) {
            if (menu[i].name == itemName) {
                return menu[i].price;
            }
        }
        if (itemName == "Dadar") return 3000;
        if (itemName == "Perkedel") return 2000;
        return 0; // fallback
    }
};

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    Restaurant* restaurant = new Restaurant();
    int choice, quantity;
    char addMore, addExtra;

    do {
        clearScreen();

        cout << "=============================================================" << endl;
        cout << "                      SELAMAT DATANG                         " << endl;
        cout << "                             DI                              " << endl;
        cout << "                    R.M PRIADI CHANIAGO                      " << endl;
        cout << "                        PUTRA MINANG                         " << endl;
        cout << " *Salamaik datang di Rumah Makan Pridai Chaniago Anak Minang*" << endl;
        cout << "=============================================================" << endl;

        restaurant->showMenu();

        cout << "Masukkan Makanan Pilihan Anda: ";
        cin >> choice;
        cout << "Masukkan Jumlah Pesanan: ";
        cin >> quantity;

        restaurant->addOrder(choice, quantity);

        cout << "Apakah Anda ingin menambahkan tambahan makanan? (Y/Ya or T/Tidak)? ";
        cin >> addExtra;
        addExtra = toupper(addExtra);

        while (addExtra == 'Y') {
            cout << "Pilih tambahan makanan (D. Dadar Rp.3.000 / P. Perkedel Rp.2.000): ";
            cin >> addExtra;
            cout << "Masukkan jumlah pesanan tambahan: ";
            cin >> quantity;

            restaurant->addExtra(addExtra, quantity);

            cout << "Apakah Anda ingin menambahkan tambahan makanan lagi? (Y/Ya or T/Tidak)? ";
            cin >> addExtra;
            addExtra = toupper(addExtra);
        }

        cout << "Apakah anda masih ingin memesan? (Y/Ya or T/Tidak)? ";
        cin >> addMore;
        addMore = toupper(addMore);

    } while (addMore == 'Y');

    clearScreen();
    restaurant->showTotal();

    delete restaurant;
    return 0;
}
