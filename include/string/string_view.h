namespace fe
{

class StringView
{
public:
    StringView ();
    StringView (const StringView & str);
    StringView (const char * str, uint32_t length);
    template <size_t N>
    StringView (const char (& str)[N]);

    const char * Ptr ();
    const char * Term ();

    bool IsEmpty () const;
    
private:
    const char * m_ptr;
    size_t       m_length;
};

} // namespace fe