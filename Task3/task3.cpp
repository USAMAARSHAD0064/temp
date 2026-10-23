#include <iostream>
using namespace std;

class myCarStack {
private:
    int cars[8];
    int topIndex;

public:
    myCarStack() {
        topIndex = -1;
    }

    void push(int carNo) {
        if (isFull()) {
            cout << "Parking is full" << endl;
            return;
        }
        topIndex++;
        cars[topIndex] = carNo;
    }

    int pop() {
        int carNo = cars[topIndex];
        topIndex--;
        return carNo;
    }

    int top() const {
        return cars[topIndex];
    }

    bool isEmpty() const {
        return topIndex == -1;
    }

    bool isFull() const {
        return topIndex == 7;
    }

    int count() const {
        return topIndex + 1;
    }

    bool search(int carNo) const {
        for (int i = 0; i <= topIndex; i++) {
            if (cars[i] == carNo)
                return true;
        }
        return false;
    }

    void display() const {
        if (isEmpty()) {
            cout << "No cars parked" << endl;
            return;
        }
        for (int i = topIndex; i >= 0; i--) {
            cout << cars[i] << " ";
        }
        cout << endl;
    }
};

void removeCar(myCarStack& parking, int carNo) {
    if (!parking.search(carNo)) {
        cout << "Car not found" << endl;
        return;
    }

    myCarStack temp;
    while (parking.top() != carNo) {
        temp.push(parking.pop());
    }

    parking.pop();
    cout << "Car " << carNo << " has left" << endl;

    while (!temp.isEmpty()) {
        parking.push(temp.pop());
    }
}

int main() {
    myCarStack parking;
    int choice, carNo;

    do {
        cout << endl;
        cout << "1. Park a new car" << endl;
        cout << "2. Remove a car" << endl;
        cout << "3. Show parked cars" << endl;
        cout << "4. Total cars parked" << endl;
        cout << "5. Search a car" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter car number: ";
            cin >> carNo;
            parking.push(carNo);
            break;
        case 2:
            cout << "Enter car number: ";
            cin >> carNo;
            removeCar(parking, carNo);
            break;
        case 3:
            parking.display();
            break;
        case 4:
            cout << "Total cars: " << parking.count() << endl;
            break;
        case 5:
            cout << "Enter car number: ";
            cin >> carNo;
            if (parking.search(carNo))
                cout << "Car is parked" << endl;
            else
                cout << "Car is not here" << endl;
            break;
        case 6:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    } while (choice != 6);

    return 0;
}
