#pragma once

#include"Vector.h"

#define STRIAGHT_PATH 0
#define CURVE_PATH 1


class MyPath
{
   public:
      MyPath();
      MyPath(int Type, MyVector3 start, MyVector3 cnt1,
            MyVector3 cnt2, MyVector3 end);
      ~MyPath();

      void SetPath(int Type, MyVector3 start, MyVector3 cnt1,
                   MyVector3 cnt2, MyVector3 end);
      void Shutdown();


      int m_type;          // Type of path this is.

      MyVector3 m_startPos; // Start location of this path.
      MyVector3 m_control1; // Control point one (only for curve paths).
      MyVector3 m_control2; // Control point two (only for curve paths).
      MyVector3 m_endPos;   // Destination location.

      float m_start;       // Starting lenght for this path animation.
      float m_total;       // Total length distance of this animation path.

      MyPath *m_next;       // Pointer to the next path in our link list.
};


class MyRoute
{
   public:
      MyRoute();
      ~MyRoute();

      bool AddPath(int Type, MyVector3 start, MyVector3 cnt1,
                   MyVector3 cnt2, MyVector3 end);


      void GetPosition(float time, MyVector3 &objPos);

      MyVector3 CalcBezierCurvePos(MyVector3 start, MyVector3 c1,
                                  MyVector3 c2, MyVector3 end,
                                  float Scalar);
      MyVector3 CalcStriaghtPath(MyVector3 start,
                                MyVector3 end, float Scalar);
      void Shutdown();


      MyPath *m_path;
      float m_startTime;
};
