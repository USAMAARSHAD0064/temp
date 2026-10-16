#include <iostream>
#include <cstring>
using namespace std;

class Employee
{
protected:
    char name[40];
    int id;

public:
    Employee()
    {
        name[0] = '\0';
        id = 0;
    }

    void setDetails(const char n[], int i)
    {
        strcpy(name, n);
        id = i;
    }

    virtual double calculateSalary() = 0;

    void print()
    {
        cout << "ID: " << id << "  Name: " << name << endl;
        cout << "Salary: Rs " << calculateSalary() << endl;
    }

    virtual ~Employee() {}
};

class FullTimeEmployee : public Employee
{
    double fixedSalary;

public:
    FullTimeEmployee()
    {
        fixedSalary = 0;
    }

    void setSalary(double s)
    {
        fixedSalary = s;
    }

    double calculateSalary()
    {
        return fixedSalary;
    }
};

class PartTimeEmployee : public Employee
{
    int hoursWorked;
    double hourlyRate;

public:
    PartTimeEmployee()
    {
        hoursWorked = 0;
        hourlyRate = 0;
    }

    void setHours(int h, double rate)
    {
        hoursWorked = h;
        hourlyRate = rate;
    }

    double calculateSalary()
    {
        return hoursWorked * hourlyRate;
    }
};

int main()
{
    FullTimeEmployee e1;
    e1.setDetails("Ahmed Raza", 101);
    e1.setSalary(85000);

    PartTimeEmployee e2;
    e2.setDetails("Hira Khan", 102);
    e2.setHours(60, 750);

    cout << "Full Time Employee" << endl;
    e1.print();

    cout << "\nPart Time Employee" << endl;
    e2.print();

    return 0;
}
