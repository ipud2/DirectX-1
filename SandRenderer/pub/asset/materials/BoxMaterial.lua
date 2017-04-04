dofile( "../Data/Material/Sampler.lua" )

sampler = Sampler or {};

MatTable = 
{
	AmbientMaterial 	= {1.0 , 1.0 , 1.0 , 1.0},
	DiffuseMaterial 	= {1.0 , 1.0 , 1.0 , 1.0},
	SpecularMaterial 	= {0.8 , 0.8 , 0.8 , 16.0},
	Reflect 			= {0.0 , 0.0 , 0.0 , 1.0},
	bUseTexture 		= true ,
	DiffuseTexture		= "bricks.dds" ,
	NormalMap	 		= "bricks_nmap.dds" ,
	LinearSampler 		= sampler,
}