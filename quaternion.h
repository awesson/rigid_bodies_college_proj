/**
 * @file quaternion.hpp
 * @brief A quaternion class.
 *
 * @author Eric Butler (edbutler)
 * @author Zeyang Li (zeyangl)
 */

#ifndef _462_MATH_QUATERNION_HPP_
#define _462_MATH_QUATERNION_HPP_

#include "math.h"
#include "gfx/vec3.h"

namespace gfx {

class Matrix3;
class Matrix4;

/*
   This code is loosely based on quaternion code from Ogre3d (www.ogre3d.org).
 */

/**
 * A basic quaternion class.
 * Quaternions represent 3D rotations and can be used to concatenate
 * rotations efficiently. The class provides functions to convert
 * to and from rotation matrices and axis-angle representations.
 *
 * Quaternions can be concatenated right-to-left, just like matrices.
 * That is, to apply rotation A, then B, then C to vector V, do C*B*A*V.
 *
 * The axis-angle representation of a quaterion is a unit vector denoting
 * the axis (starting from the origin) about which the rotation occurs.
 * The angle represents the amount of counter-clockwise rotation in radians.
 * For example, an axis of (1,0,0) and an angle of PI/2 represents the rotation
 * that leaves the x-axis the same, takes the y-axis to the z-axis, and takes
 * the z-axis to the negative y-axis.
 */
class Quaternion
{
public:

    /**
     * The quaternion filled with zero.
     */
    static const Quaternion Zero;

    /**
     * The quaternion representing the identity rotation.
     */
    static const Quaternion Identity;

    double w, x, y, z;

    /**
     * Default constructor. Leaves values uninitialized.
     */
    Quaternion() {}

    /**
     * Construct a quaternion with the given values.
     */
    Quaternion( double w, double x, double y, double z )
        : w( w ), x( x ), y( y ), z( z ) { }

    /**
     * Constructs a quaternion representing a rotation about the given axis
     * by the given angle.
     */
    Quaternion( const Vec3& axis, double radians );

    /**
     *  Constructs a quaternion from a rotation matrix.
     */
    explicit Quaternion( const Matrix3& mat );

    /**
     *  Constructs a quaternion from a rotation matrix.
     */
    explicit Quaternion( const Matrix4& mat );

    Quaternion operator*( const Quaternion& rhs ) const;

    /**
     * Rotate a vector by this quaternion.
     */
    Vec3 operator*( const Vec3& rhs ) const;

    Quaternion operator*( double s ) const {
        return Quaternion( w * s, x * s, y * s, z * s );
    }

    Quaternion& operator*=( double s ) {
        w *= s;
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    bool operator==( const Quaternion& rhs ) const {
        return rhs.x == x && rhs.y == y &&
               rhs.z == z && rhs.w == w;
    }

    bool operator!=( const Quaternion& rhs ) const {
        return !operator==( rhs );
    }

    /**
     * Convert this quaternion into an angle and axis.
     * Returns the rotation in radians about an axis.
     */
    void to_axis_angle( Vec3* axis, double* angle ) const;

    /**
     * Converts this quaternion to a 3x3 matrix.
     */
    void to_matrix( Matrix3* mat ) const;

    /**
     * Converts this quaternion to a 4x4 matrix.
     */
    void to_matrix( Matrix4* mat ) const;

    /**
     * Returns the X,Y,Z axes rotated by this quaternion.
     */
    void to_axes( Vec3 axes[3] ) const;
};

inline double norm( const Quaternion& q ) {
    return q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
}

inline Quaternion operator*( double s, const Quaternion& rhs ) {
    return rhs * s;
}

Quaternion normalize( const Quaternion& q );

Quaternion conjugate( const Quaternion& q );

std::ostream& operator <<( std::ostream& o, const Quaternion& q );

} /* _462 */

#endif /* _462_MATH_QUATERNION_HPP_ */

