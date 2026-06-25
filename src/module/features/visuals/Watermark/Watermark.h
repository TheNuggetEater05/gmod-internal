#pragma once

#ifndef WATERMARK_H
#define WATERMARK_H

#include <Singleton.h>

class Watermark : public Singleton<Watermark>
{
	friend class Singleton<Watermark>;
public:
	void Render();
};

#endif // !WATERMARK_H
