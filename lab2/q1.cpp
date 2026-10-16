#include <iostream>
using namespace std;

template <class T>
class List
{
protected:
    T* arr;
    int maxSize;
    int currentSize;

public:
    List(int size = 10)
    {
        if (size <= 0)
            size = 10;
        maxSize = size;
        currentSize = 0;
        arr = new T[maxSize];
    }

    // deep copy
    List(const List<T>& other)
    {
        maxSize = other.maxSize;
        currentSize = other.currentSize;
        arr = new T[maxSize];
        for (int i = 0; i < currentSize; i++)
            arr[i] = other.arr[i];
    }

    virtual void addElementAtFirstIndex(T) = 0;
    virtual void addElementAtLastIndex(T) = 0;
    virtual T removeElementFromEnd() = 0;
    virtual void removeElementFromStart() = 0;

    void display()
    {
        if (currentSize == 0)
        {
            cout << "List is empty" << endl;
            return;
        }
        cout << "List: ";
        for (int i = 0; i < currentSize; i++)
            cout << arr[i] << " ";
        cout << endl;
    }

    virtual ~List()
    {
        delete[] arr;
    }
};

// List is abstract so we cant make its object directly.
// this small class is only to test that List works.
template <class T>
class TestList : public List<T>
{
public:
    TestList(int size = 10) : List<T>(size) {}
    TestList(const TestList<T>& o) : List<T>(o) {}

    void addElementAtFirstIndex(T val)
    {
        if (this->currentSize == this->maxSize)
        {
            cout << "List is full" << endl;
            return;
        }
        for (int i = this->currentSize; i > 0; i--)
            this->arr[i] = this->arr[i - 1];
        this->arr[0] = val;
        this->currentSize++;
    }

    void addElementAtLastIndex(T val)
    {
        if (this->currentSize == this->maxSize)
        {
            cout << "List is full" << endl;
            return;
        }
        this->arr[this->currentSize++] = val;
    }

    T removeElementFromEnd()
    {
        if (this->currentSize == 0)
        {
            cout << "List is empty" << endl;
            return T();
        }
        this->currentSize--;
        return this->arr[this->currentSize];
    }

    void removeElementFromStart()
    {
        if (this->currentSize == 0)
        {
            cout << "List is empty" << endl;
            return;
        }
        for (int i = 0; i < this->currentSize - 1; i++)
            this->arr[i] = this->arr[i + 1];
        this->currentSize--;
    }
};

int main()
{
    TestList<int> l(5);

    l.addElementAtLastIndex(10);
    l.addElementAtLastIndex(20);
    l.addElementAtFirstIndex(5);
    l.display();

    cout << "Removed from end: " << l.removeElementFromEnd() << endl;
    l.removeElementFromStart();
    cout << "After removing from start: ";
    l.display();

    // checking copy constructor
    l.addElementAtLastIndex(30);
    TestList<int> copy(l);
    copy.addElementAtLastIndex(99);
    cout << "Original: ";
    l.display();
    cout << "Copy: ";
    copy.display();

    return 0;
}
