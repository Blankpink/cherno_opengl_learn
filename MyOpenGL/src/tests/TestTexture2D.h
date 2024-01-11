#pragma once
#include "Test.h"

#include "VertexBuffer.h"
#include "VerTexBufferLayout.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Shader.h"
#include "memory"

namespace test {
	class TestTexture2D :public Test
	{
	public:
		TestTexture2D();
		~TestTexture2D();

		virtual void OnUpdate(float deltaTime) override;
		virtual void OnRender() override;
		virtual void OnImGuiRender() override;

	private:
		//智能指针会在作用域的末尾被销毁
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;
		glm::mat4 m_Proj, m_View;
		std::unique_ptr <VertexBuffer> m_VertexBuffer;

		glm::vec3 m_TranslationA, m_TranslationB;
	};

}
