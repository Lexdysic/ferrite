//=================================================================================================
//
// File:    PhysPartioning.h
// Author:  Jason Jackson
// Date:    June 27, 2009
//
// Holds a group of objects to be easily queried by its location
//
//=================================================================================================

#ifdef PHYSPARTITIONING_H
#  error "Cannot include header more than once."
#endif
#define PHYSPARTITIONING_H

namespace Physics {

template <typename Object>
class Partitioning {
public:
    
    // Types
    struct Collision 
    {
        Collision( Object & objA, Object & objB, float32 timeOfCollision );
        Collision( const Collision & rhs );

        Object & a; // Index of the first object involved in the collision
        Object & b; // Index of the second object involved in the collision
        float32 time;   // The time at which this collision occurs
    };

    //! Retrieve a list of all collisions to happen in a delta time
    void QueryCollisions( std::vector<Collision> & out, float32 dt );

private:
    std::vector<Object> mObjects; //!< List of physics objects
    std::vector<Object/*collidabable object*/> mStatic;  //!< List of static collision objects
};

typedef Partitioning<Object2> Partitioning2;
typedef Partitioning<Object3> Partitioning3;

} // namespace Physics