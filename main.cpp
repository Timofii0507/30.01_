#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <Windows.h>

using namespace std;

class train {
public:
    string departure;
    string arrival;
    int train_number;
    int ticket_price;

    train() {
        departure = "";
        arrival = "";
        train_number = 0;
        ticket_price = 0;
    }

    train(string dp, string a, int tn, int tp) {
        departure = dp;
        arrival = a;
        train_number = tn;
        ticket_price = tp;
    }

    friend ostream& operator<<(ostream& out, train& obj) {
        return out << obj.departure << endl << obj.arrival << endl << obj.train_number << endl << obj.ticket_price << endl;
    }
};

class railway_station {
private:
    vector<train> station;

public:
    railway_station() {
        load_from_file();
    }

    void add_train() {
        string departure, arrival;
        int train_number, ticket_price;

        cout << "" << endl;
        cout << "������ ������� �����������: ";
        cin >> departure;
        cout << "������ ������� ��������: ";
        cin >> arrival;
        cout << "������ ����� ������: ";
        cin >> train_number;
        cout << "������ ������� ������: ";
        cin >> ticket_price;

        station.push_back(train(departure, arrival, train_number, ticket_price));
    }

    void print_all_trains() {
        for (auto train : station) {
            cout << train << endl;
        }
    }

    void search_train(int train_number) {
        auto it = find_if(station.begin(), station.end(), [train_number](train t) { return t.train_number == train_number; });
        if (it != station.end()) {
            cout << *it << endl;
        }
        else {
            cout << "���� � ������� " << train_number << " �� ��������" << endl;
        }
    }

    void save_to_file() {
        ofstream file("trains.txt");
        for (auto train : station) {
            file << train.departure << endl;
            file << train.arrival << endl;
            file << train.train_number << endl;
            file << train.ticket_price << endl;
        }
        file.close();
    }

    void load_from_file() {
        ifstream file("trains.txt");
        if (file.is_open()) {
            station.clear();
            string departure, arrival;
            int train_number, ticket_price;

            while (file >> departure >> arrival >> train_number >> ticket_price) {
                station.push_back(train(departure, arrival, train_number, ticket_price));
            }

            file.close();
        }
    }

    void start() {
        int choice;
        do
        {
            cout << "1. ������ ��� ��� ����" << endl;
            cout << "2. ������� ��� ��� �� �����" << endl;
            cout << "3. ������� ��� ��� ����������� ����" << endl;
            cout << "4. �����" << endl;
            cin >> choice;

            switch (choice)
            {
            case 1:
                add_train();
                break;
            case 2:
                print_all_trains();
                break;
            case 3:
                int train_number;
                cout << "" << endl;
                cout << "������ ����� ������: ";
                cin >> train_number;
                search_train(train_number);
                break;
            case 4:
                save_to_file();
                return;
            default:
                break;
            }
        } while (choice != 4);
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    railway_station station;
    station.start();
    return 0;
}