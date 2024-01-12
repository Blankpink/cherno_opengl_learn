#include "TestTexture2D.h"
#include "Renderer.h"
#include "imgui/imgui.h"


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace  test {

	TestTexture2D::TestTexture2D()
		:m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)), 
		m_View(glm::translate(glm::mat4(1.0), glm::vec3(100, 100, 0))), 
		m_TranslationA(0, 0, 0), m_TranslationB(0, 0, 0)
	{
		float positions[] =
		{
			-100.0f+0.00f, -100.0f+50.0f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f, 0.0f, 0.0f, 0.0f,
			   0.0f+0.00f, -100.0f+50.0f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f, 1.0f, 0.0f, 0.0f,
			   0.0f+0.00f,    0.0f+50.0f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f, 1.0f, 1.0f, 0.0f,
			-100.0f+0.00f,    0.0f+50.0f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f, 0.0f, 1.0f, 0.0f,

			   0.0f+100.f,    0.0f-50.0f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f, 0.0f, 0.0f, 1.0f,
			 100.0f+100.f,    0.0f-50.0f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f, 1.0f, 0.0f, 1.0f,
			 100.0f+100.f,  100.0f-50.0f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f, 1.0f, 1.0f, 1.0f,
			   0.0f+100.f,  100.0f-50.0f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f, 0.0f, 1.0f, 1.0f
		};

		unsigned int indices[] =
		{
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4
		};

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		m_VAO = std::make_unique<VertexArray>();

		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, sizeof(positions));

		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(4);
		layout.Push<float>(2);
		layout.Push<float>(1);
		
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 12);

		m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_Shader->Bind();
		m_Shader->SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

		m_Texture = std::make_unique<Texture>("1");
		// m_Texture = std::make_unique<Texture>("res/textures/RedHeart.jpg");
		//m_Shader->SetUniform1i("u_Texture", 0);
		//m_Shader->SetUniform1i("u_Texture", 0);
		int samplers[2] = { 0, 1 };
		m_Shader->SetUniform1i2("u_Textures", samplers);

	}

	TestTexture2D::~TestTexture2D()
	{

	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{

	}

	void TestTexture2D::OnRender()
	{
		GLCall(glClearColor(0.5f, 0.5f, 0.5f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		Renderer renderer;
		renderer.clear();
		m_Texture->Bind(0);
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB); //坐标变换 移动translation个单位
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);

			GLCall(renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader));


		}
	}

	void TestTexture2D::OnImGuiRender()
	{
		ImGui::SliderFloat3("TranslationB", &m_TranslationB.x, 0.0f, 960.0f);            // Edit 1 float using a slider from 0.0f to 1.0f  
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}


