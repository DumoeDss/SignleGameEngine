#pragma once

#include "MathLibrary.h"
//�߽���
class MyBoundingBase
{
public:
	MyBoundingBase(){}
	virtual ~MyBoundingBase(){}
	//�����߽���
	virtual void CreateFromPoints(MyVector3 *pointList, int numPoints) = 0;
	//�жϵ��Ƿ���ײ
	virtual bool isPointInside(MyVector3 &v) = 0;
	//�ж������Ƿ���ײ
	virtual bool Intersect(MyRay ray, float *dist) = 0;
	virtual bool Intersect(MyRay ray, float length, float *dist) = 0;
	virtual bool isRayInside(MyRay &ray, float length) = 0;
	//��ȡƽ��
	virtual void GetPlanes(MyPlane *planes) = 0;
};
//�߽��
class MyBoundingBox : public MyBoundingBase
{
public:
	MyBoundingBox(){}
	~MyBoundingBox(){}
	void CreateFromPoints(MyVector3 *pointList, int numPoints);
	bool isPointInside(MyVector3 &v);
	bool Intersect(MyRay ray, float *dist);
	bool Intersect(MyRay ray, float length, float *dist);
	void GetPlanes(MyPlane *planes);
	bool isRayInside(MyRay &ray, float length);

	MyVector3 m_min, m_max;
};
//�߽���
class MyBoundingSphere :  public MyBoundingBase
{
public:
	MyBoundingSphere():m_radius(0){}
	~MyBoundingSphere(){}

	void CreateFromPoints(MyVector3 *pointList, int numPoints);
	bool isPointInside(MyVector3 &v);
	bool Intersect(MyRay ray, float *dist);
	bool Intersect(MyRay ray, float length, float *dist);
	void GetPlanes(MyPlane *planes){};
	bool isRayInside(MyRay &ray, float length);

	MyVector3 m_center;
	float m_radius;
};
//�жϱ߽����Ƿ���ײ
bool BoxToBoxIntersect(MyBoundingBox &bb1, MyBoundingBox &bb2);
bool SphereToSphereIntersect(MyBoundingSphere &bs1, MyBoundingSphere &bs2);
