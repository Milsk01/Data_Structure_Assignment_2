#include <iostream>
#include <fstream>
#include <sstream>
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

struct linkedList
{
    Staff *head = nullptr;
    Staff *tail = nullptr;
};

inline int conversion(istringstream &records)
{
    //get an integer from istringstream and convert the integer to a string
    string integer;
    getline(records, integer, ',');
    return stoi(integer);
}

int hashFunc(int id)
{
    return id % 100;
}
void insertData(Staff *current, linkedList staff[100])
{
    int index = hashFunc(current->ID);

    if (staff[index].head == nullptr)
    {
        staff[index].head = staff[index].tail = current;
    }
    else
    {

        staff[index].tail->next = current;
        staff[index].tail = staff[index].tail->next;
    }
}

void read_csv(linkedList staff[100], const string &filename)
{
    //create a ifstream variable
    ifstream file(filename.c_str());

    //test if file is opened
    if (file)
    {
        // variable declaration
        string record;
        istringstream dataFields;

        //get a line from the file
        while (getline(file, record))
        {

            Staff *temp = new Staff();
            //put the line into istringstream
            dataFields.str(record);

            //reset the state of istringstream
            dataFields.clear();

            temp->ID = conversion(dataFields);
            getline(dataFields, temp->position, ',');
            getline(dataFields, temp->name, ',');
            temp->salary = conversion(dataFields);

            temp->next = nullptr;

            insertData(temp, staff);
        }
    }
    else
    {
        std::cout << "File is not found";
    }
}
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

int main()
{
    string filename = ".\\dummy.csv";
    linkedList staff[100];

    //data initialization
    read_csv(staff, filename);

    //test
    cout << staff[90].head->next->name;
}