#pragma once


#include"Vector.h"


class MyMatrix4x4
{
   public:
      MyMatrix4x4() { Identity(); }
      MyMatrix4x4(const MyMatrix4x4 &m);
      MyMatrix4x4(float r11, float r12, float r13, float r14,
                 float r21, float r22, float r23, float r24,
                 float r31, float r32, float r33, float r34,
                 float r41, float r42, float r43, float r44);
      ~MyMatrix4x4() {}

      void Identity();

      void operator=(MyMatrix4x4 &m);
      MyMatrix4x4 operator-(MyMatrix4x4 &m);
      MyMatrix4x4 operator+(MyMatrix4x4 &m);
      MyMatrix4x4 operator*(MyMatrix4x4 &m);

      MyMatrix4x4 operator*(float f);
      MyMatrix4x4 operator/(float f);

      void operator +=(MyMatrix4x4 &m);
      void operator -=(MyMatrix4x4 &m);
      void operator *=(MyMatrix4x4 &m);

      void operator *=(float f);
      void operator /=(float f);

      void Translate(MyVector3 &Translate);
      void Translate(float x, float y, float z);
      void inverseTranslate();

      void Rotate(double angle, int x, int y, int z);

      MyVector3 VectorMatrixMultiply(MyVector3 &v);
      MyVector3 VectorMatrixMultiply3x3(MyVector3 &v);
      
      float matrix[16];
};
