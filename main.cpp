#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <string>

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

int validation(string raw_input, int lowerBound = 1, int upperBound = 4)
{
    int temp;
    try
    {
        temp = stoi(raw_input);
        if (temp < lowerBound || temp > upperBound)
        {
            throw out_of_range("Invalid Numeric Input");
        }
    }
    catch (std::invalid_argument e)
    {
        cout << endl
             << "!!!Invalid Input!!!" << endl
             << endl;
        temp = -1;
    }
    catch (out_of_range e)
    {
        cout << endl
             << "!!!" << e.what() << "!!!"
             << endl
             << endl;
        temp = -1;
    }
    return temp;
}
int getID()
{
    int ID;
    while (true)
    {
        string temp;
        cin >> ws;
        getline(cin, temp);
        ID = validation(temp, 90020001, 90020999);
        if (ID != -1)
        {
            break;
        }
        else
        {
            cout << "Staff ID No    : ";
        }
    }
    return ID;
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
    newStaff->ID = getID();
    cout << "Staff Name    : ";
    getline(cin, newStaff->name);
    cout << "Staff Position: ";
    getline(cin, newStaff->position);
    cout << "Staff Salary  : RM ";
    cin >> newStaff->salary;
    newStaff->next = nullptr;

    return newStaff;
}

//formatted data display
void dataOutput(Staff *nodePtr, int index, int nodeCounter)
{
    cout << "\nResult:\n";
    cout << "Data Location : Index " << index << " (Node : " << nodeCounter << ")" << endl;
    cout << "Staff ID No   : " << nodePtr->ID << endl;
    cout << "Staff Name    : " << nodePtr->name << endl;
    cout << "Staff Position: " << nodePtr->position << endl;
    cout << "Staff Salary  : RM " << fixed << setprecision(2) << nodePtr->salary << endl;
}

//locates if data exists or not and displays data
void dataLocation(linkedList staff[100])
{
    int staffID;

    //menu top bar
    cout << "\n";
    cout.width(39);
    cout.fill('-');
    cout << " ";
    cout << "\n\tMenu: Data Location\n";
    cout.width(39);
    cout.fill('-');
    cout << " \n";
    cout << "Enter ID No   : ";
    staffID = getID();
    int index = hashFunc(staffID);
    int nodeCounter = 1;
    Staff *nodePtr = staff[index].head;

    //searches for data
    while (nodePtr != nullptr)
    {
        if (nodePtr->ID == staffID)
        {
            //displays data if found
            dataOutput(nodePtr, index, nodeCounter);
            break;
        }
        else
        {
            nodePtr = nodePtr->next;
            nodeCounter++;
        }
    }
    if (nodePtr == nullptr)
    {
        cout << "Record does not exist\n";
    }
}

void displayAll(linkedList staffList[100])
{
    cout << "\n";
    cout.width(39);
    cout.fill('-');
    cout << " ";
    cout << "\n\tMenu: Display All\n";
    cout.width(39);
    cout.fill('-');
    cout << " \n";

    auto begin = staffList;
    auto end = staffList + 100;

    while (begin != end)
    {
        auto head = begin->head;
        int nodeCounter = 1;
        int index;
        while (head != nullptr)
        {

            index = hashFunc(head->ID);
            dataOutput(head, index, nodeCounter);
            nodeCounter++;
            head = head->next;
        }

        begin++;
    }
}

int main()
{
    linkedList staff[100] = {linkedList{nullptr, nullptr}};
    //read dummy data

    string filename = ".\\dummy.csv";
    read_csv(staff, filename);

    cout << "STAFF RECORD 2021" << endl;
    string answer;
    int optionNo;
    while (true)
    {

        cout.width(39);
        cout.fill('-');
        cout << " ";
        cout << "\n\tMenu\n";
        cout.width(39);
        cout.fill('-');
        cout << " \n";
        cout << "1.Data Input\n";
        cout << "2.Data Location\n";
        cout << "3.Display All Record\n";
        cout << "4.Exit\n";
        cout << "Enter Option:";
        cin >> ws;
        getline(cin, answer);

        optionNo = validation(answer);
        switch (optionNo)
        {
        case 1:
            insertData(dataInput(), staff);
            break;
        case 2:
            dataLocation(staff);
            break;
        case 3:
            displayAll(staff);
            break;
        case 4:
            exit(0);
        default:
            cout << "Please submit a number between 1 and 4.\n"
                 << endl;
            break;
        }
    }
}