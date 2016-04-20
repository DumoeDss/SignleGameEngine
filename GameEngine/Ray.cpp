#include"Ray.h"


bool MyRay::Intersect(MyVector3 &pos, float radius, float *dist)
{
   MyVector3 RSDir;

   float RayToSphereLength = 0.0f;
   float IntersectPoint = 0.0f;
   float SquaredPoint = 0.0f;

   RSDir = pos - m_origin;

   RayToSphereLength = RSDir.DotProduct3(RSDir);
   IntersectPoint = RSDir.DotProduct3(m_direction);

   if(IntersectPoint < 0 ) return false;

   SquaredPoint = (radius * radius) - RayToSphereLength +
                  (IntersectPoint * IntersectPoint);

   if(SquaredPoint < 0) return false;

   if(dist) *dist = IntersectPoint - (float)sqrt(SquaredPoint);

   return true;
}


bool MyRay::Intersect(MyVector3 &p1, MyVector3 &p2, MyVector3 &p3,
                     bool cull, float *dist)
{
   MyVector3 vecAB = p2 - p1;
   MyVector3 vecAC = p3 - p1;

   MyVector3 cross;
   cross.CrossProduct(m_direction, vecAC);

   float det = vecAB.DotProduct3(cross);
   
   if(cull && det < 0.0001f) return false;
   else if(det < 0.0001f && det > -0.0001f) return false;

   MyVector3 rayPointVec = m_origin - p1;
   float test1 = rayPointVec.DotProduct3(cross);
   
   if(test1 < 0.0f || test1 > det) return false;
   
   MyVector3 cross2;
   cross2.CrossProduct(rayPointVec , vecAB);
   float test2 = m_direction.DotProduct3(cross2);

   if(test2 < 0.0f || test1 + test2 > det) return false;
   
   float inverseDet = 1.0f / det;
   
   if(dist)
      {
         *dist = vecAC.DotProduct3(cross2);
         *dist *= inverseDet;
      }

   return true;
}


bool MyRay::Intersect(MyVector3 &p1, MyVector3 &p2, MyVector3 &p3,
                     bool cull, float length, float *dist)
{
   MyVector3 vecAB = p2 - p1;
   MyVector3 vecAC = p3 - p1;

   MyVector3 cross;
   cross.CrossProduct(m_direction, vecAC);

   float det = vecAB.DotProduct3(cross);
   
   if(cull && det < 0.0001f) return false;
   else if(det < 0.0001f && det > -0.0001f) return false;
      
   MyVector3 rayPointVec = m_origin - p1;
   float test1 = rayPointVec.DotProduct3(cross);

   if(test1 < 0.0f || test1 > det) return false;
   
   MyVector3 cross2;
   cross2.CrossProduct(rayPointVec , vecAB);
   float test2 = m_direction.DotProduct3(cross2);

   if(test2 < 0.0f || test1 + test2 > det) return false;
   
   float inverseDet = 1.0f / det;
   
   if(dist)
      {
         *dist = vecAC.DotProduct3(cross2);
         *dist *= inverseDet;

         if(*dist > length) return false;
      }
   else
      {
         float l = vecAC.DotProduct3(cross2) * inverseDet;
         if(l > length) return false;
      }

   return true;
}


bool MyRay::Intersect(MyPlane &pl, bool cull,
                     MyVector3 *intersectPoint, float *dist){
   MyVector3 normal(pl.a, pl.b, pl.c);

   float rayD = normal.DotProduct3(m_direction);
   
   if(fabs(rayD) < 0.00001f) return false;
   if(cull && rayD > 0.0f) return false;

   float originD = -(normal.DotProduct3(m_origin) + pl.d);
   float intersectDist = originD / rayD;
   
   if(intersectDist < 0.001f) return false;
   
   if(dist) *dist = intersectDist;
   if(intersectPoint)
      *intersectPoint = m_origin + (m_direction * intersectDist);
   
   return true;
}


bool MyRay::Intersect(MyPlane &pl, bool cull, float length,
                     MyVector3 *intersectPoint, float *dist)
{
   MyVector3 normal(pl.a, pl.b, pl.c);

   float rayD = normal.DotProduct3(m_direction);

   if(fabs(rayD) < 0.00001f) return false;
   if(cull && rayD > 0.0f) return false;

   float originD = -(normal.DotProduct3(m_origin) + pl.d);
   
   float intersectDist = originD / rayD;
   
   if(intersectDist < 0.001f || intersectDist > length) return false;
   
   if(dist) *dist = intersectDist;
   if(intersectPoint)
      *intersectPoint = m_origin + (m_direction * intersectDist);
   
   return true;
}