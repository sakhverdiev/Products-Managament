#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Product {
private:
    int id;
    string name;
    string description;
    double price;
    int stock;

public:
    Product(int productId, const string& productName, const string& productDescription, double productPrice, int productStock)
        : id(productId), name(productName), description(productDescription), price(productPrice), stock(productStock) {}

    int getId() const {
        return id;
    }

    string getName() const {
        return name;
    }

    string getDescription() const {
        return description;
    }

    double getPrice() const {
        return price;
    }

    int getStock() const {
        return stock;
    }

    void reduceStock(int quantity) {
        stock -= quantity;
    }
};


class Admin {
private:
    string username;
    string password;

public:
    Admin(const std::string& adminUsername, const std::string& adminPassword)
        : username(adminUsername), password(adminPassword) {}

    bool authenticate(const std::string& inputUsername, const std::string& inputPassword) const {
        return (username == inputUsername && password == inputPassword);
    }

    void showAllProducts(const vector<Product>& productList) const {
        cout << "Product List:" << endl;
        for (const auto& product : productList) {
            cout << "ID: " << product.getId() << "  Name: " << product.getName() << endl;
        }
    }

    void addProduct(vector<Product>& productList) {
        int productId;
        string productName;
        string productDescription;
        double productPrice;
        int productStock;

        cout << "Enter the product ID: ";
        cin >> productId;

        cout << "Enter the product name: ";
        cin.ignore();
        getline(cin, productName);

        cout << "Enter the product description: ";
        getline(cin, productDescription);

        cout << "Enter the product price: ";
        cin >> productPrice;

        cout << "Enter the product stock: ";
        cin >> productStock;

        Product newProduct(productId, productName, productDescription, productPrice, productStock);
        productList.push_back(newProduct);
        cout << "Product added successfully!" << endl;
    }

    void deleteProduct(vector<Product>& productList) {
        int productId;
        cout << "Enter the ID of the product you want to delete: ";
        cin >> productId;

        auto it = find_if(productList.begin(), productList.end(),
            [productId](const Product& product) {
                return product.getId() == productId;
            });

        if (it != productList.end()) {
            productList.erase(it);
            cout << "Product deleted successfully!" << endl;
        }
        else {
            cout << "Product with ID " << productId << " not found!" << endl;
        }
    }
};


class Guest {
private:
    string name;
    string connectDate;

public:
    Guest(const string& guestName, const string& guestConnectDate)
        : name(guestName), connectDate(guestConnectDate) {}

    void showProductDetails(const Product& product) const {
        cout << "Product Details:" << endl;
        cout << "Name: " << product.getName() << endl;
        cout << "Description: " << product.getDescription() << endl;
        cout << "Price: " << product.getPrice() << endl;
        cout << "Stock: " << product.getStock() << endl;
    }

    void buyProduct(Product& product) {
        int quantity;
        cout << "Enter the quantity to buy: ";
        cin >> quantity;

        if (quantity <= product.getStock()) {
            cout << "Are you sure to buy " << quantity << " amount(s) of " << product.getName() << "? (y/n): ";
            char choice;
            cin >> choice;

            if (choice == 'y' || choice == 'Y') {
                product.reduceStock(quantity);
                cout << "Purchase successful!" << endl;
            }
            else {
                cout << "Purchase cancelled." << endl;
            }
        }
        else {
            cout << "Insufficient stock. Purchase failed." << endl;
        }
    }
};


int main() {
    vector<Product> productList;

    Product product1(1, "IPhone 14", "Smartphone", 1500.0, 50);
    Product product2(2, "Gaming PC", "Desktop Computer", 2000.0, 20);
    Product product3(3, "Playstation 5", "Gaming Console", 500.0, 10);

    productList.push_back(product1);
    productList.push_back(product2);
    productList.push_back(product3);

    int userType;
    cout << "Welcome to the e-shop application!" << endl;
    cout << "Please select your user type:" << endl;
    cout << "1) As Guest" << endl;
    cout << "2) As Admin" << endl;
    cout << "Enter your choice: ";
    cin >> userType;

    if (userType == 2) {
        string adminUsername;
        string adminPassword;
        cout << "Username: ";
        cin >> adminUsername;
        cout << "Password: ";
        cin >> adminPassword;

        Admin admin("admin", "admin123");
        if (admin.authenticate(adminUsername, adminPassword)) {
            int adminChoice;
            cout << "Login successful!" << endl;
            while (true) {
                cout << "Please select an option:" << endl;
                cout << "1) Show All Products" << endl;
                cout << "2) Add Product" << endl;
                cout << "3) Delete Product" << endl;
                cout << "Enter your choice: ";
                cin >> adminChoice;

                if (adminChoice == 1) {
                    admin.showAllProducts(productList);
                }
                else if (adminChoice == 2) {
                    admin.addProduct(productList);
                }
                else if (adminChoice == 3) {
                    admin.deleteProduct(productList);
                }
                else {
                    cout << "Invalid choice." << endl;
                }
            }
        }
        else {
            cout << "Invalid username or password." << endl;
        }
    }
    else {
        cout << "Welcome Guest!" << endl;

        // Show prodcuts
        Admin admin("admin", "admin123");
        admin.showAllProducts(productList);

        int productChoice;
        cout << "Enter the ID of the product you want to select: ";
        cin >> productChoice;

        // Find product
        Product* selectedProduct = nullptr;
        for (auto& product : productList) {
            if (product.getId() == productChoice) {
                selectedProduct = &product;
                break;
            }
        }

        // Show product detail
        if (selectedProduct != nullptr) {
            cout << "Selected Product: " << endl;
            cout << "ID: " << selectedProduct->getId() << endl;
            cout << "Name: " << selectedProduct->getName() << endl;
            cout << "Description: " << selectedProduct->getDescription() << endl;
            cout << "Price: " << selectedProduct->getPrice() << endl;
            cout << "Stock: " << selectedProduct->getStock() << endl;

            int actionChoice;
            cout << "Choose an action:" << endl;
            cout << "1) Buy" << endl;
            cout << "2) Show Details" << endl;
            cout << "Enter your choice: ";
            cin >> actionChoice;

            if (actionChoice == 1) {
                Guest guest("Guest", "2023-07-17");
                guest.buyProduct(*selectedProduct);
            }
            else if (actionChoice == 2) {
                Guest guest("Guest", "2023-07-17");
                guest.showProductDetails(*selectedProduct);
            }
            else {
                cout << "Invalid choice." << endl;
            }
        }
        else {
            cout << "Product with ID " << productChoice << " not found!" << endl;
        }

        return 0;
    }

    return 0;
}