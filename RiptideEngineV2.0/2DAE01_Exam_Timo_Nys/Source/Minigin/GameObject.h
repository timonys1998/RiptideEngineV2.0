#pragma once
#include <memory>

#include "Transform.h"

class BaseComponent;


	class GameObject : public std::enable_shared_from_this<GameObject>
	{
	public:
		//A create / instantiate function based upon unity
		static std::shared_ptr<GameObject> Instantiate(const FLOAT2& position = { 0.0f,0.0f });
		explicit GameObject() = default;

		void Update(float deltaTime);

	
		void AddComponent(std::shared_ptr<BaseComponent> component);
		void RemoveComponent(std::shared_ptr<BaseComponent> component);

		std::string GetTag()const { return m_Tag; }
		void SetTag(const std::string& tag)
		{
			m_Tag = tag;
		}
		
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		
		template<class T>
		std::shared_ptr<T> GetComponent()
		{
			for (const auto comp : m_spComponents)
			{
				//We dont check for nullptr cause the component should not be in the vector if its nullptr / We only check if its the type
				if (typeid(*comp) == typeid(T))
				{
					std::cout << "Component found \n";
					return std::static_pointer_cast<T>(comp);
				}
			}
			return nullptr;
		}

		template<class T>
		std::vector<std::shared_ptr<T>> GetAllComponentsOfType()
		{
			std::vector<std::shared_ptr<T>> components;
			for(const auto comp : m_spComponents)
			{
				if(typeid(*comp) == typeid(T))
				{
					components.push_back(std::static_pointer_cast<T>(comp));
				}
			}
			return components;
		}

		template<class T>
		bool HasComponent()
		{
			return GetComponent<T>() != nullptr;
		}
	protected:
		
	
	private:
		std::vector<std::shared_ptr<BaseComponent>> m_spComponents;
		std::string m_Tag {""};
	};
