//=================================================================================================
//
// File:    PhysPartioning.inl
// Author:  Jason Jackson
// Date:    June 27, 2009
//
// Represents the phsysical properties of a body moving in space
//
//=================================================================================================

namespace Physics {

template <typename Object>
Partitioning<Object>::Collision::Collision(Object & objA, Object & objB, float32 timeOfCollision) :
a(objA),
b(objB),
time(timeOfCollision)
{

}

template <typename Object>
Partitioning<Object>::Collision::Collision(const Collision & rhs) :
a(rhs.a),
b(rhs.b),
time(rhs.time)
{
}

template <typename Object>
void Partitioning<Object>::QueryCollisions(std::vector<Collision> & out, float32 dt) 
{

    // TODO: query a partitioning container

    for( uint i = 0; i < mObjects.size(); ++i )
    {
        const Object & a = mObjects[i];

        for( uint j = i + 1; j < mObjects.size(); ++j )
        {
            const Object & b = mObjects[j];

            IntersectInfo info;
            if( !Intersect(info, a, a.velocity * dt, b, b.velocity * dt) )
                continue;

            Collision coll;
            coll.indexA = i;
            coll.indexB = j;
            coll.time   = info.time;

            out.push_back(coll);
        }

        // TODO: Test vs static collision
    }
}

} // namespace Physics