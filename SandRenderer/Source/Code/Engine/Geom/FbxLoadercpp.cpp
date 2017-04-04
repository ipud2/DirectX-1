#include <Engine/PCH.h>
#include "FbxLoader.h"
#include "Engine/Pipeline/PipelineStage/StageExecutor/InputAssember/Geometry.h"
#include "FbxImporterProcesser.h"
#include "Engine/Animation/VScene.h"
#include "FFbxImporter.h"

using namespace Sand;

Geometry* FbxLoader::LoadFBX( const char* szFilename )
{
	Geometry* pGeometry = new Geometry;

	VScene scene;
	FFbxImporter importer;
	importer.SetScene( scene );
	importer.Load( szFilename );
	
	FbxImporterProcesser processer;
	processer.SetGeometry( pGeometry );
	processer.Process( scene );
	
	return processer.GetGeometry();
}