#include "DXUtil.h"

HRESULT CreateShaderFromFile(const WCHAR* csoFileNameInOut, const WCHAR* hlslFileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;

	// Ѱ���Ƿ����Ѿ�����õĶ�����ɫ��
	if (csoFileNameInOut && D3DReadFileToBlob(csoFileNameInOut, ppBlobOut) == S_OK)
	{
		return hr;
	}
	else
	{
		DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
		// ���� D3DCOMPILE_DEBUG ��־���ڻ�ȡ��ɫ��������Ϣ���ñ�־���������������飬
		// ����Ȼ������ɫ�������Ż�����
		dwShaderFlags |= D3DCOMPILE_DEBUG;

		// ��Debug�����½����Ż��Ա������һЩ����������
		dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
		ID3DBlob* errorBlob = nullptr;
		hr = D3DCompileFromFile(hlslFileName, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint, shaderModel,
			dwShaderFlags, 0, ppBlobOut, &errorBlob);
		if (FAILED(hr))
		{
			if (errorBlob != nullptr)
			{
				OutputDebugStringA(reinterpret_cast<const char*>(errorBlob->GetBufferPointer()));
			}
			SAFE_RELEASE(errorBlob);
			return hr;
		}

		// ��ָ��������ļ���������ɫ����������Ϣ���
		if (csoFileNameInOut)
		{
			return D3DWriteBlobToFile(*ppBlobOut, csoFileNameInOut, FALSE);
		}
	}

	return hr;
}

HRESULT CreateWICTexture2DCubeFromFile(ID3D11Device* d3dDevice, ID3D11DeviceContext* d3dDeviceContext, const std::wstring& cubeMapFileName, ID3D11Texture2D** textureArray, ID3D11ShaderResourceView** textureCubeView, bool generateMips)
{
	{
		using namespace DirectX;
		// ����豸���豸�������Ƿ�ǿ�
		// ���������������������ͼֻҪ������һ���ǿռ���
		if (!d3dDevice || !d3dDeviceContext || !(textureArray || textureCubeView))
			return E_INVALIDARG;

		// ******************
		// ��ȡ��պ�����
		//

		ID3D11Texture2D* srcTex = nullptr;
		ID3D11ShaderResourceView* srcTexSRV = nullptr;

		// ����Դ����GPU����
		HRESULT hResult = CreateWICTextureFromFile(d3dDevice,
			(generateMips ? d3dDeviceContext : nullptr),
			cubeMapFileName.c_str(),
			(ID3D11Resource**)&srcTex,
			(generateMips ? &srcTexSRV : nullptr));

		// �ļ�δ��
		if (FAILED(hResult))
		{
			return hResult;
		}

		D3D11_TEXTURE2D_DESC texDesc, texArrayDesc;
		srcTex->GetDesc(&texDesc);

		// Ҫ���߱�4:3
		if (texDesc.Width * 3 != texDesc.Height * 4)
		{
			SAFE_RELEASE(srcTex);
			SAFE_RELEASE(srcTexSRV);
			return E_FAIL;
		}

		// ******************
		// ��������6�����������
		//

		UINT squareLength = texDesc.Width / 4;
		texArrayDesc.Width = squareLength;
		texArrayDesc.Height = squareLength;
		texArrayDesc.MipLevels = (generateMips ? texDesc.MipLevels - 2 : 1);	// �������mip�ȼ�������λͼ����2
		texArrayDesc.ArraySize = 6;
		texArrayDesc.Format = texDesc.Format;
		texArrayDesc.SampleDesc.Count = 1;
		texArrayDesc.SampleDesc.Quality = 0;
		texArrayDesc.Usage = D3D11_USAGE_DEFAULT;
		texArrayDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		texArrayDesc.CPUAccessFlags = 0;
		texArrayDesc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;	// ������д���TextureCube

		ID3D11Texture2D* texArray = nullptr;
		hResult = d3dDevice->CreateTexture2D(&texArrayDesc, nullptr, &texArray);
		if (FAILED(hResult))
		{
			SAFE_RELEASE(srcTex);
			SAFE_RELEASE(srcTexSRV);
			return hResult;
		}

		// ******************
		// ѡȡԭ��պ������6�������������򣬿�������������
		//

		D3D11_BOX box;
		// box����������: 
		//    front
		//   / 
		//  /_____right
		//  |
		//  |
		//  bottom
		box.front = 0;
		box.back = 1;

		for (UINT i = 0; i < texArrayDesc.MipLevels; ++i)
		{
			// +X�濽��
			box.left = squareLength * 2;
			box.top = squareLength;
			box.right = squareLength * 3;
			box.bottom = squareLength * 2;
			d3dDeviceContext->CopySubresourceRegion(
				texArray,
				D3D11CalcSubresource(i, D3D11_TEXTURECUBE_FACE_POSITIVE_X, texArrayDesc.MipLevels),
				0, 0, 0,
				srcTex,
				i,
				&box);

			// -X�濽��
			box.left = 0;
			box.top = squareLength;
			box.right = squareLength;
			box.bottom = squareLength * 2;
			d3dDeviceContext->CopySubresourceRegion(
				texArray,
				D3D11CalcSubresource(i, D3D11_TEXTURECUBE_FACE_NEGATIVE_X, texArrayDesc.MipLevels),
				0, 0, 0,
				srcTex,
				i,
				&box);

			// +Y�濽��
			box.left = squareLength;
			box.top = 0;
			box.right = squareLength * 2;
			box.bottom = squareLength;
			d3dDeviceContext->CopySubresourceRegion(
				texArray,
				D3D11CalcSubresource(i, D3D11_TEXTURECUBE_FACE_POSITIVE_Y, texArrayDesc.MipLevels),
				0, 0, 0,
				srcTex,
				i,
				&box);


			// -Y�濽��
			box.left = squareLength;
			box.top = squareLength * 2;
			box.right = squareLength * 2;
			box.bottom = squareLength * 3;
			d3dDeviceContext->CopySubresourceRegion(
				texArray,
				D3D11CalcSubresource(i, D3D11_TEXTURECUBE_FACE_NEGATIVE_Y, texArrayDesc.MipLevels),
				0, 0, 0,
				srcTex,
				i,
				&box);

			// +Z�濽��
			box.left = squareLength;
			box.top = squareLength;
			box.right = squareLength * 2;
			box.bottom = squareLength * 2;
			d3dDeviceContext->CopySubresourceRegion(
				texArray,
				D3D11CalcSubresource(i, D3D11_TEXTURECUBE_FACE_POSITIVE_Z, texArrayDesc.MipLevels),
				0, 0, 0,
				srcTex,
				i,
				&box);

			// -Z�濽��
			box.left = squareLength * 3;
			box.top = squareLength;
			box.right = squareLength * 4;
			box.bottom = squareLength * 2;
			d3dDeviceContext->CopySubresourceRegion(
				texArray,
				D3D11CalcSubresource(i, D3D11_TEXTURECUBE_FACE_NEGATIVE_Z, texArrayDesc.MipLevels),
				0, 0, 0,
				srcTex,
				i,
				&box);

			// ��һ��mipLevel�������߶���ԭ����1/2
			squareLength /= 2;
		}


		// ******************
		// ���������������SRV
		//
		if (textureCubeView)
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc;
			viewDesc.Format = texArrayDesc.Format;
			viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
			viewDesc.TextureCube.MostDetailedMip = 0;
			viewDesc.TextureCube.MipLevels = texArrayDesc.MipLevels;

			hResult = d3dDevice->CreateShaderResourceView(texArray, &viewDesc, textureCubeView);
		}

		// ����Ƿ���Ҫ��������
		if (textureArray)
		{
			*textureArray = texArray;
		}
		else
		{
			SAFE_RELEASE(texArray);
		}

		SAFE_RELEASE(srcTex);
		SAFE_RELEASE(srcTexSRV);

		return hResult;
	}






}

