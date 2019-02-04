#pragma once


namespace StepWay
{



	//Super class for Resource Managers (e.g. MeshManager TextureManager ...)
	//Responsibilities:
	//	1. Caching
	//	2. ResourceLoading of resorces of certain type ( is something like factory )
	//
	//Probabal Future updates
	//	3. Add common Resource pool to share it among different Resource Managers
	class ResourceManager
	{
	public:
		virtual ~ResourceManager() {};
	};



}
