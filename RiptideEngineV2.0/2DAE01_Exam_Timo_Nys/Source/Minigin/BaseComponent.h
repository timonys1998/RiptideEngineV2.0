#pragma once

class GameObject;

	class BaseComponent
	{
	public:
		BaseComponent();
		virtual ~BaseComponent();
		virtual void Update(float deltaTime) = 0;

		virtual void SetOwner(std::weak_ptr<GameObject>owner) { m_wpOwner = owner; }
		virtual std::weak_ptr<GameObject> GetOwner()const { return m_wpOwner; }

		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

	protected:
		friend class GameObject;
		std::weak_ptr<GameObject> m_wpOwner;
	};


