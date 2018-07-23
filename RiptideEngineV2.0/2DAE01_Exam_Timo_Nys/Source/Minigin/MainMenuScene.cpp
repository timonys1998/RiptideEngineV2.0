#include "MiniginPCH.h"
#include "MainMenuScene.h"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "Minigin.h"
#include "FPSCalculatorComponent.h"
#include "InputComponent.h"
#include "Tile.h"


MainMenuScene::MainMenuScene()
	:Scene("MainMenu")
{
	Init();
}


MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::Init()
{
	mBackground = std::make_shared<GameObject>();
	mBackground->AddComponent(std::make_shared<TextureComponent>("background.jpg"));
	mBackground->GetComponent<Transform>()->SetPosition(0.0f,0.0f);
	mBackground->AddComponent(std::make_shared<RenderComponent>(mBackground->GetComponent<TextureComponent>()->GetTexture()));
	
	Add(mBackground);

	mSinglePlayerIcon = std::make_shared<GameObject>();
	mSinglePlayerIcon->AddComponent(std::make_shared<TextureComponent>("SinglePacMan.png"));
	mSinglePlayerIcon->AddComponent(std::make_shared<RenderComponent>(mSinglePlayerIcon->GetComponent<TextureComponent>()->GetTexture()));
	mSinglePlayerIcon->GetComponent<Transform>()->SetPosition(SCREEN_WIDTH / 3.5f, SCREEN_HEIGHT / 2);
	Add(mSinglePlayerIcon);

	mMultiPlayerIcon = std::make_shared<GameObject>();
	mMultiPlayerIcon->AddComponent(std::make_shared<TextureComponent>("MultiPacMan.png"));
	mMultiPlayerIcon->AddComponent(std::make_shared<RenderComponent>(mMultiPlayerIcon->GetComponent<TextureComponent>()->GetTexture()));
	mMultiPlayerIcon->GetComponent<Transform>()->SetPosition((SCREEN_WIDTH / 2) - 32.0f, SCREEN_HEIGHT / 2);
	Add(mMultiPlayerIcon);

	mGhostIcon = std::make_shared<GameObject>();
	mGhostIcon->AddComponent(std::make_shared<TextureComponent>("Ghost.png"));
	mGhostIcon->AddComponent(std::make_shared<RenderComponent>(mGhostIcon->GetComponent<TextureComponent>()->GetTexture()));
	mGhostIcon->GetComponent<Transform>()->SetPosition((SCREEN_WIDTH / 1.5f) , SCREEN_HEIGHT / 2);
	Add(mGhostIcon);


	mFpsCounter = std::make_shared<GameObject>();
	mFpsCounter->AddComponent(std::make_shared<TextComponent>("Lingua.otf",20,SDL_Color{200,155,15}));
	mFpsCounter->AddComponent(std::make_shared<FPSCalculatorComponent>());
	mFpsCounter->GetComponent<TextComponent>()->SetText(std::to_string(mFpsCounter->GetComponent<FPSCalculatorComponent>()->GetFps()));
	mFpsCounter->AddComponent(std::make_shared<RenderComponent>(mFpsCounter->GetComponent<TextComponent>()->GetTexture()));
	mFpsCounter->GetComponent<Transform>()->SetPosition(0.0f, 0);
	Add(mFpsCounter);

	mMenuText = std::make_shared<GameObject>();
	mMenuText->AddComponent(std::make_shared<TextComponent>("Lingua.otf", 20, SDL_Color{ 200,155,15 }));
	mMenuText->GetComponent<TextComponent>()->SetText("1: Singleplayer , 2: CO-OP, 3: Versus");
	mMenuText->AddComponent(std::make_shared<RenderComponent>(mMenuText->GetComponent<TextComponent>()->GetTexture()));
	mMenuText->GetComponent<Transform>()->SetPosition(SCREEN_WIDTH / 2 - 150.0f, SCREEN_HEIGHT / 2 + 50.0f);
	mMenuText->AddComponent(std::make_shared<InputComponent>());
	mMenuText->GetComponent<InputComponent>()->AddInput(InputComponent::Button::NUM1, std::make_shared<SelectMode>("PacManSinglePlayer"));
	mMenuText->GetComponent<InputComponent>()->AddInput(InputComponent::Button::NUM2, std::make_shared<SelectMode>("PacManMultiPlayer"));
	mMenuText->GetComponent<InputComponent>()->AddInput(InputComponent::Button::NUM3, std::make_shared<SelectMode>("VersusScene"));
	Add(mMenuText);
	
}

void MainMenuScene::SceneUpdate(float deltaTime)
{
	mFPSIntervalCounter += deltaTime;
	if (mFPSIntervalCounter >= mFPSTimeInterval) {
		mFpsCounter->GetComponent<TextComponent>()->SetText(std::to_string(mFpsCounter->GetComponent<FPSCalculatorComponent>()->GetFps()));
		mFpsCounter->GetComponent<RenderComponent>()->ChangeRenderingTexture(mFpsCounter->GetComponent<TextComponent>()->GetTexture());
		mFPSIntervalCounter = 0.0f;
	}

	mMenuText->GetComponent<RenderComponent>()->ChangeRenderingTexture(mMenuText->GetComponent<TextComponent>()->GetTexture());
}




