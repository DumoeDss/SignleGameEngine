#pragma once
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"Token.h"

struct MyObjModel
{
	float *vertices;
	float *normals;
	float *texCoords;
	int numFaces;
};

MyObjModel *LoadOBJModel(char *fileName);
void FreeOBJModel(MyObjModel *model);
