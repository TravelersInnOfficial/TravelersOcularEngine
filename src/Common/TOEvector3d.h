#ifndef TOEvector3D_H
#define TOEvector3D_H

/**
 * @brief TOE vector3d template class.
 * 
 * @file TOEvector3d.h
 */

#include <iostream>
#include <math.h>
#include <Constants.h>
 
template<typename T>
class TOEvector3d{

private:
public:
    // variables of vector
    T X, Y, Z;      
    
    /**
     * Creates and empty 3d vector of all 0;
    */
    TOEvector3d() : X(0), Y(0), Z(0) {}
    
    /**
     * Creates and initializes 3d vector of same number
    */
    TOEvector3d(T n) : X(n), Y(n), Z(n) {}

    /**
     * Creates and initializes 3d vector
    */
    TOEvector3d(T nx, T ny, T nz) : X(nx), Y(ny), Z(nz) {}

    /**
     * Copy constructor
    */
    TOEvector3d(const TOEvector3d<T>& other) : X(other.X), Y(other.Y), Z(other.Z) {}

    /**
     * returns length of the vector
    */
    float length(){return sqrtf(X*X + Y*Y + Z*Z);}

    /**
     * normalize the vector
     */

    void normalize(){
        float l = length();
        if(l==0){
            X = 0;
            Y = 0;
            Z = 0;
        }
        else{
            X = X/l;
            Y = Y/l;
            Z = Z/l;
        }
    }

    /**
     * convert the vector to radian
     */
    void toRadians(){
        float factor = M_PI/180;
        X = X * factor;
        Y = Y * factor;
        Z = Z * factor;
    }

    /**
     * convert the vector de degrees
     */
    void toDegrees(){
        float factor = 180/M_PI;
        X = X * factor;
        Y = Y * factor;
        Z = Z * factor;
    }

    /**
     * Sets X Value
    */

    void setX(T newX){ X = newX;}

    /**
     * Sets Y Value
    */

    void setY(T newY){ Y = newY;}

    /**
     * Sets Z Value
    */

    void setZ(T newZ){ Z = newZ;}

    //Operators
    TOEvector3d<T> operator+(const T v) const { return TOEvector3d<T>(X + v, Y + v, Z + v); }
    TOEvector3d<T> operator-(const T v) const { return TOEvector3d<T>(X - v, Y - v, Z - v); }
    TOEvector3d<T> operator*(const T v) const { return TOEvector3d<T>(X * v, Y * v, Z * v); }
    TOEvector3d<T> operator/(const T v) const { return TOEvector3d<T>(X / v, Y / v, Z / v); }
    TOEvector3d<T> operator-(TOEvector3d<T> v) const { return TOEvector3d<T>(X-v.X, Y-v.Y, Z-v.Z); }
    TOEvector3d<T> operator+(TOEvector3d<T> v) const { return TOEvector3d<T>(X+v.X, Y+v.Y, Z+v.Z); }
    TOEvector3d<T> operator*(TOEvector3d<T> v) const { return TOEvector3d<T>(X*v.X, Y*v.Y, Z*v.Z); }
    TOEvector3d<T> operator/(TOEvector3d<T> v) const { return TOEvector3d<T>(X/v.X, Y/v.Y, Z/v.Z); }

    void operator=(const TOEvector3d<T> v) { X = v.X; Y = v.Y; Z = v.Z; }
    void operator*=(const T v) { X = X*v; Y = Y*v; Z = Z*v; }

    bool operator==(const TOEvector3d<T> v) { if(v.X == X && v.Y == Y && v.Z == Z) return true; return false; }


    friend inline std::ostream& operator << (std::ostream &o,const TOEvector3d<T> &v){
        o << "(" << v.X << ", " << v.Y << ", " << v.Z << ")";
        return o;
    }
};

typedef TOEvector3d<float> TOEvector3df;
typedef TOEvector3d<int> TOEvector3di;

#endif