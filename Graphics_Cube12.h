/*===================================================================================
*	Date : 2022/10/14(Thurs)
*		Author	: Gakuto.S
*		File	: Graphics_Cube12.h
*		Detail	:
===================================================================================*/
#pragma once
#include "Graphics_DirectX12.h"

class GraphicsCube12
{
public:
	//---------------------------------------------
	/// �R���X�g���N�^ 
	/// 
	/// \return	none
	//---------------------------------------------
	GraphicsCube12();

	//---------------------------------------------
	/// ���������� 
	/// 
	/// \return	none
	//---------------------------------------------
	void Init();

	//---------------------------------------------
	/// �I������ 
	/// 
	/// \return	none
	//---------------------------------------------
	void Uninit();

	//---------------------------------------------
	/// �`�揈�� 
	/// 
	/// \return	none
	//---------------------------------------------
	void Draw(float x, float y, float z);

private:
	//--------------------------------------------------------------------------
	Microsoft::WRL::ComPtr<ID3D12Resource>			m_vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D12Resource>			m_textureBuffer;
	Microsoft::WRL::ComPtr<ID3D12Resource>			m_worldMatrixBuffer;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	m_textureHeap;
	//--------------------------------------------------------------------------

	/// <summary>
	/// ID3D12Resource			m_vertexBuffer;			// ���_�o�b�t�@
	/// ID3D12Resource			m_textureBuffer;		// �e�N�X�`�����\�[�X
	/// ID3D12Resource			m_worldMatrixBuffer;	// �萔�o�b�t�@
	/// ID3D12DescriptorHeap	m_textureHeap;			// �e�N�X�`���̃q�[�v
	/// </summary>

	//--------------------------------------------------------------------------
	DirectX::XMFLOAT3 m_translate;
	DirectX::XMFLOAT3 m_rotate;
	DirectX::XMFLOAT3 m_scale;
	//--------------------------------------------------------------------------

	/// <summary>
	/// DirectX::XMFLOAT3 m_translate;	// ���s�ړ�
	/// DirectX::XMFLOAT3 m_rotate;		// ��]
	/// DirectX::XMFLOAT3 m_scale;		// �X�P�[�����O
	/// </summary>
};

