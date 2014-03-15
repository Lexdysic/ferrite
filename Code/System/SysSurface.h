
namespace System {

class Surface// : public Lockable
{
public:
    Surface(uint width, uint height);
    ~Surface();

public: // ISurface
    uint GetWidth() const { return mBitmap.GetWidth(); }
    uint GetHeight() const { return mBitmap.GetHeight(); }

    Gdiplus::Bitmap & GetBitmap() const { return mBitmap; }

private:
    mutable Gdiplus::Bitmap mBitmap;
};

} // namespace System

//void NormalBlit(Gdiplus::Bitmap & srcBmp, uint32 destX, uint32 destY, Gdiplus::Graphics & gDest);
//void FastBlit(Gdiplus::Bitmap & srcBmp, Gdiplus::Rect destRect, Gdiplus::Graphics & gDest);
//void FastBlit(Gdiplus::Bitmap & srcBmp, uint32 destX, uint32 destY, uint32 destWidth, uint32 destHeight, Gdiplus::Graphics & gDest);
//void SlowBlit(Gdiplus::Bitmap & srcBmp, Gdiplus::Rect destRect, Gdiplus::Graphics & gDest);
