/**
                @file			main.cpp
                @author			Sergey Ivanychev, DCAM MIPT, 376 group
                @mainpage
                @version		1.03

                @par			Changelog V 1.01
                                                - New commands set added to
main_output
                                                - English mistakes fixed
                                                - little changes in functions
                @par			Changelog V 1.02
                                                - Command system has been
enchanced
                                                - Some functions have been
fixed, verifications added
                                                - VERIFY macros has been changed
                                                - check_of function fixed
                @par			Changelog V. 1.03
                                                - new stack_err_check function
added, which configures error messages output
                                                - small fizes
                                                - code style fixes

                @par			This programs allows you to create your
own stack and do whatever you want with it. There's quite friendly UI which
makes it possible

                @par			Ivanychev.h, main_output.cpp and
stack_functions.cpp are required
**/

#include "stack.h"

/**
                main				configures all functions and
rules IO
                @return				0
**/

int main() {
  OUT printf(
      "Hello, I am a program compiled from %s in %s, %s\n"
      "I've been developed by Ivanychev Sergey\n"
      "I'm 1.03 version\n"
      "You are supposed to create stack and manipulate with it using me\n",
      __FILE__, __TIME__, __DATE__);

  stack *user_stack = NULL;
  int ret = system_out(user_stack);
  printf("\nBye\n\n");
  return 0;
}
