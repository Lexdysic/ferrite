
#include <queue>

template <typename T, typename C = std::less<T>>
class TPriQueue
{
public:
    TPriQueue ();
    ~TPriQueue ();
    
    uint Count () const;
    bool IsEmpty () const;

    void Clear ();

    bool Contains (const T & value) const;

    void Resort ();

    void Push (const T & value);
    T Pop ();
    const T & Peek () const;

private:

    std::deque<T> m_queue;
    C   m_comp;
};
