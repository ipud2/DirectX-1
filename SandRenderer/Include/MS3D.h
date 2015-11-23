// MS3D File Format (as of v1.7.0)
//
// First comes the header (MS3DHeader)
// Then the number of vertices (WORD)
// Then the actual vertices (MS3DVertex)
//
// Then the number of triangles (WORD)
// Then the actual triangles (MS3DTriangle)
//
// Then the number of groups (WORD)
// Then the actual groups (MS3DGroup)
//
// Then the number of materials (WORD)
// Then the actual materials (MS3DMaterial)
//
// Now comes the keyframer data
//
// fAnimationFPS (float)
// fCurrentTime (float)
// iTotalFrames (int)
//
// Then the number of joints (WORD)
// Then the actual joints (MS3DJoint)
//
// Now comes the sub-version (int)
//
// Then the number of group comments (uint)
// Then all the actual group comments (MS3DComment) - variable length!
//
// Then the number of material comments (uint)
// Then all the actual material comments (MS3DComment) - variable length!
//
// Then the number of joint comments (uint)
// Then all the actual joint comments (MS3DComment) - variable length!
//
// Then the number of model comments (uint) - always 0 or 1
// Then all the actual model comments (MS3DComment) - variable length!
#ifndef MS3D_h
#define MS3D_h

namespace Sand
{
	struct MS3DHeader
	{
		char ID[10];						// 总是为"MS3D000000"
		unsigned int Version;				// 3
	};

	struct MS3DVertex
	{
		unsigned char Flags;				// SELECTED | SELECTED2 | HIDDEN
		float Vertex[3];
		char BoneID;
		unsigned char ReferenceCount;		// -1表示不存在骨骼
	};

	struct MS3DTriangle
	{
		unsigned short Flags;
		unsigned short VertexIndices[3];
		float VertexNormals[3][3];
		float S[3];
		float T[3];
		unsigned char SmoothingGroup;			
		unsigned char GroupIndex;
	};

	struct MS3DGroup
	{
		unsigned char Flags;				// SELECTED | HIDDEN
		char Name[32];
		unsigned short NumTriangles;
		unsigned short *TriangleIndices;	// The Groups group the triangles
		char MaterialIndex;					// 若为-1，则无材质
	};

	struct MS3DMaterial
	{
		char Name[32];
		float Ambient[4];
		float Diffuse[4];
		float Specular[4];
		float Emissive[4];
		float Shininess;					// 0.0f ~ 128.0f
		float Transparency;					// 0.0f ~ 1.0f
		char Mode;
		char Texture[128];					// Texeture.bmp
		char AlphaMap[128];					// Alpha.bmp
	};
};
#endif