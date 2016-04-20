#pragma once
// 光源
struct myLight
{
	myLight():lightType(0),
		posX(0), posY(0), posZ(0),
		dirX(0), dirY(0), dirZ(0),
		ambientR(1), ambientG(1), ambientB(1), ambientA(1),
		diffuseR(1), diffuseG(1), diffuseB(1), diffuseA(1),
		specularR(0), specularG(0), specularB(0), specularA(0),
		range(0),
		falloff(0),
		attenuation0(0), attenuation1(0), attenuation2(0),
		lightTheta(0),
		lightPhi(0)
	{

	}

	int lightType;	//类型
	float posX, posY, posZ;	//位置
	float dirX, dirY, dirZ;	//方向
	float ambientR, ambientG, ambientB, ambientA;	//环境光
	float diffuseR, diffuseG, diffuseB, diffuseA;	//漫射光
	float specularR, specularG, specularB, specularA;	//镜面光
	float range;	//光程--最远距离
	float falloff;	//衰减（聚光灯）
	float attenuation0;	//衰减
	float attenuation1;
	float attenuation2;
	float lightTheta;	//聚光灯内部锥形圆锥角
	float lightPhi;	//聚光灯外部锥形圆锥角
};
