
//=============================================================================
template <typename T, typename C>
TPriQueue<T,C>::TPriQueue ()
{
}

//=============================================================================
template <typename T, typename C>
TPriQueue<T,C>::~TPriQueue ()
{
}

//=============================================================================
template <typename T, typename C>
uint TPriQueue<T,C>::Count () const
{
    return m_queue.size();
}

//=============================================================================
template <typename T, typename C>
bool TPriQueue<T,C>::IsEmpty () const
{
    return m_queue.empty();
}

//=============================================================================
template <typename T, typename C>
void TPriQueue<T,C>::Clear ()
{
    m_queue.clear();
}

//=============================================================================
template <typename T, typename C>
bool TPriQueue<T,C>::Contains (const T & value) const
{
    return std::find(m_queue.begin(), m_queue.end(), value) != m_queue.end();
}

//=============================================================================
template <typename T, typename C>
void TPriQueue<T,C>::Resort ()
{
    std::make_heap(m_queue.begin(), m_queue.end(), m_comp);
}

//=============================================================================
template <typename T, typename C>
void TPriQueue<T,C>::Push (const T & value)
{
    m_queue.push_back(value);
    std::push_heap(m_queue.begin(), m_queue.end(), m_comp);
}

//=============================================================================
template <typename T, typename C>
T TPriQueue<T,C>::Pop ()
{
    T value = Peek();
    std::pop_heap(m_queue.begin(), m_queue.end(), m_comp);
    m_queue.pop_back();
    return value;
}

//=============================================================================
template <typename T, typename C>
const T & TPriQueue<T,C>::Peek () const
{
    return m_queue.front();
}
