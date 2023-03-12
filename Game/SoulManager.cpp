#include "pch.h"
#include "SoulManager.h"

void SoulManager::AddSoul(DirectX::SimpleMath::Vector2 location, int plane)
{
	switch (plane)
	{
		default:
			break;
	};
	m_Earth_Souls.emplace_back(new Soul);
}

void SoulManager::update()
{
	
}

void SoulManager::awake()
{
	
}
