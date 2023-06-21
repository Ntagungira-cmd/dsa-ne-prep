#ifndef CUSTOMEXCEPTIONS_H
#define CUSTOMEXCEPTIONS_H

#include <exception>
#include <string>

class FileOpenException : public std::exception
{
public:
  FileOpenException(const std::string &message) throw() : errorMessage(message) {}

  virtual const char *what() const throw()
  {
    return errorMessage.c_str();
  }

  virtual ~FileOpenException() throw() {}

private:
  std::string errorMessage;
};

class FileWriteException : public std::exception
{
public:
  FileWriteException(const std::string &message) throw() : errorMessage(message) {}

  virtual const char *what() const throw()
  {
    return errorMessage.c_str();
  }

  virtual ~FileWriteException() throw() {}

private:
  std::string errorMessage;
};

#endif // CUSTOMEXCEPTIONS_H
