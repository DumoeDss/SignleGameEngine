#include "ObjModel.h"
MyObjModel *LoadOBJModel(char *fileName)
{
	FILE *file;
	char *data = NULL;
	MyToken lexer, tempLex;
	char tempLine[512];
	char token[512];

	file = fopen(fileName, "r");
	if (!file) return NULL;

	fseek(file, 0, SEEK_END);
	int length = ftell(file);
	fseek(file, 0, SEEK_SET);

	data = new char[(length + 1) * sizeof(char)];
	if (!data) return NULL;
	fread(data, length, 1, file);
	data[length] = '\0';

	fclose(file);

	lexer.SetTokenStream(data);

	delete[] data; data = NULL;

	bool validFile = false;

	while (lexer.GetNextToken(token))
	{
		if (strcmp(token, "Wavefront") == 0)
		{
			validFile = true;
			break;
		}
	}

	if (!validFile) return NULL;

	lexer.Reset();

	int totalVertices = 0, totalNormals = 0,
		totalTexC = 0, totalFaces = 0;

	while (lexer.MoveToNextLine(tempLine))
	{
		tempLex.SetTokenStream(tempLine);

		lexer.GetNextToken(NULL);

		if (!tempLex.GetNextToken(token)) continue;

		if (strcmp(token, "v") == 0) totalVertices++;
		else if (strcmp(token, "vn") == 0) totalNormals++;
		else if (strcmp(token, "vt") == 0) totalTexC++;
		else if (strcmp(token, "f") == 0) totalFaces++;

		token[0] = '\0';
	}

	float *verts = new float[totalVertices * 3];
	float *norms = new float[totalNormals * 3];
	float *texC = new float[totalTexC * 2];
	int *faces = new int[totalFaces * 9];
	int vIndex = 0, nIndex = 0, tIndex = 0, fIndex = 0, index = 0;

	lexer.Reset();

	while (lexer.MoveToNextLine(tempLine))
	{
		tempLex.SetTokenStream(tempLine);
		lexer.GetNextToken(NULL);
		if (!tempLex.GetNextToken(token)) continue;

		if (strcmp(token, "v") == 0)
		{
			tempLex.GetNextToken(token);
			verts[vIndex] = (float)atof(token);
			vIndex++;

			tempLex.GetNextToken(token);
			verts[vIndex] = (float)atof(token);
			vIndex++;

			tempLex.GetNextToken(token);
			verts[vIndex] = (float)atof(token);
			vIndex++;
		}
		else if (strcmp(token, "vn") == 0)
		{
			tempLex.GetNextToken(token);
			norms[nIndex] = (float)atof(token);
			nIndex++;

			tempLex.GetNextToken(token);
			norms[nIndex] = (float)atof(token);
			nIndex++;

			tempLex.GetNextToken(token);
			norms[nIndex] = (float)atof(token);
			nIndex++;
		}
		else if (strcmp(token, "vt") == 0)
		{
			tempLex.GetNextToken(token);
			texC[tIndex] = (float)atof(token);
			tIndex++;

			tempLex.GetNextToken(token);
			texC[tIndex] = (float)atof(token);
			tIndex++;
		}
		else if (strcmp(token, "f") == 0)
		{
			for (int i = 0; i < 3; i++)
			{
				tempLex.GetNextToken(token);
				int len = strlen(token);

				for (int s = 0; s < len + 1; s++)
				{
					char buff[64];

					if (token[s] != '/' && s < len)
					{
						buff[index] = token[s];
						index++;
					}
					else
					{
						buff[index] = '\0';
						faces[fIndex] = (int)atoi(buff);
						fIndex++;
						index = 0;
					}
				}
			}
		}

		token[0] = '\0';
	}

	lexer.Shutdown();

	MyObjModel *model = new MyObjModel;
	if (!model) return NULL;
	memset(model, 0, sizeof(MyObjModel));

	model->numFaces = totalFaces;

	vIndex = 0, nIndex = 0, tIndex = 0, fIndex = 0, index = 0;

	model->vertices = new float[totalFaces * 3 * 3];
	if (totalNormals) model->normals = new float[totalFaces * 3 * 3];
	if (totalTexC) model->texCoords = new float[totalFaces * 3 * 2];

	for (int f = 0; f < totalFaces * 9; f += 3)
	{
		model->vertices[vIndex + 0] = verts[(faces[f + 0] - 1) * 3 + 0];
		model->vertices[vIndex + 1] = verts[(faces[f + 0] - 1) * 3 + 1];
		model->vertices[vIndex + 2] = verts[(faces[f + 0] - 1) * 3 + 2];
		vIndex += 3;

		if (model->texCoords)
		{
			model->texCoords[tIndex + 0] = texC[(faces[f + 1] - 1) * 2 + 0];
			model->texCoords[tIndex + 1] = texC[(faces[f + 1] - 1) * 2 + 1];
			tIndex += 2;
		}

		if (model->normals)
		{
			model->normals[nIndex + 0] = norms[(faces[f + 2] - 1) * 3 + 0];
			model->normals[nIndex + 1] = norms[(faces[f + 2] - 1) * 3 + 1];
			model->normals[nIndex + 2] = norms[(faces[f + 2] - 1) * 3 + 2];
			nIndex += 3;
		}
	}

	delete[] verts;
	delete[] norms;
	delete[] texC;
	delete[] faces;

	return model;
}


void FreeOBJModel(MyObjModel *model)
{
	if (!model) return;

	if (model->vertices) delete[] model->vertices;
	model->vertices = NULL;
	if (model->normals) delete[] model->normals;
	model->normals = NULL;
	if (model->texCoords) delete[] model->texCoords;
	model->texCoords = NULL;

	delete model;
	model = NULL;
}