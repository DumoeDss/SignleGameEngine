#pragma once

#include"Vector.h"

#define STRIAGHT_PATH 0
#define CURVE_PATH 1

//文件路径，用于载入模型
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


      int m_type;          

      MyVector3 m_startPos;
      MyVector3 m_control1; 
      MyVector3 m_control2; 
      MyVector3 m_endPos; 
      float m_start;    
      float m_total;     

      MyPath *m_next; 
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
