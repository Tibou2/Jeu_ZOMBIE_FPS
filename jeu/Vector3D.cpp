//
//  vector3d.cpp
//  testCamera
//
//  Created by Jean-Marie Normand on 29/09/2014.
//  Copyright (c) 2014 Jean-Marie Normand. All rights reserved.
//


#include "vector3d.h"
#include <cmath>

Vector3D::Vector3D()
{
    vX = 0;
    vY = 0;
    vZ = 0;
}

Vector3D::Vector3D(double x, double y, double z)
{
    vX = x;
    vY = y;
    vZ = z;
}

Vector3D::Vector3D(const Vector3D& v)
{
    vX = v.vX;
    vY = v.vY;
    vZ = v.vZ;
}

Vector3D::Vector3D(const Vector3D& from, const Vector3D& to)
{
    vX = to.vX - from.vX;
    vY = to.vY - from.vY;
    vZ = to.vZ - from.vZ;
}

Vector3D& Vector3D::operator= (const Vector3D& v)
{
    vX = v.vX;
    vY = v.vY;
    vZ = v.vZ;
    return *this;
}

Vector3D& Vector3D::operator+= (const Vector3D& v)
{
    vX += v.vX;
    vY += v.vY;
    vZ += v.vZ;
    return *this;
}

Vector3D Vector3D::operator+ (const Vector3D& v) const
{
    Vector3D t = *this;
    t += v;
    return t;
}

Vector3D& Vector3D::operator-= (const Vector3D& v)
{
    vX -= v.vX;
    vY -= v.vY;
    vZ -= v.vZ;
    return *this;
}

Vector3D Vector3D::operator- (const Vector3D& v) const
{
    Vector3D t = *this;
    t -= v;
    return t;
}

Vector3D& Vector3D::operator*= (const double a)
{
    vX *= a;
    vY *= a;
    vZ *= a;
    return *this;
}

Vector3D Vector3D::operator* (const double a)const
{
    Vector3D t = *this;
    t *= a;
    return t;
}

Vector3D operator* (const double a, const Vector3D& v)
{
    return Vector3D(v.vX * a, v.vY * a, v.vZ * a);
}

Vector3D& Vector3D::operator/= (const double a)
{
    vX /= a;
    vY /= a;
    vZ /= a;
    return *this;
}

Vector3D Vector3D::operator/ (const double a)const
{
    Vector3D t = *this;
    t /= a;
    return t;
}

bool Vector3D::operator==(const Vector3D v2) const
{
    return (vX == v2.getVx() || vY == v2.getVy() || vZ == v2.getVz());
}


// Setters/Getters
void Vector3D::setVx(double x) {
    vX = x;
}

double Vector3D::getVx() const {
    return vX;
}

void Vector3D::setVy(double y) {
    vY = y;
}

double Vector3D::getVy() const {
    return vY;
}

void Vector3D::setVz(double z) {
    vZ = z;
}

double Vector3D::getVz() const {
    return vZ;
}


double Vector3D::dot(const Vector3D  v) const
{
    return (vX * v.vX + vY * v.vY + vZ * v.vZ);
}

Vector3D Vector3D::crossProduct(Vector3D& v)
{
    Vector3D t;
    t.vX = vY * v.vZ - vZ * v.vY;
    t.vY = vZ * v.vX - vX * v.vZ;
    t.vZ = vX * v.vY - vY * v.vX;
    return t;
}

double Vector3D::length()const
{
    return sqrt(vX * vX + vY * vY + vZ * vZ);
}

Vector3D& Vector3D::normalize()
{
    (*this) /= length();
    return (*this);
}

Vector3D Vector3D::rotation(float angle) const
{
    Vector3D vRes;
    vRes.setVx(vX * cos(angle) - vZ * sin(angle));
    vRes.setVz(vX * sin(angle) + vZ * cos(angle));
    vRes.setVy(vX);
    return vRes;
}