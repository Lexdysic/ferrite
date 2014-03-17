#ifndef SYSAPPLICATION_H
#define SYSAPPLICATION_H

namespace System
{

class Application
{
public:
    virtual void Initialize () = 0;
    virtual void Start () = 0;
    virtual void Cleanup () = 0;
    
};

}; //namespace System

#endif //SYSAPPLICATION_H