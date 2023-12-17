#include <exception>
#include <stdexcept>
#include <string>

class NotImplementedYetException : public std::exception{

public:
  NotImplementedYetException();
  ~NotImplementedYetException();
  const char* what() const noexcept override{
    return "Not Implemented Yet";
  }

};
