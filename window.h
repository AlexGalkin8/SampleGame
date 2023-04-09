#pragma once


class Window
{
	enum class EMode
	{
		kWindow = 0,
		kBorderless,
		kFullscreen
	};

public:
	Window();
	~Window();

	bool open();

private:
	class PlatformWindowImpl* mImpl = nullptr;
};

