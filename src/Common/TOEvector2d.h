#ifndef TOEvector2D_H
#define TOEvector2D_H

/**
 * @brief TOE vector2d template class.
 * 
 * @file TOEvector2d.h
 */

#include <iostream>
#include <cmath>
#include <Constants.h>
#include <TOEvector3d.h>

template<typename T>
class TOEvector2d{

private:
public:
    // variables of vector
    T X, Y;      
    
    /**
     * Creates and empty 3d vector of all 0;
    */
    TOEvector2d() : X(0), Y(0) {}
    
    /**
     * Creates and initializes 3d vector
    */
    TOEvector2d(T nx, T ny) : X(nx), Y(ny) {}

    /**
     * Copy constructor
    */
    TOEvector2d(const TOEvector2d<T>& other) : X(other.X), Y(other.Y) {}

    /**
     * Convert 3d in 2d
     */

    TOEvector2d(const TOEvector3d<T>& other) : X(other.X), Y(other.Y) {}

    /**
     * returns length of the vector
    */
    float length(){return sqrtf(X*X + Y*Y);}

    /**
     * convert to abs the values of the vector
     */
    TOEvector2d absolute(){
    return TOEvector2d(abs(X), abs(Y));
    }

    /**
     * normalize the vector
     */

    void normalize(){
        float l = length();
        if(l==0){
            X = 0;
            Y = 0;
        }
        else{
            X = X/l;
            Y = Y/l;
        }
    }

    /**
     * Map the Angles between [-pi, pi]
     */

    void mapToRangePI(){
        if(X>M_PI){
            X = X - 2*M_PI;
        }else if(X<-M_PI){
            X = X + 2*M_PI;
        }
        if(Y>M_PI){
            Y = Y - 2*M_PI;
        }else if(Y<-M_PI){
            Y = Y + 2*M_PI;
        }
    }

    /**
     * Sets X Value
    */

    void setX(T newX){ X = newX;}

    /**
     * Sets Y Value
    */

    void setY(T newY){ Y = newY;}


    //Operators
    TOEvector2d<T> operator*(const T v) const { return TOEvector2d<T>(X * v, Y * v); }
    TOEvector2d<T> operator/(const T v) const { return TOEvector2d<T>(X / v, Y / v); }
    TOEvector2d<T> operator-(TOEvector2d<T> v) const { return TOEvector2d<T>(X-v.X, Y-v.Y); }
    TOEvector2d<T> operator+(TOEvector2d<T> v) const { return TOEvector2d<T>(X+v.X, Y+v.Y); }
    void operator=(const TOEvector2d<T> v) { X = v.X; Y = v.Y;}
    void operator*=(const T v) { X = X*v; Y = Y*v;}

    bool operator==(const TOEvector2d<T> v) { if(v.X == X && v.Y == Y) return true; return false; }

    friend inline std::ostream& operator << (std::ostream &o,const TOEvector2d<T> &v){
        o << "(" << v.X << ", " << v.Y << ")";
        return o;
    }
};

typedef TOEvector2d<float> TOEvector2df;
typedef TOEvector2d<int> TOEvector2di;

#endif