dofile( "../Data/Material/Sampler.lua" )

sampler = Sampler or {};

MatTable = 
{
	AmbientMaterial 	= {0.2 , 0.3 , 0.4 , 1.0},
	DiffuseMaterial 	= {1.0 , 1.0 , 1.0 , 1.0},
	SpecularMaterial 	= {0.9 , 0.9 , 0.9 , 16.0},
	Reflect 			= {0.4 , 0.4 , 0.4 , 1.0},
	bUseTexture 		= true ,
	DiffuseTexture	 	= "Stone.dds" ,
	NormalMap 			= "Stone_nmap.dds" ,
	SkyboxTexture	 	= "SnowCube.dds" ,
	LinearSampler 		= sampler,
	bEnabledReflect		= true,
}