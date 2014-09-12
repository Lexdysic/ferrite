//*****************************************************************************
//
//  TLink
//
//*****************************************************************************

//=============================================================================
template<class T>
TLink<T>::TLink ()
{
    // Mark this node as the end of the list, with no link offset
    m_nextNode = (T *) ((size_t) this + 1 - 0);
    m_prevLink = this;
}

//=============================================================================
template<class T>
TLink<T>::TLink (size_t offset)
{
    // Mark this node as the end of the list, with the link offset set
    m_nextNode = (T *) ((size_t) this + 1 - offset);
    m_prevLink = this;
}

//=============================================================================
template<class T>
TLink<T>::~TLink ()
{
    RemoveFromList();
}

//=============================================================================
template<class T>
void TLink<T>::SetOffset (size_t offset) {
    // Mark this node as the end of the list, with the link offset set
    m_nextNode = (T *) ((size_t) this + 1 - offset);
    m_prevLink = this;
}

//=============================================================================
template<class T>
void TLink<T>::RemoveFromList () {
    NextLink()->m_prevLink = m_prevLink;
    m_prevLink->m_nextNode = m_nextNode;
}

//=============================================================================
template<class T>
void TLink<T>::InsertBefore (T * node, TLink<T> * nextLink) {
    RemoveFromList();

    m_prevLink = nextLink->m_prevLink;
    m_nextNode = m_prevLink->m_nextNode;

    nextLink->m_prevLink->m_nextNode = node;
    nextLink->m_prevLink = this;
}

//=============================================================================
template<class T>
void TLink<T>::InsertAfter (T * node, TLink<T> * prevLink) {
    RemoveFromList();

    m_prevLink = prevLink;
    m_nextNode = prevLink->m_nextNode;

    prevLink->NextLink()->m_prevLink = this;
    prevLink->m_nextNode = node;
}

//=============================================================================
template<class T>
bool TLink<T>::IsLinked () const {
    return m_prevLink != this;
}

//=============================================================================
template<class T>
void TLink<T>::Unlink () {
    RemoveFromList();

    // Mark this node as the end of the list with no link offset
    m_nextNode = (T *) ((size_t) this + 1);
    m_prevLink = this;
}

//=============================================================================
template<class T>
TLink<T> * TLink<T>::PrevLink () {
    return m_prevLink;
}

//=============================================================================
template<class T>
TLink<T> * TLink<T>::NextLink () {
    // Calculate the offset from a node pointer to a link structure
    size_t offset = (size_t) this - ((size_t) m_prevLink->m_nextNode & ~1);

    // Get the link field for the next node
    return (TLink<T> *) (((size_t) m_nextNode & ~1) + offset);
}

//=============================================================================
template<class T>
T * TLink<T>::Prev () {
    T * prevNode = m_prevLink->m_prevLink->m_nextNode;
    if ((size_t) prevNode & 1)
        return null;
    return prevNode;
}

//=============================================================================
template<class T>
const T * TLink<T>::Prev () const {
    const T * prevNode = m_prevLink->m_prevLink->m_nextNode;
    if ((size_t) prevNode & 1)
        return null;
    return prevNode;
}

//=============================================================================
template<class T>
T * TLink<T>::Next () {
    if ((size_t) m_nextNode & 1)
        return null;
    return m_nextNode;
}

//=============================================================================
template<class T>
const T * TLink<T>::Next () const {
    if ((size_t) m_nextNode & 1)
        return null;
    return m_nextNode;
}



//*****************************************************************************
//
//  TList
//
//*****************************************************************************

//=============================================================================
template<class T>
TList<T>::~TList () {
    UnlinkAll();
}

//=============================================================================
template<class T>
TList<T>::TList () :
    m_link(),
    m_offset((size_t) -1)
{}

//=============================================================================
template<class T>
TList<T>::TList (size_t offset) :
    m_link(offset),
    m_offset(offset)
{}

//=============================================================================
template<class T>
bool TList<T>::IsEmpty () const {
    return m_link.Next() == null;
}

//=============================================================================
template<class T>
void TList<T>::UnlinkAll () {
    for (;;) {
        TLink<T> * link = m_link.PrevLink();
        if (link == &m_link)
            break;
        link->Unlink();
    }
}

//=============================================================================
template<class T>
void TList<T>::DeleteAll () {
    while (T * node = m_link.Next())
        delete node;
}

//=============================================================================
template<class T>
T * TList<T>::Head () {
    return m_link.Next();
}

//=============================================================================
template<class T>
T * TList<T>::Tail () {
    return m_link.Prev();
}

//=============================================================================
template<class T>
const T * TList<T>::Head () const {
    return m_link.Next();
}

//=============================================================================
template<class T>
const T * TList<T>::Tail () const {
    return m_link.Prev();
}

//=============================================================================
template<class T>
T * TList<T>::Prev (T * node) {
    return GetLinkFromNode(node)->Prev();
}

//=============================================================================
template<class T>
const T * TList<T>::Prev (const T * node) const {
    return GetLinkFromNode(node)->Prev();
}

//=============================================================================
template<class T>
T * TList<T>::Next (T * node) {
    return GetLinkFromNode(node)->Next();
}

//=============================================================================
template<class T>
const T * TList<T>::Next (const T * node) const {
    return GetLinkFromNode(node)->Next();
}

//=============================================================================
template<class T>
void TList<T>::InsertHead (T * node) {
    InsertAfter(node, null);
}

//=============================================================================
template<class T>
void TList<T>::InsertTail (T * node) {
    InsertBefore(node, null);
}

//=============================================================================
template<class T>
void TList<T>::InsertBefore (T * node, T * before) {
    ASSERT(!((size_t) node & 1));
    GetLinkFromNode(node)->InsertBefore(
        node,
        before ? GetLinkFromNode(before) : &m_link
    );
}

//=============================================================================
template<class T>
void TList<T>::InsertAfter (T * node, T * after) {
    ASSERT(!((size_t) node & 1));
    GetLinkFromNode(node)->InsertAfter(
        node,
        after ? GetLinkFromNode(after) : &m_link
    );
}

//=============================================================================
template<class T>
TLink<T> * TList<T>::GetLinkFromNode (const T * node) const {
    ASSERT(m_offset != (size_t) -1);
    return (TLink<T> *) ((size_t) node + m_offset);
}



//*****************************************************************************
//
//  TListDeclare
//
//*****************************************************************************

//=============================================================================
template<class T, size_t offset>
TListDeclare<T, offset>::TListDeclare () :
    TList<T>(offset)
{
}



//*****************************************************************************
//
//  TListIterator<T>
//
//*****************************************************************************

//=============================================================================
template <class T>
TListIterator<T>::TListIterator () :
    m_curr(null),
    m_list(null)
{
}

//=============================================================================
template <class T>
TListIterator<T>::TListIterator (T * curr, TList<T> * list) :
    m_curr(curr),
    m_list(list)
{
}

//=============================================================================
template <class T>
TListIterator<T>::TListIterator (const TListIterator<T> & rhs) :
    m_curr(rhs.m_curr),
    m_list(rhs.m_list)
{
}

//=============================================================================
template <class T>
TListIterator<T> & TListIterator<T>::operator= (const TListIterator<T> & rhs)
{
    m_curr = rhs.m_curr;
    m_list = rhs.m_list;
    return *this;
}

//=============================================================================
template <class T>
bool TListIterator<T>::operator == (const TListIterator<T> & rhs)
{
    return m_curr == rhs.m_curr && m_list == rhs.m_list;
}

//=============================================================================
template <class T>
bool TListIterator<T>::operator != (const TListIterator<T> & rhs)
{
    return !(*this == rhs);
}

//=============================================================================
template <class T>
TListIterator<T> & TListIterator<T>::operator++ ()
{
    m_curr = m_list->Next(m_curr);
    return *this;
}

//=============================================================================
template <class T>
TListIterator<T> & TListIterator<T>::operator++ (int)
{
    TListIterator<T> copy = *this;
    m_curr = m_list->Next(m_curr);
    return copy;
}

//=============================================================================
template <class T>
TListIterator<T> & TListIterator<T>::operator-- ()
{
    m_curr = m_list->Prev(m_curr);
    return *this;
}

//=============================================================================
template <class T>
TListIterator<T> & TListIterator<T>::operator-- (int)
{
    TListIterator<T> copy = *this;
    m_curr = m_list->Prev(m_curr);
    return copy;
}

//=============================================================================
template <class T>
T * TListIterator<T>::operator* ()
{
    return m_curr;
}

//=============================================================================
template <class T>
T * TListIterator<T>::operator-> ()
{
    return m_curr;
}

//=============================================================================
template <typename T, size_t offset>
TListIterator<T> begin (TListDeclare<T, offset> & list)
{
    return TListIterator<T>(list.Head(), &list);
}

//=============================================================================
template <typename T, size_t offset>
TListIterator<T> end (TListDeclare<T, offset> & list)
{
    return TListIterator<T>(null, &list);
}