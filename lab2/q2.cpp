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

template <class T>
class MyList : public List<T>
{
public:
    MyList(int size = 10) : List<T>(size) {}

    MyList(const MyList<T>& other) : List<T>(other) {}

    void addElementAtFirstIndex(T val)
    {
        if (full())
        {
            cout << "List is full" << endl;
            return;
        }
        // shift everything one step right
        for (int i = this->currentSize; i > 0; i--)
            this->arr[i] = this->arr[i - 1];
        this->arr[0] = val;
        this->currentSize++;
    }

    void addElementAtLastIndex(T val)
    {
        if (full())
        {
            cout << "List is full" << endl;
            return;
        }
        this->arr[this->currentSize] = val;
        this->currentSize++;
    }

    T removeElementFromEnd()
    {
        if (empty())
        {
            cout << "List is empty, nothing to remove" << endl;
            return T();
        }
        this->currentSize--;
        return this->arr[this->currentSize];
    }

    void removeElementFromStart()
    {
        if (empty())
        {
            cout << "List is empty, nothing to remove" << endl;
            return;
        }
        for (int i = 0; i < this->currentSize - 1; i++)
            this->arr[i] = this->arr[i + 1];
        this->currentSize--;
    }

    bool empty()
    {
        return this->currentSize == 0;
    }

    bool full()
    {
        return this->currentSize == this->maxSize;
    }

    int size()
    {
        return this->currentSize;
    }

    bool insertAt(int index, T value)
    {
        // index can be equal to currentSize (that means add at end)
        if (index < 0 || index > this->currentSize || full())
            return false;

        for (int i = this->currentSize; i > index; i--)
            this->arr[i] = this->arr[i - 1];
        this->arr[index] = value;
        this->currentSize++;
        return true;
    }

    T last()
    {
        if (empty())
        {
            cout << "List is empty" << endl;
            return T();
        }
        return this->arr[this->currentSize - 1];
    }

    bool search(T val)
    {
        for (int i = 0; i < this->currentSize; i++)
        {
            if (this->arr[i] == val)
                return true;
        }
        return false;
    }

    ~MyList() {}
};

int main()
{
    int cap;
    cout << "Enter size of list: ";
    cin >> cap;

    MyList<int> list(cap);
    int choice, val, idx;

    do
    {
        cout << "\n----- MENU -----" << endl;
        cout << "1. Add at start" << endl;
        cout << "2. Add at end" << endl;
        cout << "3. Remove from start" << endl;
        cout << "4. Remove from end" << endl;
        cout << "5. Insert at index" << endl;
        cout << "6. Is empty?" << endl;
        cout << "7. Is full?" << endl;
        cout << "8. Size" << endl;
        cout << "9. Last element" << endl;
        cout << "10. Search" << endl;
        cout << "11. Display" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter value: ";
            cin >> val;
            list.addElementAtFirstIndex(val);
            break;
        case 2:
            cout << "Enter value: ";
            cin >> val;
            list.addElementAtLastIndex(val);
            break;
        case 3:
            list.removeElementFromStart();
            break;
        case 4:
            if (!list.empty())
                cout << "Removed: " << list.removeElementFromEnd() << endl;
            else
                cout << "List is empty" << endl;
            break;
        case 5:
            cout << "Enter index: ";
            cin >> idx;
            cout << "Enter value: ";
            cin >> val;
            if (list.insertAt(idx, val))
                cout << "Inserted" << endl;
            else
                cout << "Invalid index or list full" << endl;
            break;
        case 6:
            if (list.empty())
                cout << "Yes, list is empty" << endl;
            else
                cout << "No, list is not empty" << endl;
            break;
        case 7:
            if (list.full())
                cout << "Yes, list is full" << endl;
            else
                cout << "No, list is not full" << endl;
            break;
        case 8:
            cout << "Size: " << list.size() << endl;
            break;
        case 9:
            if (!list.empty())
                cout << "Last element: " << list.last() << endl;
            else
                cout << "List is empty" << endl;
            break;
        case 10:
            cout << "Enter value to search: ";
            cin >> val;
            if (list.search(val))
                cout << val << " is present" << endl;
            else
                cout << val << " not found" << endl;
            break;
        case 11:
            list.display();
            break;
        case 0:
            cout << "Bye" << endl;
            break;
        default:
            cout << "Wrong choice" << endl;
        }
    } while (choice != 0);

    return 0;
}
