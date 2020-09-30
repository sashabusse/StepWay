#pragma once



namespace StepWay
{
	class OS
	{
	public:
		static OS* Create();
		virtual void SetUp() = 0;
		virtual void ShutDown() = 0;

		virtual ~OS() {};
	};
}