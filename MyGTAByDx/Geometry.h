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



	template<class VertexType= VertexPosNormalTex>
	MeshData<VertexType> CreateCylinderNoCap(float radius = 1.0f, float height = 2.0f, UINT slices = 20,
		const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f }) {
		using namespace DirectX;

		MeshData<VertexType> meshData;
		UINT vertexCount = 2 * (slices + 1);
		UINT indexCount = 6 * slices;
		meshData.vertexVector.resize(vertexCount);
		meshData.indexVector.resize(indexCount);

		float h2 = height / 2;
		float theta = 0.0f;
		float per_theta = XM_2PI / slices;

		Internal::VertexData vertexData;

		// ������涥�˵�
		for (UINT i = 0; i <= slices; ++i)
		{
			theta = i * per_theta;
			vertexData = { XMFLOAT3(radius * cosf(theta), h2, radius * sinf(theta)), XMFLOAT3(cosf(theta), 0.0f, sinf(theta)),
				XMFLOAT4(-sinf(theta), 0.0f, cosf(theta), 1.0f), color, XMFLOAT2(theta / XM_2PI, 0.0f) };
			Internal::InsertVertexElement(meshData.vertexVector[i], vertexData);
		}

		// �������׶˵�
		for (UINT i = 0; i <= slices; ++i)
		{
			theta = i * per_theta;
			vertexData = { XMFLOAT3(radius * cosf(theta), -h2, radius * sinf(theta)), XMFLOAT3(cosf(theta), 0.0f, sinf(theta)),
				XMFLOAT4(-sinf(theta), 0.0f, cosf(theta), 1.0f), color, XMFLOAT2(theta / XM_2PI, 1.0f) };
			UINT vIndex = (slices + 1) + i;
			Internal::InsertVertexElement(meshData.vertexVector[vIndex], vertexData);
		}

		// ��������
		UINT iIndex = 0;

		for (UINT i = 0; i < slices; ++i)
		{
			meshData.indexVector[iIndex++] = i;
			meshData.indexVector[iIndex++] = i + 1;
			meshData.indexVector[iIndex++] = (slices + 1) + i + 1;

			meshData.indexVector[iIndex++] = (slices + 1) + i + 1;
			meshData.indexVector[iIndex++] = (slices + 1) + i;
			meshData.indexVector[iIndex++] = i;
		}


		return meshData;
	}




	template<class VertexType = VertexPosNormalTex>
	MeshData<VertexType> CreateCylinder(float radius=2.0f, float height=2.0f, UINT slices=20, const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f })
	{
		using namespace DirectX;

		auto meshData = CreateCylinderNoCap<VertexType>(radius, height, slices, color);
		UINT vertexCount = 4 * (slices + 1) + 2;
		UINT indexCount = 12 * slices;
		meshData.vertexVector.resize(vertexCount);
		meshData.indexVector.resize(indexCount);

		float h2 = height / 2;
		float theta = 0.0f;
		float per_theta = XM_2PI / slices;

		WORD vIndex = 2 * (slices + 1), iIndex = 6 * slices;
		WORD offset = 2 * (slices + 1);
		Internal::VertexData vertexData;

		// ���붥��Բ��
		vertexData = { XMFLOAT3(0.0f, h2, 0.0f), XMFLOAT3(0.0f, 1.0f, 0.0f),
					  XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(0.5f, 0.5f) };
		Internal::InsertVertexElement(meshData.vertexVector[vIndex++], vertexData);

		// ���붥��Բ�ϸ���
		for (UINT i = 0; i <= slices; ++i)
		{
			theta = i * per_theta;
			vertexData = { XMFLOAT3(radius * cosf(theta), h2, radius * sinf(theta)), XMFLOAT3(0.0f, 1.0f, 0.0f),
						  XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(cosf(theta) / 2 + 0.5f, sinf(theta) / 2 + 0.5f) };
			Internal::InsertVertexElement(meshData.vertexVector[vIndex++], vertexData);
		}

		// ����׶�Բ��
		vertexData = { XMFLOAT3(0.0f, -h2, 0.0f), XMFLOAT3(0.0f, -1.0f, 0.0f),
					  XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(0.5f, 0.5f) };
		Internal::InsertVertexElement(meshData.vertexVector[vIndex++], vertexData);

		// ����ײ�Բ�ϸ���
		for (UINT i = 0; i <= slices; ++i)
		{
			theta = i * per_theta;
			vertexData = { XMFLOAT3(radius * cosf(theta), -h2, radius * sinf(theta)), XMFLOAT3(0.0f, -1.0f, 0.0f),
						  XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f), color, XMFLOAT2(cosf(theta) / 2 + 0.5f, sinf(theta) / 2 + 0.5f) };
			Internal::InsertVertexElement(meshData.vertexVector[vIndex++], vertexData);
		}



		// �𽥷��붥������������
		for (UINT i = 1; i <= slices; ++i)
		{
			meshData.indexVector[iIndex++] = offset;
			meshData.indexVector[iIndex++] = offset + i % (slices + 1) + 1;
			meshData.indexVector[iIndex++] = offset + i;
		}

		// �𽥷���ײ�����������
		offset += slices + 2;
		for (UINT i = 1; i <= slices; ++i)
		{
			meshData.indexVector[iIndex++] = offset;
			meshData.indexVector[iIndex++] = offset + i;
			meshData.indexVector[iIndex++] = offset + i % (slices + 1) + 1;
		}

		return meshData;
	}

}