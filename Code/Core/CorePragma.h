//=================================================================================================
//
// File:    CorePragma.h
// Author:  Jason Jackson
// Date:    May 20, 2009
//
// Used to turn off certain warnings
//
//=================================================================================================

#ifdef COREPRAGMA_H
#  error "Cannot include header more than once."
#endif
#define COREPRAGMA_H

#ifdef COMPILER_MSVC
#pragma warning(disable : 4091) //'__declspec(novtable)' : ignored on left of symbol when no variable is declared
#endif
