//==================================================================================================
//
// File:    Hash.h
// Author:  Jason Jackson
// Date:    September 27, 2008
//
// Defines hash objects that will convert data into single integers
//==================================================================================================
#ifndef HASH_H
#define HASH_H

#include "Math/MathTypes.h"
#include <string>

//==================================================================================================
//
// Represents hashed data
//==================================================================================================
class Hash32
{
public:
    Hash32( const u8*  pData, uint32 size );
    Hash32( const u16* pData, uint32 size );
    Hash32( const uint32* pData, uint32 size );
    Hash32( const u8* pStart, const u8* pEnd );

private:
    uint32             mValue; //!< The hashed value of the data
};


//==================================================================================================
//
// Represents a hashed string. After a string has been hashed, string comparisons can be acheived
// in O(1) time by instead doing a compare on a uint32.
//==================================================================================================
class StringHash32
{
public:
    StringHash32( const std::string& str );
    StringHash32( const char* pStr );

    StringHash32&   operator= ( const StringHash32& rhs );
    bool            operator==( const StringHash32& rhs ) const;
    bool            operator!=( const StringHash32& rhs ) const;
    bool            operator<=( const StringHash32& rhs ) const;
    bool            operator>=( const StringHash32& rhs ) const;
    bool            operator< ( const StringHash32& rhs ) const;
    bool            operator> ( const StringHash32& rhs ) const;
                    operator bool() const;

private:
    
    void Compute( const char* pStr );


    uint32             mHash;  //!< The hashed value of the data

    #ifdef DEBUG
        std::string mStr;   //!< string that was hashed (debug only)
    #endif
};


#endif //HASH_H