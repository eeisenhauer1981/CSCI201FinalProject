#ifndef book_H
#define book_H

#include <iostream>
#include <string>

class Book {

public:
    enum class Genre { Fiction, NonFiction, Mystery, Science, Biography, Undefined };
    enum class BookStatus { Available, CheckedOut, Unavailable };
    
    //--CONSTRUCTORS--
    Book();
    Book(std::string t, std::string a, std::string g, std::string tp);

    //--SETTERS--
    //changes string input to assign enum Genre
    Genre setGenre(std::string g);
    void setStatus(BookStatus s);

    //--GETTERS--
    //changes enum Genre to string for output
    std::string getGenre() const;
    //changes enum BookStatus to string for output
    std::string getStatus() const;
    std::string getTitle() const;
    std::string getAuthor() const;

    
    //--TASKS--
    virtual void displayInfo(std::ostream& os) const;
    bool operator==(const Book& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Book& b);



protected:
    std::string title;
    std::string author;
    std::string type;
    Genre genre;
    BookStatus status;
};

//EBook Class
class EBook : public Book {
    double fileSizeMB;
public:
    EBook(std::string t, std::string a, std::string g, std::string tp, double size);
    void displayInfo(std::ostream& os) const override;
};

//PrintedBook Class
class PrintedBook : public Book {
    int pageCount;
public:
    PrintedBook(std::string t, std::string a, std::string g, std::string tp, int pages);
    void displayInfo(std::ostream& os) const override;
};

#endif