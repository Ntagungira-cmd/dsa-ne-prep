// Inventory Management System
#include "CustomExceptions.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

struct Item
{
  string item_id;
  string item_name;
  string item_quantity;
  string item_registration_date;
};

// check if string is numeric
bool isNumeric(const string &str)
{
  for (size_t i = 0; i < str.length(); i++)
  {
    if (!isdigit(str[i]))
      return false;
  }
  return true;
}

bool validateItem(const Item &itemToValidate)
{
  // Check if item_id is positive and numeric
  if (itemToValidate.item_id.empty() || !isNumeric(itemToValidate.item_id))
  {
    cout << "Invalid item_id" << endl;
    return false;
  }

  // Check if item_name is not empty and within a valid length range
  if (itemToValidate.item_name.empty() || itemToValidate.item_name.length() > 20)
  {
    cout << "Invalid item_name" << endl;
    return false;
  }

  // Check if item_quantity is non-negative and numeric
  if (itemToValidate.item_quantity.empty() || !isNumeric(itemToValidate.item_quantity))
  {
    cout << "Invalid item_quantity" << endl;
    return false;
  }

  // Check if item_registration_date is in a valid format (assuming YYYY-MM-DD)
  if (itemToValidate.item_registration_date.empty() || itemToValidate.item_registration_date.length() != 10 ||
      itemToValidate.item_registration_date[4] != '-' || itemToValidate.item_registration_date[7] != '-')
  {
    cout << "Invalid item_registration_date" << endl;
    return false;
  }

  // All validations passed, return true
  return true;
}

// capitalise string
string toLowerCase(string text)
{
  string result = "";
  for (size_t i = 0; i < text.size(); i++)
  {
    char c = tolower(text[i]);
    result += c;
  }
  return result;
}

void welcome_screen()
{
  cout << "              =================================================       " << endl;
  cout << "              *   Welcome To Inventory Management System!   *" << endl;
  cout << "              * ********************************************** *" << endl;
  cout << endl;
  cout << "     *      Enter a command of your choice or help for assistance     *" << endl;
  cout << endl;
}


// Add item to file
void addItem(const string filename, const Item &itemToAdd)
{
  ifstream file(filename.c_str());
  if (file)
  {
    string line;
    while (getline(file, line))
    {
      stringstream ss(line);
      string idStr;
      string nameStr;
      getline(ss, idStr, ',');
      getline(ss, nameStr, ',');

      // Check if the item ID already exists in the file
      if (idStr == itemToAdd.item_id)
      {
        cout << "Item with the same ID already exists. Cannot add the item."<< endl;
        return;
      }
      if (nameStr == toLowerCase(itemToAdd.item_name))
      {
        cout << "Item with the same name already exists. Cannot add the item."<< endl;
        return;
      }
      else
      {
        continue;
      }
    }
  }

  ofstream outfile;
  try
  {
    outfile.open(filename.c_str(), ios::app);
    if (!outfile.is_open())
    {
      throw FileOpenException("Failed to open file: " + filename);
    }

    outfile << itemToAdd.item_id << "," << toLowerCase(itemToAdd.item_name) << "," << toLowerCase(itemToAdd.item_quantity) << "," << itemToAdd.item_registration_date <<endl;

    if (outfile.fail())
    {
      throw FileWriteException("Failed to write to file: " + filename);
    }

    outfile.close();
    cout << "Item " << itemToAdd.item_name << " has been added successfully!" << endl;
  }
  catch (const exception &e)
  {
    cout << "Error: " << e.what() << endl;
  }
}



// sort compare item names during sorting
bool compareName(const Item &item1, const Item &item2)
{
  return item1.item_name < item2.item_name;
}

// Display sorted items
void listItems(const string &filename)
{
  ifstream file(filename.c_str());
  // ifstream file("");
  if (!file)
  {
    throw FileOpenException("Error opening file: " + filename);
    return;
  }

  vector<Item> items;

  string line;
  while (getline(file, line))
  {
    istringstream iss(line);
    Item itemRead;

    getline(iss, itemRead.item_id, ',');
    getline(iss, itemRead.item_name, ',');
    getline(iss, itemRead.item_quantity, ',');
    getline(iss, itemRead.item_registration_date, ',');

    items.push_back(itemRead);
  }

  sort(items.begin(), items.end(), compareName);

  for (size_t i = 0; i < items.size(); i++)
  {
    const Item &item = items[i];
    cout << "Item ID: " << item.item_id << "  ";
    cout << "Item Name: " << item.item_name << "  ";
    cout << "Quantity: " << item.item_quantity << "  ";
    cout << "Item Registration Date: " << item.item_registration_date << "  " << endl;
    cout << endl;
  }
}

void help()
{
  cout << "         *******************************************" << endl;
  cout << "         *      Command Syntaxes                    *" << endl;
  cout << "         *******************************************" << endl;
  cout << "  *      itemadd <item_id> <item_name> <item_quantity> <item_registration_date>     *" << endl;
  cout << "  *      itemslist     *" << endl;
  cout << "  *      help     *" << endl;
}

int main()
{
  // file we will be working with
  const string fileName = "inventory.csv";

  // command to be entered
  string command;

  // display welcome screen
  welcome_screen();

  // command line
  while (true)
  {
    cout << "console>";
    getline(cin, command);
    istringstream iss(command);
    string commandName;
    // item to be added;
    Item itemToAdd;

    iss >> commandName >> itemToAdd.item_id >> itemToAdd.item_name >> itemToAdd.item_quantity >> itemToAdd.item_registration_date;

    if (toLowerCase(commandName) == "itemadd")
    {
      if (validateItem(itemToAdd))
      {
        addItem(fileName, itemToAdd);
      }
    }
    else if (toLowerCase(commandName) == "itemslist")
    {
      cout << endl;
      cout << "******** List of All items in inventory *********" << endl;
      cout << endl;
      listItems(fileName);
    }
    else if (toLowerCase(commandName) == "help")
    {
      help();
    }
    else if (toLowerCase(commandName) == "exit")
    {
      break;
    }
    else
    {
      cout << "Invalid command" << endl;
    }
  }
  return 0;
}