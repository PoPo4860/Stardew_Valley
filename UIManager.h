#pragma once
#include "Config.h"

class Imgage;
struct UIImage
{
	Image* inventory;
	POINT inventoryPos;
	Image* inventorySelect;
	POINT inventorySelectPos;
};
class UIManager : public Singleton<UIManager>
{
private:
	UIImage uiImage;
	int inventorySelectNum;
public:
	UIManager();
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};

