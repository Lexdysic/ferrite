#ifdef MATH_H
#  error "Cannot include header more than once."
#endif
#define MATH_H

#include <cmath>

// Interfaces
#include "MathSi.h"
#include "MathConst.h"
#include "MathTypes.h"
#include "MathScalar.h"
#include "MathAngle.h"
#include "MathFixed.h"
#include "MathVector.h"
#include "MathPoint.h"
#include "MathInterval.h"
#include "MathMatrix.h"
#include "MathQuaternion.h"
#include "MathRandom.h"

// Inline implementations
#include "MathSi.inl"
#include "MathScalar.inl"
#include "MathAngle.inl"
#include "MathFixed.inl"
#include "MathVector.inl"
#include "MathPoint.inl"
#include "MathInterval.inl"
#include "MathMatrix.inl"
#include "MathQuaternion.inl"
#include "MathRandom.inl"

