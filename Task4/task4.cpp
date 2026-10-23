#include <iostream>
using namespace std;

struct Action {
    char type;
    char ch;
};

class ActionStack {
private:
    Action arr[100];
    int topIndex;

public:
    ActionStack() {
        topIndex = -1;
    }

    void push(Action a) {
        if (topIndex == 99)
            return;
        topIndex++;
        arr[topIndex] = a;
    }

    Action pop() {
        Action a = arr[topIndex];
        topIndex--;
        return a;
    }

    bool isEmpty() const {
        return topIndex == -1;
    }

    void clear() {
        topIndex = -1;
    }
};

class TextEditor {
private:
    char text[100];
    int length;
    ActionStack undoStack;
    ActionStack redoStack;

    void addChar(char c) {
        text[length] = c;
        length++;
        text[length] = '\0';
    }

    char removeChar() {
        length--;
        char c = text[length];
        text[length] = '\0';
        return c;
    }

public:
    TextEditor() {
        length = 0;
        text[0] = '\0';
    }

    void type(char c) {
        if (length == 99) {
            cout << "Text is full" << endl;
            return;
        }
        addChar(c);
        Action a;
        a.type = 'T';
        a.ch = c;
        undoStack.push(a);
        redoStack.clear();
    }

    void deleteChar() {
        if (length == 0) {
            cout << "Nothing to delete" << endl;
            return;
        }
        Action a;
        a.type = 'D';
        a.ch = removeChar();
        undoStack.push(a);
        redoStack.clear();
    }

    void undo() {
        if (undoStack.isEmpty()) {
            cout << "Nothing to undo" << endl;
            return;
        }
        Action a = undoStack.pop();
        if (a.type == 'T')
            removeChar();
        else
            addChar(a.ch);
        redoStack.push(a);
    }

    void redo() {
        if (redoStack.isEmpty()) {
            cout << "Nothing to redo" << endl;
            return;
        }
        Action a = redoStack.pop();
        if (a.type == 'T')
            addChar(a.ch);
        else
            removeChar();
        undoStack.push(a);
    }

    void show() const {
        cout << "Text: " << text << endl;
    }
};

int main() {
    TextEditor editor;
    int choice;
    char c;

    do {
        cout << endl;
        cout << "1. Type a character" << endl;
        cout << "2. Delete a character" << endl;
        cout << "3. Undo" << endl;
        cout << "4. Redo" << endl;
        cout << "5. Show text" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter character: ";
            cin >> c;
            editor.type(c);
            editor.show();
            break;
        case 2:
            editor.deleteChar();
            editor.show();
            break;
        case 3:
            editor.undo();
            editor.show();
            break;
        case 4:
            editor.redo();
            editor.show();
            break;
        case 5:
            editor.show();
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
