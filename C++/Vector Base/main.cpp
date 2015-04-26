//!
//!         @file               main.cpp
//!         @mainpage
//!
//!         @author             Sergey Ivanychev, MIPT DCAM, sergeyivanychev@gmail.com
//!
//!         @par                This project is second generation template-based vector, which is able
//!                             to deal with any objects, with basic interface and standard types of C++.
//!
//!         @brief              The project now (v 2.0) contain main.cpp file itself and
//!
//!                             --  exception.cpp / exception.h     - Files with my exception type implemented.
//!                                                                   See description in its header
//!                             --  iv_vector.h                     - Header with VECBASE class template and it's methods templates
//!                             --  iv_alloc.h                      - Here's some stuff, which is not still developed properly. It is
//!                                                                   supposed to be special pointer table with redefined NEW and DELETE
//!                                                                   operator so that it would contain all pointers metadata, that were allocated
//!                                                                   via dynamic memory functions
//!         @version            V2.0 Beta. Rev. 1
//!
//!
//!

#define VECBASE_DEBUG

#include <iostream>
#include "exception.h"
#include "iv_vector.h"
//#include "iv_alloc.h"

std::string gen_th_string(int index);
void print_str_vec(iv_vecbase<string>& vect);
void print_int_vec(iv_vecbase<int>& vect);



using namespace std;

int tmain();

int main()
{
    int ret = 0;
    try
    {
        ret = tmain();
    }

    catch (ivException& exc)
    {
        exc.listed_report(cout);
        exc.listed_delete();
        return 1;
    }

    catch (std::exception& exc)
    {
        printf("STD:EXCEPTION CAUGHT: %s\n", exc.what());
        return 2;
    }


    catch(...)
    {
        printf("UNEXPECTED EXCEPTION CAUGHT");
    return -1;
    }

    return ret;
}

/**
*       @brief                  tmain function is a usual testing function, that was used to debug VECBASE.
*                               There are two parts of code, one of it is commented, that test <string> vector
*                               and <int> vector, showing that it could work with both objects and standard data types.
*
*
*
*
**/


int tmain()
{
    cout << "Hello world!" << endl;

//!                                                                                         Integer part
    int* iarr = new int[10];

    for (int i = 0; i < 10; ++i) iarr[i] = i;

    iv_vecbase<int> first   = iv_vecbase<int>(iarr, 5);
    iv_vecbase<int> second  = iv_vecbase<int>(10);
    iv_vecbase<int> third   = iv_vecbase<int>(first);
    iv_vecbase<int> fourth  = iv_vecbase<int>(first, (unsigned)1, (unsigned)2);
    iv_vecbase<int> fifth   = iv_vecbase<int>();

//      Playing with second
    for (unsigned i = 0; i < second.size(); ++i) second[i] = i;
    second.cut(3, 8);
//      Playing with third

    third.insert(123321, 2);

    third.insert(iarr, 3, 2);

    third.insert(third, 2);


//      Playing with fourth
    fourth.push_back(314);
    cout << fourth.pop_back();
//      Playing with fifth
    fifth.push_back(111);
    fifth.push_back(222);
    fifth.push_back(333);

    print_int_vec(first);
    getchar();
    print_int_vec(second);
    getchar();
    print_int_vec(third);
    getchar();
    print_int_vec(fourth);
    getchar();
    print_int_vec(fifth);
    getchar();

    delete[] iarr;
    getchar();


/*

//!                                                                                                 String part

    std::string* arr = new string[5];

    for (int i = 0; i < 5; ++i)       arr[i]  = gen_th_string(i);

//!     @brief      Here testing calling different constructors
    iv_vecbase<std::string> first  = iv_vecbase<std::string>(arr, 5);
    iv_vecbase<std::string> second = iv_vecbase<std::string>(10);
    iv_vecbase<std::string> third  = iv_vecbase<std::string>(first);
    iv_vecbase<std::string> fourth = iv_vecbase<std::string>(first, (unsigned)1, (unsigned)2);
    iv_vecbase<std::string> fifth  = iv_vecbase<std::string>();


    //first.dump(stdout);
    //third.dump(stdout);

//      Playing with second
    for (unsigned i = 0; i < second.size(); ++i) second[i] = gen_th_string(i);
    second.cut(3, 8);
//      Playing with third
    print_str_vec(third);
    third.insert("inserted", 2);
    print_str_vec(third);
    third.insert(arr, 3, 2);
    print_str_vec(third);
    third.insert(third, 2);
    print_str_vec(third);

//      Playing with fourth
    fourth.push_back("Pushed and popped");
    cout << fourth.pop_back();
//      Playing with fifth
    fifth.push_back("First");
    fifth.push_back("Second");
    fifth.push_back("Third");

    print_str_vec(first);
    getchar();
    print_str_vec(second);
    getchar();
    print_str_vec(third);
    getchar();
    print_str_vec(fourth);
    getchar();
    print_str_vec(fifth);
    getchar();

    delete[] arr;
    getchar();
*/

    return 0;
}


/**
*       @brief              gen_th_string                   -  generates string like "This string is [ARG]", where ARG is input number
*
*                           print_str_vec, print_int_vec    -  functions print detailed dump of string and int VECBASEs
*
**/



std::string gen_th_string(int index)
{
    char buffer[20] = {0};
    std::string out = "This string is ";
    sprintf(buffer, "%d", index);

    out.append(buffer);
    out += '\n';

    return out;
}

void print_str_vec(iv_vecbase<string>& vect)
{
    fprintf(stdout, ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    fprintf(stdout, "Debug print of string vector begin...\n");
    vect.dump(stdout);
    fprintf(stdout, "\nPrinting contained strings...\n\n");
    for (unsigned i = 0; i < vect.size(); ++i)
    {
    fprintf(stdout, "%d\t:", i);
    cout << vect[i];
    fprintf(stdout, "\n");
    }
    fprintf(stdout, "\nDebug print of string vector end\n");
    fprintf(stdout, ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
}

void print_int_vec(iv_vecbase<int>& vect)
{
    fprintf(stdout, ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    fprintf(stdout, "Debug print of integer vector begin...\n");
    vect.dump(stdout);
    fprintf(stdout, "\nPrinting contained ints...\n\n");
    for (unsigned i = 0; i < vect.size(); ++i)
    {
    fprintf(stdout, "%d\t:", i);
    cout << vect[i];
    fprintf(stdout, "\n");
    }
    fprintf(stdout, "\nDebug print of integer vector end\n");
    fprintf(stdout, ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
}

