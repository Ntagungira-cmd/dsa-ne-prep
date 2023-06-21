#ifndef CUSTOMEXCEPTIONS_H
#define CUSTOMEXCEPTIONS_H

#include <stdexcept>
#include <string>


//file Open Exception
class FileOpenException : public std::exception
{
public:
  FileOpenException(const std::string &message) : errorMessage(message) {}

  virtual const char *what() const noexcept
  {
    return errorMessage.c_str();
  }

private:
  std::string errorMessage;
};


//file write exception
class FileWriteException : public std::exception
{
public:
  FileWriteException(const std::string &message) : errorMessage(message) {}

  const char *what() const noexcept override
  {
    return errorMessage.c_str();
  }

private:
  std::string errorMessage;
};

#endif
