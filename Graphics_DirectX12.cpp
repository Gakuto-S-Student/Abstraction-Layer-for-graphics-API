/*===================================================================================
*	Date : 2022/10/13(Thurs)
*		Author	: Gakuto.S
*		File	: Graphics_DirectX12.cpp
*		Detail	:
===================================================================================*/
#include <vector>
#include "Application.h"

#include "Graphics_DirectX12.h"
using namespace DirectX;
using namespace Microsoft::WRL;

/* Initialize */
bool GraphicsDirectX12::Init(Application* app)
{
	int width = app->GetWidth();
	int height = app->GetHeight();

	if (!this->CreateDeviceAndSwapChain(width, height, (HWND)app->GetHandle()))
		return false;

	if (!this->CreateRenderTargetView())
		return false;

	if (!this->CreateDepthBuffer(width, height))
		return false;

	if (!this->CreateFence())
		return false;

	this->SetViewport(width, height);
	this->SetScissorRect(width, height);

	return true;
}

/* Uninitialize */
void GraphicsDirectX12::Uninit()
{
}

/* Clear screen */
void GraphicsDirectX12::Clear()
{
	// Get currently buffer index
	UINT index = m_swapChain->GetCurrentBackBufferIndex();
	this->SetResourceBarrier(
		index,
		D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_PRESENT,		
		D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_RENDER_TARGET	// 今からレンダーターゲットとして使用
	);

	// Set render target
	D3D12_CPU_DESCRIPTOR_HANDLE renderTargetHeapHandle = m_renderTargetViewHeap->GetCPUDescriptorHandleForHeapStart();
	renderTargetHeapHandle.ptr += index * m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	D3D12_CPU_DESCRIPTOR_HANDLE depthBufferHeapHandle = m_depthBufferHeap->GetCPUDescriptorHandleForHeapStart();
	m_commandList->OMSetRenderTargets(1, &renderTargetHeapHandle, false, &depthBufferHeapHandle);

	float clearColor[]{ 0.0f, 0.5f, 0.0f, 1.0f };
	m_commandList->ClearRenderTargetView(renderTargetHeapHandle, clearColor, 0, nullptr);	// Clear render target view command
	m_commandList->ClearDepthStencilView(													// Clear depth buffer command
		m_depthBufferHeap->GetCPUDescriptorHandleForHeapStart(),
		D3D12_CLEAR_FLAGS::D3D12_CLEAR_FLAG_DEPTH,
		D3D12_MAX_DEPTH,
		0,
		0,
		nullptr
	);

	m_commandList->RSSetViewports(1, &m_viewport);
	m_commandList->RSSetScissorRects(1, &m_scissorRect);
}

/* Present buffer */
void GraphicsDirectX12::Present()
{
	// Get currently buffer index
	UINT index = m_swapChain->GetCurrentBackBufferIndex();

	this->SetResourceBarrier(
		index,
		D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_RENDER_TARGET,
		D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_PRESENT
	);

	// Close command list
	m_commandList->Close();

	// Execute command list
	std::vector<ID3D12CommandList*> commandLists{ m_commandList.Get() };
	m_commandQueue->ExecuteCommandLists(commandLists.size(), &commandLists[0]);

	// Wait
	m_commandQueue->Signal(m_fence.Get(), ++m_fenceValue);

	if (m_fence->GetCompletedValue() != m_fenceValue)
	{
		HANDLE fenceEvent = CreateEvent(nullptr, false, false, nullptr);
		if (fenceEvent)
		{
			m_fence->SetEventOnCompletion(m_fenceValue, fenceEvent);
			WaitForSingleObject(fenceEvent, INFINITE);
			CloseHandle(fenceEvent);
		}
	}

	// Reset
	m_commandAllocator->Reset();
	m_commandList->Reset(m_commandAllocator.Get(), nullptr);

	// Flip
	m_swapChain->Present(1, 0);
}

// Create device and swapchain
bool GraphicsDirectX12::CreateDeviceAndSwapChain(const int width, const int height, const HWND hWnd)
{
	HRESULT ret{};

	// Create device
	ret = D3D12CreateDevice(
		nullptr,
		D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_12_0,
		__uuidof(ID3D12Device),
		(void**)m_device.GetAddressOf()
	);
	if (FAILED(ret))
		return false;

	// Create command allocator
	ret = m_device->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT,
		__uuidof(ID3D12CommandAllocator),
		(void**)m_commandAllocator.GetAddressOf()
	);
	if (FAILED(ret))
		return false;

	// Create command list
	ret = m_device->CreateCommandList(
		0,
		D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT,
		m_commandAllocator.Get(),
		nullptr,
		__uuidof(ID3D12GraphicsCommandList),
		(void**)m_commandList.GetAddressOf()
	);
	if (FAILED(ret))
		return false;

	// Create command queue
	D3D12_COMMAND_QUEUE_DESC queueDesc{};
	queueDesc.Flags		= D3D12_COMMAND_QUEUE_FLAGS::D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.NodeMask	= 0;
	queueDesc.Priority	= D3D12_COMMAND_QUEUE_PRIORITY::D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	queueDesc.Type		= D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT;
	ret = m_device->CreateCommandQueue(
		&queueDesc,
		__uuidof(ID3D12CommandQueue),
		(void**)m_commandQueue.GetAddressOf()
	);
	if (FAILED(ret))
		return false;

	// Create factory
	ComPtr<IDXGIFactory6> factory{};
	ret = CreateDXGIFactory2(
		0,
		__uuidof(IDXGIFactory6),
		(void**)factory.GetAddressOf()
	);
	if (FAILED(ret) || !factory)
		return false;


	// Create swap chain
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	swapChainDesc.Width					= width;
	swapChainDesc.Height				= height;
	swapChainDesc.Format				= DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDesc.Stereo				= false;
	swapChainDesc.SampleDesc.Count		= 1;
	swapChainDesc.SampleDesc.Quality	= 0;
	swapChainDesc.BufferUsage			= DXGI_USAGE_BACK_BUFFER;
	swapChainDesc.BufferCount			= k_backBufferNum;
	swapChainDesc.Scaling				=	DXGI_SCALING::DXGI_SCALING_STRETCH;
	swapChainDesc.SwapEffect			= DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.AlphaMode				= DXGI_ALPHA_MODE::DXGI_ALPHA_MODE_UNSPECIFIED;
	swapChainDesc.Flags					= DXGI_SWAP_CHAIN_FLAG::DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	ret = factory->CreateSwapChainForHwnd(
		m_commandQueue.Get(),
		hWnd,
		&swapChainDesc,
		nullptr,
		nullptr,
		(IDXGISwapChain1**)m_swapChain.GetAddressOf()
	);
	if (FAILED(ret) || !m_swapChain)
		return false;

	return true;	// Success
}

// Create render target view
bool GraphicsDirectX12::CreateRenderTargetView()
{
    HRESULT ret{};

	// Create render target view heap
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};
	heapDesc.Type			= D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	heapDesc.NodeMask		= 0;
	heapDesc.NumDescriptors = k_backBufferNum;
	heapDesc.Flags			= D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	ret = m_device->CreateDescriptorHeap(&heapDesc, __uuidof(ID3D12DescriptorHeap), (void**)m_renderTargetViewHeap.GetAddressOf());
	if (FAILED(ret))
		return false;

	DXGI_SWAP_CHAIN_DESC swapChainDesc{};
	ret = m_swapChain->GetDesc(&swapChainDesc);
	if (FAILED(ret))
		return false;

	D3D12_CPU_DESCRIPTOR_HANDLE handle = m_renderTargetViewHeap->GetCPUDescriptorHandleForHeapStart();	// heap address
	for (UINT i = 0; i < k_backBufferNum; ++i)
	{// Create back buffers
		ret = m_swapChain->GetBuffer(i, __uuidof(ID3D12Resource), (void**)m_backBuffers[i].GetAddressOf());
		if (FAILED(ret))
			return false;

		m_device->CreateRenderTargetView(m_backBuffers[i].Get(), nullptr, handle);
		handle.ptr += m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_RTV);	// RTV1つ分のサイズ分をインクリメント
	}

	return true;	// Success
}

// Create depth buffer
bool GraphicsDirectX12::CreateDepthBuffer(const int width, const int height)
{
	HRESULT ret{};
	D3D12_RESOURCE_DESC resourceDesc{};
	resourceDesc.Dimension			= D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	resourceDesc.Width				= width;
	resourceDesc.Height				= height;
	resourceDesc.DepthOrArraySize	= 1;
	resourceDesc.Format				= DXGI_FORMAT::DXGI_FORMAT_D32_FLOAT;
	resourceDesc.SampleDesc.Count	= 1;
	resourceDesc.Flags				= D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
	resourceDesc.MipLevels			= 1;
	resourceDesc.Layout				= D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_UNKNOWN;
	resourceDesc.Alignment			= 0;

	D3D12_HEAP_PROPERTIES heapProperties{};
	heapProperties.Type					= D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_DEFAULT;
	heapProperties.CPUPageProperty		= D3D12_CPU_PAGE_PROPERTY::D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL::D3D12_MEMORY_POOL_UNKNOWN;

	// Crear value
	D3D12_CLEAR_VALUE clearValue{};
	clearValue.DepthStencil.Depth	= D3D12_MAX_DEPTH;
	clearValue.Format				= DXGI_FORMAT::DXGI_FORMAT_D32_FLOAT;

	ret = m_device->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAGS::D3D12_HEAP_FLAG_NONE,
		&resourceDesc,
		D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&clearValue,
		__uuidof(ID3D12Resource),
		(void**)m_depthBuffer.GetAddressOf()
	);
	if (FAILED(ret))
		return false;

	// Create heap
	D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc{};
	descriptorHeapDesc.Type				= D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	descriptorHeapDesc.NumDescriptors	= 1;
	ret = m_device->CreateDescriptorHeap(
		&descriptorHeapDesc,
		__uuidof(ID3D12DescriptorHeap),
		(void**)m_depthBufferHeap.GetAddressOf()
	);
	if (FAILED(ret))
		return false;

	// Create depth stencil view
	D3D12_DEPTH_STENCIL_VIEW_DESC viewDesc{};
	viewDesc.Format			= DXGI_FORMAT::DXGI_FORMAT_D32_FLOAT;
	viewDesc.ViewDimension	= D3D12_DSV_DIMENSION::D3D12_DSV_DIMENSION_TEXTURE2D;
	viewDesc.Flags			= D3D12_DSV_FLAGS::D3D12_DSV_FLAG_NONE;
	m_device->CreateDepthStencilView(m_depthBuffer.Get(), &viewDesc, m_depthBufferHeap->GetCPUDescriptorHandleForHeapStart());

	return true;	// Success
}

// Create fence
bool GraphicsDirectX12::CreateFence()
{
	HRESULT ret{};
	ret = m_device->CreateFence(
		m_fenceValue,
		D3D12_FENCE_FLAGS::D3D12_FENCE_FLAG_NONE,
		__uuidof(ID3D12Fence),
		(void**)m_fence.GetAddressOf()
	);
	if (FAILED(ret))
		return false;

	return true;
}

// Resource barrier setting
void GraphicsDirectX12::SetResourceBarrier(const UINT index, D3D12_RESOURCE_STATES before, D3D12_RESOURCE_STATES after)
{
	D3D12_RESOURCE_BARRIER barrierDesc{};
	barrierDesc.Type					= D3D12_RESOURCE_BARRIER_TYPE::D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrierDesc.Flags					= D3D12_RESOURCE_BARRIER_FLAGS::D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrierDesc.Transition.pResource	= m_backBuffers[index].Get();
	barrierDesc.Transition.Subresource	= D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	barrierDesc.Transition.StateBefore	= before;
	barrierDesc.Transition.StateAfter	= after;
	m_commandList->ResourceBarrier(1, &barrierDesc);
}

// Set viewport
void GraphicsDirectX12::SetViewport(const int width, const int height)
{
	m_viewport.Width		= FLOAT(width);
	m_viewport.Height		= FLOAT(height);
	m_viewport.MaxDepth		= D3D12_MAX_DEPTH;
}

// Set scissor rect
void GraphicsDirectX12::SetScissorRect(const int width, const int height)
{
	m_scissorRect.left		= 0;
	m_scissorRect.top		= 0;
	m_scissorRect.right		= m_scissorRect.left + width;
	m_scissorRect.bottom	= m_scissorRect.top + height;
}
