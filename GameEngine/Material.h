#pragma once
// ²ÄÖÊ
struct myMaterial
{
	myMaterial():
		ambientR(1), ambientG(1), ambientB(1), ambientA(1),
		diffuseR(1), diffuseG(1), diffuseB(1), diffuseA(1),
		specularR(0), specularG(0), specularB(0), specularA(0),
		emissiveR(0), emissiveG(0), emissiveB(0), emissiveA(0),
		power(0)
	{

	}

	float ambientR, ambientG, ambientB, ambientA;	
	float diffuseR, diffuseG, diffuseB, diffuseA;
	float specularR, specularG, specularB, specularA;
	float emissiveR, emissiveG, emissiveB, emissiveA;
	float power;
};
