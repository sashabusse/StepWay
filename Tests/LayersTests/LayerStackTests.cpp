#include <gtest/gtest.h>
#include "Layers/LayerStack.h"
#include "Log.h"

using StepWay::graphics::LayerStack;

using StepWay::graphics::Layer;

class LayerStackTests : public ::testing::Test
{
protected:
	void SetUp() override
	{
	}
	void TearDown() override
	{
	}
	static void SetUpTestSuite()
	{
		StepWay::Log::Init();
	}

	static void TearDownTestSuite()
	{
		StepWay::Log::ShutDown();
	}
};


class TestLayer : public Layer
{
public:
	virtual void OnAttach()
	{
		IsAttached = true;
	};
	virtual void OnDetach()
	{
		IsAttached = false;
	};

	bool IsAttached = false;

	virtual void OnUpdate() {};
	virtual void OnEvent(StepWay::Event& e) {};

	virtual std::string ToString() const { return std::string(); };
	virtual std::wstring ToWString() const { return std::wstring(); };

};

TEST_F(LayerStackTests, push_pop)
{
	LayerStack stack;

	//check empty
	EXPECT_EQ(stack.begin(), stack.end());

	TestLayer tstLayer;

	stack.PushLayer(&tstLayer);
	EXPECT_TRUE(tstLayer.IsAttached);
	EXPECT_NE(stack.begin(), stack.end());
	EXPECT_EQ((++stack.begin()), stack.end());

	stack.PopLayer(&tstLayer);
	EXPECT_FALSE(tstLayer.IsAttached);

	EXPECT_EQ(stack.begin(), stack.end());
}