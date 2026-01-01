#include <iostream>
#include <cctype>
using namespace std;

/* ---------- FUNCTION PROTOTYPES ---------- */
bool isValidID(string id);
bool serialExists(string serial, string serialArr[], int count);
int findStudent(string id, string idArr[], int count);

void showMenu();
void addLaptop(string idArr[], string serialArr[], int* count, int maxStudents);
void updateLaptop(string idArr[], string serialArr[], int count);
void checkLaptop(string serialArr[], string idArr[], int count);
void searchByID(string idArr[], string serialArr[], int count);
void checkOutLaptop(string idArr[], string serialArr[], int* count);
void displayStatus(string idArr[], string serialArr[], int count);

int main() {
    int maxStudents;
    cout << "Enter number of students/laptops you want to register: ";
    cin >> maxStudents;

    // Create arrays based on the user's input
    string idArr[maxStudents];
    string serialArr[maxStudents];
    int count = 0;
    char choice;

    do {
        showMenu();
        cin >> choice;
        choice = toupper(choice);

        switch (choice) {
            case 'A':
                addLaptop(idArr, serialArr, &count, maxStudents);
                break;
            case 'U':
                updateLaptop(idArr, serialArr, count);
                break;
            case 'C':
                checkLaptop(serialArr, idArr, count);
                break;
            case 'F':
                searchByID(idArr, serialArr, count);
                break;
            case 'O':
                checkOutLaptop(idArr, serialArr, &count);
                break;
            case 'S':
                displayStatus(idArr, serialArr, count);
                break;
            case 'Q':
                cout << "Program terminated.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 'Q');

    return 0;
}

/* ---------- FUNCTIONS ---------- */

bool isValidID(string id) {
    if (id.length() != 9)
        return false;
    if (toupper(id[0]) != 'E' || toupper(id[1]) != 'T' || toupper(id[2]) != 'S')
        return false;
    for (int i = 3; i < 9; i++) {
        if (!isdigit(id[i]))
            return false;
    }
    return true;
}

bool serialExists(string serial, string serialArr[], int count) {
    for (int i = 0; i < count; i++) {
        if (serialArr[i] == serial)
            return true;
    }
    return false;
}

int findStudent(string id, string idArr[], int count) {
    for (int i = 0; i < count; i++) {
        if (idArr[i] == id)
            return i;
    }
    return -1;
}

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

void addLaptop(string idArr[], string serialArr[], int* count, int maxStudents) {
    if (*count >= maxStudents) {
        cout << "System storage full. Cannot add more students.\n";
        return;
    }

    string id, serial;
    cout << "Enter Student ID: ";
    cin >> id;
    for (int i = 0; i < 3; i++)
        id[i] = toupper(id[i]);  // only student ID letters uppercase

    if (!isValidID(id)) {
        cout << "Invalid ID format.\n";
        return;
    }

    if (findStudent(id, idArr, *count) != -1) {
        cout << "Student already has a laptop. Update serial if lost.\n";
        return;
    }

    cout << "Enter Laptop Serial Number: ";
    cin >> serial;  // case-sensitive

    if (serialExists(serial, serialArr, *count)) {
        cout << "This laptop already belongs to another student.\n";
        return;
    }

    idArr[*count] = id;
    serialArr[*count] = serial;
    (*count)++;
    cout << "Laptop registered successfully.\n";
}

void updateLaptop(string idArr[], string serialArr[], int count) {
    string id, newSerial;
    cout << "Enter Student ID: ";
    cin >> id;
    for (int i = 0; i < 3; i++)
        id[i] = toupper(id[i]);

    int index = findStudent(id, idArr, count);
    if (index == -1) {
        cout << "Student not found.\n";
        return;
    }

    cout << "Enter New Laptop Serial Number: ";
    cin >> newSerial; // case-sensitive

    if (serialExists(newSerial, serialArr, count)) {
        cout << "This serial already exists.\n";
        return;
    }

    serialArr[index] = newSerial;
    cout << "Laptop serial updated successfully.\n";
}

void checkLaptop(string serialArr[], string idArr[], int count) {
    string serial;
    cout << "Enter Laptop Serial Number: ";
    cin >> serial;

    for (int i = 0; i < count; i++) {
        if (serialArr[i] == serial) {
            cout << "Laptop belongs to Student ID: " << idArr[i] << endl;
            return;
        }
    }
    cout << "Laptop not found in the system.\n";
}

void searchByID(string idArr[], string serialArr[], int count) {
    string id;
    cout << "Enter Student ID to search: ";
    cin >> id;
    for (int i = 0; i < 3; i++)
        id[i] = toupper(id[i]);

    int index = findStudent(id, idArr, count);
    if (index != -1) {
        cout << "Student ID: " << idArr[index]
             << " owns Laptop Serial: " << serialArr[index] << endl;
    } else {
        cout << "Student ID not found in the system.\n";
    }
}

void checkOutLaptop(string idArr[], string serialArr[], int* count) {
    string id, serial;
    cout << "Enter Student ID: ";
    cin >> id;
    for (int i = 0; i < 3; i++)
        id[i] = toupper(id[i]);

    int index = findStudent(id, idArr, *count);
    if (index == -1) {
        cout << "Student ID not found.\n";
        return;
    }

    cout << "Enter Laptop Serial Number: ";
    cin >> serial;

    if (serialArr[index] != serial) {
        cout << "Serial does not match the student's laptop. Cannot check out.\n";
        return;
    }

    for (int i = index; i < *count - 1; i++) {
        idArr[i] = idArr[i + 1];
        serialArr[i] = serialArr[i + 1];
    }
    (*count)--;
    cout << "Laptop checked out. Student has left the university.\n";
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
