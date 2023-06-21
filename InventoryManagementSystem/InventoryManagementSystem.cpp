// Inventory Management System
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Item
{
  int item_id;
  string item_name;
  int item_quantity;
  string item_registration_date;

  bool isEmpty() const
  {
    // Check if any of the essential fields is empty or uninitialized
    return (item_id == 0) || item_name.empty() || (item_quantity == 0) || item_registration_date.empty();
  }
};

// custom stoi function
int custom_stoi(const std::string &str)
{
  int result = 0;
  int sign = 1;
  size_t i = 0;

  if (str[0] == '-')
  {
    sign = -1;
    i = 1;
  }

  for (; i < str.length(); i++)
  {
    result = result * 10 + (str[i] - '0');
  }

  return sign * result;
}

// validate the user input to match item structure
bool validateItem(const Item &itemToValidate)
{
  // Check if item_id is positive
  if (itemToValidate.item_id < 0)
  {
    std::cout << "Invalid item_id" << std::endl;
    return false;
  }

  // Check if item_name is not empty
  if (itemToValidate.item_name.empty())
  {
    std::cout << "Invalid item_name" << std::endl;
    return false;
  }

  // Check if item_quantity is non-negative
  if (itemToValidate.item_quantity < 0)
  {
    std::cout << "Invalid item_quantity" << std::endl;
    return false;
  }

  // Check if item_registration_date is not empty
  if (itemToValidate.item_registration_date.empty())
  {
    std::cout << "Invalid item_registration_date" << std::endl;
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
  cout << "                                                                       " << endl;
  cout << "               * It is developed by RCA Ntagungira Ali Rashid *" << endl;
  cout << "                     * DSA Evaluation of end of year 3 *           " << endl;
  cout << "                                                                        " << endl;
}

void addItem(const string filename, const Item &itemToAdd)
{
  ifstream file(filename.c_str());
  if (file)
  {
    string line;
    while (std::getline(file, line))
    {
      stringstream ss(line);
      string idStr;
      string nameStr;
      getline(ss, idStr, ',');

      // Check if the item ID already exists in the file
      if (custom_stoi(idStr) == itemToAdd.item_id)
      {
        cout << "Item with the same ID already exists. Cannot add the item.";
        return;
      }
      if (nameStr == itemToAdd.item_name)
      {
        cout << "Item with the same name already exists. Cannot add the item.";
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
      throw std::runtime_error("Failed to open file: " + filename);
    }

    outfile << itemToAdd.item_id << "," << itemToAdd.item_name << "," << itemToAdd.item_quantity << "," << itemToAdd.item_registration_date << std::endl;

    if (outfile.fail())
    {
      throw std::runtime_error("Failed to write to file: " + filename);
    }

    outfile.close();
    std::cout << "Item " << itemToAdd.item_name << " has been added successfully!" << std::endl;
  }
  catch (const std::exception &e)
  {
    std::cout << "Error: " << e.what() << std::endl;
  }
}

// sort compare item names during sorting
bool compareItems(const Item &item1, const Item &item2)
{
  return item1.item_id < item2.item_id;
}

// Display sorted items
void listItems(const std::string &filename)
{
  std::ifstream file(filename.c_str());
  if (!file)
  {
    std::cerr << "Error opening file: " << filename << std::endl;
    return;
  }

  vector<Item> items;

  std::string line;
  while (getline(file, line))
  {
    std::istringstream iss(line);
    Item itemRead;

    std::string idStr;
    std::string quantityStr;

    getline(iss, idStr, ',');
    getline(iss, itemRead.item_name, ',');
    getline(iss, quantityStr, ',');
    getline(iss, itemRead.item_registration_date, ',');
    itemRead.item_id = stoi(idStr);
    itemRead.item_quantity = stoi(quantityStr);

    if(itemRead.isEmpty()){
      items.push_back(itemRead);
    }
    else
    {
      cerr << "Error parsing line: " << line << std::endl;
    }
  }

  sort(items.begin(), items.end(), compareItems);

  for (size_t i = 0; i < items.size(); i++)
  {
    const Item &item = items[i];
    std::cout << "Item ID: " << item.item_id << "  ";
    std::cout << "Item Name: " << item.item_name << "  ";
    std::cout << "Item Quantity: " << item.item_quantity << "  ";
    std::cout << "Item Registration Date: " << item.item_registration_date << "  " << std::endl;
    std::cout << std::endl;
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
  cout << endl;
  cout << "                *******************************************" << endl;
  cout << "                *      Enter a command of your choice     *" << endl;
  cout << "                *******************************************" << endl;

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
    else if (commandName == "exit")
    {
      break;
    }
    else
    {
      std::cout << "Invalid command" << std::endl;
    }
  }
  return 0;
}