//*****************************************************************************
//
// Hash32
//
//*****************************************************************************

class Hash32
{
public: // Construction

    Hash32 ();
    Hash32 (const uint8 *  pData, uint size);
    Hash32 (const uint16 * pData, uint size);
    Hash32 (const uint32 * pData, uint size);
    Hash32 (const uint8 * start, const uint8 * end);

    template <typename T>
    Hash32 (const T & pod)
    {
        Add(pod);
    }

public: // Add

    void Add (const uint8 *  pData, uint size);
    void Add (const uint16 * pData, uint size);
    void Add (const uint32 * pData, uint size);
    void Add (const uint8 * start, const uint8 * end);

    template <typename T>
    void Add (const T & pod)
    {
        //static_assert(std::is_pointere<T>::value, "Can only be used with POD types");
        const byte * ptr = (byte *)&pod;
        Add(ptr, sizeof(T));
    }

public: // Access

    explicit operator uint32 () const { return m_value; }
    uint32 GetHash () const { return m_value; }

private: // Simple Type

    SIMPLE_TYPE_DATA(uint32, m_value);
    SIMPLE_TYPE_EQUATABLE(Hash32);
    SIMPLE_TYPE_COMPARABLE(Hash32);
};