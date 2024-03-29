#ifndef _cVAOManager_HG_
#define _cVAOManager_HG_

#include "GLCommon.h"

// Will load the models and place them 
// into the vertex and index buffers to be drawn

#include <string>
#include <map>
#include "cMesh.h"				// File as loaded from the file


// The vertex structure 
//	that's ON THE GPU (eventually) 
// So dictated from THE SHADER
//////struct sVertex
//////{
//////	float x, y, z, w;			// w coordinate	
//////	float r, g, b, a;	// a = alpha (transparency)
//////	float nx, ny, nz, nw;
//////	float u0, v0, u1, v1;
//////};

#include "sVertex_xyz_rgba_n_uv2_bt_4Bones.h"
//static const unsigned int NUMBEROFBONES = 4;
//struct sVertex_xyz_rgba_n_uv2_bt_4Bones
//{
//	sVertex_xyz_rgba_n_uv2_bt_4Bones();
//
//	float x, y, z, w;			// w coordinate	
//	float r, g, b, a;	// a = alpha (transparency)
//	float nx, ny, nz, nw;
//	float u0, v0, u1, v1;
//
//	// For bump mapping
//	float tx, ty, tz, tw;	// tangent				// 
//	float bx, by, bz, bw;	// bi-normal			// 
//
//	// For skinned mesh
//	// For the 4 bone skinned mesh information
//	float boneID[NUMBEROFBONES]; 		// New		// 
//	float boneWeights[NUMBEROFBONES];	// New		// 
//};


#include "sModelDrawInfo.h"
#include "sModelDrawInfo.h"

//struct sModelDrawInfo
//{
//	sModelDrawInfo(); 
//
//	std::string meshName;
//
//	unsigned int VAO_ID;
//
//	unsigned int VertexBufferID;
//	unsigned int VertexBuffer_Start_Index;
//	unsigned int numberOfVertices;
//
//	unsigned int IndexBufferID;
//	unsigned int IndexBuffer_Start_Index;
//	unsigned int numberOfIndices;
//	unsigned int numberOfTriangles;
//
//	// The "local" (i.e. "CPU side" temporary array)
////	sVertex* pVertices;	//  = 0;
//	sVertex_xyz_rgba_n_uv2_bt_4Bones * pVertices;
//	// The index buffer (CPU side)
//	unsigned int* pIndices;		
//
//	// You could store the max and min values of the 
//	//  vertices here (determined when you load them):
//	float maxX, maxY, maxZ;
//	float minX, minY, minZ;
//
////	scale = 5.0/maxExtent;		-> 5x5x5
//	float maxExtent;
//	float extentX, extentY, extentZ;
//
//	void CalcExtents(void);
//};


class cVAOManager
{
public:

	// Takes a cMesh object and copies it into the GPU (as a VOA)
	bool LoadModelIntoVAO(std::string fileName,
		cMesh& theMesh,				// NEW
		sModelDrawInfo& drawInfo,
		unsigned int shaderProgramID);

	// Temp thing to see if the skinned mesh loader loaded the draw info OK
	bool LoadModelDrawInfoIntoVAO(sModelDrawInfo& drawInfo,
		unsigned int shaderProgramID);

	// We don't want to return an int, likely
	bool FindDrawInfoByModelName(std::string filename,
		sModelDrawInfo& drawInfo);

	std::string getLastError(bool bAndClear = true);

private:

	std::map< std::string /*model name*/,
		sModelDrawInfo /* info needed to draw*/ >
		m_map_ModelName_to_VAOID;

};

#endif	// _cVAOManager_HG_
