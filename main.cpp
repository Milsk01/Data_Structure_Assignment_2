#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

//data structure
struct Staff
{
    int ID;
    std::string name;
    std::string position;
    float salary;
    Staff *next = nullptr;
};

//create a new record
Staff *dataInput()
{
    Staff *newStaff = new Staff();

    cout << "\n";
    cout.width(39);
    cout.fill('-');
    cout << " ";
    cout << "\n\tMenu: Data Input\n";
    cout.width(39);
    cout.fill('-');
    cout << " \n";
    cout << "Staff ID No   : ";
    cin >> newStaff->ID;
    cin.ignore();
    cout << "Staff Name    : ";
    getline(cin, newStaff->name);
    cout << "Staff Position: ";
    getline(cin, newStaff->position);
    cout << "Staff Salary  : RM ";
    cin >> newStaff->salary;
    newStaff->next = nullptr;

    return newStaff;
}
int hashFunc(int id)
{
    return id % 100;
}
void insertData(Staff *current, Staff *staff[100])
{
    int index = hashFunc(current->ID);

    if (staff[index] == nullptr)
    {
        staff[index] = current;
    }
    else
    {
        staff[index]->next = current;
    }
}

int main()
{
    Staff *staff[100] = {nullptr};
    Staff *data = dataInput();
    insertData(data, staff);
    cout << staff[hashFunc(data->ID)]->name;
}