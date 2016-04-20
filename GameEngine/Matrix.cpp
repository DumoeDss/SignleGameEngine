#include"Matrix.h"
#include"MathDefines.h"


MyMatrix4x4::MyMatrix4x4(const MyMatrix4x4 &m)
{
   matrix[0]  = m.matrix[0];
   matrix[4]  = m.matrix[4];
   matrix[8]  = m.matrix[8];
   matrix[12] = m.matrix[12];

   matrix[1]  = m.matrix[1];
   matrix[5]  = m.matrix[5];
   matrix[9]  = m.matrix[9];
   matrix[13] = m.matrix[13];

   matrix[2]  = m.matrix[2];
   matrix[6]  = m.matrix[6];
   matrix[10] = m.matrix[10];
   matrix[14] = m.matrix[14];

   matrix[3]  = m.matrix[3];
   matrix[7]  = m.matrix[7];
   matrix[11] = m.matrix[11];
   matrix[15] = m.matrix[15];
}


MyMatrix4x4::MyMatrix4x4(float r11, float r12, float r13, float r14,
                       float r21, float r22, float r23, float r24,
                       float r31, float r32, float r33, float r34,
                       float r41, float r42, float r43, float r44)
{
   matrix[0]  = r11; matrix[1]  = r12; matrix[2]  = r13; matrix[3]  = r14;
	matrix[4]  = r21; matrix[5]  = r22; matrix[6]  = r23; matrix[7]  = r24;
	matrix[8]  = r31; matrix[9]  = r32; matrix[10] = r33; matrix[11] = r34;
	matrix[12] = r41; matrix[13] = r42; matrix[14] = r43; matrix[15] = r44;
}


void MyMatrix4x4::Identity()
{
   matrix[0]  = 1.0f; matrix[1]  = 0.0f; matrix[2]  = 0.0f; matrix[3]  = 0.0f;
	matrix[4]  = 0.0f; matrix[5]  = 1.0f; matrix[6]  = 0.0f; matrix[7]  = 0.0f;
	matrix[8]  = 0.0f; matrix[9]  = 0.0f; matrix[10] = 1.0f; matrix[11] = 0.0f;
	matrix[12] = 0.0f; matrix[13] = 0.0f; matrix[14] = 0.0f; matrix[15] = 1.0f;
}


void MyMatrix4x4::operator =(MyMatrix4x4 &m)
{
   matrix[0]  = m.matrix[0]; matrix[1] = m.matrix[1];
   matrix[2] = m.matrix[2]; matrix[3]  = m.matrix[3];
	matrix[4]  = m.matrix[4]; matrix[5] = m.matrix[5];
	matrix[6] = m.matrix[6]; matrix[7]  = m.matrix[7];
	matrix[8]  = m.matrix[8]; matrix[9] = m.matrix[9];
	matrix[10] = m.matrix[10]; matrix[11] = m.matrix[11];
	matrix[12] = m.matrix[12]; matrix[13] = m.matrix[13];
	matrix[14] = m.matrix[14]; matrix[15] = m.matrix[15];
}


MyMatrix4x4 MyMatrix4x4::operator -(MyMatrix4x4 &m)
{
   return MyMatrix4x4(matrix[0] - m.matrix[0], matrix[1] - m.matrix[1], matrix[2] - m.matrix[2],
                     matrix[3] - m.matrix[3], matrix[4] - m.matrix[4], matrix[5] - m.matrix[5],
                     matrix[6] - m.matrix[6], matrix[7] - m.matrix[7], matrix[8] - m.matrix[8],
                     matrix[9] - m.matrix[9], matrix[10] - m.matrix[10], matrix[11] - m.matrix[11],
                     matrix[12] - m.matrix[12], matrix[13] - m.matrix[13],
                     matrix[14] - m.matrix[14], matrix[15] - m.matrix[15]);
}


MyMatrix4x4 MyMatrix4x4::operator +(MyMatrix4x4 &m)
{
   return MyMatrix4x4(matrix[0] + m.matrix[0], matrix[1] + m.matrix[1], matrix[2] + m.matrix[2],
                     matrix[3] + m.matrix[3], matrix[4] + m.matrix[4], matrix[5] + m.matrix[5],
                     matrix[6] + m.matrix[6], matrix[7] + m.matrix[7], matrix[8] + m.matrix[8],
                     matrix[9] + m.matrix[9], matrix[10] + m.matrix[10], matrix[11] + m.matrix[11],
                     matrix[12] + m.matrix[12], matrix[13] + m.matrix[13],
                     matrix[14] + m.matrix[14], matrix[15] + m.matrix[15]);
}


MyMatrix4x4 MyMatrix4x4::operator *(MyMatrix4x4 &m)
{
   return MyMatrix4x4(matrix[0] * m.matrix[0] + matrix[4] * m.matrix[1] + matrix[8] *
                     m.matrix[2] + matrix[12] * m.matrix[3],
						   matrix[1] * m.matrix[0] + matrix[5] * m.matrix[1] + matrix[9] *
                     m.matrix[2] + matrix[13] * m.matrix[3],
						   matrix[2] * m.matrix[0] + matrix[6] * m.matrix[1] + matrix[10] *
                     m.matrix[2] + matrix[14] * m.matrix[3],
						   matrix[3] * m.matrix[0] + matrix[7] * m.matrix[1] + matrix[11] *
                     m.matrix[2] + matrix[15] * m.matrix[3],
						   matrix[0] * m.matrix[4] + matrix[4] * m.matrix[5] + matrix[8] *
                     m.matrix[6] + matrix[12] * m.matrix[7],
						   matrix[1] * m.matrix[4] + matrix[5] * m.matrix[5] + matrix[9] *
                     m.matrix[6] + matrix[13] * m.matrix[7],
						   matrix[2] * m.matrix[4] + matrix[6] * m.matrix[5] + matrix[10] *
                     m.matrix[6] + matrix[14] * m.matrix[7],
						   matrix[3] * m.matrix[4] + matrix[7] * m.matrix[5] + matrix[11] *
                     m.matrix[6] + matrix[15] * m.matrix[7],
						   matrix[0] * m.matrix[8] + matrix[4] * m.matrix[9] + matrix[8] *
                     m.matrix[10] + matrix[12] * m.matrix[11],
						   matrix[1] * m.matrix[8] + matrix[5] * m.matrix[9] + matrix[9] *
                     m.matrix[10] + matrix[13] * m.matrix[11],
						   matrix[2] * m.matrix[8] + matrix[6] * m.matrix[9] + matrix[10] *
                     m.matrix[10] + matrix[14] * m.matrix[11],
						   matrix[3] * m.matrix[8] + matrix[7] * m.matrix[9] + matrix[11] *
                     m.matrix[10] + matrix[15] * m.matrix[11],
						   matrix[0] * m.matrix[12] + matrix[4] * m.matrix[13] + matrix[8] *
                     m.matrix[14] + matrix[12] * m.matrix[15],
						   matrix[1] * m.matrix[12] + matrix[5] * m.matrix[13] + matrix[9] *
                     m.matrix[14] + matrix[13] * m.matrix[15],
						   matrix[2] * m.matrix[12] + matrix[6] * m.matrix[13] + matrix[10] *
                     m.matrix[14] + matrix[14] * m.matrix[15],
						   matrix[3] * m.matrix[12] + matrix[7] * m.matrix[13] + matrix[11] *
                     m.matrix[14] + matrix[15] * m.matrix[15]);
}


MyMatrix4x4 MyMatrix4x4::operator *(float f)
{
   return MyMatrix4x4(matrix[0]  * f, matrix[1]  * f, matrix[2]  * f, matrix[3]  * f,
                     matrix[4]  * f, matrix[5]  * f, matrix[6]  * f, matrix[7]  * f,
                     matrix[8]  * f, matrix[9]  * f, matrix[10] * f, matrix[11] * f,
                     matrix[12] * f, matrix[13] * f, matrix[14] * f, matrix[15] * f);
}


MyMatrix4x4 MyMatrix4x4::operator /(float f)
{
   if(f == 0) f = 1;
   f = 1/f;

   return MyMatrix4x4(matrix[0]  * f, matrix[1]  * f, matrix[2]  * f, matrix[3]  * f,
                     matrix[4]  * f, matrix[5]  * f, matrix[6]  * f, matrix[7]  * f,
                     matrix[8]  * f, matrix[9]  * f, matrix[10] * f, matrix[11] * f,
                     matrix[12] * f, matrix[13] * f, matrix[14] * f, matrix[15] * f);
}


void MyMatrix4x4::operator +=(MyMatrix4x4 &m)
{
   (*this) = (*this) + m;
}


void MyMatrix4x4::operator -=(MyMatrix4x4 &m)
{
   (*this) = (*this) - m;
}


void MyMatrix4x4::operator *=(MyMatrix4x4 &m)
{
   (*this) = (*this) * m;
}


void MyMatrix4x4::operator *=(float f)
{
   (*this) = (*this) * f;
}


void MyMatrix4x4::operator /=(float f)
{
   (*this) = (*this) / f;
}


void MyMatrix4x4::Translate(MyVector3 &Translate)
{
   matrix[12] = Translate.x;
   matrix[13] = Translate.y;
   matrix[14] = Translate.z;
   matrix[15] = 1.0f;
}


void MyMatrix4x4::Translate(float x, float y, float z)
{
   matrix[12] = x;
   matrix[13] = y;
   matrix[14] = z;
   matrix[15] = 1.0f;
}


void MyMatrix4x4::inverseTranslate()
{
   matrix[12] = -matrix[12];
   matrix[13] = -matrix[13];
   matrix[14] = -matrix[14];
}


void MyMatrix4x4::Rotate(double angle, int x, int y, int z)
{
   angle = angle * PI / 180;
   float cosAngle = cosf((float)angle);
   float sineAngle = sinf((float)angle);

   if(z)
      {
         matrix[0] = cosAngle;
	      matrix[1] = sineAngle;
	      matrix[4] = -sineAngle;
	      matrix[5] = cosAngle;
      }

   if(y)
      {
         matrix[0]  = cosAngle;
	      matrix[2]  = -sineAngle;
	      matrix[8]  = sineAngle;
	      matrix[10] = cosAngle;
      }

   if(x)
      {
	      matrix[5]  = cosAngle;
	      matrix[6]  = sineAngle;
	      matrix[9]  = -sineAngle;
	      matrix[10] = cosAngle;
      }
}


MyVector3 MyMatrix4x4::VectorMatrixMultiply(MyVector3 &v)
{
   MyVector3 out;

   out.x = (v.x * matrix[0]) + (v.y * matrix[4]) + (v.z * matrix[8]) + matrix[12];
   out.y = (v.x * matrix[1]) + (v.y * matrix[5]) + (v.z * matrix[9]) + matrix[13];
   out.z = (v.x * matrix[2]) + (v.y * matrix[6]) + (v.z * matrix[10]) + matrix[14];

   return out;
}


MyVector3 MyMatrix4x4::VectorMatrixMultiply3x3(MyVector3 &v)
{
   MyVector3 out;

   out.x = (v.x * matrix[0]) + (v.y * matrix[4]) + (v.z * matrix[8]);
   out.y = (v.x * matrix[1]) + (v.y * matrix[5]) + (v.z * matrix[9]);
   out.z = (v.x * matrix[2]) + (v.y * matrix[6]) + (v.z * matrix[10]);

   return out;
}