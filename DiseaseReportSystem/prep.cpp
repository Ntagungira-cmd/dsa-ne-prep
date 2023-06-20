#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <set>

using namespace std;

void welcome_screen()
{
  cout << "              =================================================       " << endl;
  cout << "              *   Welcome To Disease Cases reporting System!   *" << endl;
  cout << "              * ********************************************** *" << endl;
  cout << "                                                                       " << endl;
  cout << "          *                                                        *" << endl;
  cout << "               * It is developed by RCA Ntagungira Ali Rashid *" << endl;
  cout << "                     * Evaluation of end of year 3 *           " << endl;
  cout << "                                                                        " << endl;
  cout << "                                                                        " << endl;
}

// add location
void add_location(string location, string filename)
{
  ofstream file;
  file.open(filename.c_str(), ios::app);
  if (file.is_open())
  {
    file << location << endl;
    file.close();
  }
  else
  {
    file.open(filename.c_str());
    if (file.is_open())
    {
      cout << "*******************************************" << filename << endl;
      cout << "*your data will be stored in a file called*" << filename << endl;
      cout << "*******************************************" << filename << endl;
      file << location << endl;
      cout << "                                             " << endl;
      cout << "Location " << location << " has been added successfully!" << endl;
      file.close();
    }
  }
}

// delete location
void delete_location(string filename, string itemToDelete)
{

  ifstream file(filename.c_str());
  vector<string> lines;
  string line;

  // read all lines in file
  while (getline(file, line))
  {
    lines.push_back(line);
  }
  file.close();

  // delete location
  vector<string>::iterator it = lines.begin();
  while (it != lines.end())
  {
    istringstream iss(*it);
    string item;

    while (std::getline(iss, item, ' '))
    {
      if (item == itemToDelete)
      {
        it = lines.erase(it);
        break;
      }

      if (it != lines.end())
      {
        ++it;
      }
    }
  }

  // write to the file again
  ofstream file2;
  file2.open(filename.c_str());

  if (file2.is_open())
  {
    for (size_t i = 0; i < lines.size(); i++)
    {
      file2 << lines[i] << " " << endl;
    }
    file2.close();
  }
  else
  {
    cout << "Deleting location " << itemToDelete << " failed!!!!" << endl;
  }
}

// add disease and cases
void record_disease_cases(string filename, string location, string disease, int cases)
{
  ofstream file;
  file.open(filename.c_str(), ios::app);
  if (file.is_open())
  {
    file << location << " " << disease << " " << cases << endl;
    file.close();
  }
  else
  {
    file.open(filename.c_str());
    if (file.is_open())
    {
      file << location << " " << disease << " " << cases << endl;
      file.close();
    }
    else
    {
      cout << "Error may have occurred in recording" << endl;
    }
  }
}

// list diseases or locations depending on the format of the command
void list_locations_diseases(string filname, string location)
{
  ifstream file(filname.c_str());
  vector<string> lines;
  vector<string> diseases;
  vector<string> locations;
  string line;

  while (getline(file, line))
  {
    istringstream iss(line);
    string location, disease;
    iss >> location >> disease;
    locations.push_back(location);
    diseases.push_back(disease);
  }
  file.close();
  if (location == "locations")
  {
    cout << "[ ";
    for (size_t i = 0; i < locations.size(); ++i)
    {
      cout << locations[i] << " ";
    }
    cout << "]" << endl;
  }

  if (location == "diseases")
  {
    cout << "[ ";
    for (size_t i = 0; i < diseases.size(); ++i)
    {
      cout << diseases[i] << " ";
    }
    cout << "]" << endl;
  }
}

// given a disease find all the locations where it exists
void find_where_disease_exists(string filename, string disease)
{
  ifstream file(filename.c_str());
  set<string> locations;
  string line;

  while (getline(file, line))
  {
    istringstream iss(line);
    string location, ailment;
    // seaparate line into variables location and disease
    iss >> location >> ailment;
    if (disease == ailment)
    {
      locations.insert(location);
    }
  }
  file.close();
  if (locations.size() == 0)
  {
    cout << "No location with this disease" << endl;
  }
  cout << "[ ";
  for (set<string>::iterator it = locations.begin(); it != locations.end(); ++it)
  {
    cout << *it << " ";
  }
  cout << "]" << endl;
}

// find disease cases in a location
void find_cases_in_location(string filename, string location, string disease)
{
  ifstream file(filename.c_str());
  string line;

  while (getline(file, line))
  {
    string place, ailment;
    int cases;
    istringstream iss(line);
    iss >> place >> ailment >> cases;
    if (place == location && ailment == disease)
    {
      cout << "Cases of " << disease << " in " << location << " are: " << cases << endl;
    }
  }
}

// find cases of a disease
void find_cases_of_disease(string filename, string disease)
{
  ifstream file(filename.c_str());
  string line;
  string location, ailment;
  int total_cases = 0;
  while (getline(file, line))
  {
    int cases;
    istringstream iss(line);
    iss >> location >> ailment >> cases;
    if (ailment == disease)
    {
      total_cases += cases;
    }
    location = "";
    ailment = "";
  }
  cout << "Total cases of " << disease << " = " << total_cases << endl;
}

// user manual
void help()
{
  cout << "==========================================================" << endl;
  cout << "*                   HELP MENU                            *" << endl;
  cout << "==========================================================" << endl;
  cout << endl;
  cout << "1. add <location>                             : add new location" << endl;
  cout << endl;
  cout << "2. delete <location>                          : delete an existing location" << endl;
  cout << endl;
  cout << "3. record <location> <disease> <cases>        : Record a disease and its cases" << endl;
  cout << endl;
  cout << "4. list locations                             : list existing locations" << endl;
  cout << endl;
  cout << "5. list diseases                              : list existing diseases in locations" << endl;
  cout << endl;
  cout << "6. where <disease>                            : find where disease exists" << endl;
  cout << endl;
  cout << "7. cases <location> <disease>                 : find cases of a disease in a location" << endl;
  cout << endl;
  cout << "8. cases <disease>                            : Record a disease and its cases" << endl;
  cout << endl;
  cout << "9. help                                       : user manual" << endl;
  cout << endl;
  cout << "10. quit/q                                    : Exit the program" << endl;
  cout << endl;
}

// capitalise string
string capitalise(string text)
{
  string result = "";
  for (size_t i = 0; i < text.size(); i++)
  {
    char c = toupper(text[i]);
    result += c;
  }
  return result;
}

// main function for our program
int main()
{

  string command;
  string filename = "diseaseReportingSystemData.csv";

  // function to display intro UI
  welcome_screen();
  cout << "                *******************************************" << endl;
  cout << "                *      Enter a command of your choice     *" << endl;
  cout << "                *******************************************" << endl;

  while (true)
  {
    cout << "Console >";
    getline(std::cin, command);

    istringstream iss(command);
    string action, param1, param2;
    int param3;
    iss >> action >> param1 >> param2 >> param3;

    if (action == "quit" || action == "q")
    {
      break;
    }
    else if (action == "add")
    {
      add_location(capitalise(param1), filename);
    }
    else if (action == "delete")
    {
      if (param1.empty())
      {
        cout << "delet must have a location" << endl;
      }
      delete_location(filename, capitalise(param1));
    }
    else if (action == "record")
    {
      if (param1.empty() || param2.empty() || !param3)
      {
        cout << "record must have a location, disease and cases" << endl;
      }
      record_disease_cases(filename, capitalise(param1), capitalise(param2), param3);
    }
    else if (action == "list" && (param1 == "locations" || param1 == "diseases"))
    {
      list_locations_diseases(filename, param1);
    }
    else if (action == "where" && !param1.empty())
    {
      find_where_disease_exists(filename, capitalise(param1));
    }
    else if (action == "cases" && !param1.empty() && !param2.empty())
    {
      find_cases_in_location(filename, capitalise(param1), capitalise(param2));
    }
    else if (action == "cases" && !param1.empty())
    {
      find_cases_of_disease(filename, capitalise(param1));
    }
    else if (action == "help")
    {
      help();
    }
    else
    {
      cout << "Wrong Command!!!!!! " << endl;
      cout << "Enter \"help\" for more information on commands." << endl;
    }
  }

  return 0;
}
