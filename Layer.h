#pragma once

class Level;

class Layer
{
public:
	virtual ~Layer() {}

	virtual void Update(Level* level_) = 0;
	virtual void Render() = 0;
};