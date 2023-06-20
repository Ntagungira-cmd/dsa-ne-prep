#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>

using namespace std;

// This is a banking system in C++.

struct Account
{
  string name;
  string accountNumber;
  double balance;
};

const string ACCOUNT_FILE = "accounts.csv";

//function to convert string to double
double stringToDouble(const std::string &str)
{
  double d;
  std::istringstream iss(str);
  iss >> d;
  return d;
}
void createAccount()
{
  // check if account file exists and create it if it doesn't and then open it in append mode
  ofstream accountFile(ACCOUNT_FILE.c_str(), ios::app);
  if (!accountFile)
  {
    cerr << "Error creating account file" << endl;
    return;
  }
  // initialize account object
  Account account;
  cout << "Enter your name: ";
  getline(cin >> ws, account.name);
  cout << "Enter your account number: ";
  getline(cin >> ws, account.accountNumber);
  cout << "Enter your account balance: ";
  cin >> account.balance;
  // save account to file
  accountFile << account.name << "," << account.accountNumber << "," << account.balance << endl;
  // close file
  accountFile.close();
  cout << "Account created successfully" << endl;
}

// function to do a deposit
void deposit()
{
  cout << "Deposit" << endl;
  // check if account file exists
  ifstream accountFile(ACCOUNT_FILE.c_str());
  if (!accountFile)
  {
    cerr << "Error opening account file" << endl;
    return;
  }

  ofstream tempFile("temp.csv");
  if (!tempFile)
  {
    cerr << "Error creating temp file" << endl;
    return;
  }
  bool found = false;
  string line;
  string accountNumber;
  double depositAmount;
  cout << "Enter your account number: ";
  getline(cin >> ws, accountNumber);
  cout << "Enter amount to deposit: ";
  cin >> depositAmount;
  // read account file line by line
  while (getline(accountFile, line))
  {
    // initialize account object
    Account account;
    // parse line to get account details
    size_t pos = line.find(",");
    account.name = line.substr(0, pos);
    line.erase(0, pos + 1);
    pos = line.find(",");
    account.accountNumber = line.substr(0, pos);
    line.erase(0, pos + 1);
    account.balance = stringToDouble(line);
    if (account.accountNumber == accountNumber)
    {
      account.balance += depositAmount;
      found = true;
    }
    tempFile << account.name << "," << account.accountNumber << "," << account.balance << endl;
  }
  accountFile.close();
  tempFile.close();
  remove(ACCOUNT_FILE.c_str());
  rename("temp.csv", ACCOUNT_FILE.c_str());

  if (found == true)
  {
    cout << "Deposit Succefull" << endl;
  }
  else
  {
    cout << "Deposit failed!! account may not exist" << endl;
  }
}

// function to do a withdrawal
void withdraw()
{
  cout << "Withdraw" << endl;
  // check if account file exists
  ifstream accountFile(ACCOUNT_FILE.c_str());
  if (!accountFile)
  {
    cerr << "Error opening account file" << endl;
    return;
  }
  ofstream tempFile("temp.csv");
  if (!tempFile)
  {
    cerr << "Error creating temp file" << endl;
    return;
  }
  bool found = false;
  string line;
  string accountNumber;
  double withdrawAmount;
  cout << "Enter your account number: ";
  getline(cin >> ws, accountNumber);
  cout << "Enter amount to withdraw: ";
  cin >> withdrawAmount;
  // read account file line by line
  while (getline(accountFile, line))
  {
    // initialize account object
    Account account;
    // parse line to get account details
    size_t pos = line.find(",");
    account.name = line.substr(0, pos);
    line.erase(0, pos + 1);
    pos = line.find(",");
    account.accountNumber = line.substr(0, pos);
    line.erase(0, pos + 1);
    account.balance = stringToDouble(line);
    if (account.accountNumber == accountNumber)
    {
      if (account.balance >= withdrawAmount)
      {
        account.balance -= withdrawAmount;
        found = true;
      }
      else
      {
        cout << "Insufficient balance" << endl;
      }
    }
    tempFile << account.name << "," << account.accountNumber << "," << account.balance << endl;
  }
  accountFile.close();
  tempFile.close();
  remove(ACCOUNT_FILE.c_str());
  rename("temp.csv", ACCOUNT_FILE.c_str());
  if (found == true)
  {
    cout << "Withdrawal Succefull" << endl;
  }
  else
  {
    cout << "Withdrawal failed!! account may not exist" << endl;
  }
}

// function to check balance
void checkBalance()
{
  cout << "Check balance" << endl;
  // check if account file exists
  ifstream accountFile(ACCOUNT_FILE.c_str());
  if (!accountFile)
  {
    cerr << "Error opening account file" << endl;
    return;
  }
  bool found = false;
  string line;
  string accountNumber;
  cout << "Enter your account number: ";
  getline(cin >> ws, accountNumber);
  // read account file line by line
  while (getline(accountFile, line))
  {
    // initialize account object
    Account account;
    // parse line to get account details
    size_t pos = line.find(",");
    account.name = line.substr(0, pos);
    line.erase(0, pos + 1);
    pos = line.find(",");
    account.accountNumber = line.substr(0, pos);
    line.erase(0, pos + 1);
    account.balance = stringToDouble(line);
    if (account.accountNumber == accountNumber)
    {
      cout << "Your balance is: " << account.balance << endl;
      found = true;
    }
  }
  accountFile.close();
  if (found == false)
  {
    cout << "Account not found" << endl;
  }
}

// function to transfer money
void transfer()
{
  cout << "Transfer" << endl;
  // check if account file exists
  ifstream accountFile(ACCOUNT_FILE.c_str());
  if (!accountFile)
  {
    cerr << "Error opening account file" << endl;
    return;
  }
  ofstream tempFile("temp.csv");
  if (!tempFile)
  {
    cerr << "Error creating temp file" << endl;
    return;
  }
  bool found = false;
  string line;
  string senderAccountNumber;
  string receiverAccountNumber;
  double transferAmount;
  cout << "Enter your account number: ";
  getline(cin >> ws, senderAccountNumber);
  cout << "Enter receiver account number: ";
  getline(cin >> ws, receiverAccountNumber);
  cout << "Enter amount to transfer: ";
  cin >> transferAmount;
  // read account file line by line
  while (getline(accountFile, line))
  {
    // initialize account object
    Account account;
    // parse line to get account details
    size_t pos = line.find(",");
    account.name = line.substr(0, pos);
    line.erase(0, pos + 1);
    pos = line.find(",");
    account.accountNumber = line.substr(0, pos);
    line.erase(0, pos + 1);
    account.balance = stringToDouble(line);
    // check if sender account number matches
    if (account.accountNumber == senderAccountNumber)
    {
      if (account.balance >= transferAmount)
      {
        account.balance -= transferAmount;
        found = true;
      }
      else
      {
        cout << "Insufficient balance" << endl;
      }
    }
    // check if receiver account number matches
    if (account.accountNumber == receiverAccountNumber)
    {
      account.balance += transferAmount;
    }
    tempFile << account.name << "," << account.accountNumber << "," << account.balance << endl;
  }
  accountFile.close();
  tempFile.close();
  remove(ACCOUNT_FILE.c_str());
  rename("temp.csv", ACCOUNT_FILE.c_str());
  if (found == true)
  {
    cout << "Transfer Succefull" << endl;
  }
  else
  {
    cout << "Transfer failed!! account may not exist" << endl;
  }
}

void consoleDecoration()
{
  // make console look good for user experience
  cout << "=====Welcome to the banking system=====" << endl;
  cout << "1. Create account" << endl;
  cout << "2. Deposit" << endl;
  cout << "3. Withdraw" << endl;
  cout << "4. Check balance" << endl;
  cout << "5. Transfer" << endl;
  cout << "0. Exit" << endl;
}

int main()
{
  int choice;

  do
  {
    consoleDecoration();
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
      createAccount();
      break;
    case 2:
      deposit();
      break;
    case 3:
      withdraw();
      break;
    case 4:
      checkBalance();
      break;
    case 5:
      transfer();
      break;
    case 0:
      cout << "Thank you for using BMS Goodbye" << endl;
      break;
    default:
      cout << "Invalid choice. Please try again!!!" << endl;
    }
    cout << endl;
  } while (choice != 0);

  return 0;
}