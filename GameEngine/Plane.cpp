#include"Plane.h"


MyPlane::MyPlane()
{
   a = 0; b = 0; c = 0; d = 0;
}


MyPlane::MyPlane(float A, float B, float C, float D)
{
   a = A; b = B; c = C; d = D;
}


MyPlane::MyPlane(MyVector3 &n, float D)
{
   a = n.x; b = n.y; c = n.z; d = D;
}


void MyPlane::CreatePlaneFromTri(MyVector3 &v1, MyVector3 &v2, MyVector3 &v3)
{
   MyVector3 normal, e1, e2;

   e1 = v3 - v1;
   e2 = v2 - v1;

   e1.Normal();
   e2.Normal();

   normal.CrossProduct(e1, e2);
   normal.Normal();

   a = normal.x;
   b = normal.y;
   c = normal.z;
   d = - (a * v1.x + b * v1.y + c * v1.z);
}


bool MyPlane::Intersect(MyPlane &p2, MyPlane &p3, MyVector3 *intersectPoint)
{
   MyVector3 temp;
   MyVector3 normal(a, b, c);
   MyVector3 p2Normal(p2.a, p2.b, p2.c);
   MyVector3 p3Normal(p3.a, p3.b, p3.c);

   temp.CrossProduct(p2Normal, p3Normal);

   float dp = normal.DotProduct3(temp);
   if(dp == 0.0f) return false;

   if(intersectPoint)
      {
         *intersectPoint = temp * d;

         temp.CrossProduct(p3Normal, normal);
         *intersectPoint = *intersectPoint + (temp * p2.d);

         temp.CrossProduct(normal, p2Normal);
         *intersectPoint = *intersectPoint + (temp * p3.d);

         *intersectPoint = *intersectPoint / -dp;
      }

   return true;
}


bool MyPlane::Intersect(MyPlane &pl, MyVector3 *intersectPoint)
{
   MyVector3 cross;
   MyVector3 normal(a, b, c);
   MyVector3 plNormal(pl.a, pl.b, pl.c);
   float length = 0;

   cross.CrossProduct(normal, plNormal);
   length = cross.DotProduct3(cross);

   if(length < 1e-08f) return false;

   if(intersectPoint)
      {
         float l0 = normal.DotProduct3(normal);
         float l1 = normal.DotProduct3(plNormal);
         float l2 = plNormal.DotProduct3(plNormal);
         float det = l0 * l2 - l1 * l1;
         float invDet = 0;

         if(fabs(det) < 1e-08f) return false;

         invDet = 1 / det;
         float d0 = (l2 * d - l1 * pl.d) * invDet;
         float d1 = (l0 * pl.d - l1 * d) * invDet;

         (*intersectPoint) = normal * d0 + plNormal * d1;
      }

   return true;
}


bool MyPlane::Intersect(MyPlane &pl, MyRay *intersect)
{
   MyVector3 cross;
   MyVector3 normal(a, b, c);
   MyVector3 plNormal(pl.a, pl.b, pl.c);
   float length = 0;

   cross.CrossProduct(normal, plNormal);
   length = cross.DotProduct3(cross);

   if(length < 1e-08f) return false;

   if(intersect)
      {
         float l0 = normal.DotProduct3(normal);
         float l1 = normal.DotProduct3(plNormal);
         float l2 = plNormal.DotProduct3(plNormal);
         float det = l0 * l2 - l1 * l1;
         float invDet = 0;
         
         if(fabs(det) < 1e-08f) return false;
         
         invDet = 1 / det;
         float d0 = (l2 * d - l1 * pl.d) * invDet;
         float d1 = (l0 * pl.d - l1 * d) * invDet;
         
         (*intersect).m_origin = normal * d0 + plNormal * d1;
         (*intersect).m_direction = cross;
      }

   return true;
}


int MyPlane::ClassifyPolygon(MyPolygon &pol)
{
   int frontPolys = 0;
   int backPolys = 0;
   int planePolys = 0;
   int type = 0;

   for(int i = 0; i < 3; i++)
      {
         type = ClassifyPoint(pol.m_vertexList[i]);

         switch(type)
            {
               case OBJ_FRONT:
                  frontPolys++;
                  break;
               
               case OBJ_BACK:
                  backPolys++;
                  break;
               
               default:
                  frontPolys++;
                  backPolys++;
                  planePolys++;
                  break;
            }
      }

   if(planePolys == 3) return OBJ_ON_PLANE;
   else if(frontPolys == 3) return OBJ_FRONT;
   else if(backPolys == 3) return OBJ_BACK;

   return OBJ_CLIPPED;
}


int MyPlane::ClassifyPoint(MyVector3 &v)
{
   float distance = a * v.x + b * v.y + c * v.z + d;

   if(distance > 0.001) return OBJ_FRONT;
   if(distance < -0.001) return OBJ_BACK;

   return OBJ_ON_PLANE;
}


int MyPlane::ClassifyPoint(float x, float y, float z)
{
   float distance = a * x + b * y + c * z + d;

   if(distance > 0.001) return OBJ_FRONT;
   if(distance < -0.001) return OBJ_BACK;

   return OBJ_ON_PLANE;
}


void MyPlane::Lerp(MyPlane &p1, MyPlane &p2, float amount)
{
   a = p1.a * (1.0f - amount) + p2.a * amount;
   b = p1.b * (1.0f - amount) + p2.b * amount;
   c = p1.c * (1.0f - amount) + p2.c * amount;
   d = p1.d * (1.0f - amount) + p2.d * amount;

   float length = (float)sqrt((a * a + b * b + c * c));
   
   if(length == 0.0f) length = 1.0f;
   length = 1 / length;

   a = a * length;
   b = b * length;
   c = c * length;
}