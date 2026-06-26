#pragma once

#ifndef VISUALS_H
#define VISUALS_H

#include <Singleton.h>

class Visuals : public Singleton<Visuals>
{
	friend class Singleton<Visuals>;
public:
	void Init();
	void Render();
};

#endif // !VISUALS_H
