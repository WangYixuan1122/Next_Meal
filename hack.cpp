#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

class Restaurant{
    private:
        string name;
        int capacity = 0; //number of tables in the restaurant
        int occupied = 0; //number of occupied table now in the restaurant
        int* reservation = nullptr; //number of reservation for different periods of a day.
        int* estimation = nullptr; //estimation of number of occupied table in the restaurant for different periods of a day
    public:
        Restaurant(string name, int capacity, int occupied, int* reservation, int* estimation)
        : name(name), capacity(capacity), occupied(occupied)
        {
            this->estimation = new int[14];
            this->reservation = new int[14];
            for (int i = 0; i < 14; i++){
                this->reservation[i] = reservation[i];
            }
            for (int i = 0; i < 14; i++){
                this->estimation[i] = estimation[i];
            }
        }
        int getCapacity() const{return capacity;}
        int getOccupied() const{return occupied;}
        int getReservation(int period) const{return reservation[period];}
        int getEstimation(int period) const{return estimation[period];}
        void setEstimation(int period, int estimation){this->estimation[period] = estimation;}
};
int main()
{
    /* We use only three restaurants for simplicity. 
       The number of occupied table is derived from the database, therefore is set as given.
       The estimated number of table is derived from the database, therefore is set as given.
       Assume all the restaurant open at 9 a.m. and close at 23 p.m.
       The unit of estimation period is one hour for simplicity.
       The following program will only focus on the process of reservation.*/
    
    int R1_reservation[14] = {0, 2, 5, 8, 7, 1, 0, 8, 11, 7, 2, 0, 0, 0};
    int R1_estimation[14] = {3, 5, 10, 18, 16, 8, 2, 12, 16, 20, 19, 10, 3, 0};
    int R2_reservation[14] = {0, 4, 10, 18, 22, 5, 0, 6, 10, 17, 8, 1, 0, 0};
    int R2_estimation[14] = {0, 6, 20, 25, 21, 17, 3, 16, 26, 34, 30, 22, 6, 0};
    int R3_reservation[14] = {0, 1, 2, 5, 7, 3, 0, 0, 6, 7, 0, 0, 0, 0};
    int R3_estimation[14] = {0, 1, 3, 8, 7, 11, 4, 2, 1, 5, 10, 14, 3, 0};
    Restaurant R1("A", 20, 4, R1_reservation, R1_estimation);
    Restaurant R2("B", 40, 6, R2_reservation, R2_estimation);
    Restaurant R3("C", 15, 2, R3_reservation, R2_estimation);

    char choice1;
    cout << "Which restaurant would you like to eat: (A, B or C) ";
    cin >> choice1;
    while (choice1 != 'A' && choice1 != 'B' && choice1 != 'C')
    {
        cout << "Restaurant " << choice1 << " does not exist. Please try again: ";
        cin >> choice1;
    }
    
    int now_available = 0;
    switch(choice1)
    {
        case 'A': now_available = R1.getCapacity()-R1.getOccupied(); break;
        case 'B': now_available = R2.getCapacity()-R2.getOccupied(); break;
        case 'C': now_available = R2.getCapacity()-R2.getOccupied(); break;
    }
    cout << "Number of available tables now: " << now_available << endl;
    Sleep(1000);

    int choice2;
    cout << "What do you want to do: (1 for Ordering; 2 for Reservation) ";
    cin >> choice2;
    while (choice2 != 1 && choice2 != 2)
    {
        cout << "You entered a wrong number. Please try again: " ;
        cin >> choice2;
    }

    if (choice2 == 1)
    {
        cout << "Loading the menu..." << endl; //The process of ordering is omitted for simplicity.
        Sleep(2000);
        cout << "(order process)" << endl;
        Sleep(2000);
        cout << "Finish ordering! Thank you! Have a nice day:)" << endl;
        return 0;
    }
    else
    {
        int time = 0;
        cout << "When do you want to arrive: (Enter a number between 9 to 22) ";
        cin >> time;
        while (time < 9 || time > 22)
        {
            cout << "The restaurant is closed at that time. Please try again: ";
            cin >> time;
        }

        int available = 0;
        int predict = 0;
        switch(choice1)
        {
            case 'A': available = R1.getCapacity()-R1.getReservation(time-9); 
                      predict = R1.getCapacity()-R1.getEstimation(time-9); break;
            case 'B': available = R2.getCapacity()-R2.getReservation(time-9); 
                      predict = R2.getCapacity()-R2.getEstimation(time-9); break;
            case 'C': available = R3.getCapacity()-R3.getReservation(time-9); 
                      predict = R3.getCapacity()-R3.getEstimation(time-9); break;
        }

        cout << "Checking available table..." << endl;
        Sleep(2000);

        cout << "Number of unreserved table: " << available << endl;
        Sleep(1000);

        cout << "Predicted number of available table from " << time << " to " << time+1 << " o'clock: " << predict << endl;
        Sleep(1000);

        if (available <= 3 || predict <= 2)
        {
            int choice3 = 0;
            cout << "You are highly recommended to dine out because possibly you have to wait! (1 for Yes; 2 for No) ";
            cin >> choice3;
            while (choice3 != 1 && choice3 != 2)
            {
                cout << "You entered a wrong number. Please try again: ";
                cin >> choice3;
            }
            if (choice3 == 1)
            {
                cout << "Transfer to dine-out oredering... Done." << endl; //The process of dine-out ordering is omitted for simplicity.
                return 0;
            }  
        }
        
        int choice4;
        cout << "Please confirm your reservation: Restaurant " << choice1 << " at " << time << " o'clock (1 for Yes; 2 for No) ";
        cin >> choice4;
        while(choice4 != 1 && choice4 != 2)
        {
            cout << "You entered a wrong number. Please try again: ";
            cin >> choice4;
        }
        if (choice4 == 1)
        {
            cout << "Your reservation is successful! Thank you!" << endl;
        }
        else
        {
            cout << "Please try again. Exit." << endl;
            return 0;
        }
    }
}