#include"Frustum.h"


void MyFrustum::CalculateFrustum(float *mv, float *proj)
{
   if(mv == 0 || proj == 0)
      return;

   float clip[16] = {0};

   clip[0] = mv[0] * proj[0] + mv[1] * proj[4] + mv[2] * proj[8]  + mv[3] * proj[12];
	clip[1] = mv[0] * proj[1] + mv[1] * proj[5] + mv[2] * proj[9]  + mv[3] * proj[13];
	clip[2] = mv[0] * proj[2] + mv[1] * proj[6] + mv[2] * proj[10] + mv[3] * proj[14];
	clip[3] = mv[0] * proj[3] + mv[1] * proj[7] + mv[2] * proj[11] + mv[3] * proj[15];

	clip[4] = mv[4] * proj[0] + mv[5] * proj[4] + mv[6] * proj[8]  + mv[7] * proj[12];
	clip[5] = mv[4] * proj[1] + mv[5] * proj[5] + mv[6] * proj[9]  + mv[7] * proj[13];
	clip[6] = mv[4] * proj[2] + mv[5] * proj[6] + mv[6] * proj[10] + mv[7] * proj[14];
	clip[7] = mv[4] * proj[3] + mv[5] * proj[7] + mv[6] * proj[11] + mv[7] * proj[15];

	clip[8]  = mv[8] * proj[0] + mv[9] * proj[4] + mv[10] * proj[8]  + mv[11] * proj[12];
	clip[9]  = mv[8] * proj[1] + mv[9] * proj[5] + mv[10] * proj[9]  + mv[11] * proj[13];
	clip[10] = mv[8] * proj[2] + mv[9] * proj[6] + mv[10] * proj[10] + mv[11] * proj[14];
	clip[11] = mv[8] * proj[3] + mv[9] * proj[7] + mv[10] * proj[11] + mv[11] * proj[15];

	clip[12] = mv[12] * proj[0] + mv[13] * proj[4] + mv[14] * proj[8]  + mv[15] * proj[12];
	clip[13] = mv[12] * proj[1] + mv[13] * proj[5] + mv[14] * proj[9]  + mv[15] * proj[13];
	clip[14] = mv[12] * proj[2] + mv[13] * proj[6] + mv[14] * proj[10] + mv[15] * proj[14];
	clip[15] = mv[12] * proj[3] + mv[13] * proj[7] + mv[14] * proj[11] + mv[15] * proj[15];
	
    Frustum[0].a = clip[3]  - clip[0];
	Frustum[0].b = clip[7]  - clip[4];
	Frustum[0].c = clip[11] - clip[8];
	Frustum[0].d = clip[15] - clip[12];

	Frustum[1].a = clip[3]  + clip[0];
	Frustum[1].b = clip[7]  + clip[4];
	Frustum[1].c = clip[11] + clip[8];
	Frustum[1].d = clip[15] + clip[12];

	Frustum[2].a = clip[3]  + clip[1];
	Frustum[2].b = clip[7]  + clip[5];
	Frustum[2].c = clip[11] + clip[9];
	Frustum[2].d = clip[15] + clip[13];

	Frustum[3].a = clip[3]  - clip[1];
	Frustum[3].b = clip[7]  - clip[5];
	Frustum[3].c = clip[11] - clip[9];
	Frustum[3].d = clip[15] - clip[13];

	Frustum[4].a = clip[3]  - clip[2];
	Frustum[4].b = clip[7]  - clip[6];
	Frustum[4].c = clip[11] - clip[10];
	Frustum[4].d = clip[15] - clip[14];

	Frustum[5].a = clip[3]  + clip[2];
	Frustum[5].b = clip[7]  + clip[6];
	Frustum[5].c = clip[11] + clip[10];
	Frustum[5].d = clip[15] + clip[14];

   NormalizeFrustum();
}


void MyFrustum::NormalizeFrustum()
{
   float magnitude = 0.0f;

   for(int i = 0; i < MAX_SIDES; i++)
      {
          magnitude = (float)sqrt(Frustum[i].a * Frustum[i].a + 
			   		               Frustum[i].b * Frustum[i].b + 
						               Frustum[i].c * Frustum[i].c);
          magnitude = 1 / magnitude;

	      Frustum[i].a *= magnitude;
	      Frustum[i].b *= magnitude;
	      Frustum[i].c *= magnitude;
	      Frustum[i].d *= magnitude;
      }
}


bool MyFrustum::isPointVisiable(float x, float y, float z)
{
   for(int i = 0; i < MAX_SIDES; i++)
      {
         if(Frustum[i].GetDistance(x, y, z) < 0)
            return false;
      }

   return true;
}


bool MyFrustum::isSphereVisiable(float x, float y, float z, float radius)
{
   float distance = 0;

   for(int i = 0; i < MAX_SIDES; i++)
      {
         distance = Frustum[i].GetDistance(x, y, z);

         if(distance < -radius)
            return false;
      }

   return true;
}


bool MyFrustum::isBoxVisiable(float x, float y, float z, float size)
{
   float minX, maxX;
   float minY, maxY;
   float minZ, maxZ;

   minX = x - size; maxX = x + size;
   minY = y - size; maxY = y + size;
   minZ = z - size; maxZ = z + size;

   for(int i = 0; i < MAX_SIDES; i++)
      {
         if(Frustum[i].GetDistance(minX, minY, minZ) > 0) continue;
         if(Frustum[i].GetDistance(maxX, minY, minZ) > 0) continue;   
         if(Frustum[i].GetDistance(minX, maxY, minZ) > 0) continue;   
         if(Frustum[i].GetDistance(maxX, maxY, minZ) > 0) continue;   
         if(Frustum[i].GetDistance(minX, minY, maxZ) > 0) continue;   
         if(Frustum[i].GetDistance(maxX, minY, maxZ) > 0) continue;   
         if(Frustum[i].GetDistance(minX, maxY, maxZ) > 0) continue;   
         if(Frustum[i].GetDistance(maxX, maxY, maxZ) > 0) continue;
         
         return false;
      }

   return true;
}