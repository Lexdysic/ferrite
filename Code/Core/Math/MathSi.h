namespace SI
{

//*****************************************************************************
//
// TSi
//
//*****************************************************************************

template <
    sint L = 0, // meter
    sint M = 0, // kilogram
    sint T = 0, // second
    sint I = 0, // ampere
    sint K = 0, // kelvin
    sint N = 0, // mole
    sint J = 0  // candela
>
struct TSi
{
public: // Construction

    TSi () = default;
    ~TSi () = default;
    TSi (const TSi & value) = default;
    explicit TSi (float32 value) : m_value(value) {}
    
public: // Operators

    //template <sint L, sint M, sint T, sint I, sint K, sint N, sint J>
    //friend inline TSi<L, M, T, I, K, N, J>
    //operator+ (const TSi<L, M, T, I, K, N, J> &, const TSi<L, M, T, I, K, N, J> &);

    //template <sint L, sint M, sint T, sint I, sint K, sint N, sint J>
    //friend inline TSi<L, M, T, I, K, N, J>
    //operator- (const TSi<L, M, T, I, K, N, J> &, const TSi<L, M, T, I, K, N, J> &);

    //template <sint Ll, sint Ml, sint Tl, sint Il, sint Kl, sint Nl, sint Jl, sint Lr, sint Mr, sint Tr, sint Ir, sint Kr, sint Nr, sint Jr>
    //friend inline TSi<Ll+Lr, Ml+Mr, Tl+Tr, Il+Ir, Kl+Kr, Nl+Nr, Jl+Jr>
    //operator* (const TSi<Ll, Ml, Tl, Il, Kl, Nl, Jl> & lhs, const TSi<Lr, Mr, Tr, Ir, Kr, Nr, Jr> & rhs);

    //template <sint Ll, sint Ml, sint Tl, sint Il, sint Kl, sint Nl, sint Jl, sint Lr, sint Mr, sint Tr, sint Ir, sint Kr, sint Nr, sint Jr>
    //friend inline TSi<Ll-Lr, Ml-Mr, Tl-Tr, Il-Ir, Kl-Kr, Nl-Nr, Jl-Jr>
    //operator/ (const TSi<Ll, Ml, Tl, Il, Kl, Nl, Jl> & lhs, const TSi<Lr, Mr, Tr, Ir, Kr, Nr, Jr> & rhs);

private: // Data

    float32 m_value;
};
 



//           m, kg,  s,  A,  K,mol, cd
// Base Units
typedef TSi< 0,  0,  0,  0,  0,  0,  0> Unitless;
typedef TSi< 1,  0,  0,  0,  0,  0,  0> Meter;
typedef TSi< 0,  1,  0,  0,  0,  0,  0> Kilogram;
typedef TSi< 0,  0,  1,  0,  0,  0,  0> Second;
typedef TSi< 0,  0,  0,  1,  0,  0,  0> Ampere;
typedef TSi< 0,  0,  0,  0,  1,  0,  0> Kelvin;
typedef TSi< 0,  0,  0,  0,  0,  1,  0> Mole;
typedef TSi< 0,  0,  0,  0,  0,  0,  1> Candela;

// Derived SI Units
typedef TSi< 0,  0, -1,  0,  0,  0,  0> Hertz;          // Hz = 1/s
typedef TSi< 1,  1, -2,  0,  0,  0,  0> Newton;         // N = kg * m / s**2
typedef TSi<-1,  1, -2,  0,  0,  0,  0> Pascal;         // Pa = N/m**2 = kg * m / s**2
typedef TSi< 2,  1, -2,  0,  0,  0,  0> Joule;          // J = N * m = kg * m**2 / s**2
typedef TSi< 2,  1, -3,  0,  0,  0,  0> Watt;           // W = J/s = kg * m**2 * s**-3
typedef TSi< 0,  0,  1,  1,  0,  0,  0> Coulomb;        // C = s * A
typedef TSi< 2,  1, -3, -1,  0,  0,  0> Volt;           // V = W/A = kg * m**2 * s**-3 * A**-1
typedef TSi<-2, -1,  4,  2,  0,  0,  0> Farad;          // F = C/V = kg**-1 * m**-2 * S**4 * A**2
typedef TSi< 1,  0,  0,  0,  0,  0,  0> Ohm;            // Ohm = V/A = kg * m**2 * s**?3 * A**2
typedef TSi<-2, -1,  3,  2,  0,  0,  0> Siemens;        // S = A/V = kg**1 * m**2 * s**3 * A**2
typedef TSi< 2,  1, -2, -1,  0,  0,  0> Weber;          // Wb = V * s = kg * m**2 * s**?2* A**1
typedef TSi< 0,  1, -2, -1,  0,  0,  0> Tesla;          // T =  Wb / m**2 = kg * s**?2 * A**1
typedef TSi< 2,  1, -2, -2,  0,  0,  0> Henry;          // H = Wb/A = kg * m**2 * s**-2 * A**-2
typedef TSi< 0,  0,  0,  0,  1,  0,  0> Celsius;        // C = K
typedef TSi< 0,  0,  0,  0,  0,  0,  1> Lumen;          // lm = cd * sr = cd
typedef TSi<-2,  0,  0,  0,  0,  0,  1> Lux;            // lx = lm / m**2 = cd / m**2
typedef TSi< 0,  0, -1,  0,  0,  0,  0> Bacquerel;      // Bq = 1/s
typedef TSi< 2,  0, -2,  0,  0,  0,  0> Gray;           // Gy = J/kg = m**2 / s**2
typedef TSi< 2,  0, -2,  0,  0,  0,  0> Sievert;        // Sv = J/kg = m**2 / s**2
typedef TSi< 0,  0, -1,  0,  0,  1,  0> Katal;          // kat = mol / s

// Physical Units
typedef TSi< 1,  0, -1,  0,  0,  0,  0> Velocity;       // m / s
typedef TSi< 1,  0, -2,  0,  0,  0,  0> Acceleration;   // m / s**2
typedef TSi< 1,  0, -3,  0,  0,  0,  0> Jerk;           // m / s**3
typedef TSi< 1,  0, -4,  0,  0,  0,  0> Snap;           // m / s**4
typedef TSi< 2,  0,  0,  0,  0,  0,  0> Area;           // m**2
typedef TSi< 3,  0,  0,  0,  0,  0,  0> Volume;         // m**3
typedef TSi<-3,  1,  0,  0,  0,  0,  0> Density;        // kg / m**3
typedef TSi<-2,  1,  0,  0,  0,  0,  0> AreaDensity;    // kg / m**2
typedef TSi< 3,  0, -1,  0,  0,  0,  0> Flow;           // m**3 / s
typedef TSi< 2,  1, -2,  0,  0,  0,  0> Torque;         // m**2 * kg / s**2
typedef TSi< 1,  1, -1,  0,  0,  0,  0> Momentum;       // m * kg / s


template <typename T>
struct Vector2
{
public: // Construction

public: // Operations

public: // Data
    T x;
    T y;
};

template <typename T>
struct Vector3
{
public: // Construction

public: // Operations

public: // Data
    T x;
    T y;
    T z;
};

typedef Vector2<Meter>    Position2;
typedef Vector2<Velocity> Velocity2;

} // namespace SI