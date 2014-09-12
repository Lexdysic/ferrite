#ifdef MATHVECTOR_H
#  error "Cannot include header more than once."
#endif
#define MATHVECTOR_H


//*****************************************************************************
//
// Vector2
//
//*****************************************************************************

class Vector2
{
public: // Construction

    inline Vector2 ();
    inline Vector2 (const Vector2 & v);
    inline Vector2 (float32 x, float32 y);
    
public: // Assignment

    inline Vector2 &    operator=  (const Vector2 & v);

public: // Operators

    inline Vector2 &    operator*= (float32 s);
    inline Vector2 &    operator/= (float32 s);
    inline Vector2 &    operator*= (const Vector2 & v);
    inline Vector2 &    operator/= (const Vector2 & v);
    inline Vector2 &    operator+= (const Vector2 & v);
    inline Vector2 &    operator-= (const Vector2 & v);

public: // Accessors

    inline const float32 &  operator[] (uint i) const;
    inline       float32 &  operator[] (uint i);

public: // Constants

    static const Vector2 Zero;
    static const Vector2 One;
    static const Vector2 UnitX;
    static const Vector2 UnitY;
    static const Vector2 Infinity;

public: // Data
    
    float32 x;
    float32 y;
};



//*****************************************************************************
//
// Vector3
//
//*****************************************************************************

class Vector3
{
public: // Construction

    inline Vector3 ();
    inline Vector3 (const Vector3 & v);
    inline explicit Vector3 (const Vector2 & xy, float32 z);
    inline explicit Vector3 (float32 x, const Vector2 & yz);
    inline Vector3 (float32 x, float32 y, float32 z);

public: // Assignment

    inline Vector3 & operator=( const Vector3 & v );

public: // Operators

    inline Vector3 & operator/= (const Vector3 & v);
    inline Vector3 & operator/= (float32 s);
    inline Vector3 & operator*= (const Vector3 & v);
    inline Vector3 & operator*= (float32 s);
    inline Vector3 & operator+= (const Vector3 & v);
    inline Vector3 & operator-= (const Vector3 & v);

public: // Accessors

    inline const float32 & operator[] (uint32 i) const;
    inline       float32 & operator[] (uint32 i);

public: // Constants

    static const Vector3 Zero;
    static const Vector3 One;
    static const Vector3 UnitX;
    static const Vector3 UnitY;
    static const Vector3 UnitZ;
    static const Vector3 Infinity;

public: // Data

    float32 x;
    float32 y;
    float32 z;
};



//*****************************************************************************
//
// Vector4
//
//*****************************************************************************

class Vector4
{
public: // Construction

    inline Vector4 ();
    inline Vector4 (const Point3 & p);
    inline Vector4 (const Vector3 & v);
    inline Vector4 (const Vector4 & v);
    inline Vector4 (const Quaternion & q);
    inline Vector4 (const Vector3 & xyz, float32 w);
    inline Vector4 (float32 x, const Vector3 & yzw);
    inline Vector4 (const Vector2 & xy, const Vector2 & xw);
    inline Vector4 (float32 x, const Vector2 & yz, float32 w);
    inline Vector4 (float32 x, float32 y, float32 z, float32 w);

public: // Assignment

    inline Vector4 & operator= (const Vector4 & v);

public: // Operators

    inline Vector4 & operator/= (const Vector4 & v);
    inline Vector4 & operator/= (float32 s);
    inline Vector4 & operator*= (const Vector4 & v);
    inline Vector4 & operator*= (float32 s);
    inline Vector4 & operator+= (const Vector4 & v);
    inline Vector4 & operator-= (const Vector4 & v);

public: // Accessors

    inline const float32 & operator[] (uint i) const;
    inline       float32 & operator[] (uint i);

public: // Constants

    static const Vector4 Zero;
    static const Vector4 One;
    static const Vector4 UnitX;
    static const Vector4 UnitY;
    static const Vector4 UnitZ;
    static const Vector4 UnitW;
    static const Vector4 Infinity;

public: // Data
    union
    {
        struct
        {
            Vector3 xyz;
            float32 _;
        };
        struct
        {
            float32 x;
            float32 y;
            float32 z;
            float32 w;
        };
    };
};



//*****************************************************************************
//
// Operators
//
//*****************************************************************************

inline Vector2   operator+ (const Vector2 & lhs, const Vector2 & rhs);
inline Vector3   operator+ (const Vector3 & lhs, const Vector3 & rhs);
inline Vector4   operator+ (const Vector4 & lhs, const Vector4 & rhs);

inline Vector2   operator- (const Vector2 & lhs, const Vector2 & rhs);
inline Vector3   operator- (const Vector3 & lhs, const Vector3 & rhs);
inline Vector4   operator- (const Vector4 & lhs, const Vector4 & rhs);

inline Vector2   operator* (const float32 & lhs, const Vector2 & rhs);
inline Vector3   operator* (const float32 & lhs, const Vector3 & rhs);
inline Vector4   operator* (const float32 & lhs, const Vector4 & rhs);

inline Vector2   operator* (const Vector2 & rhs, const float32 & lhs);
inline Vector3   operator* (const Vector3 & rhs, const float32 & lhs);
inline Vector4   operator* (const Vector4 & rhs, const float32 & lhs);

inline Vector2   operator* (const Vector2 & lhs, const Vector2 & rhs);
inline Vector3   operator* (const Vector3 & lhs, const Vector3 & rhs);
inline Vector4   operator* (const Vector4 & lhs, const Vector4 & rhs);
                           
inline Vector2   operator/ (const Vector2 & lhs, const Vector2 & rhs);
inline Vector3   operator/ (const Vector3 & lhs, const Vector3 & rhs);
inline Vector4   operator/ (const Vector4 & lhs, const Vector4 & rhs);

inline Vector2   operator/ (const Vector2 & rhs, const float32 & lhs);
inline Vector3   operator/ (const Vector3 & rhs, const float32 & lhs);
inline Vector4   operator/ (const Vector4 & rhs, const float32 & lhs);

inline Vector2   operator- (const Vector2 & v );
inline Vector3   operator- (const Vector3 & v );
inline Vector4   operator- (const Vector4 & v );

inline bool operator== (const Vector2 & lhs, const Vector2 & rhs);
inline bool operator== (const Vector3 & lhs, const Vector3 & rhs);
inline bool operator== (const Vector4 & lhs, const Vector4 & rhs);

inline bool operator!= (const Vector2 & lhs, const Vector2 & rhs);
inline bool operator!= (const Vector3 & lhs, const Vector3 & rhs);
inline bool operator!= (const Vector4 & lhs, const Vector4 & rhs);

inline float32  Dot (const Vector2 & lhs, const Vector2 & rhs);
inline float32  Dot (const Vector3 & lhs, const Vector3 & rhs);
inline float32  Dot (const Vector4 & lhs, const Vector4 & rhs);

inline float32 Cross (const Vector2 & lhs, const Vector2 & rhs);
inline Vector3 Cross (const Vector3 & lhs, const Vector3 & rhs);

inline Vector2 Perpendicular (const Vector2 & v);

inline Matrix22  Tensor (const Vector2 & lhs, const Vector2 & rhs);
inline Matrix33  Tensor (const Vector3 & lhs, const Vector3 & rhs);

inline Vector2 Sq (const Vector2 & v);
inline Vector3 Sq (const Vector3 & v);

inline Vector2   Normalize (const Vector2 & v);
inline Vector3   Normalize (const Vector3 & v);
inline Vector4   Normalize (const Vector4 & v);

inline Vector2   Normalize (const Vector2 & v, float32 * outLength);
inline Vector3   Normalize (const Vector3 & v, float32 * outLength);
inline Vector4   Normalize (const Vector4 & v, float32 * outLength);

// TODO (jason): want a better name for this
inline float32  Normalize2 (Vector2 & v);
inline float32  Normalize2 (Vector3 & v);
inline float32  Normalize2 (Vector4 & v);

inline float32  Length (const Vector2 & v);
inline float32  Length (const Vector3 & v);
inline float32  Length (const Vector4 & v);

inline float32  LengthSq (const Vector2 & v);
inline float32  LengthSq (const Vector3 & v);
inline float32  LengthSq (const Vector4 & v);

inline bool IsParallel (const Vector2 & a, const Vector2 & b);
inline bool IsParallel (const Vector3 & a, const Vector3 & b);
inline bool IsParallel (const Vector4 & a, const Vector4 & b);

inline bool IsPerpendicular (const Vector2 & a, const Vector2 & b);
inline bool IsPerpendicular (const Vector3 & a, const Vector3 & b);
inline bool IsPerpendicular (const Vector4 & a, const Vector4 & b);

inline Vector2 Mirror (const Vector2 & a, const Vector2 & n);
inline Vector3 Mirror (const Vector3 & a, const Vector3 & n);

inline float32 Min (const Vector2 & v);
inline float32 Min (const Vector3 & v);
inline float32 Min (const Vector4 & v);

inline Vector2 Min (const Vector2 & a, const Vector2 & b);
inline Vector3 Min (const Vector3 & a, const Vector3 & b);
inline Vector4 Min (const Vector4 & a, const Vector4 & b);

inline float32 Max (const Vector2 & v);
inline float32 Max (const Vector3 & v);
inline float32 Max (const Vector4 & v);

inline Vector2 Max (const Vector2 & a, const Vector2 & b);
inline Vector3 Max (const Vector3 & a, const Vector3 & b);
inline Vector4 Max (const Vector4 & a, const Vector4 & b);

inline Vector2 Abs (const Vector2 & v);
inline Vector3 Abs (const Vector3 & v);
inline Vector4 Abs (const Vector4 & v);

inline Vector2 Sign (const Vector2 & v);
inline Vector3 Sign (const Vector3 & v);
inline Vector4 Sign (const Vector4 & v);

inline bool Equal (const Vector2 & a, const Vector2 & b, sint32 maxUlps = Math::MaxUlps);
inline bool Equal (const Vector3 & a, const Vector3 & b, sint32 maxUlps = Math::MaxUlps);
inline bool Equal (const Vector4 & a, const Vector4 & b, sint32 maxUlps = Math::MaxUlps);

inline bool Normalized (const Vector2 & v, sint32 maxUlps = Math::MaxUlps);
inline bool Normalized (const Vector3 & v, sint32 maxUlps = Math::MaxUlps);
inline bool Normalized (const Vector4 & v, sint32 maxUlps = Math::MaxUlps);

void BuildBasis (const Vector3 & x, Vector3 & u, Vector3 & v, Vector3 & w);


