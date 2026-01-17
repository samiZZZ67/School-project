#include "functions.h"

void showMenu() {
    cout << "\n===== Laptop Ownership System =====\n";
    cout << "A - Add Laptop (New Student)\n";
    cout << "U - Update Laptop Serial (Lost Laptop)\n";
    cout << "C - Check Laptop Owner by Serial\n";
    cout << "F - Search Laptop by Student ID\n";
    cout << "O - Check Out Laptop (Student Leaving)\n";
    cout << "S - Display All Records\n";
    cout << "Q - Quit\n";
    cout << "Enter choice: ";
}

void displayStatus(string idArr[], string serialArr[], int count) {
    cout << "\n----- Registered Laptops -----\n";
    if (count == 0) {
        cout << "No records available.\n";
        return;
    }
    cout << "Student ID\tLaptop Serial\n";
    for (int i = 0; i < count; i++) {
        cout << idArr[i] << "\t" << serialArr[i] << endl;
    }
    cout << "Total Registered Laptops: " << count << endl;
}
