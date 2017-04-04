dofile( "../Data/Material/Sampler.lua" )

sampler = Sampler or {};

MatTable = 
{
	AmbientMaterial 	= {1.0 , 1.0 , 1.0 , 1.0},
	DiffuseMaterial 	= {1.0 , 1.0 , 1.0 , 1.0},
	SpecularMaterial 	= {0.8 , 0.8 , 0.8 , 16.0},
	Reflect 			= {0.0 , 0.0 , 0.0 , 1.0},
	bUseTexture 		= true ,
	DiffuseTexture		= "floor.dds" ,
	NormalMap	 		= "floor_nmap.dds" ,
	LinearSampler 		= sampler,
	bEnabledReflect     = false,
	MaxTessDistance		= 1.0,
	MinTessDistance		= 25.0,
	MinTessFactor		= 1.0 ,
	MaxTessFactor 		= 5.0 ,
	HeightScale			= 0.07,
}