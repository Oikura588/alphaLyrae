#pragma once
#include "DXUtil.h"
#include <vector>
#include <string>
#include <map>
#include "VertexTypes.h"

namespace Geometry {
	// ���������˳��


	namespace Internal {
		//���л��õ�����Ϣ
		struct VertexData
		{
			DirectX::XMFLOAT3 pos;
			DirectX::XMFLOAT3 normal;
			DirectX::XMFLOAT4 tangent;
			DirectX::XMFLOAT4 color;
			DirectX::XMFLOAT2 tex;
		};
		template<class VertexType>
		inline void InsertVertexElement(VertexType& vertexDst, const VertexData& vertexSrc) {
			using namespace std;
			static string semanticName;
			//��Ӧ��ϵ
			static const std::map<std::string, std::pair<size_t, size_t>> semanticSizeMap = {
				{"POSITION", std::pair<size_t, size_t>(0, 12)},
				{"NORMAL", std::pair<size_t, size_t>(12, 24)},
				{"TANGENT", std::pair<size_t, size_t>(24, 40)},
				{"COLOR", std::pair<size_t, size_t>(40, 56)},
				{"TEXCOORD", std::pair<size_t, size_t>(56, 64)}
			};

			//ȷ��������ֽ�ƫ����
			//��ΪVertexType�а������벼����Ϣ,���Ը���
			for (size_t i = 0; i < ARRAYSIZE(VertexType::inputLayout); ++i) {
				semanticName = VertexType::inputLayout[i].SemanticName;
				const auto& range= semanticSizeMap.at(semanticName);
				memcpy_s(
					reinterpret_cast<char *>(&vertexDst)+ VertexType::inputLayout[i].AlignedByteOffset,
					range.second-range.first,
					reinterpret_cast<const char*>(&vertexSrc) + range.first,
					range.second - range.first
				);

			}


		}


	}


	template<class VertexType=VertexPosNormalTex>
	struct MeshData {
		std::vector<VertexType> vertexVector;  // ��������
		std::vector<WORD> indexVector;    // ��������
	};


	template<class VertexType = VertexPosNormalTex>
	MeshData<VertexType> CreateCube(float width = 2.0f, float height = 2.0f, float depth = 2.0f, const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f }) {
		using namespace DirectX;

		MeshData<VertexType> meshData;
		//Cube��Ϊ����normal��ͬ��ԭ����Ҫ3*8��
		//֮ǰ�����������ַ�ʽ��������
		meshData.vertexVector.resize(24);

		Internal::VertexData vertexDataArr[24];
		float w2 = width / 2.f, h2 = height / 2.f, d2 = depth / 2.f;

		//������������ֵ


		// ����(+X��)
		vertexDataArr[0].pos = XMFLOAT3(w2, -h2, -d2);
		vertexDataArr[1].pos = XMFLOAT3(w2, h2, -d2);
		vertexDataArr[2].pos = XMFLOAT3(w2, h2, d2);
		vertexDataArr[3].pos = XMFLOAT3(w2, -h2, d2);
		// ����(-X��)
		vertexDataArr[4].pos = XMFLOAT3(-w2, -h2, d2);
		vertexDataArr[5].pos = XMFLOAT3(-w2, h2, d2);
		vertexDataArr[6].pos = XMFLOAT3(-w2, h2, -d2);
		vertexDataArr[7].pos = XMFLOAT3(-w2, -h2, -d2);
		// ����(+Y��)
		vertexDataArr[8].pos = XMFLOAT3(-w2, h2, -d2);
		vertexDataArr[9].pos = XMFLOAT3(-w2, h2, d2);
		vertexDataArr[10].pos = XMFLOAT3(w2, h2, d2);
		vertexDataArr[11].pos = XMFLOAT3(w2, h2, -d2);
		// ����(-Y��)
		vertexDataArr[12].pos = XMFLOAT3(w2, -h2, -d2);
		vertexDataArr[13].pos = XMFLOAT3(w2, -h2, d2);
		vertexDataArr[14].pos = XMFLOAT3(-w2, -h2, d2);
		vertexDataArr[15].pos = XMFLOAT3(-w2, -h2, -d2);
		// ����(+Z��)
		vertexDataArr[16].pos = XMFLOAT3(w2, -h2, d2);
		vertexDataArr[17].pos = XMFLOAT3(w2, h2, d2);
		vertexDataArr[18].pos = XMFLOAT3(-w2, h2, d2);
		vertexDataArr[19].pos = XMFLOAT3(-w2, -h2, d2);
		// ����(-Z��)
		vertexDataArr[20].pos = XMFLOAT3(-w2, -h2, -d2);
		vertexDataArr[21].pos = XMFLOAT3(-w2, h2, -d2);
		vertexDataArr[22].pos = XMFLOAT3(w2, h2, -d2);
		vertexDataArr[23].pos = XMFLOAT3(w2, -h2, -d2);

		for (UINT i = 0; i < 4; ++i)
		{
			// ����(+X��)
			vertexDataArr[i].normal = XMFLOAT3(1.0f, 0.0f, 0.0f);
			vertexDataArr[i].tangent = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
			vertexDataArr[i].color = color;
			// ����(-X��)
			vertexDataArr[i + 4].normal = XMFLOAT3(-1.0f, 0.0f, 0.0f);
			vertexDataArr[i + 4].tangent = XMFLOAT4(0.0f, 0.0f, -1.0f, 1.0f);
			vertexDataArr[i + 4].color = color;
			// ����(+Y��)
			vertexDataArr[i + 8].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
			vertexDataArr[i + 8].tangent = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
			vertexDataArr[i + 8].color = color;
			// ����(-Y��)
			vertexDataArr[i + 12].normal = XMFLOAT3(0.0f, -1.0f, 0.0f);
			vertexDataArr[i + 12].tangent = XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f);
			vertexDataArr[i + 12].color = color;
			// ����(+Z��)
			vertexDataArr[i + 16].normal = XMFLOAT3(0.0f, 0.0f, 1.0f);
			vertexDataArr[i + 16].tangent = XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f);
			vertexDataArr[i + 16].color = color;
			// ����(-Z��)
			vertexDataArr[i + 20].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
			vertexDataArr[i + 20].tangent = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
			vertexDataArr[i + 20].color = color;
		}

		//����
		for (UINT i = 0; i < 6; ++i)
		{
			vertexDataArr[i * 4].tex = XMFLOAT2(0.0f, 1.0f);
			vertexDataArr[i * 4 + 1].tex = XMFLOAT2(0.0f, 0.0f);
			vertexDataArr[i * 4 + 2].tex = XMFLOAT2(1.0f, 0.0f);
			vertexDataArr[i * 4 + 3].tex = XMFLOAT2(1.0f, 1.0f);
		}

		//��������浽meshData.vertexVec��
		for (UINT i = 0; i < 24; ++i)
		{
			Internal::InsertVertexElement(meshData.vertexVector[i], vertexDataArr[i]);
		}

		meshData.indexVector = {
	   0, 1, 2, 2, 3, 0,       // ����(+X��)
	   4, 5, 6, 6, 7, 4,       // ����(-X��)
	   8, 9, 10, 10, 11, 8,    // ����(+Y��)
	   12, 13, 14, 14, 15, 12, // ����(-Y��)
	   16, 17, 18, 18, 19, 16, // ����(+Z��)
	   20, 21, 22, 22, 23, 20  // ����(-Z��)
		};


		return meshData;
	}








}