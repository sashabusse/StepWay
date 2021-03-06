//#include "Window.h"
#include "Platform/Win32/Win32Window.h"
#include "gtest/gtest.h"
#include "Log.h"


class Win32WindowFixture : public ::testing::Test
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



TEST_F(Win32WindowFixture, InitializationTest)
{
	StepWay::Window* window = StepWay::Window::Create();//new StepWay::Win32Window;
	StepWay::WindowProp prop;
	prop.height = 800;
	prop.width = 1200;
	prop.luX = 0;
	prop.luY = 0;
	EXPECT_TRUE(window->SetUp(prop));
	window->ShutDown();
	delete window;
}



TEST_F(Win32WindowFixture, MultipleInitializationTest)
{
	StepWay::Window* window = new StepWay::Win32::Win32Window;
	StepWay::Window* window2 = new StepWay::Win32::Win32Window;

	StepWay::WindowProp prop;
	prop.height = 800;
	prop.width = 1200;
	prop.luX = 0;
	prop.luY = 0;

	EXPECT_TRUE(window->SetUp(prop));
	EXPECT_TRUE(window2->SetUp(prop));

	window2->ShutDown();
	window->ShutDown();

	delete window2;
	delete window;
}


TEST_F(Win32WindowFixture, InitialState)
{
	StepWay::Window* window = new StepWay::Win32::Win32Window;
	
	StepWay::WindowProp prop;
	prop.height = 800;
	prop.width = 1200;
	prop.luX = 0;
	prop.luY = 0;

	window->SetUp(prop);

	EXPECT_EQ(prop.height, window->GetHeight());
	EXPECT_EQ(prop.width, window->GetWidth());
	EXPECT_EQ(prop.luX, window->GetX());
	EXPECT_EQ(prop.luY, window->GetY());

	window->ShutDown();
	delete window;

}


TEST_F(Win32WindowFixture, Move)
{
	StepWay::Window* window = new StepWay::Win32::Win32Window;

	StepWay::WindowProp prop;
	prop.height = 800;
	prop.width = 1200;
	prop.luX = 0;
	prop.luY = 0;

	window->SetUp(prop);

	int x = 450, y = 120;

	for (int i = 0; i < 15; i++)
	{
		x += i;
		y += i;
		window->SetPosition(x, y);

		EXPECT_EQ(x, window->GetX());
		EXPECT_EQ(y, window->GetY());
	}

	window->ShutDown();
	delete window;
}

TEST_F(Win32WindowFixture, WindowDestroyCallback)
{
	StepWay::Window* window = new StepWay::Win32::Win32Window;

	StepWay::WindowProp prop;
	prop.height = 800;
	prop.width = 1200;
	prop.luX = 0;
	prop.luY = 0;

	window->SetUp(prop);
	bool is_destroyed = false;
	window->SetEventCallback
	(
		[&](StepWay::Event& e) { if (e.GetEventType() == StepWay::EventType::WINDOW_DESTROY) is_destroyed = true; }
	);
	window->Close();
	window->OnUpdate();
	
	EXPECT_TRUE(is_destroyed);

	window->ShutDown();
	delete window;
}