#pragma once

class Level;

class Layer
{
public:

	virtual void Update(Level* level_) = 0;
	virtual void Render() = 0;

protected:

	virtual ~Layer() {}
};