#include"Polygon.h"


void MyPolygon::Copy(MyPolygon &pol)
{
   m_vertexList[0] = pol.m_vertexList[0];
   m_vertexList[1] = pol.m_vertexList[1];
   m_vertexList[2] = pol.m_vertexList[2];
   m_flag = pol.m_flag;
}


void MyPolygon::Clip(MyPlane &pl, MyPolygon *front, MyPolygon *back)
{
   MyVector3 frontVecs[3], backVecs[3];
   int frontIndex = 0;
   int backIndex = 0;

   if(!front && !back) return;

   switch(pl.ClassifyPoint(m_vertexList[0]))
      {
         case OBJ_FRONT:
            frontVecs[frontIndex++] = m_vertexList[0];
            break;
         
         case OBJ_BACK:
            backVecs[backIndex++] = m_vertexList[0];
            break;
         
         case OBJ_ON_PLANE:
            frontVecs[frontIndex++] = m_vertexList[0];
            backVecs[backIndex++] = m_vertexList[0];
            //frontVecs[backIndex++] = m_vertexList[0];
            break;
         
         default:
            return;
      }

   int index = 0;
   int v1Type = 0, v2Type = 0;
   MyVector3 v1, v2, intersectPoint;
   MyRay ray;

   for(int i = 1; i < 4; i++)
      {
         if(i == 3) index = 0;
         else index = i;

         v1 = m_vertexList[i - 1];
         v2 = m_vertexList[index];

         v1Type = pl.ClassifyPoint(v1);
         v2Type = pl.ClassifyPoint(v2);

         if(v2Type == OBJ_ON_PLANE)
            {
               frontVecs[frontIndex++] = m_vertexList[index];
               backVecs[backIndex++] = m_vertexList[index];
            }
         else
            {
               float length = 0;
               ray.m_origin = v1;
               ray.m_direction = v2 - v1;
               length = ray.m_direction.GetLength();
               ray.m_direction.Normal();
               
               if(ray.Intersect(pl, false, length, &intersectPoint, 0) &&
                  (v1Type != OBJ_ON_PLANE))
                  {
                     frontVecs[frontIndex++] = intersectPoint;
                     backVecs[backIndex++] = intersectPoint;
                  }
               
               if(index == 0) continue;
               if(v2Type == OBJ_FRONT) frontVecs[frontIndex++] = m_vertexList[index];
               else if(v2Type == OBJ_BACK) backVecs[backIndex++] = m_vertexList[index];
            }
      }
   
   if(front)
      {
         MyPlane fPl;
         MyVector3 n, n2;

         fPl.CreatePlaneFromTri(frontVecs[0], frontVecs[1], frontVecs[2]);
         n.x = fPl.a; n.y = fPl.b; n.z = fPl.c;
         n2.x = pl.a; n2.y = pl.b; n2.z = pl.c;

         if(n.DotProduct3(n2) >= 0.0f)
            {
               front->m_vertexList[0] = frontVecs[0];
               front->m_vertexList[1] = frontVecs[1];
               front->m_vertexList[2] = frontVecs[2];
            }
         else
            {
               front->m_vertexList[0] = frontVecs[2];
               front->m_vertexList[1] = frontVecs[1];
               front->m_vertexList[2] = frontVecs[0];
            }
      }
   
   if(back)
      {
         MyPlane fPl;
         MyVector3 n, n2;

         fPl.CreatePlaneFromTri(backVecs[0], backVecs[1], backVecs[2]);
         n.x = fPl.a; n.y = fPl.b; n.z = fPl.c;
         n2.x = pl.a; n2.y = pl.b; n2.z = pl.c;

         if(n.DotProduct3(n2) >= 0.0f)
            {
               back->m_vertexList[0] = backVecs[0];
               back->m_vertexList[1] = backVecs[1];
               back->m_vertexList[2] = backVecs[2];
            }
         else
            {
               back->m_vertexList[0] = backVecs[2];
               back->m_vertexList[1] = backVecs[1];
               back->m_vertexList[2] = backVecs[0];
            }
      }
}


bool MyPolygon::Intersect(MyRay &ray, bool cull, float *dist)
{
   if(!ray.Intersect(m_vertexList[0], m_vertexList[1],
      m_vertexList[2], false, dist)) return false;
   
   if(!cull)
      {
         if(!ray.Intersect(m_vertexList[2], m_vertexList[1],
            m_vertexList[0], false, dist)) return false;
      }
   
   return true;
}