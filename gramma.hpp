/*******************************************************************************
 *
 *      Autor:      Jan Johansson (ejanjoh)
 *      Copyright:  Copyright (c) 2017 Jan Johansson (ejanjoh)
 *      Created:    2017-04-07
 *      Updated:
 *
 *      Project:    Calculate Matematical Expression (Math_Parser)
 *      File name:  gramma.hpp
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

#ifndef gramma_hpp
#define gramma_hpp

#include "token.hpp"
#include "localexcept.hpp"

void CheckGramma(unsigned int first, unsigned int last, TokenList& tokenList) throw (GrammaError);

#endif /* gramma_hpp */
