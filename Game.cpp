﻿//
// Game.cpp
//

#include "pch.h"
#include "Game.h"

#include "DXDevice.h"
#include "ModelManager.h"

#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

extern void ExitGame();

using namespace DirectX;
using namespace DirectX::SimpleMath;

using Microsoft::WRL::ComPtr;

Game::Game()
{
    m_deviceResources = std::make_unique<DX::DeviceResources>();
    m_deviceResources->RegisterDeviceNotify(this);
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
	// キーボードの作成
	m_keyboard = std::make_unique<Keyboard>();

	// マウスの作成
	m_mouse = std::make_unique<Mouse>();
	m_mouse->SetWindow(window);

	// デバッグカメラの作成
	m_debugCamera = std::make_unique<DebugCamera>(width, height);

    m_deviceResources->SetWindow(window, width, height);

    m_deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */

}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here.
    elapsedTime;

	// デバッグカメラの更新
	m_debugCamera->Update();

	m_player->SetPosition(Vector3(m_ball->GetPosition().x,m_ball->GetPosition().y + 0.5,m_ball->GetPosition().z));

	

	auto kb = Keyboard::Get().GetState();

	if (kb.Up)
	{
		m_ball->Move(Ball::FORWARD);
	}
	if (kb.Down)
	{
		m_ball->Move(Ball::BACK);
	}
	if (kb.Left)
	{
		m_ball->Move(Ball::TURN_LEFT);
	}
	if (kb.Right)
	{
		m_ball->Move(Ball::TURN_RIGHT);
	}

	// カメラを後ろに設定する
	Vector3 vec(0.0f, 6.0f, 10.0f);
	Matrix rotY = Matrix::CreateRotationY(m_ball->GetDirection());
	vec = Vector3::Transform(vec, rotY);
	Vector3 target = m_player->GetPosition();
	Vector3 eye = target + vec;
	m_camera.SetPositionTarget(eye, target);

	// 各アップデート関数の呼び出し
	m_ball->Update(elapsedTime);
	m_player->Update(elapsedTime);
	m_enemyEye->Update(elapsedTime);

	//int id;
	//Vector3 s;
	//Vector3 ballPos = m_ball->GetPosition();
	//Vector3 v[2] = { Vector3(ballPos.x,100.0f,ballPos.z),Vector3(ballPos.x,-100.0f,ballPos.z) };

	//if (m_floor->HitCheck_Segment(v[0], v[1], &id, &s) == true)
	//{
	//	s.y += 1.0f;

	//	m_ball->SetPosition(s);
	//}

	m_ball->SetPosition(FloorCol(m_ball->GetPosition()));
	m_enemyEye->SetPosition(FloorCol(m_enemyEye->GetPosition()));
	
	

}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
	// Don't try to render anything before the first Update.
	if (m_timer.GetFrameCount() == 0)
	{
		return;
	}

	Clear();

	m_deviceResources->PIXBeginEvent(L"Render");
	auto context = m_deviceResources->GetD3DDeviceContext();



	// ビュー行列の作成
	// m_view = m_debugCamera->GetCameraMatrix();
	m_view = Matrix::CreateLookAt(m_camera.GetEyePosition(), m_camera.GetTargetPosition(), Vector3::Up);

	// グリッドの床の描画
	m_gridFloor->Render(context, m_view, m_projection);

	// 床の描画
	m_floor->DrawCollision(context,m_view,m_projection);
	// ここから描画処理を記述する

	// 各レンダー関数の呼び出し
	m_ball->Render();
	m_player->Render();
	m_enemyEye->Render();

	m_floorModel->Draw(context,*m_states,m_world,m_view,m_projection );

	// ここまで

    m_deviceResources->PIXEndEvent();

    // Show the new frame.
    m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    m_deviceResources->PIXBeginEvent(L"Clear");

    // Clear the views.
    auto context = m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::DarkBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    auto viewport = m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 800;
    height = 600;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
	// デバイスの作成
    ID3D11Device* device = m_deviceResources->GetD3DDevice();
	ID3D11DeviceContext* context = m_deviceResources->GetD3DDeviceContext();

	// コモンステートの作成
	m_states = std::make_unique<CommonStates>(device);
	// スプライトバッチの作成
	m_sprites = std::make_unique<SpriteBatch>(context);
	// スプライトフォントの作成
	m_font = std::make_unique<SpriteFont>(device, L"SegoeUI_18.spritefont");


	// デバイスのセット
	DXDevice::GetInstance().SetDevice(device);
	DXDevice::GetInstance().SetContext(context);
	// モデルマネージャーのセット
	ModelManager::GetInstance().SetProjcton(&m_projection);
	ModelManager::GetInstance().SetView(&m_view);
	ModelManager::GetInstance().SetStates(m_states.get());


	EffectFactory fx(device);
	fx.SetDirectory(L"Resources\\Models"); // モデルのテクスチャが入っているフォルダを指定

    // TODO: Initialize device dependent objects here (independent of window size).
    device;

	/// <summary>
	/// モデルの作成
	/// </summary>

	// グリッドの床の作成
	m_gridFloor = std::make_unique<GridFloor>(device, context, m_states.get(), 10.0f, 10);
	
	// ball
	m_ball = std::make_unique<Ball>();
	/*m_ball->SetupEffect();*/

	// player
	m_player = std::make_unique<Player>();

	// enemyEye
	m_enemyEye = std::make_unique<Enemy>();

	// yuka
	m_floorModel = Model::CreateFromCMO(device, L"Resources\\Models\\FloorModel.cmo",fx);
	// 床のコリジョンメッシュの作成
	m_floor = std::make_unique<CollisionMesh>(device, L"Obj\\floor.obj");

}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.

	// ウインドウサイズからアスペクト比を算出する
	RECT size = m_deviceResources->GetOutputSize();
	float aspectRatio = float(size.right) / float(size.bottom);

	// 画角を設定
	float fovAngleY = XMConvertToRadians(45.0f);

	// 射影行列を作成する
	m_projection = Matrix::CreatePerspectiveFieldOfView(
		fovAngleY,
		aspectRatio,
		0.01f,
		100.0f
	);

	// デバッグカメラにウインドウのサイズ変更を伝える
	m_debugCamera->SetWindowSize(size.right, size.bottom);
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.

	// コモンステートの解放
	m_states.reset();

	// スプライトバッチの解放
	m_sprites.reset();

	// スプライトフォントの解放
	m_font.reset();

	// グリッドの床の解放
	m_gridFloor.reset();

}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}

// 地面との当たり判定用関数
Vector3 Game::FloorCol(Vector3 objPos)
{
	int id;
	Vector3 s;
	Vector3 pos = objPos;
	Vector3 v[2] = { Vector3(pos.x,100.0f,pos.z),Vector3(pos.x,-100.0f,pos.z) };

	if (m_floor->HitCheck_Segment(v[0], v[1], &id, &s) == true)
	{
		s.y += 1.0f;

		return s;

		//m_ball->SetPosition(s);
	}
	return pos;
}
#pragma endregion
