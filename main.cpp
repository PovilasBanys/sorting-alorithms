//Povilas Banys ISF 19-1
//ADS 3 laboratorinis darbas. 3 variantas
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <random>

using namespace std;
using namespace std::chrono;

void swap(unsigned int *xp, unsigned int *yp)
{
    int tem = *xp;
    *xp = *yp;
    *yp = tem;
}

int main()
{

    unsigned int seed = chrono::steady_clock::now().time_since_epoch().count();
    default_random_engine engine(seed);
    uniform_int_distribution<int> distr(1000, 9999);

    unsigned int data[200000];
    int data_count = 0, sort_count=0, key = 0;
    long long int compare_count = 0;
    int read = 0;
    int temp = 0;
    int max = 0;

    bool correct_number = false;

    srand(time(0));
    bool running = true;
    int choice = 0;
    int sorting_type = 0;
    int random_space = 0;

    while (running) {

        cout << "*--------------------------------------------------------------------------------------------*" << endl;
        cout << "1 - Isrinkimo sort metodas" << endl;
        cout << "2 - Iterpimo sort metodas" << endl;
        cout << "3 - Skaiciu generavimas" << endl;
        cout << "4 - Darbo pabaiga" << endl;
        cout << "*--------------------------------------------------------------------------------------------*" << endl;
        cout << "Iveskite pasirinkima: ";
        cin >> choice;


        if (choice == 1) {

            if (data_count == 0) {
                cout << "Bandoma rusiuoti su 0 duomenu, nutraukiama programa" << endl;
                exit(-1);
            }
            else {
                ifstream is("Pradiniai.txt");

                if (is.fail()) {
                    cout << "Failas neegzistuoja, programa nutraukiama" << endl;
                    exit(-2);
                }
                else {
                    for (int i = 0; i < data_count; i++) {
                        is >> read;
                        data[i] = read;
                    }
                    is.close();
                }
            }

            auto start = high_resolution_clock::now();
            for (int i = 0; i < data_count-1; i++) {
                    sort_count++;
                 max = i;
                for (int j = i+1; j < data_count; j++) {
                    compare_count++;
                    if (data[j] > data[max]) {
                        max = j;
                        swap(&data[max], &data[i]);

                    }
                }
            }

            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

            ofstream os("Rezultatas.txt");
            os << "Naudotas metodas: Isrinkimas" << endl;

            os << "Rezultato duomenys: ";
            for (int i = 0; i < data_count; i++) {

                if (i % 15 == 0) {
                    os << endl;
                }

                if (data[i] <= 200000) {
                    os << data[i] << " ";
                }
                else {
                    continue;
                }
            }
            os << endl;
            os << "Palyginimu skaicius : " << compare_count << endl;
            os << "Keitimu skaicius : " << sort_count << endl;
            sort_count = 0;
            os << "Milisekundes, per kiek buvo padarytas darbas : " << duration.count() << endl;
            os << "Sekundes, per kiek buvo padarytas darbas  : " << fixed << setprecision(10) << duration.count() / 1000;
            compare_count = 0;
            os.close();
        }

        else if (choice == 2) {

            ofstream os("Rezultatas.txt");
            os << "Naudotas metodas: Iterpimas" << endl;
            if (data_count == 0) {
                cout << "Bandoma rusiuoti su 0 duomenu, nutraukiama programa" << endl;
                exit(-1);
            }

            else {
                ifstream is("Pradiniai.txt");

                if (is.fail()) {
                    cout << " Programa nutraukiama" << endl;
                    exit(-2);
                }

                else {
                    for (int i = 0; i < data_count; i++) {
                        is >> read;
                        data[i] = read;
                    }
                    is.close();
                }
            }

            os << "Rusiavimo metodas : Iterpimas" << endl;

            auto start = high_resolution_clock::now();
            for (int i = 0; i < data_count; i++) {
                key = data[i];
                temp = i;
                compare_count++;
                while (temp > 0 && data[temp - 1] < key) {
                    sort_count++;
                    data[temp] = data[temp - 1];
                    temp--;
                }
                data[temp] = key;
            }

            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

            os << "Rezultato duomenys: ";
            for (int i = 0; i < data_count; i++) {
                if (i % 15 == 0) {
                    os << endl;
                }
                if (data[i] <= 9999) {
                    os << data[i] << " ";
                }
                else {
                    continue;
                }
            }
            os << endl;
            os << "Palyginimu skaicius: " << sort_count << endl;
            os << "Keitimu skaicius: " << compare_count << endl;
            sort_count = 0;
            os << "Milisekundes, per kiek  buvo padarytas darbas: " << duration.count() << endl;
            os << "Sekundes, per kiek  buvo padarytas darbas: " << fixed << setprecision(10) << duration.count() / 1000;
            compare_count = 0;
            os.close();
        }

        else if (choice == 3) {
        cout << "Iveskite skaiciu duomenu, su kuriais dirbsime (nuo 2-200000)" << endl;
        while (!correct_number) {
            cin >> data_count;
            if (data_count < 2 || data_count > 200000) {
                cout << "Neteisingai ivestas skaicius" << endl;
            }
            else {
                break;
            }
        }

        cout << "*------------------------------------------------------------------------------*" << endl;
        cout << "Pasirinkite generavimui atveji: " << endl;
        cout << "1 - Geriausias atvejis (visi isrikiuoti isskyrus viena)" << endl;
        cout << "2 - Vidutinis atvejis (atsitiktiniai skaiciai)" << endl;
        cout << "3 - Blogiausias atvejis (skaiciai surikiuoti atvirkstine tvarka)" << endl;
        cout << "*------------------------------------------------------------------------------*" << endl;
        while (!correct_number) {
            cin >> sorting_type;
            if (sorting_type < 1 || sorting_type > 3) {
                cout << "Neteisingai ivestas skaicius" << endl;
            }
            else {
                break;
            }
        }

        ofstream os("Pradiniai.txt");
        if (sorting_type == 3) {

            for (int i = 0; i < data_count; i++) {
                    data[i] = i;
                    os << data[i] << " ";

                if (i % 15 == 0 && i!=0) {
                    os << endl;
                }
            }
        }

        else if (sorting_type == 2) {

            for (int i = 0; i < data_count; i++) {
                data[i] = distr(engine);
                if (i % 15 == 0 && i!=0) {
                    os << endl;
                }
                os << data[i] << " ";
            }
        }

        else if (sorting_type == 1) {
                random_space = 1 + (rand() % data_count);
            data[random_space] = distr(engine);
            for (int i = 0; i <= data_count; i++) {
                if (i == random_space) {
                    os << data[random_space];
                    os << " ";
                }
                data[i] = distr(engine);
            }

            for (int i = 0; i < data_count; i++) {
                key = data[i];
                temp = i;
                sort_count++;
                while (temp > 0 && data[temp - 1] < key) {
                    compare_count++;
                    data[temp] = data[temp - 1];
                    temp--;
                }
                data[temp] = key;
            }

            for (int i = 0; i < data_count; i++) {
                if (i % 15 == 0 && i != 0) {
                    os << endl;
                }
                os << data[i] << " ";
            }

        }

        os.close();
}

        else if (choice == 4) {
            cout << "Darbas baigiamas" << endl;
            running = false;
        }
    }


    return 0;
}













































