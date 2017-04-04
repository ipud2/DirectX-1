dofile( "../Data/Material/Sampler.lua" )

sampler = Sampler or {};

MatTable = 
{
	AmbientMaterial 	= {0.2 , 0.2 , 0.2 , 1.0},
	DiffuseMaterial 	= {0.2 , 0.2 , 0.2 , 1.0},
	SpecularMaterial 	= {0.8 , 0.8 , 0.8 , 16.0},
	Reflect 			= {0.5 , 0.5 , 0.5 , 1.0},
	bUseTexture 		= false ,
	bEnabledReflect 	= true ,
	SkyboxTexture	 	= "SnowCube.dds" ,
	LinearSampler 		= sampler,
}