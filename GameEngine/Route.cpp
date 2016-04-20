#include"Route.h"
#include<windows.h>
#include<mmsystem.h>


MyPath::MyPath() : m_type(0), m_start(0), m_total(0), m_next(0)
{
}


MyPath::MyPath(int Type, MyVector3 start, MyVector3 cnt1, MyVector3 cnt2, MyVector3 end)
{
   m_start = 0;
   m_total = 0;
   m_next = 0;

   SetPath(Type, start, cnt1, cnt2, end);
}


MyPath::~MyPath()
{
   Shutdown();
}


void MyPath::SetPath(int Type, MyVector3 start, MyVector3 cnt1, MyVector3 cnt2, MyVector3 end)
{
   m_type = Type;
   m_startPos = start;
   m_control1 = cnt1;
   m_control2 = cnt2;
   m_endPos = end;
}


void MyPath::Shutdown()
{
   if(m_next)
      {
         m_next->Shutdown();
         delete m_next;
         m_next = 0;
      }
}


MyRoute::MyRoute()
{
   m_path = 0;
   m_startTime = 0;
}


MyRoute::~MyRoute()
{
   Shutdown();
}


bool MyRoute::AddPath(int Type, MyVector3 start, MyVector3 cnt1, MyVector3 cnt2, MyVector3 end)
{
   MyPath *ptr;

   if(m_path == 0)
      {
         m_path = new MyPath(Type, start, cnt1, cnt2, end);

         if(m_path == 0) return false;

         m_path->m_start = 0;

         if(Type == STRIAGHT_PATH)
            {
               m_path->m_total = MyVector3(start - end).GetLength();
            }
         else if(Type == CURVE_PATH)
            {
               float Length01 = MyVector3(cnt1 - start).GetLength();
               float Length12 = MyVector3(cnt2 - cnt1).GetLength();
               float Length23 = MyVector3(end - cnt2).GetLength();
               float Length03 = MyVector3(end - start).GetLength();
               m_path->m_total = (Length01 + Length12 + Length23) * 0.5f + Length03 * 0.5f;
            }
         else
            return false;
      }
   else
      {
         ptr = m_path;

         while(ptr->m_next != 0)
            {
               ptr = ptr->m_next;
            }

         ptr->m_next = new MyPath(Type, start, cnt1, cnt2, end);

         if(ptr->m_next == 0) return false;

         ptr->m_next->m_start = ptr->m_total + ptr->m_start;;

         if(Type == STRIAGHT_PATH)
            {
               ptr->m_next->m_total = MyVector3(start - end).GetLength();
            }
         else if(Type == CURVE_PATH)
            {
               float Length01 = MyVector3(cnt1 - start).GetLength();
               float Length12 = MyVector3(cnt2 - cnt1).GetLength();
               float Length23 = MyVector3(end - cnt2).GetLength();
               float Length03 = MyVector3(end - start).GetLength();
               ptr->m_next->m_total = (Length01 + Length12 + Length23) * 0.5f + Length03 * 0.5f;
            }
         else
            return false;
      }

   return true;
}


void MyRoute::GetPosition(float time, MyVector3 &objPos)
{
   MyPath *ptr = m_path;

   if(m_path == 0) return;

   if(m_startTime == 0) m_startTime = (float)timeGetTime();

   do
      {
         if(time >= ptr->m_start && time < ptr->m_start + ptr->m_total)
            {
               time -= ptr->m_start;

               float Scalar = time / ptr->m_total;

               if(ptr->m_type == 0)
                  {
                     objPos = (CalcStriaghtPath(ptr->m_startPos, ptr->m_endPos, Scalar));
                  }
               else
                  objPos = (CalcBezierCurvePos(ptr->m_startPos, ptr->m_control1, ptr->m_control2,
                                               ptr->m_endPos, Scalar));

               break;
            }
         else
            {
               if(ptr->m_next == 0) m_startTime = (float)timeGetTime();
            }

         ptr = ptr->m_next;
      }while(ptr != 0);

   return;
}


MyVector3 MyRoute::CalcBezierCurvePos(MyVector3 start, MyVector3 c1, MyVector3 c2, MyVector3 end, float Scalar)
{
   MyVector3 out;

   out = start * (1.0f - Scalar) * (1.0f - Scalar) * (1.0f - Scalar) +
         c1 * 3.0f * Scalar * (1.0f - Scalar) * (1.0f - Scalar) +
         c2 * 3.0f * Scalar * Scalar * (1.0f - Scalar) +
         end * Scalar * Scalar * Scalar;

   return out;
}


MyVector3 MyRoute::CalcStriaghtPath(MyVector3 start, MyVector3 end, float Scalar)
{
   MyVector3 out = (end - start) * Scalar + start;

   return out;
}


void MyRoute::Shutdown()
{
   if(m_path)
      {
         m_path->Shutdown();
         delete m_path;
         m_path = 0;
      }
}