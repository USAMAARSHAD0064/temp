#include <iostream>
#include <cstring>
using namespace std;

// template functions from lab 1

template <class T>
void selectionSort(T arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min])
                min = j;
        }
        if (min != i)
        {
            T temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
        }
    }
}

template <class T, class K>
int linearSearch(T arr[], int n, K key)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == key)
            return i;
    }
    return -1;
}

// array must be sorted before calling this
template <class T, class K>
int binarySearch(T arr[], int n, K key)
{
    int low = 0, high = n - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

// abstract class for anything kept in the library
class LibraryItem
{
public:
    virtual void display() const = 0;
    virtual ~LibraryItem() {}
};

class Book : public LibraryItem
{
    char title[60];
    char author[40];
    int pages;

public:
    Book()
    {
        title[0] = '\0';
        author[0] = '\0';
        pages = 0;
    }

    Book(const char t[], const char a[], int p)
    {
        strcpy(title, t);
        strcpy(author, a);
        pages = p;
    }

    void display() const
    {
        cout << "Book: " << title << " | Author: " << author
             << " | Pages: " << pages << endl;
    }

    // sorting is done on pages
    bool operator<(const Book& b) const
    {
        return pages < b.pages;
    }

    bool operator>(const Book& b) const
    {
        return pages > b.pages;
    }

    // used by linear search to match title
    bool operator==(const char t[]) const
    {
        return strcmp(title, t) == 0;
    }

    // used by binary search on pages
    bool operator==(int p) const { return pages == p; }
    bool operator<(int p) const { return pages < p; }
};

class Newspaper : public LibraryItem
{
    char name[50];
    char date[15];
    char edition[40];

public:
    Newspaper()
    {
        name[0] = '\0';
        date[0] = '\0';
        edition[0] = '\0';
    }

    Newspaper(const char n[], const char d[], const char e[])
    {
        strcpy(name, n);
        strcpy(date, d);
        strcpy(edition, e);
    }

    void display() const
    {
        cout << "Newspaper: " << name << " | Date: " << date
             << " | Edition: " << edition << endl;
    }

    // alphabetical order of edition
    bool operator<(const Newspaper& n) const
    {
        return strcmp(edition, n.edition) < 0;
    }

    bool operator==(const char n[]) const
    {
        return strcmp(name, n) == 0;
    }
};

const int MAX = 20;

class Library
{
    Book books[MAX];
    Newspaper papers[MAX];
    int bookCount;
    int paperCount;

public:
    Library()
    {
        bookCount = 0;
        paperCount = 0;
    }

    void addBook(const Book& b)
    {
        if (bookCount < MAX)
            books[bookCount++] = b;
        else
            cout << "No space for more books" << endl;
    }

    void addNewspaper(const Newspaper& n)
    {
        if (paperCount < MAX)
            papers[paperCount++] = n;
        else
            cout << "No space for more newspapers" << endl;
    }

    void displayCollection()
    {
        LibraryItem* item;   // base pointer, display() decided at runtime

        cout << "Books:" << endl;
        for (int i = 0; i < bookCount; i++)
        {
            item = &books[i];
            item->display();
        }

        cout << "Newspapers:" << endl;
        for (int i = 0; i < paperCount; i++)
        {
            item = &papers[i];
            item->display();
        }
    }

    void sortBooksByPages()
    {
        selectionSort(books, bookCount);
    }

    void sortNewspapersByEdition()
    {
        selectionSort(papers, paperCount);
    }

    // books are sorted by pages not title, so linear search here
    Book* searchBookByTitle(const char title[])
    {
        int idx = linearSearch(books, bookCount, title);
        if (idx == -1)
            return NULL;
        return &books[idx];
    }

    Newspaper* searchNewspaperByName(const char name[])
    {
        int idx = linearSearch(papers, paperCount, name);
        if (idx == -1)
            return NULL;
        return &papers[idx];
    }

    // books are sorted by pages so binary search works for this one
    // (call sortBooksByPages first)
    Book* searchBookByPages(int pages)
    {
        int idx = binarySearch(books, bookCount, pages);
        if (idx == -1)
            return NULL;
        return &books[idx];
    }
};

int main() {
    // Create book objects
    Book book1("The Catcher in the Rye", "J.D. Salinger", 277);
    Book book2("To Kill a Mockingbird", "Harper Lee", 324);

    // Create newspaper objects
    Newspaper newspaper1("Washington Post", "2024-10-13", "Morning Edition");
    Newspaper newspaper2("The Times", "2024-10-12", "Weekend Edition");

    // Create a library object
    Library library;

    // Add books and newspapers to the library
    library.addBook(book1);
    library.addBook(book2);
    library.addNewspaper(newspaper1);
    library.addNewspaper(newspaper2);

    // Display the entire collection
    cout << "Before Sorting:\n";
    library.displayCollection();

    // Sort books by pages and newspapers by edition
    library.sortBooksByPages();
    library.sortNewspapersByEdition();

    cout << "\nAfter Sorting:\n";
    library.displayCollection();

    // Search for a book by title
    Book* foundBook = library.searchBookByTitle("The Catcher in the Rye");
    if (foundBook) {
        cout << "\nFound Book:\n";
        foundBook->display();
    } else {
        cout << "\nBook not found.\n";
    }

    // Search for a newspaper by name
    Newspaper* foundNewspaper = library.searchNewspaperByName("The Times");
    if (foundNewspaper) {
        cout << "\nFound Newspaper:\n";
        foundNewspaper->display();
    } else {
        cout << "\nNewspaper not found.\n";
    }

    return 0;
}
