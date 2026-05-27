#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <ctime>
using namespace std;

class Expense
{
    string category, date;
    float amount;

public:
    void Print();

    Expense()
    {
        string d, c;
        float a;
        time_t timestamp;
        time(&timestamp);
        d = ctime(&timestamp);
        cout << "Enter Category: " << endl;
        cin >> c;
        cout << "Enter Amount: " << endl;
        cin >> a;
        this->amount = a;
        this->category = c;
        this->date = d;
    }

    Expense(string date, string category, float amount)
    {
        this->date = date;
        this->category = category;
        this->amount = amount;
    }

    void Display()
    {
        cout << date << endl;
        cout << category << endl;
        cout << amount << endl;
    }

    int retrieveAmount()
    {
        int amt = amount;
        return amt;
    }
};
void Expense::Print()
{
    ofstream myFile("../expt.txt", ios::app);
    myFile << date << endl;
    myFile << category << endl;
    myFile << amount << endl;
    myFile << "-------------------------------" << endl;
    myFile.close();
}

vector<string> File()
{
    ifstream myFile("../expt.txt");
    string str;
    vector<string> data;
    if (myFile.is_open())
    {
        while (getline(myFile, str))
        {
            data.push_back(str);
        }
        myFile.close();
    }
    return data;
}
vector<Expense> TrackRecords()
{
    vector<string> data = File();
    int total = data.size();
    float numb;
    cout << "Collecting expense records" << endl;
    vector<Expense> Records;
    for (int i = 0; i < total; i += 5)
    {
        numb = stof(data[i + 3]);
        Expense ex = Expense(
            data[i],
            data[i + 2],
            numb);
        Records.push_back(ex);
    }
    return Records;
}

void createRecord () {
    Expense* ptr = new Expense;
    ptr->Print();
}

void ViewRecords()
{
    vector<Expense> Records = TrackRecords();
    cout << "-------------------------------------" << endl;
    cout << "Here's your expense records till date" << endl;
    cout << "-------------------------------------" << endl;
    for (Expense ex : Records)
    {
        ex.Display();
        cout << "-------------------------------------" << endl;
    }
}

void TotalExpense()
{
    vector<Expense> Records = TrackRecords();
    float totalExpense = 0.00;
    for (Expense ex : Records)
    {
        int amt = ex.retrieveAmount();
        totalExpense += amt;
    }
    cout << "-------------------------------------" << endl;
    cout<<"Total Expense is "<<totalExpense<<endl;
    cout << "-------------------------------------" << endl;
}

void Menu()
{
    int choice;
    do
    {
        cout << "<----Menu---->" << endl;
        cout << "(1) Add new expense record" << endl;
        cout << "(2) View expense records" << endl;
        cout << "(3) Total expense" << endl;
        cout << "(4) Exit." << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            createRecord();
            break;
        case 2:
            ViewRecords();
            break;
        case 3:
            TotalExpense();
            break;
        case 4:
            break;
        default:
            cout << "Invalid choice, try again" << endl;
            break;
        }
    } while (choice != 4);
}

int main()
{
    Menu();
    return 0;
}