//=================================================================================================
//
// File:    CorePragma.h
// Author:  Jason Jackson
// Date:    May 20, 2009
//
// Used to turn off certain warnings
//
//=================================================================================================
#pragma once

#ifdef COMPILER_MSVC
#pragma warning(disable : 4091) //'__declspec(novtable)' : ignored on left of symbol when no variable is declared
#endif
