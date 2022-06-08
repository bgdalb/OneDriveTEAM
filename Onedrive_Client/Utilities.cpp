#include "Utilites.h"
#include <iostream>

std::string removelast(std::string path)
{
	int lastpos = 0;
	for (int i = 0; i < path.size(); i++)
	{
		if (path[i] == '/' || path[i] == '\\')
		{
			lastpos = i;
		}
	}
	path = path.substr(0, lastpos);
	return path;
}

std::string correctslashes(std::string path)
{
	for (int i = 0; i < path.length(); i++)
	{
		if (path[i] == '\\') path[i] = '/';
	}
	return path;
}

QString correctslashes(QString path)
{
	for (int i = 0; i < path.length(); i++)
	{
		if (path[i] == '\\') path[i] = '/';
	}
	return path;
}

