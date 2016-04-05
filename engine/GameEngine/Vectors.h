//
//  Vectors.hpp
//  GameEngine
//
//  Created by David Lively on 2/10/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef VECTORS_H
#define VECTORS_H

#include <ostream>



struct Vector2
{
    float X;
    float Y;
    
    Vector2() : X(0), Y(0)
    {
    }
    
    Vector2(float x, float y) : X(x), Y(y)
    {
        
    }
    
};

struct Vector3 : public Vector2
{
    float Z;
    
    Vector3() : Vector2(), Z(0)
    {
        
    }
    
    Vector3(float x, float y, float z) : Vector2(x,y), Z(z)
    {
        
    }
    
    template<typename T>
    inline Vector3 operator* (const T& multiplier) const
    {
        return Vector3(X * multiplier, Y * multiplier, Z * multiplier);
    }
    
    template<typename T>
    inline Vector3 operator/ (const T& divisor) const
    {
        return Vector3(X/divisor, Y/divisor, Z/divisor);
    }
    
    Vector3 operator* (const Vector3 multiplier)
    {
        return Vector3(X * multiplier.X, Y * multiplier.Y, Z * multiplier.Z);
    }
    
    Vector3 operator*= (const Vector3 rval)
    {
        X *= rval.X;
        Y *= rval.Y;
        Z *= rval.Z;
        
        return *this;
    }
    Vector3 operator/= (const Vector3 rval)
    {
        X /= rval.X;
        Y /= rval.Y;
        Z /= rval.Z;
        
        return *this;
    }
    
    template<typename T>
    inline Vector3& operator*=(const T& rval)
    {
        X *= rval;
        Y *= rval;
        Z *= rval;
        
        return *this;
    }
    
    template<typename T>
    inline Vector3& operator+=(const T& rval)
    {
        X += rval.X;
        Y += rval.Y;
        Z += rval.Z;
        
        return *this;
    }

    template<typename T>
    inline Vector3& operator-=(const T& rval)
    {
        X -= rval.X;
        Y -= rval.Y;
        Z -= rval.Z;
        
        return *this;
    }
    
//    template<typename T>
//    inline Vector3& operator/=(const T& rval)
//    {
//        X /= rval.X;
//        Y /= rval.Y;
//        Z /= rval.Z;
//        
//        return *this;
//    }

    template<typename T>
    inline Vector3& operator=(const T& rval)
    {
        X = rval;
        Y = rval;
        Z = rval;
        
        return *this;
    }
    
    template<typename T>
    inline Vector3 operator-(const T& rval)
    {
        Vector3 temp;
        temp.X = X-rval.X;
        temp.Y = Y-rval.Y;
        temp.Z = Z-rval.Z;
        
        return temp;
    }
    
    inline Vector3 operator-(const float rval)
    {
        Vector3 temp;
        temp.X = X-rval;
        temp.Y = Y-rval;
        temp.Z = Z-rval;
        
        return temp;
    }
    
    
    friend std::ostream &operator<<(std::ostream &out, Vector3 v)     //output
    {
        out << v.X << "," << v.Y << "," << v.Z;

        return out;
    }

    
    
};

struct Vector4 : public Vector3
{
    float W;
    
    Vector4() : Vector3(), W(0)
    {
        
    }
    
    Vector4(float x, float y, float z, float w) : Vector3(x,y,z)
    {
        W = w;
        
    }
};

inline float dotProduct(Vector3 a, Vector3 b)
{
    // a . b
    
    float dot;
    
    dot = (a.X * b.X) + (a.Y * b.Y) + (a.Z * b.Z);
    
    return dot;
    
};


inline float dotProduct(Vector4 a, Vector4 b)
{
    // a . b
    
    float dot;
    
    dot = (a.X * b.X) + (a.Y * b.Y) + (a.Z * b.Z) + (a.W * b.W);
    
    return dot;
    
};
inline Vector3 crossProduct(Vector3 a, Vector3 b)
{
    //a X b
    
    Vector3 temp;
    
    temp.X = (a.Y * b.Z)-(a.Z * b.Y);
    temp.Y = (a.Z * b.X)-(a.X * b.Z);
    temp.Z = (a.X * b.Y)-(a.Y * b.X);
    
    return temp;
    
};





#endif /* Vectors_hpp */
