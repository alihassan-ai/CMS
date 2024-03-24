#include "Header.h"
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

void menu()
{
   User *obj;
   int specialchoice;
   int ret;

   do
   {
      system("clear");
      cout << "============================CMS Portal============================\nPress\n";

      cout << "1. To enter Administrator Portal" << endl;
      cout << "2. To enter Cafe staff Portal" << endl;
      cout << "3. To enter Customer Portal" << endl;
      cout << "4. To Close App" << endl;
      cout << "Select : ";
      cin >> specialchoice;
      switch (specialchoice)
      {
      case 1:
         obj = new Administrator;
         obj->Login();
         break;
      case 2:
         obj = new CafeStaff;
         obj->portal();
         break;
      case 3:
         obj = new Customer;
         obj->portal();
         break;
      case 4:
         cout << "\n\tThanks for Using//\n";
         exit(1);
      default:
         cout << "Invalid Choice Press 0 to Try Again else Exit..";
         cin >> ret;
         break;
      }
   } while (ret == 0);
}

string getPassword() // Function for Hiding password used in member function of class user below
{
   string pass;
   char ch;

   // Save current terminal settings
   termios oldt, newt;
   tcgetattr(STDIN_FILENO, &oldt);
   newt = oldt;

   // Disable echoing of characters
   newt.c_lflag &= ~ECHO;
   tcsetattr(STDIN_FILENO, TCSANOW, &newt);

   cout << flush;

   // Read password
   while (1)
   {
      ch = getchar();
      if (ch == '\n' || ch == '\r')
      {
         break;
      }
      pass.push_back(ch);
      cout << '*';    // Display asterisk for each character
      fflush(stdout); // Force flushing the output buffer
   }

   // Restore terminal settings
   tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
   cout << endl; // Move to the next line after password input

   return pass;
}

void User::getlog() // Function to get login Detais of users
{

   cout << "\nEnter Username  : ";
   cin >> user;
   // Capitalize the first letter of the username
   if (!user.empty())
   {
      user[0] = toupper(user[0]);
   }

   // Clear input buffer
   cin.ignore(numeric_limits<streamsize>::max(), '\n');

   // Hide password input
   cout << "Enter Password : ";
   pass = getPassword();
}

// Function to check if a string contains at least one uppercase letter and one digit
bool isValidPassword(const string &password)
{
   bool hasUpperCase = false;
   bool hasDigit = false;

   for (char ch : password)
   {
      if (isupper(ch))
      {
         hasUpperCase = true;
      }
      else if (isdigit(ch))
      {
         hasDigit = true;
      }

      if (hasUpperCase && hasDigit)
      {
         return true; // Password meets the criteria
      }
   }

   return false; // Password does not meet the criteria
}

// Function to get user registration information from the console
void User::getreg()
{
   int count = 1;

   // Get username
   cout << "Enter username(Only First Name): ";
   cin >> user;

   // Clear the input buffer
   cin.ignore(numeric_limits<streamsize>::max(), '\n');

   // Get password
   string password;
   bool isValid = false;

   while (!isValid)
   {
      cout << "Enter password (8 characters, at least 1 uppercase letter, and 1 digit): \n";
      getline(cin, password); // Use getline instead of cin for password input

      // Check password length and criteria
      if (password.length() >= 8 && isValidPassword(password))
      {
         isValid = true;
      }
      else
      {
         system("clear");
         if (count >= 5)
         {
            menu();
         }
         cout << "Please Follow Password Format. Try again (" << count++ << " attempts left).\n\n";
      }
   }

   pass = password;
}
///////////////////////////////////////Administrator def////////////////////////////////////////////

void Administrator::Login()
{
again:
   getlog();
   if (user == Username && pass == Password)
   {
      portal();
   }
   else
   {
      system("clear");
      cout << "Wrong username or Password!......Try again\n\n  " << endl;
      goto again;
   }
}
void Administrator::Logout()
{
   menu();
}
void Administrator::Register()
{
   //
}
void Administrator::AddMenuItem()
{
   getitemdet();
   system("clear");

   ofstream Menu;
   Menu.open("text/Menu.txt", ios::app);
   if (!Menu)
   {
      cout << "We cannot find menu please check database\n";
      // A loop for delay
      for (int i = 5; i > 0; --i)
      {
         system("clear");
         cout << "Going back to Portal in " << i << " seconds...\n"
              << flush;
         sleep(1);
      }
      portal();
   }
   else
   {
      Menu << ItemID << endl
           << ItemName << endl
           << Price << endl
           << ItemDescription << endl
           << QuantityInStock << endl
           << Rating << endl;
   }

   Menu.close();

   // Introduce a 5-second countdown. A loop for delay
   for (int i = 5; i > 0; --i)
   {
      system("clear");
      cout << "Item Added to Menu Successfuly\n\n";
      cout << "Going back to Portal in " << i << " seconds...\n"
           << flush;
      sleep(1);
   }
   portal();
}
void Administrator::ViewMenu()
{
   string e = "010101010";
   while (e == "010101010")
   {
      ReadItem("text/Menu.txt");
      cout << "\n\n\t\t\t\t\t\tPress any key to go back to portal...";
      cin >> e;
   }
   portal();
}
void Administrator::RemoveMenuItem()
{
   int Id;
   ReadItem("text/Menu.txt");
   cout << "Enter Id of Item to Remove: ";
   cin >> Id;
   removeitem(Id);
   for (int i = 5; i > 0; --i)
   {
      system("clear");
      cout << "Item Rated Successfuly\n\n";
      cout << "Going back to Portal in " << i << " seconds...\n"
           << flush;
      sleep(1);
   }
   portal();
}
void Administrator::RateMenuItem()
{
   int Id;
   float R;
   ReadItem("text/Menu.txt");
   cout << "Enter Id of Item: ";
   cin >> Id;
   cout << "\nEnter Rating of Item";
   cin >> R;
   setrating(Id, R);
   for (int i = 5; i > 0; --i)
   {
      system("clear");
      cout << "Item Rated Successfuly\n\n";
      cout << "Going back to Portal in " << i << " seconds...\n"
           << flush;
      sleep(1);
   }
   portal();
}
void Administrator::ManageInventory()
{
   int S;
   int Id;
   cout << "Enter Id of Item: ";
   cin >> Id;
   cout << "\nEnter Value of stock to add: ";
   cin >> S;
   setstock(Id, S);

   for (int i = 5; i > 0; --i)
   {
      system("clear");
      cout << "Item Added to Menu Successfuly\n\n";
      cout << "Going back to Portal in " << i << " seconds...\n"
           << flush;
      sleep(1);
   }
   portal();
}
void Administrator::ViewUsersFromFile()
{
gopi:
   system("clear");
   cout << "Press\n1. To view Cafe staff\n";
   cout << "2. To view Faculty Customers\n";
   cout << "3. To view Non-Faculty Customers\n";
   cout << "4. To view Student Customers\n";
   int choice, i = 1;
   cin >> choice;

   ifstream file; // Use ifstream for reading from the file
   string fileName;

   switch (choice)
   {
   case 1:
      fileName = "text/staff.txt";
      cout << "-----------------------------------------Cafe Staff-----------------------------------------\n";
      break;
   case 2:
      fileName = "customer/Faculty.txt";
      cout << "-----------------------------------------Faculty-----------------------------------------\n";
      break;
   case 3:
      fileName = "customer/NonFaculty.txt";
      cout << "-----------------------------------------Non-Faculty-----------------------------------------\n";
      break;
   case 4:
      fileName = "customer/Students.txt";
      cout << "-----------------------------------------Students-----------------------------------------\n";
      break;
   default:
      cout << "Invalid choice\n";
      // A loop for delay
      for (int i = 5; i > 0; --i)
      {
         system("clear");
         cout << "Invalid choice....";
         cout << "Going back to Portal in " << i << " seconds...\n"
              << flush;
         sleep(1);
      }
      portal();
   }

   file.open(fileName, ios::in);
   if (!file)
   {
      cout << "Something went wrong. Try again...";
   }
   string line;
   while (getline(file, line))
   {
      // Use istringstream to split the line into username and password
      istringstream iss(line);
      string Username, Password;

      if (iss >> Username >> Password)
      {
         // Process Username and Password as needed
         // cout<<"---------------------------------------------------------------------------\n";

         cout << "ID " << i << " Username: " << Username << ", Password: " << Password << endl;
         i++;
      }
      else
      {
         cout << "Error reading line: " << line << endl;
      }
   }

   file.close();

   cout << "\n\nEnter 0 to go back\t\t\tEnter 1 to Go to Portal\n\t\t\t";
   cin >> i;
   switch (i)
   {
   case 0:
      goto gopi;

      break;
   case 1:
      portal();

      break;

   default:
      portal();
      break;
   }
}
void Administrator::ViewOrderHistory()
{
   ifstream OrderHistoryFile("text/orderHistory.txt");

   if (!OrderHistoryFile.is_open())
   {
      cout << "Unable to open order history file.\n";
      return;
   }

   string line;

   cout << "Order History\n";
   cout << "---------------------------\n";

   while (getline(OrderHistoryFile, line))
   {
      cout << line << "\n";

      // Display the order details until the "-----------------" separator
      while (getline(OrderHistoryFile, line) && line != "-----------------")
      {
         cout << line << "\n";
      }

      cout << "---------------------------\n";
   }
   string ask;
   cout << "Press Y to go back to portal: ";
   cin >> ask;
   OrderHistoryFile.close();
   portal();
}
void Administrator::CalculatemonthlyEarnings()
{
   
   ifstream OrderHistoryFile("text/orderHistory");

    if (!OrderHistoryFile.is_open())
    {
        cout << "Unable to open order history file.\n";
    }

    string line;
    double totalEarnings = 0.0;

    while (getline(OrderHistoryFile, line))
    {
        // Skip lines until the price is encountered
        while (getline(OrderHistoryFile, line) && line!= "Total Bill:");

        // Read the price and add it to the total earnings
        double price = 0.0;
        OrderHistoryFile >> price;
        totalEarnings += price;

        // Skip the rest of the current order entry until the "-----------------" separator
        while (getline(OrderHistoryFile, line) && line != "-----------------");
    }

    OrderHistoryFile.close();
   cout<<"Total sales this month till now: "<<totalEarnings;
   portal();
}
void Administrator::portal()
{
   int ret;
   int choice;
   do
   {
      system("clear");

      cout << "Press\n1. To view menu \n"; // item
      cout << "2. Add menu item \n";       // item
      cout << "3. Remove menu item \n";
      cout << "4. View order History\n"; // order
      cout << "5. Rate Menu Item\n";
      cout << "6. Manage inventory \n";
      cout << "7. View Users from File\n";
      cout << "8. Calculate Monthly Earnings\n"; // Payement
      cout << "9. Logout\n";
      cin >> choice;
      switch (choice)
      {
      case 1:
         ViewMenu();
         break;
      case 2:
         AddMenuItem();
         break;
      case 3:
         RemoveMenuItem();
         break;
      case 4:
         ViewOrderHistory();
         break;
      case 5:
         RateMenuItem();
         break;
      case 6:
         ManageInventory();
         break;
      case 7:
         ViewUsersFromFile();
         break;
      case 8:
         CalculatemonthlyEarnings();
      case 15:
         Logout();
         break;
      default:
         cout << "Invalid Choice Press 0 to Try Again else Exit..";
         cin >> ret;
         break;
      }
   } while (ret == 0);
}

///////////////////////////////////////Cafe Staff def//////////////////////////////////////////////

void CafeStaff::Login()
{
   int count = 1; // To count Input Attempts
again1:
   getlog();
   if (checkusertype(user, pass) == 1)
   {
      int ret;
      int choice;
      do
      {
         system("clear");

         cout << "Press\n1. To view menu \n";
         cout << "2. Add menu item \n";
         cout << "3. Remove menu item \n";
         cout << "4. Process Order\n";
         cout << "5. Logout\n";
         cin >> choice;
         switch (choice)
         {
         case 1:
            ViewMenu();
            break;
         case 2:
            AddMenuItem();
            break;
         case 3:
            RemoveMenuItem();
         case 4:
            ProcessOrder();
            break;
         case 5:
            Logout();
            break;

         default:
            cout << "\nInvalid Choice Press 0 to Try Again else Exit..";
            cin >> ret;
            break;
         }
      } while (ret == 0);
   }
   else
   {
      system("clear");
      if (count >= 5)
      {
         menu();
      }
      cout << "Wrong username or Password!......Try again (" << count++ << " attempts left).\n\n";
      goto again1;
   }
}
void CafeStaff::Register()
{
   system("clear");
   getreg();
   ofstream staff;
   staff.open("text/staff.txt", ios::app);
   if (!staff)
   {
      cout << "We can't access our staff data base please Try again Later";
   }
   else
   {
      staff << user << " " << pass << " " << endl;
   }

   staff.close();

   cout << "Registration Successful : Congratulations" << endl;
   for (int i = 7; i > 0; --i)
   {
      system("clear");

      cout << "Signing in " << i << " seconds...\n"
           << flush;
      sleep(1);
   }
   portallogged();
}
void CafeStaff::Logout()
{
   menu();
}
void CafeStaff::ViewMenu()
{
   {
      string e = "010101010";
      while (e == "010101010")
      {
         ReadItem("text/Menu.txt");
         cout << "\n\n\t\t\t\t\t\tPress any key to go back to portal...";
         cin >> e;
      }
      portallogged();
   }
}
void CafeStaff::ProcessOrder()
{
   cout<<"No Current Orders...";
   sleep(10);
   portallogged();
}
void CafeStaff::AddMenuItem()
{
   getitemdet();
   system("clear");

   ofstream Menu;
   Menu.open("text/Menu.txt", ios::app);
   if (!Menu)
   {
      cout << "We cannot find menu please check database\n";
      // A loop for delay
      for (int i = 5; i > 0; --i)
      {
         system("clear");
         cout << "Going back to Portal in " << i << " seconds...\n"
              << flush;
         sleep(1);
      }
      portal();
   }
   else
   {
      Menu << ItemID << endl
           << ItemName << endl
           << Price << endl
           << ItemDescription << endl
           << QuantityInStock << endl
           << Rating << endl;
   }

   Menu.close();

   // Introduce a 5-second countdown. A loop for delay
   for (int i = 5; i > 0; --i)
   {
      system("clear");
      cout << "Item Added to Menu Successfuly\n\n";
      cout << "Going back to Portal in " << i << " seconds...\n"
           << flush;
      sleep(1);
   }
   portal();
}
void CafeStaff::RemoveMenuItem()
{
   int Id;
   ReadItem("text/Menu.txt");
   cout << "Enter Id of Item to Remove: ";
   cin >> Id;
   removeitem(Id);
   for (int i = 5; i > 0; --i)
   {
      system("clear");
      cout << "Item Rated Successfuly\n\n";
      cout << "Going back to Portal in " << i << " seconds...\n"
           << flush;
      sleep(1);
   }
   portal();
}
void CafeStaff::portal()
{
   int ret;
   int choice;
   do
   {
      system("clear");

      cout << "Press\n1. To Login \n";
      cout << "2. To Register\n";
      cin >> choice;
      switch (choice)
      {
      case 1:
         Login();
         break;
      case 2:
         Register();
         break;
      case 4:
         // menu();
      default:
         cout << "Invalid Choice Press 0 to Try Again else Exit..";
         cin >> ret;
         break;
      }
   } while (ret == 0);
}
void CafeStaff::portallogged()
{
   int ret;
   int choice;
   do
   {
      system("clear");

      cout << "Press\n1. To view menu \n";
      cout << "2. Add menu item \n";
      cout << "3. Remove menu item \n";
      cout << "4. Process Order\n";
      cout << "5. Logout\n";
      cin >> choice;
      switch (choice)
      {
      case 1:
         ViewMenu();
         break;
      case 2:
         AddMenuItem();
         break;
      case 3:
         RemoveMenuItem();
      case 4:
         ProcessOrder();
         break;
      case 5:
         Logout();
         break;

      default:
         cout << "\nInvalid Choice Press 0 to Try Again else Exit..";
         cin >> ret;
         break;
      }
   } while (ret == 0);
}
///////////////////////////////////////Customer def////////////////////////////////////////////////

void Customer::Login()
{
   int count = 1; // attempt counter
again2:
   getlog();
   bool verified = false;
   usertype = "default";
   int userTypeResult = checkusertype(user, pass);

   switch (userTypeResult)
   {
   case 2:
      verified = true;
      usertype = "Faculty";
      break;
   case 3:
      verified = true;
      usertype = "Non-Faculty";
      break;
   case 4:
      verified = true;
      usertype = "Student";
      break;
   default:
      cout << "You are not found in our Data Base Please Register Your Self\n";
      break;
   }

   if (verified)
   {
      int ret;
      int choice;
      do
      {
         system("clear");
         cout << "\t\t\t\tWelcome to " << usertype << " Portal\n\n";
         cout << "Press\n1. To view menu \n";
         cout << "2. Place Order \n";
         cout << "3. View Order History \n";
         cout << "4. Jangoooo\n";
         cout << "5. Logout\n";
         cin >> choice;
         switch (choice)
         {
         case 1:
            ViewMenu();
            break;
         case 2:
            PlaceOrder();
            break;
         case 3:
            ViewOrderHistory();
            break;
         case 4:
            // Logout();
            break;
         case 5:
            Logout();
            break;

         default:
            cout << "Invalid Choice Press 0 to Try Again else Exit..";
            cin >> ret;
            break;
         }
      } while (ret == 0);
   }
   else
   {
      system("clear");
      if (count >= 5)
      {
         menu();
      }
      cout << "Wrong username or Password!......Try again (" << count++ << " attempts left).\n\n";
      goto again2;
   }
}
void Customer::Register()
{
   int usertype;
   cout << "Press\n1. If you are a Faculty customer\n2. If you are a Non-Faculty customer\n3. If you are a Student\n\n";
   cin >> usertype;
   string fileName;

   switch (usertype)
   {
   case 1:
      fileName = "customer/Faculty.txt";
      cout << "-----------------------------------------Faculty-----------------------------------------\n";
      break;
   case 2:
      fileName = "customer/NonFaculty.txt";
      cout << "-----------------------------------------Non-Faculty-----------------------------------------\n";
      break;
   case 3:
      fileName = "customer/Student.txt";
      cout << "-----------------------------------------Students-----------------------------------------\n";
      break;
   default:
      for (int i = 2; i > 0; --i)
      {
         system("clear");
         cout << "Invalid choice....";
         cout << "Going back to Portal in " << i << " seconds...\n"
              << flush;
         sleep(1);
      }
      portal();
   }
   // Getting Regitration Details
   system("clear");
   getreg();
   // Registring the user on file
   ofstream file;
   file.open(fileName, ios::app);
   if (!file)
   {
      cout << "We can't access our data base please Try again Later";
   }
   else
   {
      file << user << " " << pass << " " << endl;
   }

   file.close();

   cout << "Registration Successful : Congratulations" << endl
        << endl;
   // A loop for delay
   for (int i = 7; i > 0; --i)
   {

      system("clear");
      cout << "Signing in " << i << " seconds...\n"
           << flush;
      sleep(1);
   }
   portal();
}
void Customer::Logout()
{
   menu();
}
void Customer::ViewMenu()
{
   {
      {
         string e = "010101010";
         while (e == "010101010")
         {
            if (usertype == "Faculty")
            {
               ReadItem("text/Menu.txt");
            }
            else if (usertype == "Non-Faculty" || usertype == "Student")
            {
               ReadItem("text/Menu.txt", 10);
            }
            cout << "\n\n\t\t\t\t\t\tPress any key to go back to portal...";
            cin >> e;
         }
         portallogged();
      }
   }
}
void Customer::Displaybill(Order items[], int itemCount, double totalBill)
{
   string ask;
   cout << "---------------------------\n";
   cout << "          Bill\n";
   cout << "---------------------------\n";

   for (int i = 0; i < itemCount; ++i)
   {
      cout << "Item ID: " << items[i].ID << "\n";
      cout << "Item Name: " << items[i].Name << "\n";
      cout << "Item Price: " << items[i].pprice << "\n";
      cout << "---------------------------\n";
   }
   if (usertype == "Faculty")
   {
      cout << "Total Bill: " << totalBill << "\n";
      cout<<"Faculty Discount 30%: -"<<(0.3*totalBill);
      cout<< "Discounted Bill: "<<(0.7*totalBill);
      cout << "---------------------------\n";
   }

   cout << "\nDo you want to go back to portal or logout(y/n): ";
   cin >> ask;
   if (ask == "y")
   {
      portallogged();
   }
   menu();
}
void Customer::PlaceOrder()
{
   if (usertype == "Faculty")
   {
      ReadItem("text/Menu.txt");
   }
   else if (usertype == "Non-Faculty" || usertype == "Student")
   {
      ReadItem("text/Menu.txt", 10);
   }
   string ask;
   Order items[100];
   int I, i = 0; // Initialize i to 0 instead of 1
   double totalBill = 0.0;

   do
   {
      cout << "\n\n\t\t\tAnything you like to order?(y/n)\n";
      cin >> ask;
      if (ask == "y")
      {
         cout << "\nEnter Item ID(from menu above): ";
         cin >> I;
         fstream Menu("text/Menu.txt", ios::in | ios::out);

         while (Menu >> ItemID)
         {
            // Read other data for the current item
            getline(Menu >> ws, ItemName);
            Menu >> Price >> ws;
            getline(Menu >> ws, ItemDescription);
            Menu >> QuantityInStock >> ws;
            Menu >> Rating >> ws;

            // Check if the current item has the specified ID
            if (ItemID == I)
            {
               items[i].ID = I;
               items[i].Name = ItemName;
               items[i].pprice = Price;
               totalBill += Price;
               i++;
            }
         }

         cout << "Item with ID " << I << " Added to cart\n";
      }

   } while (ask == "y");

   cout << "Total bill is: " << totalBill << endl;
   cout << "Do You want to confirm Order(y/n)?: ";
   cin >> ask;

   if (ask == "y")
   {
      for (int j = 10; j > 0; --j)
      {
         system("clear");
         cout << "\t\t\tDone with ordering...Be patient while We prepare it\n";
         cout << j << " seconds...\n"
              << flush;
         sleep(1);
      }

      system("clear");
      cout << "Order Prepared. Enjoy your meal!\n";

      // Save the order to a file with User ID
      ofstream OrderHistory("text/orderHistory");

      if (OrderHistory.is_open())
      {

         for (int j = 0; j < i; ++j)
         {
            OrderHistory << user << "\n";
            OrderHistory << items[j].ID << "\n";
            OrderHistory << items[j].Name << "\n";
            OrderHistory << items[j].pprice << "\n";
            OrderHistory << "-----------------\n";
         }

         OrderHistory << "Total Bill: " << totalBill << "\n";
         // OrderHistory << "Order Date and Time: " << getCurrentDateTime() << "\n";

         OrderHistory.close();
      }

      cout << "Do you want to Proceed with The bill?(y/n): ";
      cin >> ask;
      if (ask == "y")
      {
         Displaybill(items, i, totalBill);
      }
      cout << "Payement Pending!!!";
      sleep(5);
      cout << "Going back to poratl";
   }
}
void Customer::ViewOrderHistory()
{
   ifstream OrderHistoryFile("text/orderHistory");

   if (!OrderHistoryFile.is_open())
   {
      cout << "Unable to open order history file.\n";
      return;
   }

   string line;
   bool foundUser = false;

   while (getline(OrderHistoryFile, line))
   {
      if (line == user)
      {
         foundUser = true;
         cout << "Order History for User: " << user << "\n";
         cout << "---------------------------\n";

         // Display the order details
         while (getline(OrderHistoryFile, line) && line != "-----------------")
         {
            cout << line << "\n";
         }

         cout << "---------------------------\n";
         string ask;
         cout << "Press y to go back to portal: ";
         cin >> ask;
         portallogged();
      }
   }

   OrderHistoryFile.close();

   if (!foundUser)
   {
      cout << "No order history found for User: " << user << "\n";
   }
}
void Customer::portal()
{
   int ret;
   int choice;
   do
   {
      system("clear");

      cout << "Press\n1. To Login \n";
      cout << "2. To Register\n";
      cin >> choice;
      switch (choice)
      {
      case 1:
         Login();
         break;
      case 2:
         Register();
         break;
      case 4:
         // menu();
      default:
         cout << "Invalid Choice Press 0 to Try Again else Exit..";
         cin >> ret;
         break;
      }
   } while (ret == 0);
}
void Customer::portallogged()
{
   int ret;
   int choice;
   do
   {
      system("clear");
      cout << "\t\t\t\tWelcome to " << usertype << " Portal\n\n";
      cout << "Press\n1. To view menu \n";
      cout << "2. Place Order \n";
      cout << "3. View Order History \n";
      cout << "4. Jangoooo\n";
      cout << "5. Logout\n";
      cin >> choice;
      switch (choice)
      {
      case 1:
         ViewMenu();
         break;
      case 2:
         PlaceOrder();
         break;
      case 3:
         ViewOrderHistory();
         break;
      case 4:
         // Logout();
         break;
      case 5:
         Logout();
         break;

      default:
         cout << "Invalid Choice Press 0 to Try Again else Exit..";
         cin >> ret;
         break;
      }
   } while (ret == 0);
}
///////////////////////////////////////Check's def/////////////////////////////////////////////////
bool check::checkUser(string a, string b, string checkfile)
{
   fstream file;
   file.open(checkfile, ios::in);
   if (!file)
   {
      cout << "This File not found in Database...Try again...";
   }
   while (!file.eof())
   {
      file >> User >> Pass;
      if (a == User && b == Pass)
      {
         isfound = 1;
         break;
      }
      else
      {
         isfound = 0;
      }
   }
   return isfound;
}
int check::checkusertype(string a, string b)
{
   if (checkUser(a, b, "text/staff.txt") == 1)
   {
      return 1;
   }
   else if (checkUser(a, b, "Customer/Faculty.txt") == 1)
   {
      return 2;
   }
   else if (checkUser(a, b, "Customer/NonFaculty.txt") == 1)
   {
      return 3;
   }
   else if (checkUser(a, b, "Customer/Student.txt") == 1)
   {
      return 4;
   }
   return 0; // Or any other value indicating an unknown user type.
}

///////////////////////////////////////MenuItem's def//////////////////////////////////////////////

void MenuItem::getitemdet()
{
   // Prompt user for input
   cout << "Enter Item ID: ";
   cin >> ItemID;

   cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear newline from buffer

   cout << "Enter Item Name: ";
   getline(cin, ItemName);

   cout << "Enter Item Description: ";
   getline(cin, ItemDescription);

   cout << "Enter Price: PKR";
   cin >> Price;

   cout << "Enter Quantity In Stock: ";
   cin >> QuantityInStock;
}
void MenuItem::ReadItem(string file)
{
   system("clear");

   ifstream Menu;
   Menu.open(file, ios::in);

   if (!Menu)
   {
      cout << "Menu Not found in the database. Please check it.\n";

      for (int i = 5; i > 0; --i)
      {
         system("clear");
         cout << "Going back to Portal in " << i << " seconds...\n"
              << flush;
         sleep(1);
      }
      // portal();
   }
   else
   {
      // Print header
      cout << "-------------------------------------------------------------------------------------------------------------------------\n\n";

      // Reading from the file
      while (Menu >> ItemID >> ws)
      {
         getline(Menu, ItemName) >> ws;
         Menu >> ws >> Price >> ws;
         getline(Menu, ItemDescription) >> ws;
         Menu >> QuantityInStock >> ws;
         Menu >> Rating >> ws;

         // Print each item
         cout << "ItemID: " << ItemID << "\n"
              << "Item Name: " << ItemName << "\n"
              << "Item Price: Pkr" << fixed << setprecision(2) << Price << "\n"
              << "Item Description: " << ItemDescription << "\n"
              << "Quantity: " << QuantityInStock << "\n"
              << "Rating: " << Rating << "\n\n";
         cout << "-------------------------------------------------------------------------------------------------------------------------\n\n";
      }

      // Print footer
   }

   Menu.close();
}
void MenuItem::ReadItem(string file, int quant)
{
   {
      system("clear");

      ifstream Menu;
      Menu.open(file, ios::in);

      if (!Menu)
      {
         cout << "Menu Not found in the database. Please check it.\n";

         for (int i = 5; i > 0; --i)
         {
            system("clear");
            cout << "Going back to Portal in " << i << " seconds...\n"
                 << flush;
            sleep(1);
         }
         // portal();
      }
      else
      {
         // Print header
         cout << "-------------------------------------------------------------------------------------------------------------------------\n\n";

         // Reading from the file
         do
         {
            Menu >> ItemID >> ws;
            getline(Menu, ItemName) >> ws;
            Menu >> ws >> Price >> ws;
            getline(Menu, ItemDescription) >> ws;
            Menu >> QuantityInStock >> ws;
            Menu >> Rating >> ws;

            // Print each item
            cout << "ItemID: " << ItemID << "\n"
                 << "Item Name: " << ItemName << "\n"
                 << "Item Price: Pkr" << fixed << setprecision(2) << Price << "\n"
                 << "Item Description: " << ItemDescription << "\n"
                 << "Quantity: " << QuantityInStock << "\n"
                 << "Rating: " << Rating << "\n\n";
            cout << "-------------------------------------------------------------------------------------------------------------------------\n\n";
         } while (ItemID <= quant);

         // Print footer
      }

      Menu.close();
   }
}
void MenuItem::setrating(int ID, float R)
{
   system("clear");

   fstream Menu("text/Menu.txt", ios::in | ios::out);

   if (!Menu)
   {
      cout << "Menu Not found in the database. Please check it.\n";

      for (int i = 5; i > 0; --i)
      {
         system("clear");
         cout << "Going back to Portal in " << i << " seconds...\n"
              << flush;
         sleep(1);
      }
      // portal();
      return;
   }
   else
   {
      // Store the current position in the file
      streampos currentPos = Menu.tellg();

      while (Menu >> ItemID)
      {
         // Read other data for the current item
         getline(Menu >> ws, ItemName);
         Menu >> Price >> ws;
         getline(Menu >> ws, ItemDescription);
         Menu >> QuantityInStock >> ws;
         Menu >> Rating >> ws;

         // Check if the current item has the specified ID
         if (ItemID == ID)
         {
            // Update the rating
            Rating = (Rating + R) / 2;

            // Move the file pointer back to the beginning of the current record
            Menu.seekp(currentPos);

            // Output the updated item information to the file with fixed precision
            Menu << ItemID << "\n"
                 << ItemName << "\n"
                 << Price << "\n"
                 << ItemDescription << "\n"
                 << QuantityInStock << "\n"
                 << Rating << "\n\n";

            // Move the file pointer to the end of the file
            Menu.seekg(0, ios::end);
         }

         // Store the current position in the file
         currentPos = Menu.tellg();
      }
   }

   // Close the file
   Menu.close();
}
void MenuItem::setstock(int ID, int S)
{
   system("clear");

   fstream Menu("text/Menu.txt", ios::in | ios::out);

   if (!Menu)
   {
      cout << "Menu Not found in the database. Please check it.\n";

      for (int i = 5; i > 0; --i)
      {
         system("clear");
         cout << "Going back to Portal in " << i << " seconds...\n"
              << flush;
         sleep(1);
      }
      // portal();
      return;
   }
   else
   {
      // Store the current position in the file
      streampos currentPos = Menu.tellg();

      while (Menu >> ItemID)
      {
         // Read other data for the current item
         getline(Menu >> ws, ItemName);
         Menu >> Price >> ws;
         getline(Menu >> ws, ItemDescription);
         Menu >> QuantityInStock >> ws;
         Menu >> Rating >> ws;

         // Check if the current item has the specified ID
         if (ItemID == ID)
         {
            // Update the quantity in stock
            QuantityInStock += S;

            // Move the file pointer back to the beginning of the current record
            Menu.seekp(currentPos);

            // Output the updated item information to the file
            Menu << ItemID << "\n"
                 << ItemName << "\n"
                 << Price << "\n"
                 << ItemDescription << "\n"
                 << QuantityInStock << "\n"
                 << Rating << "\n";

            // Move the file pointer to the end of the file
            Menu.seekg(0, ios::end);
         }

         // Store the current position in the file
         currentPos = Menu.tellg();
      }
   }

   // Close the file
   Menu.close();
}
void MenuItem::removeitem(int ID)
{

   system("clear");

   ifstream Menu;
   Menu.open("text/Menu.txt", ios::in);

   if (!Menu)
   {
      cout << "Menu Not found in the database. Please check it.\n";

      for (int i = 5; i > 0; --i)
      {
         system("clear");
         cout << "Going back to Portal in " << i << " seconds...\n"
              << flush;
         sleep(1);
      }
   }
   else
   {
      ofstream TempMenu("text/TempMenu.txt", ios::out);

      // Store the current position in the file
      streampos currentPos = Menu.tellg();
      int check = 0;
      while (Menu >> ItemID)
      {

         // Read other data for the current item
         getline(Menu >> ws, ItemName);
         Menu >> Price >> ws;
         getline(Menu >> ws, ItemDescription);
         Menu >> QuantityInStock >> ws;
         Menu >> Rating >> ws;
         if (check == 1)
         {
            ItemID = ItemID - 1;
            cout << "Check tru\n";
         }

         // Check if the current item has the specified ID
         if (ItemID == ID)
         {
            // Move the file pointer to the end of the file
            //  Menu.seekg(0, ios::end);
            check = 1;
            cout << "Got itemid\n";
         }
         else
         {
            // Output the item information to the temporary file
            TempMenu << ItemID << "\n"
                     << ItemName << "\n"
                     << Price << "\n"
                     << ItemDescription << "\n"
                     << QuantityInStock << "\n"
                     << Rating << "\n\n";
         }

         // Store the current position in the file
         currentPos = Menu.tellg();
      }

      // Close both files
      Menu.close();
      TempMenu.close();

      // Remove the original file
      remove("text/Menu.txt");

      // Rename the temporary file to the original file
      rename("text/TempMenu.txt", "text/Menu.txt");
   }
}

///////////////////////////////////////Order's def//////////////////////////////////////////////
/*
// Order(int id, int customerID)
//  : OrderID(id), CustomerID(customerID), TotalPrice(0), OrderStatus("Pending"){}
void Customer::getitem(int id)
{

   fstream Menu("text/Menu.txt", ios::in | ios::out);

   if (!Menu)
   {
      cout << "Menu Not found in the database. Please check it.\n";

      for (int i = 5; i > 0; --i)
      {
         system("clear");
         cout << "Going back to Portal in " << i << " seconds...\n"
              << flush;
         sleep(1);
      }
      // portal();
      return;
   }
   else
   {
      while (Menu >> ItemID)
      {
         // Read other data for the current item
         getline(Menu >> ws, ItemName);
         Menu >> Price >> ws;
         getline(Menu >> ws, ItemDescription);
         Menu >> QuantityInStock >> ws;
         Menu >> Rating >> ws;

         // Check if the current item has the specified ID
         if (ItemID == id)
         {

            Order order(ItemID, ItemName, Price);
         }
      }
   }

   // Close the file
   Menu.close();
}
void Order::AddItem()
{

}

//void Order::RemoveItem(const MenuItem& item) {
    // Implement removing an item from the order
// }

void Order::CalculateTotal() {
    // Implement calculating the total price
}

void Order::ConfirmOrder() {
    // Implement confirming the order
}

void Order::CancelOrder() {
    // Implement canceling the order
}*/