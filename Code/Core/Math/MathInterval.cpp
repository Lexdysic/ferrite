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

const Interval Interval::Null(0.0f, -1.0f);
const Interval Interval::Infinite(-Math::Infinity, Math::Infinity);