
//=============================================================================
const Vector2 & Matrix22::Row (uint32 r) const { ASSERT(r < 2); return row[r]; }
const Vector3 & Matrix23::Row (uint32 r) const { ASSERT(r < 2); return row[r]; }
const Vector3 & Matrix33::Row (uint32 r) const { ASSERT(r < 3); return row[r]; }
const Vector4 & Matrix34::Row (uint32 r) const { ASSERT(r < 3); return row[r]; }
const Vector4 & Matrix44::Row (uint32 r) const { ASSERT(r < 4); return row[r]; }

//=============================================================================
Vector2 Matrix22::Column (uint32 c) const { ASSERT(c < 2); return Vector2(row[0][c], row[1][c]); }
Vector2 Matrix23::Column (uint32 c) const { ASSERT(c < 3); return Vector2(row[0][c], row[1][c]); }
Vector3 Matrix33::Column (uint32 c) const { ASSERT(c < 3); return Vector3(row[0][c], row[1][c], row[2][c]); }
Vector3 Matrix34::Column (uint32 c) const { ASSERT(c < 4); return Vector3(row[0][c], row[1][c], row[2][c]); }
Vector4 Matrix44::Column (uint32 c) const { ASSERT(c < 4); return Vector4(row[0][c], row[1][c], row[2][c], row[3][c]); }

//=============================================================================
Matrix22 operator+ (const Matrix22 & lhs, const Matrix22 & rhs) { return Matrix22(lhs.row[0] + rhs.row[0], lhs.row[1] + rhs.row[1]); }
Matrix33 operator+ (const Matrix33 & lhs, const Matrix33 & rhs) { return Matrix33(lhs.row[0] + rhs.row[0], lhs.row[1] + rhs.row[1], lhs.row[2] + rhs.row[2]); };
Matrix34 operator+ (const Matrix34 & lhs, const Matrix34 & rhs) { return Matrix34(lhs.row[0] + rhs.row[0], lhs.row[1] + rhs.row[1], lhs.row[2] + rhs.row[2]); };
Matrix44 operator+ (const Matrix44 & lhs, const Matrix44 & rhs) { return Matrix44(lhs.row[0] + rhs.row[0], lhs.row[1] + rhs.row[1], lhs.row[2] + rhs.row[2], lhs.row[3] + rhs.row[3]); };

//=============================================================================
Matrix22 operator- (const Matrix22 & lhs, const Matrix22 & rhs) { return Matrix22(lhs.row[0] - rhs.row[0], lhs.row[1] - rhs.row[1]); }
Matrix33 operator- (const Matrix33 & lhs, const Matrix33 & rhs) { return Matrix33(lhs.row[0] - rhs.row[0], lhs.row[1] - rhs.row[1], lhs.row[2] - rhs.row[2]); };
Matrix34 operator- (const Matrix34 & lhs, const Matrix34 & rhs) { return Matrix34(lhs.row[0] - rhs.row[0], lhs.row[1] - rhs.row[1], lhs.row[2] - rhs.row[2]); };
Matrix44 operator- (const Matrix44 & lhs, const Matrix44 & rhs) { return Matrix44(lhs.row[0] - rhs.row[0], lhs.row[1] - rhs.row[1], lhs.row[2] - rhs.row[2], lhs.row[3] - rhs.row[3]); };

//=============================================================================
Vector2 operator* (const Matrix22 & lhs, const Vector2 & rhs) { return Vector2(Dot(lhs.Row(0), rhs), Dot(lhs.Row(1), rhs)); }
Vector2 operator* (const Matrix23 & lhs, const Vector2 & rhs) { Vector3 v(lhs * Vector3(rhs, 1.0f)); return Vector2(v.x, v.y); }
Vector3 operator* (const Matrix23 & lhs, const Vector3 & rhs) { return Vector3(Dot(lhs.Row(0), rhs), Dot(lhs.Row(1), rhs), 0.0f); }
Vector3 operator* (const Matrix33 & lhs, const Vector3 & rhs) { return Vector3(Dot(lhs.Row(0), rhs), Dot(lhs.Row(1), rhs), Dot(lhs.Row(2), rhs)); }
Vector3 operator* (const Matrix34 & lhs, const Vector3 & rhs) { return lhs * Vector4(rhs, 1.0f); }
Vector3 operator* (const Matrix34 & lhs, const Vector4 & rhs) { return Vector3(Dot(lhs.Row(0), rhs), Dot(lhs.Row(1), rhs), Dot(lhs.Row(2), rhs)); }
Vector4 operator* (const Matrix44 & lhs, const Vector4 & rhs) { return Vector4(Dot(lhs.Row(0), rhs), Dot(lhs.Row(1), rhs), Dot(lhs.Row(2), rhs), Dot(lhs.Row(3), rhs)); }

//=============================================================================
Matrix22 operator* (const Matrix22 & lhs, const float32 & rhs) { return Matrix22(lhs.row[0]*rhs, lhs.row[1]*rhs); }
Matrix23 operator* (const Matrix23 & lhs, const float32 & rhs) { return Matrix23(lhs.row[0]*rhs, lhs.row[1]*rhs); }
Matrix33 operator* (const Matrix33 & lhs, const float32 & rhs) { return Matrix33(lhs.row[0]*rhs, lhs.row[1]*rhs, lhs.row[2]*rhs); } 
Matrix34 operator* (const Matrix34 & lhs, const float32 & rhs) { return Matrix34(lhs.row[0]*rhs, lhs.row[1]*rhs, lhs.row[2]*rhs); } 
Matrix44 operator* (const Matrix44 & lhs, const float32 & rhs) { return Matrix44(lhs.row[0]*rhs, lhs.row[1]*rhs, lhs.row[2]*rhs, lhs.row[3]*rhs); } 

//=============================================================================
Matrix22 operator* (const float32 & lhs, const Matrix22 & rhs) { return rhs * lhs; }
Matrix33 operator* (const float32 & lhs, const Matrix33 & rhs) { return rhs * lhs; }
Matrix34 operator* (const float32 & lhs, const Matrix34 & rhs) { return rhs * lhs; }
Matrix44 operator* (const float32 & lhs, const Matrix44 & rhs) { return rhs * lhs; }

//=============================================================================
Matrix22 operator/ (const Matrix22 & lhs, const float32 & rhs) { return lhs * (1.0f / rhs); }
Matrix23 operator/ (const Matrix23 & lhs, const float32 & rhs) { return lhs * (1.0f / rhs); }
Matrix33 operator/ (const Matrix33 & lhs, const float32 & rhs) { return lhs * (1.0f / rhs); }
Matrix34 operator/ (const Matrix34 & lhs, const float32 & rhs) { return lhs * (1.0f / rhs); }
Matrix44 operator/ (const Matrix44 & lhs, const float32 & rhs) { return lhs * (1.0f / rhs); }

//=============================================================================
Matrix22 operator* (const Matrix22 & lhs, const Matrix22 & rhs)
{
    return Matrix22(
        Dot(lhs.Row(0), rhs.Column(0)),     Dot(lhs.Row(0), rhs.Column(1)),
        Dot(lhs.Row(1), rhs.Column(0)),     Dot(lhs.Row(1), rhs.Column(1))
    );
}

//=============================================================================
Matrix23 operator* (const Matrix23 & lhs, const Matrix23 & rhs)
{
    const Vector3 & lhsRow0 = lhs.Row(0);
    const Vector3 & lhsRow1 = lhs.Row(1);
    const Vector3 & rhsCol0 = Vector3(rhs.Column(0), 0.0f);
    const Vector3 & rhsCol1 = Vector3(rhs.Column(1), 0.0f);
    const Vector3 & rhsCol2 = Vector3(rhs.Column(2), 1.0f);
    return Matrix23(
        Dot(lhsRow0, rhsCol0),   Dot(lhsRow0, rhsCol1),   Dot(lhsRow0, rhsCol2),
        Dot(lhsRow1, rhsCol0),   Dot(lhsRow1, rhsCol1),   Dot(lhsRow1, rhsCol2)
    );
}

//=============================================================================
Matrix33 operator* (const Matrix33 & lhs, const Matrix33 & rhs)
{
    return Matrix33(
        Dot(lhs.Row(0), rhs.Column(0)),     Dot(lhs.Row(0), rhs.Column(1)),     Dot(lhs.Row(0), rhs.Column(2)),
        Dot(lhs.Row(1), rhs.Column(0)),     Dot(lhs.Row(1), rhs.Column(1)),     Dot(lhs.Row(1), rhs.Column(2)),
        Dot(lhs.Row(2), rhs.Column(0)),     Dot(lhs.Row(2), rhs.Column(1)),     Dot(lhs.Row(2), rhs.Column(2))
    );
}

//=============================================================================
Matrix34 operator* (const Matrix34 & lhs, const Matrix34 & rhs)
{
    return Matrix34(
        Dot(lhs.Row(0).xyz, rhs.Column(0)),     Dot(lhs.Row(0).xyz, rhs.Column(1)),     Dot(lhs.Row(0).xyz, rhs.Column(2)),     Dot(lhs.Row(0), Vector4(rhs.Column(3),1)),  
        Dot(lhs.Row(1).xyz, rhs.Column(0)),     Dot(lhs.Row(1).xyz, rhs.Column(1)),     Dot(lhs.Row(1).xyz, rhs.Column(2)),     Dot(lhs.Row(1), Vector4(rhs.Column(3),1)),
        Dot(lhs.Row(2).xyz, rhs.Column(0)),     Dot(lhs.Row(2).xyz, rhs.Column(1)),     Dot(lhs.Row(2).xyz, rhs.Column(2)),     Dot(lhs.Row(2), Vector4(rhs.Column(3),1))
    );
}

//=============================================================================
Matrix44 operator* (const Matrix44 & lhs, const Matrix44 & rhs)
{
    return Matrix44(
        Dot(lhs.Row(0), rhs.Column(0)),     Dot(lhs.Row(0), rhs.Column(1)),     Dot(lhs.Row(0), rhs.Column(2)),     Dot(lhs.Row(0), rhs.Column(3)), 
        Dot(lhs.Row(1), rhs.Column(0)),     Dot(lhs.Row(1), rhs.Column(1)),     Dot(lhs.Row(1), rhs.Column(2)),     Dot(lhs.Row(1), rhs.Column(3)),
        Dot(lhs.Row(2), rhs.Column(0)),     Dot(lhs.Row(2), rhs.Column(1)),     Dot(lhs.Row(2), rhs.Column(2)),     Dot(lhs.Row(2), rhs.Column(3)),
        Dot(lhs.Row(3), rhs.Column(0)),     Dot(lhs.Row(3), rhs.Column(1)),     Dot(lhs.Row(3), rhs.Column(2)),     Dot(lhs.Row(3), rhs.Column(3))
    );
}

//=============================================================================
bool operator== (const Matrix22 & lhs, const Matrix22 & rhs) { return lhs.Row(0)==rhs.Row(0) && lhs.Row(1)==rhs.Row(1); }
bool operator== (const Matrix33 & lhs, const Matrix33 & rhs) { return lhs.Row(0)==rhs.Row(0) && lhs.Row(1)==rhs.Row(1) && lhs.Row(2)==rhs.Row(2); }
bool operator== (const Matrix34 & lhs, const Matrix34 & rhs) { return lhs.Row(0)==rhs.Row(0) && lhs.Row(1)==rhs.Row(1) && lhs.Row(2)==rhs.Row(2); }
bool operator== (const Matrix44 & lhs, const Matrix44 & rhs) { return lhs.Row(0)==rhs.Row(0) && lhs.Row(1)==rhs.Row(1) && lhs.Row(2)==rhs.Row(2) && lhs.Row(3)==rhs.Row(3); }

//=============================================================================
bool operator!= (const Matrix22 & lhs, const Matrix22 & rhs) { return !(lhs == rhs); }
bool operator!= (const Matrix33 & lhs, const Matrix33 & rhs) { return !(lhs == rhs); }
bool operator!= (const Matrix34 & lhs, const Matrix34 & rhs) { return !(lhs == rhs); }
bool operator!= (const Matrix44 & lhs, const Matrix44 & rhs) { return !(lhs == rhs); }

//=============================================================================
Matrix22 Transpose (const Matrix22 & m) { return Matrix22(m.Column(0), m.Column(1)); }
Matrix33 Transpose (const Matrix33 & m) { return Matrix33(m.Column(0), m.Column(1), m.Column(2)); }
Matrix34 Transpose (const Matrix34 & m) { m; ASSERT(!"Not implemented"); }
Matrix44 Transpose (const Matrix44 & m) { return Matrix44(m.Column(0), m.Column(1), m.Column(2), m.Column(3)); }

//=============================================================================
float32 Trace (const Matrix22 & m) { return m.m00 + m.m11; }
float32 Trace (const Matrix33 & m) { return m.m00 + m.m11 + m.m22; }
float32 Trace (const Matrix34 & m) { return m.m00 + m.m11 + m.m22 + 1.0f; }
float32 Trace (const Matrix44 & m) { return m.m00 + m.m11 + m.m22 + m.m33; }

//=============================================================================
float32 Determinant (const Matrix22 & m)
{
    return m.m00 * m.m11 - m.m01 * m.m10;
}

//=============================================================================
float32 Determinant (const Matrix23 & m)
{
    return Dot(m.row0, Cross(m.row1, Vector3(0, 0, 1)));
}

//=============================================================================
float32 Determinant (const Matrix33 & m)
{
    return Dot(m.row0, Cross(m.row1, m.row2));
}

//=============================================================================
float32 Determinant (const Matrix34 & m)
{
    const float32 s2 = (m.m00 * m.m13 - m.m03 * m.m10);
    const float32 s4 = (m.m01 * m.m13 - m.m03 * m.m11);
    const float32 s5 = (m.m02 * m.m13 - m.m03 * m.m12);

    return s2 * m.m20 - s4 * m.m21 + s5 * m.m22;
}

//=============================================================================
float32 Determinant (const Matrix44 & m)
{
    const float32 s0 = (m.m00 * m.m11 - m.m01 * m.m10);
    const float32 s1 = (m.m00 * m.m12 - m.m02 * m.m10);
    const float32 s2 = (m.m00 * m.m13 - m.m03 * m.m10);
    const float32 s3 = (m.m01 * m.m12 - m.m02 * m.m11);
    const float32 s4 = (m.m01 * m.m13 - m.m03 * m.m11);
    const float32 s5 = (m.m02 * m.m13 - m.m03 * m.m12);

    const float32 c0 = (m.m22 * m.m33 - m.m23 * m.m32);
    const float32 c1 = (m.m21 * m.m33 - m.m23 * m.m31);
    const float32 c2 = (m.m21 * m.m32 - m.m22 * m.m31);
    const float32 c3 = (m.m20 * m.m33 - m.m23 * m.m30);
    const float32 c4 = (m.m20 * m.m32 - m.m22 * m.m30);
    const float32 c5 = (m.m20 * m.m31 - m.m21 * m.m30);

    return s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0;
}

//=============================================================================
Matrix22 Inverse (const Matrix22 & m)
{
    const float32 det = Determinant(m);

    ASSERT(!Equal(det, 0.0f));

    Matrix22 out(
         m.m11, -m.m01,
        -m.m10,  m.m00
   );

    return out / det;
}

//=============================================================================
Matrix23 Inverse (const Matrix23 & m)
{
    const float32 det = Determinant(m);

    ASSERT(!Equal(det, 0.0f));

    Matrix23 out(
        (m.m11 * 1.0f - m.m12 * 0.0f),   (m.m02 * 0.0f - m.m01 * 1.0f),   (m.m01 * m.m12 - m.m02 * m.m11),
        (m.m12 * 0.0f - m.m10 * 1.0f),   (m.m00 * 1.0f - m.m02 * 0.0f),   (m.m02 * m.m10 - m.m00 * m.m12)
   );

    return out / det;
}

//=============================================================================
Matrix33 Inverse (const Matrix33 & m)
{
    const float32 det = Determinant(m);

    ASSERT(!Equal(det, 0.0f));

    Matrix33 out(
        (m.m11 * m.m22 - m.m12 * m.m21),   (m.m02 * m.m21 - m.m01 * m.m22),   (m.m01 * m.m12 - m.m02 * m.m11),
        (m.m12 * m.m20 - m.m10 * m.m22),   (m.m00 * m.m22 - m.m02 * m.m20),   (m.m02 * m.m10 - m.m00 * m.m12),
        (m.m10 * m.m21 - m.m11 * m.m20),   (m.m01 * m.m20 - m.m00 * m.m21),   (m.m00 * m.m11 - m.m01 * m.m10));

    return out / det;
}

//=============================================================================
Matrix34 Inverse (const Matrix34 & m)
{
    const float32 det = Determinant(m);

    ASSERT(!Equal(det, 0.0f));

    ASSERT(!"Not implemented"); 
    
    return Matrix34();
}

//=============================================================================
Matrix44 Inverse (const Matrix44 & m)
{
    const float32 det = Determinant(m);

    ASSERT(!Equal(det, 0.0f));

    ASSERT(!"Not implemented"); 
    
    return Matrix44();
}

//=============================================================================
bool Equal (const Matrix22 & lhs, const Matrix22 & rhs, sint32 maxUlps)   
{ 
    return  Equal(lhs.Row(0), rhs.Row(0), maxUlps) && 
            Equal(lhs.Row(1), rhs.Row(1), maxUlps); 
}

//=============================================================================
bool Equal (const Matrix33 & lhs, const Matrix33 & rhs, sint32 maxUlps)
{ 
    return  Equal(lhs.Row(0), rhs.Row(0), maxUlps) && 
            Equal(lhs.Row(1), rhs.Row(1), maxUlps) && 
            Equal(lhs.Row(2), rhs.Row(2), maxUlps); 
}

//=============================================================================
bool Equal (const Matrix34 & lhs, const Matrix34 & rhs, sint32 maxUlps)
{ 
    return  Equal(lhs.Row(0), rhs.Row(0), maxUlps) && 
            Equal(lhs.Row(1), rhs.Row(1), maxUlps) && 
            Equal(lhs.Row(2), rhs.Row(2), maxUlps); 
}

//=============================================================================
bool Equal (const Matrix44 & lhs, const Matrix44 & rhs, sint32 maxUlps)
{ 
    return  Equal(lhs.Row(0), rhs.Row(0), maxUlps) && 
            Equal(lhs.Row(1), rhs.Row(1), maxUlps) && 
            Equal(lhs.Row(2), rhs.Row(2), maxUlps) && 
            Equal(lhs.Row(3), rhs.Row(3), maxUlps); 
}

