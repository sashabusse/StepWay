#include "gtest/gtest.h"
#include "Resource/ResourceGroupManager.h"


using namespace StepWay;



TEST(ResourceGroupManagerBundles, ResBundleAdd)
{
	ResourceGroupManager::Init();
	ResourceGroupManager& instance = ResourceGroupManager::GetInstanceRef();


	for (int i = 0; i < 10; i++)
	{
		EXPECT_NE(instance.AddResBundle("some/path/here.deb", BundleType::DEBUG), nullptr);
		EXPECT_EQ(instance.GetResBundleCount(), 1);
		EXPECT_NE(instance.GetResBundle("some/path/here.deb"), nullptr);
	}
	for (int i = 0; i < 20; i++)
	{
		EXPECT_NE(instance.AddResBundle("another/path/here.deb", BundleType::DEBUG), nullptr);
		EXPECT_EQ(instance.GetResBundleCount(), 2);
		EXPECT_NE(instance.GetResBundle("another/path/here.deb"), nullptr);
	}
	for (int i = 0; i < 20; i++)
	{
		EXPECT_NE(instance.AddResBundle("some/path/here.deb", BundleType::DEBUG), nullptr);
		EXPECT_EQ(instance.GetResBundleCount(), 2);
		EXPECT_NE(instance.GetResBundle("some/path/here.deb"), nullptr);
	}

	StepWay::ResourceGroupManager::Destroy();
}


TEST(ResourceGroupManagerBundles, ResBundleMultippleAdd)
{

}
