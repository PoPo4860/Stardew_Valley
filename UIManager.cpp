#include "UIManager.h"
#include "Config.h"
#include "Image.h"

#define SPACE 4

UIManager::UIManager()
	:uiImage{}, inventorySelectNum{0}{}
HRESULT UIManager::Init()
{
	uiImage.inventory = ImageManager::GetSingleton()->FindImage("Image/UI/Inventory.bmp", 200, 24, 1, 1);
	uiImage.inventoryPos.x = (WIN_SIZE_X / 2);
	uiImage.inventoryPos.y = WIN_SIZE_Y - (uiImage.inventory->GetFrameHeight() / 2)- SPACE;

	uiImage.inventorySelect = ImageManager::GetSingleton()->FindImage("Image/UI/InventorySelect.bmp", 16, 16, 1, 1);
	uiImage.inventorySelectPos.x = (WIN_SIZE_X / 2) + SPACE -
		(uiImage.inventory->GetFrameWidth() / 2) + (uiImage.inventorySelect->GetFrameWidth()/2);
	uiImage.inventorySelectPos.y = WIN_SIZE_Y - (uiImage.inventorySelect->GetFrameHeight() / 2) - (SPACE * 2);
	return S_OK;
}

void UIManager::Update()
{
}

void UIManager::Render(HDC hdc)
{
	uiImage.inventory->Render(hdc, 
		uiImage.inventoryPos.x, 
		uiImage.inventoryPos.y,
		0, 0);

	uiImage.inventorySelect->Render(hdc,
		uiImage.inventorySelectPos.x + (TILE_SIZE * inventorySelectNum), 
		uiImage.inventorySelectPos.y, 
		0, 0);
}

void UIManager::Release()
{
	ReleaseSingleton();
}
