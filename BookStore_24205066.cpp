//Please refer to the PDF document to gain a comprehensive understanding of all the features, functionalities, and the operational procedures of this system.
//Must be read the pdf documentation first
// cub_id 24205066

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <sstream>

class Book {
private:
    static int nextID;
    int bookID;
    std::string bookName;
    int quantity;
    int pages;
    double price;

public:
    Book(const std::string& name, int qty, int pg, double pr)
        : bookName(name), quantity(qty), pages(pg), price(pr) {
        bookID = nextID++;
    }

    int getBookID() const { return bookID; }
    std::string getBookName() const { return bookName; }
    int getQuantity() const { return quantity; }
    int getPages() const { return pages; }
    double getPrice() const { return price; }

    bool purchase(int qty) {
        if (quantity >= qty) {
            quantity -= qty;
            return true;
        }
        return false;
    }

    void displayDetails() const {
        std::cout << "ID: " << bookID
                  << ", Name: " << bookName
                  << ", Quantity: " << quantity
                  << ", Pages: " << pages
                  << ", Price: " << std::fixed << std::setprecision(2) << price << " Tk" << std::endl;
    }
};

int Book::nextID = 1;

class Bookstore {
private:
    std::vector<Book> books;
    std::vector<std::string> transactionHistory;
    double storeIncome = 0.0;

public:
    void setBooks(const std::string& name, int qty, int pg, double pr) {
        books.emplace_back(name, qty, pg, pr);
        const Book& newBook = books.back();
        std::cout << "\n🎉 Book added successfully! Here are the details:\n";
        newBook.displayDetails();
    }

    void purchaseBook(const std::string& name, int qty, double amount) {
        std::string lowercaseName = name;
        std::transform(lowercaseName.begin(), lowercaseName.end(), lowercaseName.begin(), ::tolower);

        for (auto& book : books) {
            std::string bookNameLower = book.getBookName();
            std::transform(bookNameLower.begin(), bookNameLower.end(), bookNameLower.begin(), ::tolower);

            if (bookNameLower == lowercaseName) {
                double totalPrice = book.getPrice() * qty;

                if (qty <= 0) {
                    std::cout << "\n⚠️ Invalid quantity. Please enter a positive quantity.\n";
                    return;
                }

                if (amount < totalPrice) {
                    std::cout << "\n⚠️ Not enough money to complete the purchase.\n"
                              << "Required: " << std::fixed << std::setprecision(2) << totalPrice << " Tk, Provided: " << amount << " Tk.\n";
                    transactionHistory.push_back("Purchase failed: Insufficient funds for '" + name + "'.");
                    return;
                }

                if (book.getQuantity() < qty) {
                    std::cout << "\n⚠️ Purchase failed: Not enough stock for '" << name + "'.\n"
                              << "Requested: " << qty << ", Available: " << book.getQuantity() << ".\n";
                    transactionHistory.push_back("Purchase failed: Insufficient stock for '" + name + "'.");
                    return;
                }

                book.purchase(qty);
                storeIncome += totalPrice;

                double change = amount - totalPrice;
                std::ostringstream transaction;
                transaction << std::fixed << std::setprecision(2);
                transaction << "Purchase successful: " << qty << " of '" << name << "' for " << totalPrice << " Tk.";
                transactionHistory.push_back(transaction.str());

                std::cout << "\n✅ Purchase successful!\n";
                std::cout << "Book: " << name << ", Quantity: " << qty << ", Total Cost: " << totalPrice << " Tk\n";

                if (change > 0) {
                    std::cout << "You will get change of: " << change << " Tk\n";
                }
                return;
            }
        }

        transactionHistory.push_back("Purchase failed: Book '" + name + "' not found.");
        std::cout << "\n❌ Purchase failed: Book '" << name << "' not found in our inventory.\n";
    }

    void transactionHistoryLog() const {
        std::cout << "\n--- Transaction History ---\n";
        for (const auto& record : transactionHistory) {
            std::cout << record << std::endl;
        }
    }

    void displayBooks() const {
        std::cout << "\n--- Available Books ---\n";
        for (const auto& book : books) {
            book.displayDetails();
        }
    }

    void displayIncome() const {
        std::cout << "\n💰 Total Store Income: " << std::fixed << std::setprecision(2) << storeIncome << " Tk\n";
    }
};

int getPositiveIntegerInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail() || value <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\n⚠️ Invalid input. Please enter the correct value.\n";
        } else {
            return value;
        }
    }
}

double getPositiveDoubleInput(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail() || value < 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\n⚠️ Invalid input. Please enter a valid number.\n";
        } else {
            return value;
        }
    }
}

int main() {
    Bookstore store;
    int choice;

    do {
        std::cout << "\n--- 📚 Welcome to the Bookstore! ---\n";
        std::cout << "1. Add Book\n";
        std::cout << "2. Purchase Book\n";
        std::cout << "3. Display Books\n";
        std::cout << "4. Show Transaction History\n";
        std::cout << "5. Show Total Income\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        while (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\n⚠️ Invalid input. Please enter an integer value for your choice: ";
            std::cin >> choice;
        }

        switch (choice) {
            case 1: {
                std::string name;
                std::cin.ignore();
                std::cout << "\nEnter Book Name: ";
                std::getline(std::cin, name);

                int qty = getPositiveIntegerInput("\nEnter Quantity: ");
                int pages = getPositiveIntegerInput("Enter Pages: ");
                double price = getPositiveDoubleInput("Enter Price: ");

                store.setBooks(name, qty, pages, price);
                break;
            }
            case 2: {
                std::string name;
                std::cin.ignore();
                std::cout << "\nEnter Book Name: ";
                std::getline(std::cin, name);

                int qty = getPositiveIntegerInput("\nEnter Quantity: ");
                double amount = getPositiveDoubleInput("Enter Amount: ");

                store.purchaseBook(name, qty, amount);
                break;
            }
            case 3:
                store.displayBooks();
                break;
            case 4:
                store.transactionHistoryLog();
                break;
            case 5:
                store.displayIncome();
                break;
            case 6:
                std::cout << "\n👋 Thank you for visiting the bookstore. Goodbye!\n";
                break;
            default:
                std::cout << "\n❌ Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
