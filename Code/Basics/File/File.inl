namespace File
{

//=============================================================================
template <typename T>
T CBinaryReader::Read ()
{
    T out;
    Read(&out);
    return out;
}

//=============================================================================
template <typename T>
void CBinaryReader::Read (T * out)
{
    static_assert(std::is_pod<T>::value, "Can only read POD types");

    fread((void *)out, sizeof(T), 1, (FILE *)m_file);
}


} // namespace File