//==================================================================================================
//
// File:    MathTypes.h
// Author:  Jason Jackson
// Date:    May 23, 2009
//
// Basic name substitutions and types
//
//==================================================================================================

#ifdef CORETYPE_H
#  error "Cannot include header more than once."
#endif
#define CORETYPES_H



//*****************************************************************************
//
// Explicitly sized basic types
//
//*****************************************************************************

typedef float           float32;
typedef double          float64;

typedef int8_t          sint8;
typedef int16_t         sint16;
typedef int32_t         sint32;
typedef int64_t         sint64;

typedef uint8_t         uint8;
typedef uint16_t        uint16;
typedef uint32_t        uint32;
typedef uint64_t        uint64;

typedef unsigned int    uint;
typedef signed int      sint;

typedef wchar_t         wchar;

typedef uint8           byte;



//*****************************************************************************
//
// Simple conversion helper
//
//*****************************************************************************
union float32sint32
{
    float32 f;
    sint32 i;
};

union float32uint32
{
    float32 f;
    uint32 i;
};

typedef decltype(nullptr) nullptr_t;




//*****************************************************************************
//
// SIMPLE_TYPE_*
//
//*****************************************************************************

#define SIMPLE_TYPE_DATA(VarType, VarName) \
    private: \
    VarType _SimpleTypeGetData() const { return VarName; } \
    VarType VarName

#define SIMPLE_TYPE_EQUATABLE(T) \
    friend bool operator== (const T & lhs, const T & rhs) { return lhs._SimpleTypeGetData() == rhs._SimpleTypeGetData(); } \
    friend bool operator!= (const T & lhs, const T & rhs) { return lhs._SimpleTypeGetData() != rhs._SimpleTypeGetData(); }

#define SIMPLE_TYPE_EQUATABLE_TO(T, U) \
    friend bool operator== (const T & lhs, const U & rhs) { return lhs._SimpleTypeGetData() == rhs; } \
    friend bool operator!= (const T & lhs, const U & rhs) { return lhs._SimpleTypeGetData() != rhs; } \
    friend bool operator== (const U & lhs, const T & rhs) { return lhs == rhs._SimpleTypeGetData(); } \
    friend bool operator!= (const U & lhs, const T & rhs) { return lhs != rhs._SimpleTypeGetData(); }

#define SIMPLE_TYPE_COMPARABLE(T) \
    friend bool operator<  (const T & lhs, const T & rhs) { return lhs._SimpleTypeGetData() <  rhs._SimpleTypeGetData(); } \
    friend bool operator<= (const T & lhs, const T & rhs) { return lhs._SimpleTypeGetData() <= rhs._SimpleTypeGetData(); } \
    friend bool operator>  (const T & lhs, const T & rhs) { return lhs._SimpleTypeGetData() >  rhs._SimpleTypeGetData(); } \
    friend bool operator>= (const T & lhs, const T & rhs) { return lhs._SimpleTypeGetData() >= rhs._SimpleTypeGetData(); }

#define SIMPLE_TYPE_COMPARABLE_TO(T, U) \
    friend bool operator<  (const T & lhs, const U & rhs) { return lhs._SimpleTypeGetData() <  (decltype(lhs._SimpleTypeGetData()))rhs; } \
    friend bool operator<= (const T & lhs, const U & rhs) { return lhs._SimpleTypeGetData() <= (decltype(lhs._SimpleTypeGetData()))rhs; } \
    friend bool operator>  (const T & lhs, const U & rhs) { return lhs._SimpleTypeGetData() >  (decltype(lhs._SimpleTypeGetData()))rhs; } \
    friend bool operator>= (const T & lhs, const U & rhs) { return lhs._SimpleTypeGetData() >= (decltype(lhs._SimpleTypeGetData()))rhs; } \
    friend bool operator<  (const U & lhs, const T & rhs) { return (decltype(rhs._SimpleTypeGetData()))lhs <  rhs._SimpleTypeGetData(); } \
    friend bool operator<= (const U & lhs, const T & rhs) { return (decltype(rhs._SimpleTypeGetData()))lhs <= rhs._SimpleTypeGetData(); } \
    friend bool operator>  (const U & lhs, const T & rhs) { return (decltype(rhs._SimpleTypeGetData()))lhs >  rhs._SimpleTypeGetData(); } \
    friend bool operator>= (const U & lhs, const T & rhs) { return (decltype(rhs._SimpleTypeGetData()))lhs >= rhs._SimpleTypeGetData(); }



//*****************************************************************************
//
// Flag
//
//*****************************************************************************

template <typename T>
class Flag
{
    static_assert(
        std::numeric_limits<T>::is_integer && 
        !std::numeric_limits<T>::is_signed,
        "Must be use unsigned integral type"
    );
public:
    explicit Flag (T f);

private:
     T m_value;
};



//*****************************************************************************
//
// Flags
//
//*****************************************************************************

template <typename T>
class Flags
{
    static_assert(
        std::numeric_limits<T>::is_integer && 
        !std::numeric_limits<T>::is_signed,
        "Must be use unsigned integral type"
    );

public:
    inline Flags ();
    inline Flags (T f);

    inline void Set (T flags);
    inline void SetTo (T flags, bool value);
    inline void SetBit (uint bit);
    inline void SetAll ();
    inline void Clear (T flags);
    inline void ClearBit (uint bit);
    inline void ClearAll ();
    inline bool Test (T flags) const;
    inline bool TestBit (uint bit) const;
    inline bool AnySet () const;
    inline bool NoneSet () const;

    inline operator T () const;

public:
    static const Flags<T> All;
    static const Flags<T> None;

private:
    T mFlags;

    static const uint NUM_BITS = std::numeric_limits<uint8>::digits * sizeof(T);
};

typedef Flags<uint64> Flags64;
typedef Flags<uint32> Flags32;
typedef Flags<uint16> Flags16;
typedef Flags<uint8>  Flags8;

template <typename T> Flags<T> operator| (Flag<T> lha, Flag<T> rhs);
template <typename T> Flags<T> operator& (Flag<T> lha, Flag<T> rhs);
template <typename T> Flags<T> operator^ (Flag<T> lha, Flag<T> rhs);
template <typename T> Flags<T> operator| (Flags<T> lha, Flag<T> rhs);
template <typename T> Flags<T> operator& (Flags<T> lha, Flag<T> rhs);
template <typename T> Flags<T> operator^ (Flags<T> lha, Flag<T> rhs);
template <typename T> Flags<T> operator| (Flag<T> lha, Flags<T> rhs);
template <typename T> Flags<T> operator& (Flag<T> lha, Flags<T> rhs);
template <typename T> Flags<T> operator^ (Flag<T> lha, Flags<T> rhs);



//*****************************************************************************
//
// Coord2Base
//
//*****************************************************************************

template <typename T>
struct Coord2Base {
    Coord2Base () : x(0), y(0) {}
    Coord2Base (T x, T y) : x(x), y(y) {}
    T x, y;
};

template <typename T>
inline bool operator== (const Coord2Base<T> & lhs, const Coord2Base<T> & rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

struct Vector2u :
    Coord2Base<uint>
{
    Vector2u () {}
    Vector2u (uint x, uint y) : Coord2Base<uint>(x, y) {}
};

struct Vector2s :
    Coord2Base<sint>
{
    Vector2s () {}
    Vector2s (sint x, sint y) : Coord2Base<sint>(x, y) {}
};

struct Point2u :
    Coord2Base<uint>
{
    Point2u () {}
    Point2u (uint x, uint y) : Coord2Base<uint>(x, y) {}
};

struct Point2s :
    Coord2Base<sint>
{
    Point2s () {}
    Point2s (sint x, sint y) : Coord2Base<sint>(x, y) {}
};
