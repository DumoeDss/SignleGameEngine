#include"BoundingGeometry.h"

//创建边界框
void MyBoundingBox::CreateFromPoints(MyVector3 *pointList, int numPoints)
{
   for(int i = 0; i < numPoints; i++)
      {
         if(pointList[i].x < m_min.x) m_min.x = pointList[i].x;
         if(pointList[i].x > m_max.x) m_max.x = pointList[i].x;

         if(pointList[i].y < m_min.y) m_min.y = pointList[i].y;
         if(pointList[i].y > m_max.y) m_max.y = pointList[i].y;

         if(pointList[i].z < m_min.z) m_min.z = pointList[i].z;
         if(pointList[i].z > m_max.z) m_max.z = pointList[i].z;
      }
}

//判断某点是否在边界框内
bool MyBoundingBox::isPointInside(MyVector3 &v)
{
   if(m_max.x <= v.x) return false;
   if(m_min.x >= v.x) return false;
   if(m_max.y <= v.y) return false;
   if(m_min.y >= v.y) return false;
   if(m_max.z <= v.z) return false;
   if(m_min.z >= v.z) return false;

   return true;	
}

//判断是否与射线相交
bool MyBoundingBox::Intersect(MyRay ray, float *dist)
{
   float t0, t1, temp;
   float min = -999999.9f;
   float max = 999999.9f;

   if(fabs(ray.m_direction.x) < 0.00001f)
      {
         if((ray.m_origin.x < m_min.x) ||
            (ray.m_origin.x > m_max.x)) return false;
      }

   t0 = (m_min.x - ray.m_origin.x) / ray.m_direction.x;
   t1 = (m_max.x - ray.m_origin.x) / ray.m_direction.x;

   if(t0 > t1) { temp = t0; t0 = t1; t1 = temp; }
   if(t0 > min) min = t0;
   if(t1 < max) max = t1;
   if(min > max) return false;
   if(max < 0) return false;


   if(fabs(ray.m_direction.y) < 0.00001f)
      {
         if((ray.m_origin.y < m_min.y) ||
            (ray.m_origin.y > m_max.y)) return false;
      }

   t0 = (m_min.y - ray.m_origin.y) / ray.m_direction.y;
   t1 = (m_max.y - ray.m_origin.y) / ray.m_direction.y;

   if(t0 > t1) { temp = t0; t0 = t1; t1 = temp; }
   if(t0 > min) min = t0;
   if(t1 < max)  max = t1;
   if(min > max) return false;
   if(max < 0) return false;


   if(fabs(ray.m_direction.z) < 0.00001f)
      {
         if((ray.m_origin.z < m_min.z) ||
            (ray.m_origin.z > m_max.z)) return false;
      }

   t0 = (m_min.z - ray.m_origin.z) / ray.m_direction.z;
   t1 = (m_max.z - ray.m_origin.z) / ray.m_direction.z;

   if(t0 > t1) { temp = t0; t0 = t1; t1 = temp; }
   if(t0 > min) min = t0;
   if(t1 < max) max = t1;
   if(min > max) return false;
   if(max < 0) return false;


   if(min > 0) if(dist) *dist = min;
   else if(dist) *dist = max;

   return true;
}

//判断是否与射线相交
bool MyBoundingBox::Intersect(MyRay ray, float length, float *dist)
{
   float t0, t1, temp;
   float min = -999999.9f;
   float max = 999999.9f;
   float d = 0;

   if(fabs(ray.m_direction.x) < 0.00001f)
      {
         if((ray.m_origin.x < m_min.x) ||
            (ray.m_origin.x > m_max.x)) return false;
      }

   t0 = (m_min.x - ray.m_origin.x) / ray.m_direction.x;
   t1 = (m_max.x - ray.m_origin.x) / ray.m_direction.x;

   if(t0 > t1) { temp = t0; t0 = t1; t1 = temp; }
   if(t0 > min) min = t0;
   if(t1 < max) max = t1;
   if(min > max) return false;
   if(max < 0) return false;


   if(fabs(ray.m_direction.y) < 0.00001f)
      {
         if((ray.m_origin.y < m_min.y) ||
            (ray.m_origin.y > m_max.y)) return false;
      }

   t0 = (m_min.y - ray.m_origin.y) / ray.m_direction.y;
   t1 = (m_max.y - ray.m_origin.y) / ray.m_direction.y;

   if(t0 > t1) { temp = t0; t0 = t1; t1 = temp; }
   if(t0 > min) min = t0;
   if(t1 < max)  max = t1;
   if(min > max) return false;
   if(max < 0) return false;


   if(fabs(ray.m_direction.z) < 0.00001f)
      {
         if((ray.m_origin.z < m_min.z) ||
            (ray.m_origin.z > m_max.z)) return false;
      }

   t0 = (m_min.z - ray.m_origin.z) / ray.m_direction.z;
   t1 = (m_max.z - ray.m_origin.z) / ray.m_direction.z;

   if(t0 > t1) { temp = t0; t0 = t1; t1 = temp; }
   if(t0 > min) min = t0;
   if(t1 < max) max = t1;
   if(min > max) return false;
   if(max < 0) return false;

   if(min > 0) d = min;
   else d = max;
   
   if(d > length) return false;
   if(dist) *dist = d;

   return true;
}

//获取平面
void MyBoundingBox::GetPlanes(MyPlane *planes)
{
   planes[0].a = 1.0f; planes[0].b = 0.0f; planes[0].c = 0.0f;
   planes[0].d = -(1 * m_max.x + 0 * m_max.y + 0 * m_max.z);
   
   planes[1].a = -1.0f; planes[1].b = 0.0f; planes[1].c = 0.0f;
   planes[1].d = -(-1 * m_min.x + 0 * m_min.y + 0 * m_min.z);
   
   planes[2].a = 0.0f; planes[2].b = 0.0f; planes[2].c = -1.0f;
   planes[2].d = -(0 * m_min.x + 0 * m_min.y + -1 * m_min.z);
   
   planes[3].a = 0.0f; planes[3].b = 0.0f; planes[3].c = 1.0f;
   planes[3].d = -(0 * m_max.x + 0 * m_max.y + 1 * m_max.z);

   planes[4].a = 0.0f; planes[4].b = 1.0f; planes[4].c = 0.0f;
   planes[4].d = -(0 * m_max.x + 1 * m_max.y + 0 * m_max.z);

   planes[5].a = 0.0f; planes[5].b = -1.0f; planes[5].c = 0.0f;
   planes[5].d = -(0 * m_min.x + -1 * m_min.y + 0 * m_min.z);
}

//判断射线是否在边界框内
bool MyBoundingBox::isRayInside(MyRay &ray, float length)
{
   MyVector3 endPos = ray.m_origin + (ray.m_direction * length);
   return (isPointInside(ray.m_origin) && isPointInside(endPos));
}

//创建边界球
void MyBoundingSphere::CreateFromPoints(MyVector3 *pointList, int numPoints)
{
   MyVector3 min, max;
   float dist = 0, maxDistance = 0.0f;

   for(int i = 0; i < numPoints; i++)
      {
         if(pointList[i].x < min.x) min.x = pointList[i].x;
         if(pointList[i].x > max.x) max.x = pointList[i].x;

         if(pointList[i].y < min.y) min.y = pointList[i].y;
         if(pointList[i].y > max.y) max.y = pointList[i].y;

         if(pointList[i].z < min.z) min.z = pointList[i].z;
         if(pointList[i].z > max.z) max.z = pointList[i].z;
      }

   m_center = (max + min) * 0.5f;

   for(int i = 0; i < numPoints; i++)
      {
         dist = ((pointList[i].x - m_center.x) * (pointList[i].x - m_center.x)) +
                ((pointList[i].y - m_center.y) * (pointList[i].y - m_center.y)) +
                ((pointList[i].z - m_center.z) * (pointList[i].z - m_center.z));

		   if(dist > maxDistance)
            maxDistance = dist;
      }

   m_radius = sqrt(maxDistance);
}

//判断点是否在边界球内
bool MyBoundingSphere::isPointInside(MyVector3 &v)
{
   MyVector3 intersect = m_center - v;
	
   if(sqrt(intersect.x * intersect.x + intersect.y * intersect.y +
           intersect.z * intersect.z) < m_radius)
      return true;

   return false;
}

//判断是否与射线相交
bool MyBoundingSphere::Intersect(MyRay ray, float *dist)
{
   MyVector3 RayToSphereDir;

   float RayToSphereLength = 0.0f;
   float IntersectPoint = 0.0f;
   float SquaredPoint = 0.0f;

   RayToSphereDir = m_center - ray.m_origin;

   RayToSphereLength = RayToSphereDir.DotProduct3(RayToSphereDir);

   IntersectPoint = RayToSphereDir.DotProduct3(ray.m_direction);

   if(IntersectPoint < 0 ) return false;

   SquaredPoint = (m_radius * m_radius) - RayToSphereLength +
                  (IntersectPoint * IntersectPoint);

   if(SquaredPoint < 0) return false;

   if(dist) *dist = IntersectPoint - (float)sqrt(SquaredPoint);

   return true;
}

//判断是否与射线相交
bool MyBoundingSphere::Intersect(MyRay ray, float length, float *dist)
{
   MyVector3 RayToSphereDir;

   float RayToSphereLength = 0.0f;
   float IntersectPoint = 0.0f;
   float SquaredPoint = 0.0f;

   RayToSphereDir = m_center - ray.m_origin;

   RayToSphereLength = RayToSphereDir.DotProduct3(RayToSphereDir);

   IntersectPoint = RayToSphereDir.DotProduct3(ray.m_direction);

   if(IntersectPoint < 0 ) return false;

   SquaredPoint = (m_radius * m_radius) - RayToSphereLength +
                  (IntersectPoint * IntersectPoint);

   if(SquaredPoint < 0) return false;

   float d = IntersectPoint - (float)sqrt(SquaredPoint);

   if(d > length) return false;

   if(dist) *dist = d;

   return true;
}

//判断射线是否在边界框内
bool MyBoundingSphere::isRayInside(MyRay &ray, float length)
{
   MyVector3 endPos = ray.m_origin + (ray.m_direction * length);
   return (isPointInside(ray.m_origin) && isPointInside(endPos));
}

//判断边界框是否碰撞
bool BoxToBoxIntersect(MyBoundingBox &bb1, MyBoundingBox &bb2)
{
   if((bb1.m_min.x > bb2.m_max.x) || (bb2.m_min.x > bb1.m_max.x))
      return false;
   if((bb1.m_min.y > bb2.m_max.y) || (bb2.m_min.y > bb1.m_max.y))
      return false;
   if((bb1.m_min.z > bb2.m_max.z) || (bb2.m_min.z > bb1.m_max.z))
      return false;

   return true;
}

//判断边界球是否碰撞
bool SphereToSphereIntersect(MyBoundingSphere &bs1, MyBoundingSphere &bs2)
{
   MyVector3 intersect = bs1.m_center - bs2.m_center;
	
   if(sqrt(intersect.x * intersect.x + intersect.y * intersect.y +
           intersect.z * intersect.z) < bs1.m_radius + bs2.m_radius)
      return true;

   return false;
}