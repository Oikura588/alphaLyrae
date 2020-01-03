#include "World.h"
#include <iostream>
World::World()
{
    std::cout << "World Construstor!\n";
}

World::~World()
{
}

void World::BeginPlay()
{
    for (auto a : Actors) {
        a->BeginPlay();
	}
}

void World::AddActor(Actor& InActor)
{
    Actors.push_back(&InActor);
}

void World::RemoveActor(int ActorIndex)
{
}
