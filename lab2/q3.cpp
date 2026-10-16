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

template <class T>
class CustomList : public MyList<T>
{
    bool isPrime(T n)
    {
        if (n < 2)
            return false;
        for (T i = 2; i * i <= n; i++)
        {
            if (n % i == 0)
                return false;
        }
        return true;
    }

    // rotate part arr[start..end] one step to the right
    void rightOnce(int start, int end)
    {
        if (end <= start)
            return;
        T temp = this->arr[end];
        for (int i = end; i > start; i--)
            this->arr[i] = this->arr[i - 1];
        this->arr[start] = temp;
    }

    // rotate part arr[start..end] one step to the left
    void leftOnce(int start, int end)
    {
        if (end <= start)
            return;
        T temp = this->arr[start];
        for (int i = start; i < end; i++)
            this->arr[i] = this->arr[i + 1];
        this->arr[end] = temp;
    }

public:
    CustomList(int size = 10) : MyList<T>(size) {}

    CustomList(const CustomList<T>& other) : MyList<T>(other) {}

    T sum_ofPrime()
    {
        T sum = 0;
        for (int i = 0; i < this->currentSize; i++)
        {
            if (isPrime(this->arr[i]))
                sum += this->arr[i];
        }
        return sum;
    }

    T secondMaxEven()
    {
        bool gotMax = false, gotSecond = false;
        T max = 0, second = 0;

        for (int i = 0; i < this->currentSize; i++)
        {
            T x = this->arr[i];
            if (x % 2 != 0)
                continue;

            if (!gotMax || x > max)
            {
                if (gotMax)
                {
                    second = max;
                    gotSecond = true;
                }
                max = x;
                gotMax = true;
            }
            else if (x < max && (!gotSecond || x > second))
            {
                second = x;
                gotSecond = true;
            }
        }

        if (!gotSecond)
        {
            cout << "(not enough even numbers) ";
            return 0;
        }
        return second;
    }

    T secondMinOdd()
    {
        bool gotMin = false, gotSecond = false;
        T min = 0, second = 0;

        for (int i = 0; i < this->currentSize; i++)
        {
            T x = this->arr[i];
            if (x % 2 == 0)
                continue;

            if (!gotMin || x < min)
            {
                if (gotMin)
                {
                    second = min;
                    gotSecond = true;
                }
                min = x;
                gotMin = true;
            }
            else if (x > min && (!gotSecond || x < second))
            {
                second = x;
                gotSecond = true;
            }
        }

        if (!gotSecond)
        {
            cout << "(not enough odd numbers) ";
            return 0;
        }
        return second;
    }

    void printDuplicates()
    {
        bool found = false;
        cout << "Duplicates: ";
        for (int i = 0; i < this->currentSize; i++)
        {
            // skip if this value already came before
            bool seen = false;
            for (int k = 0; k < i; k++)
            {
                if (this->arr[k] == this->arr[i])
                {
                    seen = true;
                    break;
                }
            }
            if (seen)
                continue;

            int count = 1;
            for (int j = i + 1; j < this->currentSize; j++)
            {
                if (this->arr[j] == this->arr[i])
                    count++;
            }
            if (count > 1)
            {
                cout << this->arr[i] << "(" << count << " times) ";
                found = true;
            }
        }
        if (!found)
            cout << "none";
        cout << endl;
    }

    // first half = 0 to n/2-1, second half = n/2 to n-1
    void rotateClockwaise(int r)
    {
        int n = this->currentSize;
        if (n < 2)
            return;
        int mid = n / 2;
        for (int i = 0; i < r; i++)
        {
            rightOnce(0, mid - 1);
            rightOnce(mid, n - 1);
        }
    }

    void rotateanitclockwaise(int rt)
    {
        int n = this->currentSize;
        if (n < 2)
            return;
        int mid = n / 2;
        for (int i = 0; i < rt; i++)
        {
            leftOnce(0, mid - 1);
            leftOnce(mid, n - 1);
        }
    }

    ~CustomList() {}
};

int main()
{
    int cap;
    cout << "Enter size of list: ";
    cin >> cap;

    CustomList<int> list(cap);
    int choice, val, r;

    do
    {
        cout << "\n----- MENU -----" << endl;
        cout << "1. Add element at end" << endl;
        cout << "2. Add element at start" << endl;
        cout << "3. Display list" << endl;
        cout << "4. Sum of prime numbers" << endl;
        cout << "5. Second max even" << endl;
        cout << "6. Second min odd" << endl;
        cout << "7. Print duplicates" << endl;
        cout << "8. Rotate clockwise" << endl;
        cout << "9. Rotate anti-clockwise" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter value: ";
            cin >> val;
            list.addElementAtLastIndex(val);
            break;
        case 2:
            cout << "Enter value: ";
            cin >> val;
            list.addElementAtFirstIndex(val);
            break;
        case 3:
            list.display();
            break;
        case 4:
            cout << "Sum of primes: " << list.sum_ofPrime() << endl;
            break;
        case 5:
            cout << "Second max even: " << list.secondMaxEven() << endl;
            break;
        case 6:
            cout << "Second min odd: " << list.secondMinOdd() << endl;
            break;
        case 7:
            list.printDuplicates();
            break;
        case 8:
            cout << "How many times: ";
            cin >> r;
            list.rotateClockwaise(r);
            list.display();
            break;
        case 9:
            cout << "How many times: ";
            cin >> r;
            list.rotateanitclockwaise(r);
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
