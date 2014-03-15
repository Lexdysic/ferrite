#ifndef SYSTEMSTATE_H
#define SYSTEMSTATE_H

namespace System
{

class State
{
public:
    inline State();
    inline ~State();

protected:
    virtual void Update (float32 deltaTime, float32 UnsuspendedDeltaTime) = 0;

};

}; //namespace System

#endif //SYSTEMSTATE_H