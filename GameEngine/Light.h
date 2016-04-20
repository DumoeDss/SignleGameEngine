#pragma once
// ��Դ
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

	int lightType;	//����
	float posX, posY, posZ;	//λ��
	float dirX, dirY, dirZ;	//����
	float ambientR, ambientG, ambientB, ambientA;	//������
	float diffuseR, diffuseG, diffuseB, diffuseA;	//�����
	float specularR, specularG, specularB, specularA;	//�����
	float range;	//���--��Զ����
	float falloff;	//˥�����۹�ƣ�
	float attenuation0;	//˥��
	float attenuation1;
	float attenuation2;
	float lightTheta;	//�۹���ڲ�׶��Բ׶��
	float lightPhi;	//�۹���ⲿ׶��Բ׶��
};
