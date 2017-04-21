/*******************************************************************************
 *
 *      Autor:      Jan Johansson (ejanjoh)
 *      Copyright:  Copyright (c) 2017 Jan Johansson (ejanjoh)
 *      Created:    2017-04-07
 *      Updated:
 *
 *      Project:    Calculate Matematical Expression (Math_Parser)
 *      File name:  localexcept.hpp
 *
 *
 *      Version history mapped on changes in this file:
 *      -----------------------------------------------
 *      ver 1       Created
 *
 *
 *      Reference:
 *
 ******************************************************************************/

#ifndef localexcept_hpp
#define localexcept_hpp

#include <stdexcept>
using namespace std;


class GrammaError : public runtime_error {
public:
    GrammaError(const char *what_arg): runtime_error(what_arg) {}
};


class SortingError : public logic_error {
public:
    SortingError(const char *what_arg): logic_error(what_arg) {}
};

#endif /* localexcept_hpp */
