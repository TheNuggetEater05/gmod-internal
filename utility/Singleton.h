#pragma once

#ifndef SINGLETON_H
#define SINGLETON_H

template<typename T>
class Singleton
{
public:
	static T& Get()
	{
		static T instance;
		return instance;
	}
protected:
	Singleton() = default;
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
};

#endif