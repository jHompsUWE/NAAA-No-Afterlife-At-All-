// #pragma once
// #include "fbxsdk.h"
// #include <stdio.h>
// #include <windows.h>
// #include <iostream>
// #include <vector>
// #include <tchar.h>
//
// struct MyVertex
// {
// 	float pos[3];
// };
//
// FbxManager* g_pFbxSdkManager = nullptr;
//
// class MyClass
// {
// public:
// 	MyClass();
// 	~MyClass();
//
// 	static HRESULT LoadFBX(std::vector<MyVertex>* pOutVertexVector)
// 	{
// 		if (g_pFbxSdkManager == nullptr)
// 		{
// 			g_pFbxSdkManager = FbxManager::Create();
//
// 			FbxIOSettings* pIOsettings = FbxIOSettings::Create(g_pFbxSdkManager, IOSROOT);
// 			g_pFbxSdkManager->SetIOSettings(pIOsettings);
//
// 		}
//
// 		FbxImporter* pImporter = FbxImporter::Create(g_pFbxSdkManager, "");
// 		FbxScene* pFbxSence = FbxScene::Create(g_pFbxSdkManager, "");
//
// 		bool bSuccess = pImporter->Initialize("F:\\Games Technology\\Second Year\\Game Engine Programming\\NAAA-No-Afterlife-At-All-\\Models\\Tile\\TileFBX.fbx", -1, g_pFbxSdkManager->GetIOSettings());
// 		if (!bSuccess) return E_FAIL;
//
// 		bSuccess = pImporter->Import(pFbxSence);
// 		if (!bSuccess) return  E_FAIL;
//
// 		pImporter->Destroy();
//
//
// 		FbxNode* pFbxRootNode = pFbxSence->GetRootNode();
// 		if (pFbxRootNode)
// 		{
// 			for (int i = 0; i < pFbxRootNode->GetChildCount(); i++)
// 			{
// 				FbxNode* pFbxChildNode = pFbxRootNode->GetChild(i);
//
// 				if (pFbxChildNode->GetNodeAttribute() == NULL) continue;
//
// 				FbxNodeAttribute::EType AttributeType = pFbxChildNode->GetNodeAttribute()->GetAttributeType();
//
// 				if (AttributeType != FbxNodeAttribute::eMesh) continue;
//
// 				FbxMesh* pMesh = (FbxMesh*) pFbxChildNode->GetNodeAttribute();
//
// 				FbxVector4* pVertices = pMesh->GetControlPoints();
//
// 				for (int j = 0; j < pMesh->GetPolygonCount(); j++)
// 				{
// 					int iNumVertices = pMesh->GetPolygonSize(j);
// 					assert( iNumVertices == 3 );
//
// 					for (int k = 0; k < iNumVertices; k++)             {                int iControlPointIndex = pMesh->GetPolygonVertex(j, k);
//
// 						MyVertex vertex;
// 						vertex.pos[0] = (float)pVertices[iControlPointIndex].mData[0];
// 						vertex.pos[1] = (float)pVertices[iControlPointIndex].mData[1];
// 						vertex.pos[2] = (float)pVertices[iControlPointIndex].mData[2];
// 						pOutVertexVector->push_back( vertex );
// 					}
// 				}
// 				
// 			}
// 		}		
// 		return S_OK;
// 	}
// };
//
