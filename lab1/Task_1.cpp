#include <iostream>
using namespace std;

// base class, cant make object of this
class Course
{
protected:
    char title[50];

public:
    Course(const char t[])
    {
        int i = 0;
        while (t[i] != '\0' && i < 49)
        {
            title[i] = t[i];
            i++;
        }
        title[i] = '\0';
    }

    virtual int duration() = 0;   // pure virtual

    void show()
    {
        cout << "Course: " << title << endl;
        cout << "Total duration: " << duration() << " hours" << endl;
    }

    virtual ~Course() {}
};

class OnlineCourse : public Course
{
    int weeks;
    int hoursPerWeek;

public:
    OnlineCourse(const char t[], int w, int h) : Course(t)
    {
        weeks = w;
        hoursPerWeek = h;
    }

    int duration()
    {
        return weeks * hoursPerWeek;
    }
};

class OfflineCourse : public Course
{
    int months;
    int hoursPerDay;

public:
    OfflineCourse(const char t[], int m, int h) : Course(t)
    {
        months = m;
        hoursPerDay = h;
    }

    // taking 1 month = 30 days
    int duration()
    {
        return months * 30 * hoursPerDay;
    }
};

int main()
{
    OnlineCourse c1("Web Development", 8, 6);
    OfflineCourse c2("Graphic Designing", 3, 2);

    // using base class pointer so the right duration() gets called
    Course* p;

    p = &c1;
    cout << "--- Online Course ---" << endl;
    p->show();

    p = &c2;
    cout << "\n--- Offline Course ---" << endl;
    p->show();

    return 0;
}
