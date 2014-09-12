
namespace SI
{

//*****************************************************************************
//
// TSi
//
//*****************************************************************************

//=============================================================================
// Addition
template <
    sint L, sint M, sint T, sint I, sint K, sint N, sint J
>
inline
TSi<L, M, T, I, K, N, J>
operator+ (
    const TSi<L, M, T, I, K, N, J> & lhs,
    const TSi<L, M, T, I, K, N, J> & rhs
) {
    return TSi<L, M, T, I, K, N, J>(lhs.m_value + rhs.m_value);
}

//=============================================================================
// Subtraction
template <
    sint L, sint M, sint T, sint I, sint K, sint N, sint J
>
inline
TSi<L, M, T, I, K, N, J>
operator- (
    const TSi<L, M, T, I, K, N, J> & lhs,
    const TSi<L, M, T, I, K, N, J> & rhs
) {
    return TSi<L, M, T, I, K, N, J>(lhs.m_value - rhs.m_value);
}

//=============================================================================
// Multiply
template <
    sint Ll, sint Ml, sint Tl, sint Il, sint Kl, sint Nl, sint Jl,
    sint Lr, sint Mr, sint Tr, sint Ir, sint Kr, sint Nr, sint Jr
>
inline
TSi<Ll+Lr, Ml+Mr, Tl+Tr, Il+Ir, Kl+Kr, Nl+Nr, Jl+Jr>
operator* (
    const TSi<Ll, Ml, Tl, Il, Kl, Nl, Jl> & lhs,
    const TSi<Lr, Mr, Tr, Ir, Kr, Nr, Jr> & rhs
) {
    return TSi<Ll+Lr, Ml+Mr, Tl+Tr, Il+Ir, Kl+Kr, Nl+Nr, Jl+Jr>(lhs.m_value * rhs.m_value);
}

//=============================================================================
// Divide
template <
    sint Ll, sint Ml, sint Tl, sint Il, sint Kl, sint Nl, sint Jl,
    sint Lr, sint Mr, sint Tr, sint Ir, sint Kr, sint Nr, sint Jr
>
inline
TSi<Ll-Lr, Ml-Mr, Tl-Tr, Il-Ir, Kl-Kr, Nl-Nr, Jl-Jr>
operator/ (
    const TSi<Ll, Ml, Tl, Il, Kl, Nl, Jl> & lhs,
    const TSi<Lr, Mr, Tr, Ir, Kr, Nr, Jr> & rhs
) {
    return TSi<Ll-Lr, Ml-Mr, Tl-Tr, Il-Ir, Kl-Kr, Nl-Nr, Jl-Jr>(lhs.m_value / rhs.m_value);
}

   
} // namespace SI