namespace Meta
{

//=============================================================================
template <typename T> struct IsFloat          { static const bool value = false; };
template <>           struct IsFloat<float32> { static const bool value = true; };
template <>           struct IsFloat<float64> { static const bool value = true; };

//=============================================================================
template <typename T> struct IsInteger          { static const bool value = false; };
template <>           struct IsInteger<sint8>   { static const bool value = true; };
template <>           struct IsInteger<sint16>  { static const bool value = true; };
template <>           struct IsInteger<sint32>  { static const bool value = true; };
template <>           struct IsInteger<sint64>  { static const bool value = true; };
template <>           struct IsInteger<uint8>   { static const bool value = true; };
template <>           struct IsInteger<uint16>  { static const bool value = true; };
template <>           struct IsInteger<uint32>  { static const bool value = true; };
template <>           struct IsInteger<uint64>  { static const bool value = true; };

//=============================================================================
template <typename T> struct IsSigned          { static const bool value = false; };
template <>           struct IsSigned<float32> { static const bool value = true; };
template <>           struct IsSigned<float64> { static const bool value = true; };
template <>           struct IsSigned<sint8>   { static const bool value = true; };
template <>           struct IsSigned<sint16>  { static const bool value = true; };
template <>           struct IsSigned<sint32>  { static const bool value = true; };
template <>           struct IsSigned<sint64>  { static const bool value = true; };

//=============================================================================
template <typename T> struct IsBuiltin          { static const bool value = false; };
template <>           struct IsBuiltin<float32> { static const bool value = true; };
template <>           struct IsBuiltin<float64> { static const bool value = true; };
template <>           struct IsBuiltin<sint8>   { static const bool value = true; };
template <>           struct IsBuiltin<sint16>  { static const bool value = true; };
template <>           struct IsBuiltin<sint32>  { static const bool value = true; };
template <>           struct IsBuiltin<sint64>  { static const bool value = true; };
template <>           struct IsBuiltin<uint8>   { static const bool value = true; };
template <>           struct IsBuiltin<uint16>  { static const bool value = true; };
template <>           struct IsBuiltin<uint32>  { static const bool value = true; };
template <>           struct IsBuiltin<uint64>  { static const bool value = true; };
template <>           struct IsBuiltin<bool>    { static const bool value = true; };

//=============================================================================
template <typename T> struct IsNumeric          { static const bool value = false; };
template <>           struct IsNumeric<float32> { static const bool value = true; };
template <>           struct IsNumeric<float64> { static const bool value = true; };
template <>           struct IsNumeric<sint8>   { static const bool value = true; };
template <>           struct IsNumeric<sint16>  { static const bool value = true; };
template <>           struct IsNumeric<sint32>  { static const bool value = true; };
template <>           struct IsNumeric<sint64>  { static const bool value = true; };
template <>           struct IsNumeric<uint8>   { static const bool value = true; };
template <>           struct IsNumeric<uint16>  { static const bool value = true; };
template <>           struct IsNumeric<uint32>  { static const bool value = true; };
template <>           struct IsNumeric<uint64>  { static const bool value = true; };

} // namespace Meta