#ifndef HEADER_H
#define HEADER_H
#include <cstring>
#include <limits>    //Just for asterik Password Input
#include <termios.h> //Just for asterik Password Input
#include <unistd.h>  //Just for asterik Password Input
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <iostream>
using namespace std;

/*class Portal
{
public:
    virtual void portal() = 0;
};*/
class User
{
protected:
    int UserID;
    string user;
    string pass;
    string usertype;

public:
    void getlog(); // Function to get login details on console in a PERFECT WAY
    void getreg(); // Function to get Registration Details on COnsole in  a PERFECT WAY
    virtual void portal() = 0;
    virtual void Register() = 0;
    virtual void Login() = 0;
    virtual void Logout() = 0;
};

class check
{
protected:
    string User;
    string Pass;

public:
    bool isfound;
    bool checkUser(string a, string b, string checkfile);
    int checkusertype(string a, string b);
};

struct Order
{
   int ID;
   string Name;
   double pprice;
};
/*
class Order : public MenuItem{
protected:
    
    double Price;

public:
    Order(int id, string name, float price): OrderID(id), CustomerName(name), TotalPrice(price), OrderStatus("Pending"){}
    void getitem(int id);
    void AddItem();

    void RemoveItem(const MenuItem& item);

    void CalculateTotal();

    void ConfirmOrder();

    void CancelOrder();
};
*/
class Payment {
protected:
    int PaymentID;
    int OrderID;
    double Amount;
    string PaymentStatus;

public:
    Payment(int id, int orderID, double amount)
        : PaymentID(id), OrderID(orderID), Amount(amount), PaymentStatus("Pending") {}

    void ProcessPayment() {
        // Implement processing the payment
    }
};
class MenuItem
{
protected:
    int ItemID;
    string ItemName;
    string ItemDescription;
    double Price;
    int QuantityInStock;
    double Rating = 0;

public:
    void getitemdet(); // Method to get item details
    void ReadItem(string file);
    void ReadItem(string file, int quant);
    void setrating(int ID, float R);
    void setstock(int ID, int S);
    void removeitem(int id);
};
class Administrator : public User, public MenuItem
{
private:
    const string Username;
    const string Password;
    void Login();
    void Register(); // Administrator is once registered entity
    void Logout();
    void portal();
    void ViewUsersFromFile();
    void AddNotification();
    void RemoveNotification();

public:
    Administrator() : Username("Ali"), Password("0541") {}
    void ViewMenu();
    void AddMenuItem();
    void RemoveMenuItem();
    void ManageInventory();
    void ManageDiscountPromotion();
    void ViewOrderHistory(); 
    void RateMenuItem();
    void ViewOrdersFromFile(const string &fileName);
    void CalculatemonthlyEarnings();
};

class CafeStaff : public User, public check, public MenuItem
{
public:
    void Register();
    void Login();
    void ViewMenu();
    void ProcessOrder();
    void AddMenuItem();
    void RemoveMenuItem();
    void Logout();
    void portal();
    void portallogged();
};

class Customer : public User, public check, public MenuItem
{
private:
public:
    void Register();
    void Login();
    void ViewMenu();
    void PlaceOrder();
    void ViewOrderHistory();
    void getitem(int id);
    void Displaybill(Order items[], int itemCount, double totalBill);
    void Logout();
    void portal();
    void portallogged();
};

void menu();

#endif // HEADER_H
