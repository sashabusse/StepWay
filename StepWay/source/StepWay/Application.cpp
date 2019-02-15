#include "StepWayPCH.h"
#include "Application.h"
#include "Events/KeyEvent.h"
#include "Events/WindowEvent.h"
#include "Memory/Memory.h"

//for test rendering
#include "../../vendor/glad/include/glad/glad.h"


bool StepWay::Application::SetUp()
{
	m_IsRunning = false;

	m_MemoryManager.Init();//rename it

	//TODO:
	//decide where to SetUp call!!!
	m_MainContext = graphics::API::Context::Create(graphics::API::GraphicsAPIType::OPENGL);//same as next
	m_MainContext->SetUp();
	m_MainWindow = Window::Create();//think about protected constructors


	//main window initialization
	WindowProp prop;
	prop.height = 500;
	prop.width = 500;
	prop.luX = 100;
	prop.luY = 100;
	prop.title = L"Main App Window";

	if (!m_MainWindow->SetUp(prop))
	{
		SW_CORE_ERROR("failed to Init Window");
		return false;
	}
	m_MainWindow->SetEventCallback(SW_BIND_METH_1(Application::OnEvent));
	m_MainWindow->BindContext(m_MainContext);
	m_MainWindow->MakeContextCurrent();


	m_IsRunning = ImplSetUp();
	return m_IsRunning;
}


void StepWay::Application::ShutDown()
{
	ImplShutDown();

	m_MainWindow->ShutDown();

	//make static method for window deletion
	SW_DELETE m_MainWindow;

	m_MainContext->ShutDown();//same as prev
	SW_DELETE m_MainContext;

	m_MemoryManager.Destroy();
	SW_TRACE("Successful App Destruction");
}


void StepWay::Application::Run()
{
	SW_CORE_TRACE("Entering Main Loop");
	while (m_IsRunning)
	{
		//update layers
		for(auto it = m_layers.begin(); it != m_layers.end(); ++it)
		{
			(*it)->OnUpdate();
		}

		//update overlays
		for (auto it = m_overlays.begin(); it != m_overlays.end(); ++it)
		{
			(*it)->OnUpdate();
		}

		//some test rendering here
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		GLuint err = glGetError();
		glClear(GL_COLOR_BUFFER_BIT);
		err = glGetError();
		/*err = glGetError();
		GLuint buffer;
		glGenBuffers(1, &buffer);
		err = glGetError();
		glBindBuffer(GL_VERTEX_ARRAY, buffer);
		err = glGetError();
		GL_NO_ERROR
		struct vec2
		{
			float x, y;
		};
		vec2 pos[3] =
		{
			-0.5f,-0.5f,
			0.5f,-0.5f,
			0.0f,0.5f,
		};

		glBufferData(GL_VERTEX_ARRAY, sizeof(float) * 2 * 3, pos, GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		
		glDrawArrays(GL_TRIANGLES, 0, 3);*/
		glBegin(GL_QUADS);

		glVertex2f(-0.8, -0.8);

		glVertex2f(0.8, -0.8);

		glVertex2f(0.8, 0.8);

		glVertex2f(-0.8, 0.8);

		glEnd();
		//glBegin(GL_TRIANGLES);
		//
		//glVertex2f(-1, -1);
		//glVertex2f(0, 1);
		//glVertex2f(1, -1);
		//
		//glEnd();
	

		m_MainWindow->OnUpdate();
	}
}

void StepWay::Application::OnEvent(Event & e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowDestroyEvent>(SW_BIND_METH_1(Application::OnMainWindowClose));

	//Messaging overlays
	for (auto it = m_overlays.end(); it != m_overlays.begin();)
	{
		--it;
		(*it)->OnEvent(e);
	}

	//Messaging layers
	for (auto it = m_layers.end(); it != m_layers.begin();)
	{
		--it;
		(*it)->OnEvent(e);
	}

}

void StepWay::Application::PushLayer(Layer * layer)
{
	SW_CORE_TRACE("(Layer)");
	m_layers.PushLayer(layer);
}

void StepWay::Application::PopLayer(Layer * layer)
{
	m_layers.PopLayer(layer);
}

void StepWay::Application::PushOverLay(Layer * overlay)
{
	SW_CORE_TRACE("(Overlay)");
	m_overlays.PushLayer(overlay);
}

void StepWay::Application::PopOverlay(Layer * overlay)
{
	m_overlays.PopLayer(overlay);
}


StepWay::Application::~Application()
{
}

void StepWay::Application::OnMainWindowClose(WindowDestroyEvent & e)
{
	SW_CORE_INFO("Main window closed");
	m_IsRunning = false;
}
