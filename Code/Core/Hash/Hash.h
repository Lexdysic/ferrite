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

public: // 

    void Add (const uint8 *  pData, uint size);
    void Add (const uint16 * pData, uint size);
    void Add (const uint32 * pData, uint size);
    void Add (const uint8 * start, const uint8 * end);

private: // Simple Type

    SIMPLE_TYPE_DATA(uint32, m_value);
    SIMPLE_TYPE_EQUATABLE(Hash32);
    SIMPLE_TYPE_COMPARABLE(Hash32);
};