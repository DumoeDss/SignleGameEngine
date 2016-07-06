#include "Terrain.h"
#include <fstream>
#include <cmath>

const DWORD MyTerrain::TerrainVertex::FVF = D3DFVF_XYZ | D3DFVF_TEX1;

MyTerrain::MyTerrain(IDirect3DDevice9* device,
	std::string heightmapFileName,
	int numVertsPerRow,
	int numVertsPerCol,
	int cellSpacing,
	float heightScale)
{
	m_device = device;
	m_numVertsPerRow = numVertsPerRow;
	m_numVertsPerCol = numVertsPerCol;
	m_cellSpacing = cellSpacing;
	//单元格数=顶点数-1
	m_numCellsPerRow = m_numVertsPerRow - 1;
	m_numCellsPerCol = m_numVertsPerCol - 1;
	//宽度=单元格数*单元格距离
	m_width = m_numCellsPerRow * m_cellSpacing;
	m_depth = m_numCellsPerCol * m_cellSpacing;
	//顶点总数=每行顶点*每列顶点
	m_numVertices = m_numVertsPerRow * m_numVertsPerCol;
	//三角形总数=每行单元格数*每列单元格数*2
	m_numTriangles = m_numCellsPerRow * m_numCellsPerCol * 2;
	//高度缩放系数
	m_heightScale = heightScale;
	//读取高度图
	if (!readRawFile(heightmapFileName))
	{
		::MessageBox(0, "readRawFile - FAILED", 0, 0);
		::PostQuitMessage(0);
	}
	//缩放高度
	for (int i = 0; i != m_heightmap.size(); ++i)
		m_heightmap[i] *= heightScale;

	//计算顶点缓存
	if (!computeVertices())
	{
		::MessageBox(0, "computeVertices - FAILED", 0, 0);
		::PostQuitMessage(0);
	}

	//计算索引缓存
	if (!computeIndices())
	{
		::MessageBox(0, "computeIndices - FAILED", 0, 0);
		::PostQuitMessage(0);
	}
}

MyTerrain::~MyTerrain()
{
	SAFE_RELEASE(m_vertexBuffer);
	SAFE_RELEASE(m_indexBuffer);
	SAFE_RELEASE(m_texture);
}
//从vector中获取高度
int MyTerrain::getHeightmapEntry(int row, int col)
{
	return m_heightmap[row * m_numVertsPerRow + col];
}
//设置高度信息
void MyTerrain::setHeightmapEntry(int row, int col, int value)
{
	m_heightmap[row * m_numVertsPerRow + col] = value;
}
//计算顶点缓存
bool MyTerrain::computeVertices()
{
	HRESULT hr = 0;
	//创建顶点缓存
	hr = m_device->CreateVertexBuffer(
		m_numVertices * sizeof(TerrainVertex),
		D3DUSAGE_WRITEONLY,
		TerrainVertex::FVF,
		D3DPOOL_MANAGED,
		&m_vertexBuffer,
		0);

	if (FAILED(hr))
		return false;

	int startX = -m_width / 2;
	int startZ = m_depth / 2;

	int endX = m_width / 2;
	int endZ = -m_depth / 2;

	//uv值
	float uCoordIncrementSize = 1.0f / (float)m_numCellsPerRow;
	float vCoordIncrementSize = 1.0f / (float)m_numCellsPerCol;

	TerrainVertex* v = 0;
	m_vertexBuffer->Lock(0, 0, (void**)&v, 0);

	int i = 0;
	for (int z = startZ; z >= endZ; z -= m_cellSpacing)
	{
		int j = 0;
		for (int x = startX; x <= endX; x += m_cellSpacing)
		{
			//索引
			int index = i * m_numVertsPerRow + j;

			v[index] = TerrainVertex(
				(float)x,
				(float)m_heightmap[index],
				(float)z,
				(float)j * uCoordIncrementSize,
				(float)i * vCoordIncrementSize);

			j++;
		}
		i++;
	}

	m_vertexBuffer->Unlock();

	return true;
}
//计算索引缓存
bool MyTerrain::computeIndices()
{
	HRESULT hr = 0;
	//创建索引缓存
	hr = m_device->CreateIndexBuffer(
		m_numTriangles * 3 * sizeof(DWORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX32,
		D3DPOOL_MANAGED,
		&m_indexBuffer,
		0);

	if (FAILED(hr))
		return false;

	DWORD* indices = 0;
	m_indexBuffer->Lock(0, 0, (void**)&indices, 0);

	int baseIndex = 0;

	for (int i = 0; i < m_numCellsPerCol; i++)
	{
		for (int j = 0; j < m_numCellsPerRow; j++)
		{
			//每个单元格有两个三角形，六个顶点
			indices[baseIndex] = i   * m_numVertsPerRow + j;
			indices[baseIndex + 1] = i   * m_numVertsPerRow + j + 1;
			indices[baseIndex + 2] = (i + 1) * m_numVertsPerRow + j;

			indices[baseIndex + 3] = (i + 1) * m_numVertsPerRow + j;
			indices[baseIndex + 4] = i   * m_numVertsPerRow + j + 1;
			indices[baseIndex + 5] = (i + 1) * m_numVertsPerRow + j + 1;

			baseIndex += 6;
		}
	}

	m_indexBuffer->Unlock();

	return true;
}
//加载纹理贴图
bool MyTerrain::loadTexture(std::string fileName)
{
	HRESULT hr = 0;

	hr = D3DXCreateTextureFromFile(
		m_device,
		fileName.c_str(),
		&m_texture);

	if (FAILED(hr))
		return false;

	return true;
}
//计算纹理
bool MyTerrain::genTexture(D3DXVECTOR3* directionToLight)
{
	HRESULT hr = 0;

	int texWidth = m_numCellsPerRow;
	int texHeight = m_numCellsPerCol;

	hr = D3DXCreateTexture(
		m_device,
		texWidth, texHeight,
		0,
		0,
		D3DFMT_X8R8G8B8,
		D3DPOOL_MANAGED, &m_texture);

	if (FAILED(hr))
		return false;

	D3DSURFACE_DESC textureDesc;
	m_texture->GetLevelDesc(0, &textureDesc);

	if (textureDesc.Format != D3DFMT_X8R8G8B8)
		return false;

	D3DLOCKED_RECT lockedRect;
	m_texture->LockRect(0, &lockedRect, 0, 0);

	DWORD* imageData = (DWORD*)lockedRect.pBits;
	for (int i = 0; i < texHeight; i++)
	{
		for (int j = 0; j < texWidth; j++)
		{
			D3DXCOLOR c;

			float height = (float)getHeightmapEntry(i, j) / m_heightScale;

			if ((height) < 42.5f) 		 c = BEACH_SAND;
			else if ((height) < 85.0f)	 c = LIGHT_YELLOW_GREEN;
			else if ((height) < 127.5f) c = PUREGREEN;
			else if ((height) < 170.0f) c = DARK_YELLOW_GREEN;
			else if ((height) < 212.5f) c = DARKBROWN;
			else	                     c = WHITE;

			imageData[i * lockedRect.Pitch / 4 + j] = (D3DCOLOR)c;
		}
	}

	m_texture->UnlockRect(0);

	if (!lightTerrain(directionToLight))
	{
		::MessageBox(0, "lightTerrain() - FAILED", 0, 0);
		return false;
	}

	hr = D3DXFilterTexture(
		m_texture,
		0,
		0,
		D3DX_DEFAULT);

	if (FAILED(hr))
	{
		::MessageBox(0, "D3DXFilterTexture() - FAILED", 0, 0);
		return false;
	}

	return true;
}
//光照
bool MyTerrain::lightTerrain(D3DXVECTOR3* directionToLight)
{
	HRESULT hr = 0;

	D3DSURFACE_DESC textureDesc;
	m_texture->GetLevelDesc(0, &textureDesc);

	if (textureDesc.Format != D3DFMT_X8R8G8B8)
		return false;

	D3DLOCKED_RECT lockedRect;
	m_texture->LockRect(
		0,
		&lockedRect,
		0,
		0);

	DWORD* imageData = (DWORD*)lockedRect.pBits;
	for (int i = 0; i < textureDesc.Height; i++)
	{
		for (int j = 0; j < textureDesc.Width; j++)
		{
			int index = i * lockedRect.Pitch / 4 + j;

			D3DXCOLOR c(imageData[index]);

			c *= computeShade(i, j, directionToLight);;
			imageData[index] = (D3DCOLOR)c;
		}
	}

	m_texture->UnlockRect(0);

	return true;
}
//计算阴影
float MyTerrain::computeShade(int cellRow, int cellCol, D3DXVECTOR3* directionToLight)
{
	float heightA = getHeightmapEntry(cellRow, cellCol);
	float heightB = getHeightmapEntry(cellRow, cellCol + 1);
	float heightC = getHeightmapEntry(cellRow + 1, cellCol);

	D3DXVECTOR3 u(m_cellSpacing, heightB - heightA, 0.0f);
	D3DXVECTOR3 v(0.0f, heightC - heightA, -m_cellSpacing);

	D3DXVECTOR3 n;
	D3DXVec3Cross(&n, &u, &v);
	D3DXVec3Normalize(&n, &n);

	float cosine = D3DXVec3Dot(&n, directionToLight);

	if (cosine < 0.0f)
		cosine = 0.0f;

	return cosine;
}
//读取高度图
bool MyTerrain::readRawFile(std::string fileName)
{
	//用于存储高度数据字节
	std::vector<BYTE> temp(m_numVertices);
	std::ifstream ifs(fileName.c_str(), std::ios_base::binary);
	if (!ifs)
		return false;
	ifs.read((char*)&temp[0], temp.size());
	ifs.close();
	//复制数据到m_heightmap中
	m_heightmap.resize(m_numVertices);
	for (int i = 0; i != temp.size(); ++i)
		m_heightmap[i] = temp[i];
	return true;
}
//获取某一点高度信息
float MyTerrain::getHeight(float x, float z)
{
	x = ((float)m_width / 2.0f) + x;
	z = ((float)m_depth / 2.0f) - z;

	x /= (float)m_cellSpacing;
	z /= (float)m_cellSpacing;

	float col = ::floorf(x);
	float row = ::floorf(z);

	float A = getHeightmapEntry(row, col);
	float B = getHeightmapEntry(row, col + 1);
	float C = getHeightmapEntry(row + 1, col);
	float D = getHeightmapEntry(row + 1, col + 1);

	float dx = x - col;
	float dz = z - row;

	float height = 0.0f;
	if (dz < 1.0f - dx)
	{
		float uy = B - A;
		float vy = C - A;

		height = A + Lerp(0.0f, uy, dx) + Lerp(0.0f, vy, dz);
	}
	else
	{
		float uy = C - D;
		float vy = B - D;

		height = D + Lerp(0.0f, uy, 1.0f - dx) + Lerp(0.0f, vy, 1.0f - dz);
	}

	return height;
}
//渲染地形
bool MyTerrain::renderTerrain(D3DXMATRIX* world, bool drawTris)
{
	HRESULT hr = 0;

	if (m_device)
	{
		m_device->SetTransform(D3DTS_WORLD, world);
		m_device->SetStreamSource(0, m_vertexBuffer, 0, sizeof(TerrainVertex));
		m_device->SetFVF(TerrainVertex::FVF);
		m_device->SetIndices(m_indexBuffer);
		m_device->SetTexture(0, m_texture);
		m_device->SetRenderState(D3DRS_LIGHTING, false);
		hr = m_device->DrawIndexedPrimitive(
			D3DPT_TRIANGLELIST,
			0,
			0,
			m_numVertices,
			0,
			m_numTriangles);

		m_device->SetRenderState(D3DRS_LIGHTING, true);

		if (drawTris)
		{
			m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			hr = m_device->DrawIndexedPrimitive(
				D3DPT_TRIANGLELIST,
				0,
				0,
				m_numVertices,
				0,
				m_numTriangles);

			m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		}

		if (FAILED(hr))
			return false;
	}

	return true;
}

