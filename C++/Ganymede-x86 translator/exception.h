#ifndef EXCEPTION_INCLUDE_
#define EXCEPTION_INCLUDE_

#include "Ganymede-x86.h"

using namespace std;

/**
                @file				exception.h

                @par				See full explanation in
exception.cpp

**/

//------------------------------------------------------------------------------

class ivException : public exception {
  std::string _name;
  std::string _func;
  unsigned int _line;
  std::string _message;
  std::string _file;

public:
  void console_report() const;

  template <typename kind_of_stream>
  void stream_report(kind_of_stream &stream) const;

  ivException(const string &exc_name, const string &file, const string &func,
              unsigned int line, const string &message);
  ivException(const string &exc_name, const string &file, const string &func,
              unsigned int line, const string &message, ivException *cause);

  // template <typename T>
  void listed_report(ostream &stream) const;
  void listed_delete() const;
  const char *what() const;
  ivException *because = NULL;
};

#define IVEXCEPTION_INHERITOR_TEMPLATE(name, printing_name)                    \
  class iv##name : public ivException {                                        \
  public:                                                                      \
    iv##name(const string &file, const string &func, unsigned int line,        \
             const string &message)                                            \
        : ivException(printing_name, file, func, line, message){};             \
    iv##name(const string &file, const string &func, unsigned int line,        \
             const string &message, ivException *cause)                        \
        : ivException(printing_name, file, func, line, message, cause){};      \
  }

IVEXCEPTION_INHERITOR_TEMPLATE(Logic_error, "Logic error");
IVEXCEPTION_INHERITOR_TEMPLATE(Runtime_error, "Runtime error");

#define CHECK_PTR(name)                                                        \
  if (name == NULL) {                                                          \
    ivRuntime_error *to_throw =                                                \
        new ivRuntime_error(__FILE__, __FUNCSIG__, __LINE__,                   \
                            #name " variable caused NULL pointer exception");  \
    throw *to_throw;                                                           \
  }

#define CATCH_ALLOC_EXCEPTION(varname)                                         \
  catch (bad_alloc & ba) {                                                     \
                                                                               \
    ivRuntime_error *to_throw =                                                \
        new ivRuntime_error(__FILE__, __FUNCSIG__, __LINE__,                   \
                            #varname " memory allocation is failed");          \
    throw *to_throw;                                                           \
  }

#define TEMPLATE_ASSERT(exc, cond, msg)                                        \
  if (!(cond)) {                                                               \
    exc *to_throw = new exc(__FILE__, __FUNCSIG__, __LINE__, msg);             \
    throw to_throw;                                                            \
  }

#define RT_ASSERT(cond, msg) TEMPLATE_ASSERT(ivRuntime_error, cond, msg)
#define LG_ASSERT(cond, msg) TEMPLATE_ASSERT(ivLogic_error, cond, msg)

#define CATCH_IV(msg)                                                          \
  catch (ivException & exc) {                                                  \
    ivRuntime_error *to_throw =                                                \
        new ivRuntime_error(__FILE__, __FUNCSIG__, __LINE__, msg, &exc);       \
    throw *to_throw;                                                           \
  }

#define CALL(call, msg)                                                        \
  try {                                                                        \
    call;                                                                      \
  }                                                                            \
  CATCH_IV(msg)

#define TRY_ALLOC(var_name, constructor)                                       \
  try {                                                                        \
    var_name = new constructor;                                                \
  }                                                                            \
                                                                               \
  CATCH_ALLOC_EXCEPTION(var_name)

/*

class ivNull_pointer: public ivException
{
public:

        ivNull_pointer(const string& file, const string& func, unsigned int
line, const string& var_name): ivException(file, func, line, var_name + "
pointer is null")
                {
                        assert(this);
                        init_name("Null pointer exception");
                };
        ivNull_pointer(const string& file, const string& func, unsigned int
line, const string& var_name, ivException cause): ivException(file, func, line,
var_name + " pointer is null", cause)
                {
                        assert(this);
                        init_name("Null pointer exception");
                };
};

class ivAllocate_error: public ivException
{
public:

        ivAllocate_error(const string& file, const string& func, unsigned int
line, const string& var_name, ofstream& log_stream): ivException(file, func,
line, "Allocation for " + var_name + " is failed", log_stream)
        {
                assert(this);
                init_name("Memory allocation exception");
        };
};

*/

#define LOG_MESSAGE(message)                                                   \
  log_stream << message << endl                                                \
             << "File:\t" << __FILE__ << endl                                  \
             << "Line:\t" << __LINE__ << endl                                  \
             << "Function:\t" << __FUNCSIG__ << endl                           \
             << endl;

#define BUFFER_CHECK RT_ASSERT(check(), "Buffer verification failed")

#endif