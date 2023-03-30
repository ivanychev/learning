/**
                @file					exception.cpp

                @par					this file and its
header(exception.h) contain defenitions of ivException class and its inheritors
                                                                that are used
through all the code.

                                                                There are two
main inheritors of that class - ivRuntime_error and ivLogic_error, that are used
to catch differrent error messages. The main proc is that generating exception
is like building list of exceptions. If MAIN function caught it, there will be
printed the list of messages with links between exceptions. If function catches
the exception, it creates the new one, saving the pointer of caught, dynamically
allocated exception.


**/

#include "exception.h"

ivException::ivException(const string &exc_name, const string &file,
                         const string &func, unsigned int line,
                         const string &message)
    : _name(exc_name), _file(file), _line(line), _func(func), _message(message),
      because(NULL) {
  assert(this);
  printf("Exception constructed\n");
}

//----------------------------------------------------------------------------------------------------------------------

ivException::ivException(const string &exc_name, const string &file,
                         const string &func, unsigned int line,
                         const string &message, ivException *cause)
    : _name(exc_name), _file(file), _line(line), _func(func), _message(message),
      because(cause) {
  assert(this);
  printf("Exception constructed\n");
}

//----------------------------------------------------------------------------------------------------------------------

ivException::~ivException() throw() {
  if (because != NULL) {
    because->~ivException();
    because = NULL;
  }
  _line = INT_POISON;
  printf("Exception destructed\n");
}

//----------------------------------------------------------------------------------------------------------------------

void ivException::console_report() const {
  assert(this);
  stream_report(cout);
}

//------------------------------------------------------------------------------

template <typename kind_of_stream>
void ivException::stream_report(kind_of_stream &stream) const {
  assert(this);

  bool stream_health = (&stream != NULL);

  if (stream_health == false) {
    cout << "Invalid stream to report in. Calling console reporting..." << endl;

    stream_report(cout);
    return;
  }

  stream << "Exception name : \t\t" << _name << endl;
  stream << "File name:\t\t\t" << _file << endl;
  stream << "Function name:\t\t" << _func << endl;
  stream << "Occuration line: \t\t" << _line << endl;
  stream << "Message received:\n" << _message << endl;

  stream << "\nEnd of report\n";

  return;
}

//----------------------------------------------------------------------------------------------------------------------

const char *ivException::what() const throw() {
  assert(this);
  return _message.c_str();
}

//----------------------------------------------------------------------------------------------------------------------

// template <typename T>
void ivException::listed_report(ostream &stream) const {
  if (because != NULL)
    because->listed_report(stream);
  stream << "||\n||\n||\nV\n";
  stream_report(stream);
}

//----------------------------------------------------------------------------------------------------------------------

void ivException::listed_delete() const {
  if (because != NULL)
    because->listed_delete();
  delete this;
}

//------------------------------------------------------------------------------
