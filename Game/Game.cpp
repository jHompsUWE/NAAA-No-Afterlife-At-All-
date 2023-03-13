//
// Game.cpp
//

#include "pch.h"
#include "Game.h"
#include <time.h>

//Scarle Headers
#include "GameData.h"
#include "GameState.h"
#include "DrawData.h"
#include "DrawData2D.h"
#include "ObjectList.h"

// GameState headers
#include "FBXImporter.h"
#include "GameStateBase.h"
#include "GameMenu.h"
#include "GamePlay.h"
#include "GameTutorial.h"
#include "GamePaused.h"
#include "GameOver.h"
#include "helper.h"

extern void ExitGame() noexcept;

using namespace DirectX;

using Microsoft::WRL::ComPtr;

Game::Game() noexcept :
    m_window(nullptr),
    m_outputWidth(800),
    m_outputHeight(600),
    m_featureLevel(D3D_FEATURE_LEVEL_11_0)
{

}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND _window, int _width, int _height)
{
    m_window = _window;
    m_outputWidth = std::max(_width, 1);
    m_outputHeight = std::max(_height, 1);

    CreateDevice();

    CreateResources();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */
    
    //seed the random number generator
    srand((UINT)time(NULL));

    //set up keyboard and mouse system
    //documentation here: https://github.com/microsoft/DirectXTK/wiki/Mouse-and-keyboard-input
    m_keyboard = std::make_unique<Keyboard>();
    m_mouse = std::make_unique<Mouse>();
    m_mouse->SetWindow(_window);
    m_mouse->SetMode(Mouse::MODE_ABSOLUTE);
    //Hide the mouse pointer
    ShowCursor(true);

    //create GameData struct and populate its pointers
    m_GD = new GameData;
    m_GD->m_GS = GS_PLAY_MAIN_CAM;
    m_GD->current_state = State::GAME_MENU;


    //set up systems for 2D rendering
    m_DD2D = new DrawData2D();
    m_DD2D->m_Sprites.reset(new SpriteBatch(m_d3dContext.Get()));
    m_DD2D->m_Font.reset(new SpriteFont(m_d3dDevice.Get(), L"..\\Assets\\italic.spritefont"));
    m_states = new CommonStates(m_d3dDevice.Get());

    //set up DirectXTK Effects system
    m_fxFactory = new EffectFactory(m_d3dDevice.Get());
    //Tell the fxFactory to look to the correct build directory to pull stuff in from
    ((EffectFactory*)m_fxFactory)->SetDirectory(L"..\\Assets");
    //init render system for VBGOs
    VBGO::Init(m_d3dDevice.Get());

    //set audio system
    AUDIO_ENGINE_FLAGS eflags = AudioEngine_Default;
#ifdef _DEBUG
    eflags = eflags | AudioEngine_Debug;
#endif
    m_audioEngine = std::make_unique<AudioEngine>(eflags);

    m_DD = new DrawData;
    m_DD->m_pd3dImmediateContext = nullptr;
    m_DD->m_states = m_states;
    m_DD->m_cam = m_TPScam;
    m_DD->m_light = m_light;
    
    game_states.insert(std::make_pair(State::GAME_MENU,     std::make_unique<GameMenu>      (State::GAME_MENU,     m_GD, m_DD, m_DD2D, m_fxFactory, m_d3dDevice)));
    game_states.insert(std::make_pair(State::GAME_PLAY,     std::make_unique<GamePlay>      (State::GAME_PLAY,     m_GD, m_DD, m_DD2D, m_fxFactory, m_d3dDevice)));
    game_states.insert(std::make_pair(State::GAME_TUTORIAL, std::make_unique<GameTutorial>  (State::GAME_TUTORIAL, m_GD, m_DD, m_DD2D, m_fxFactory, m_d3dDevice)));
    game_states.insert(std::make_pair(State::GAME_PAUSED,   std::make_unique<GamePaused>    (State::GAME_PAUSED,   m_GD, m_DD, m_DD2D, m_fxFactory, m_d3dDevice)));
    game_states.insert(std::make_pair(State::GAME_OVER,     std::make_unique<GameOver>      (State::GAME_OVER,     m_GD, m_DD, m_DD2D, m_fxFactory, m_d3dDevice)));
    
    

    //example basic 2D stuff
    //ImageGO2D* logo = new ImageGO2D("logo_small", m_d3dDevice.Get());
   // logo->SetPos(200.0f * Vector2::One);
    //m_GameObjects2D.push_back(logo);
    //ImageGO2D* bug_test = new ImageGO2D("bug_test", m_d3dDevice.Get());
    //bug_test->SetPos(300.0f * Vector2::One);
    //m_GameObjects2D.push_back(bug_test);
    

    //TextGO2D* text = new TextGO2D("Test Text");
    //text->SetPos(Vector2(100, 10));
    //text->SetColour(Color((float*)&Colors::Yellow));
   // m_GameObjects2D.push_back(text);

    //Test Sounds
    Loop* loop = new Loop(m_audioEngine.get(), "NightAmbienceSimple_02");
    loop->SetVolume(0.05f);
    loop->Play();
    m_Sounds.push_back(loop);

    TestSound* TS = new TestSound(m_audioEngine.get(), "Explo1");
    TS->SetVolume(0.05f);
    
    m_Sounds.push_back(TS);
    
    event_manager = std::make_shared<EventManager>();
    GameManager::get()->addManager(event_manager, ManagerType::EVENT);
    economy_manager_ = std::make_shared<EconomyManager>();
    GameManager::get()->addManager(economy_manager_, ManagerType::ECONOMY);
    file_manager_ = std::make_shared<FileManager>();
    GameManager::get()->addManager(file_manager_, ManagerType::FILE);
    input_manager = std::make_shared<InputManager>();
    GameManager::get()->addManager(input_manager, ManagerType::INPUT);

    world_manager = std::make_shared<WorldManager>();
    GameManager::get()->addManager(world_manager, ManagerType::WORLD);
    world_manager->init(m_d3dContext, m_fxFactory);

    
    
    // GameState initialisation
    for (auto& state : game_states)
    {
        if (!state.second->init(_window, _width, _height, m_GD))
        { 
            //return false;
        }
    }

	auto& world = world_manager->getWorld();
    world[PlaneType::Heaven][2]->createBuilding(m_d3dContext);
    world[PlaneType::Heaven][1]->createBuilding(m_d3dContext);
    world[PlaneType::Heaven][0]->createBuilding(m_d3dContext);
    world_manager->updateVibes(*world[PlaneType::Heaven][25], PlaneType::Heaven);
}

// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
        lateUpdate(m_timer);
    });
    
    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& _timer)
{
    auto mouse = m_mouse->GetState();
    m_GD->m_mouseButtons.Update(mouse);
    float elapsedTime = float(_timer.GetElapsedSeconds());
    m_GD->m_dt = elapsedTime;

    // GameState updates
    // Change state depending on update result
    State prev_state = m_GD->current_state;
    m_GD->current_state = game_states[m_GD->current_state]->update(*m_GD);
    if (m_GD->current_state != prev_state)
    {
        if (m_GD->current_state == State::GAME_EXIT)
        {
            // Exit game
            return;
        }
        else
        {
            if (m_GD->current_state == State::GAME_PLAY)
            {
                GameManager::get()->getEventManager()->addListener(&game_states[m_GD->current_state]->getCam());
            }
            else if (prev_state == State::GAME_PLAY)
            {
                GameManager::get()->getEventManager()->removeListener(&game_states[prev_state]->getCam());
            }

            Event event{};
            event.type = EventType::STATE_TRANSITION;
            event.payload.state_transition.current = (int)m_GD->current_state;
            event.payload.state_transition.previous = (int)prev_state;
            event_manager->triggerEvent(std::make_shared<Event>(event));

            game_states[m_GD->current_state]->reset();
        }
    }


    //this will update the audio engine but give us chance to do somehting else if that isn't working
    if (!m_audioEngine->Update())
    {
        if (m_audioEngine->IsCriticalError())
        {
            // We lost the audio device!
        }
    }
    else
    {
        //update sounds playing
        for (list<Sound*>::iterator it = m_Sounds.begin(); it != m_Sounds.end(); it++)
        {
            (*it)->Tick(m_GD);
        }
    }

    ReadInput();
    //upon space bar switch camera state
    //see docs here for what's going on: https://github.com/Microsoft/DirectXTK/wiki/Keyboard
    if (m_GD->m_KBS_tracker.pressed.Space)
    {
        if (m_GD->m_GS == GS_PLAY_MAIN_CAM)
        {
            m_GD->m_GS = GS_PLAY_TPS_CAM;
        }
        else
        {
            m_GD->m_GS = GS_PLAY_MAIN_CAM;
        }
    }
}

void Game::lateUpdate(DX::StepTimer const& _timer)
{
    GameManager::get()->lateUpdate(*m_GD);
}

// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

    //set immediate context of the graphics device
    m_DD->m_pd3dImmediateContext = m_d3dContext.Get();

    //update the constant buffer for the rendering of VBGOs
    
    
    game_states[m_GD->current_state]->render3D();
    //Draw 3D Game Obejects
    

    
    
    // Draw sprite batch stuff 
    m_DD2D->m_Sprites->Begin(SpriteSortMode_Deferred, m_states->NonPremultiplied());
    game_states[m_GD->current_state]->render2D();
    m_DD2D->m_Sprites->End();
    //drawing text screws up the Depth Stencil State, this puts it back again!
    m_d3dContext->OMSetDepthStencilState(m_states->DepthDefault(), 0);

    
    Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    // Clear the views.
    m_d3dContext->ClearRenderTargetView(m_renderTargetView.Get(), Colors::CornflowerBlue);
    m_d3dContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    m_d3dContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());

    // Set the viewport.
    CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(m_outputWidth), static_cast<float>(m_outputHeight));
    m_d3dContext->RSSetViewports(1, &viewport);
}

// Presents the back buffer contents to the screen.
void Game::Present()
{
    // The first argument instructs DXGI to block until VSync, putting the application
    // to sleep until the next VSync. This ensures we don't waste any cycles rendering
    // frames that will never be displayed to the screen.
    HRESULT hr = m_swapChain->Present(1, 0);

    // If the device was reset we must completely reinitialize the renderer.
    if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
    {
        OnDeviceLost();
    }
    else
    {
        DX::ThrowIfFailed(hr);
    }
}

// Message handlers
void Game::OnActivated()
{
    m_GD->m_mouseButtons.Reset();
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
    m_GD->m_mouseButtons.Reset();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowSizeChanged(int _width, int _height)
{
    m_outputWidth = std::max(_width, 1);
    m_outputHeight = std::max(_height, 1);

    CreateResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& _width, int& _height) const noexcept
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    _width = 800;
    _height = 600;
}

// These are the resources that depend on the device.
void Game::CreateDevice()
{
    UINT creationFlags = 0;

#ifdef _DEBUG
    //creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
    //something missing on the machines in 2Q28
    //this should work!
#endif

    static const D3D_FEATURE_LEVEL featureLevels [] =
    {
        // TODO: Modify for supported Direct3D feature levels
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1,
    };

    // Create the DX11 API device object, and get a corresponding context.
    ComPtr<ID3D11Device> device;
    ComPtr<ID3D11DeviceContext> context;
    DX::ThrowIfFailed(D3D11CreateDevice(
        nullptr,                            // specify nullptr to use the default adapter
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        creationFlags,
        featureLevels,
        static_cast<UINT>(std::size(featureLevels)),
        D3D11_SDK_VERSION,
        device.ReleaseAndGetAddressOf(),    // returns the Direct3D device created
        &m_featureLevel,                    // returns feature level of device created
        context.ReleaseAndGetAddressOf()    // returns the device immediate context
        ));

#ifndef NDEBUG
    ComPtr<ID3D11Debug> d3dDebug;
    if (SUCCEEDED(device.As(&d3dDebug)))
    {
        ComPtr<ID3D11InfoQueue> d3dInfoQueue;
        if (SUCCEEDED(d3dDebug.As(&d3dInfoQueue)))
        {
#ifdef _DEBUG
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
#endif
            D3D11_MESSAGE_ID hide [] =
            {
                D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS,
                // TODO: Add more message IDs here as needed.
            };
            D3D11_INFO_QUEUE_FILTER filter = {};
            filter.DenyList.NumIDs = static_cast<UINT>(std::size(hide));
            filter.DenyList.pIDList = hide;
            d3dInfoQueue->AddStorageFilterEntries(&filter);
        }
    }
#endif

    DX::ThrowIfFailed(device.As(&m_d3dDevice));
    DX::ThrowIfFailed(context.As(&m_d3dContext));

    // TODO: Initialize device dependent objects here (independent of window size).
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateResources()
{
    // Clear the previous window size specific context.
    ID3D11RenderTargetView* nullViews [] = { nullptr };
    m_d3dContext->OMSetRenderTargets(static_cast<UINT>(std::size(nullViews)), nullViews, nullptr);
    m_renderTargetView.Reset();
    m_depthStencilView.Reset();
    m_d3dContext->Flush();

    const UINT backBufferWidth = static_cast<UINT>(m_outputWidth);
    const UINT backBufferHeight = static_cast<UINT>(m_outputHeight);
    const DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;
    const DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
    constexpr UINT backBufferCount = 2;

    // If the swap chain already exists, resize it, otherwise create one.
    if (m_swapChain)
    {
        HRESULT hr = m_swapChain->ResizeBuffers(backBufferCount, backBufferWidth, backBufferHeight, backBufferFormat, 0);

        if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
        {
            // If the device was removed for any reason, a new device and swap chain will need to be created.
            OnDeviceLost();

            // Everything is set up now. Do not continue execution of this method. OnDeviceLost will reenter this method 
            // and correctly set up the new device.
            return;
        }
        else
        {
            DX::ThrowIfFailed(hr);
        }
    }
    else
    {
        // First, retrieve the underlying DXGI Device from the D3D Device.
        ComPtr<IDXGIDevice1> dxgiDevice;
        DX::ThrowIfFailed(m_d3dDevice.As(&dxgiDevice));

        // Identify the physical adapter (GPU or card) this device is running on.
        ComPtr<IDXGIAdapter> dxgiAdapter;
        DX::ThrowIfFailed(dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf()));

        // And obtain the factory object that created it.
        ComPtr<IDXGIFactory2> dxgiFactory;
        DX::ThrowIfFailed(dxgiAdapter->GetParent(IID_PPV_ARGS(dxgiFactory.GetAddressOf())));

        // Create a descriptor for the swap chain.
        DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
        swapChainDesc.Width = backBufferWidth;
        swapChainDesc.Height = backBufferHeight;
        swapChainDesc.Format = backBufferFormat;
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.SampleDesc.Quality = 0;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.BufferCount = backBufferCount;

        DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = {};
        fsSwapChainDesc.Windowed = TRUE;

        // Create a SwapChain from a Win32 window.
        DX::ThrowIfFailed(dxgiFactory->CreateSwapChainForHwnd(
            m_d3dDevice.Get(),
            m_window,
            &swapChainDesc,
            &fsSwapChainDesc,
            nullptr,
            m_swapChain.ReleaseAndGetAddressOf()
            ));

        // This template does not support exclusive fullscreen mode and prevents DXGI from responding to the ALT+ENTER shortcut.
        DX::ThrowIfFailed(dxgiFactory->MakeWindowAssociation(m_window, DXGI_MWA_NO_ALT_ENTER));
    }

    // Obtain the backbuffer for this window which will be the final 3D rendertarget.
    ComPtr<ID3D11Texture2D> backBuffer;
    DX::ThrowIfFailed(m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf())));

    // Create a view interface on the rendertarget to use on bind.
    DX::ThrowIfFailed(m_d3dDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, m_renderTargetView.ReleaseAndGetAddressOf()));

    // Allocate a 2-D surface as the depth/stencil buffer and
    // create a DepthStencil view on this surface to use on bind.
    CD3D11_TEXTURE2D_DESC depthStencilDesc(depthBufferFormat, backBufferWidth, backBufferHeight, 1, 1, D3D11_BIND_DEPTH_STENCIL);

    ComPtr<ID3D11Texture2D> depthStencil;
    DX::ThrowIfFailed(m_d3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, depthStencil.GetAddressOf()));

    CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
    DX::ThrowIfFailed(m_d3dDevice->CreateDepthStencilView(depthStencil.Get(), &depthStencilViewDesc, m_depthStencilView.ReleaseAndGetAddressOf()));

    // TODO: Initialize windows-size dependent objects here.
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.

    m_depthStencilView.Reset();
    m_renderTargetView.Reset();
    m_swapChain.Reset();
    m_d3dContext.Reset();
    m_d3dDevice.Reset();

    CreateDevice();

    CreateResources();
}

void Game::ReadInput()
{
    m_GD->m_KBS = m_keyboard->GetState();
    m_GD->m_KBS_tracker.Update(m_GD->m_KBS);
    //quit game on hiting escape
    if (m_GD->m_KBS.Escape)
    {
        ExitGame();
    }

    // temp - kill later. 
    if (m_GD->m_KBS.N)
    {
        m_GD->current_state = State::GAME_PLAY;
        GameManager::get()->getEventManager()->addListener(&game_states[m_GD->current_state]->getCam());
    }

    m_GD->m_MS = m_mouse->GetState();
}
