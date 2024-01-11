#pragma once
#include <functional>
#include <vector>
#include <string>
#include <iostream>

namespace test {
	class Test
	{
	public:
		Test() {}
		virtual ~Test() {}

		//该处用虚函数而不是用纯虚函数，是因为有的地方别的类可能用不到，就不用重写了
		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};
	class TestMenu :public Test
	{
	public:
		TestMenu(Test*& currentTestPointer);
		//~TestMenu();

		//virtual void OnUpdate(float deltaTime) override;
		virtual void OnRender() override;
		//virtual void OnImGuiRender() override;

		template<typename T>
		void RegisterTest(const std::string& name)
		{
			std::cout << "Registering test : " << name << std::endl;
			m_Tests.push_back(std::make_pair(name, []() {return new T(); }));
		}

	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;
	};
}