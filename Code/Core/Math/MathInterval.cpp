//==================================================================================================
//
// File:    MathInterval.cpp
// Author:  Jason Jackson
// Date:    September 20, 2008
//
// An interval on a number line
//
//==================================================================================================

#include "MathPch.h"

const Interval Interval::Null(Math::Infinity, -Math::Infinity);
const Interval Interval::Infinite(-Math::Infinity, Math::Infinity);