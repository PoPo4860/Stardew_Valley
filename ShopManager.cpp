#pragma warning(disable : 4996)
#include "ShopManager.h"
#include "ItemCode.h"
#include "Image.h"
#include "CommonFunction.h"
#include<string>

#define PORTRAIT_POS POINTFLOAT{ 76,68 }

void ShopManager::ActiveShop(string shopTypeString)
{
	if (shopTypeString == "BlackSmith")
	{
		shopType = ShopType::BlackSmith;
		isActive = true;
	}

}

ShopManager::ShopManager()
	:isActive{ false }, shopImage{}, salesListStartNum{ 0 }{};

void ShopManager::Init()
{
	shopImage.main = ImageManager::GetSingleton()->FindImage("Image/Shop/Shop_Main.bmp", 356, 178, 1, 1);
	shopImage.mainPos = POINTFLOAT{ (WIN_SIZE_X / 2) ,(WIN_SIZE_Y / 2)};
	SetRect(&shopImage.mainRect, shopImage.mainPos, shopImage.main->GetWidth(), shopImage.main->GetHeight());

	shopImage.up = ImageManager::GetSingleton()->FindImage("Image/Shop/Shop_ArrowUp.bmp", 10, 11, 1, 1);
	shopImage.upPos = POINTFLOAT{ (WIN_SIZE_X / 2) + 185 ,(WIN_SIZE_Y / 2) - 70 };
	SetRect(&shopImage.upRect, shopImage.upPos, shopImage.up->GetWidth(), shopImage.up->GetHeight());

	shopImage.down = ImageManager::GetSingleton()->FindImage("Image/Shop/Shop_ArrowDown.bmp", 10, 11, 1, 1);
	shopImage.downPos = POINTFLOAT{ (WIN_SIZE_X / 2) + 185 ,(WIN_SIZE_Y / 2) + 15 };
	SetRect(&shopImage.downRect, shopImage.downPos, shopImage.down->GetWidth(), shopImage.down->GetHeight());

	shopImage.cancel = ImageManager::GetSingleton()->FindImage("Image/Shop/Shop_Cancel.bmp", 11, 11, 1, 1);
	shopImage.cancelPos = POINTFLOAT{ (WIN_SIZE_X / 2) + 184 ,(WIN_SIZE_Y / 2) - 85 };
	SetRect(&shopImage.cancelRect, shopImage.cancelPos, shopImage.cancel->GetWidth(), shopImage.cancel->GetHeight());

	blackSmith.masterName = "클린트";
	blackSmith.portrait = ImageManager::GetSingleton()->FindImage("Image/Shop/Shop_Portrait_Smith.bmp", 66, 66, 1, 1);
	blackSmith.portraitPos = PORTRAIT_POS;
	blackSmith.salesList = new int[5];
	blackSmith.salesListMaxNum = 5;
	blackSmith.salesList[0] = STONE;
	blackSmith.salesList[1] = COAL;
	blackSmith.salesList[2] = COPPER;
	blackSmith.salesList[3] = STEEL;
	blackSmith.salesList[4] = GOLD;
	shopType = ShopType::None;

	coinImage = ImageManager::GetSingleton()->FindImage("Image/Shop/Shop_Coin.bmp", 11, 11, 1, 1);
}

bool ShopManager::Update()
{
	if (isActive == false) return false;

	switch (shopType)
	{
	case ShopType::BlackSmith:
		break;
	}

	if (Input::GetButtonDown(VK_LBUTTON) && PtInRect(&(shopImage.upRect), GetMousePoint()))
	{	// 위에버튼
		if (salesListStartNum != 0)
		{
			--salesListStartNum;
		}
	}
	if (Input::GetButtonDown(VK_LBUTTON) && PtInRect(&(shopImage.downRect), GetMousePoint()))
	{	// 아래버튼
		if (salesListStartNum + 4 < blackSmith.salesListMaxNum)
		{
			++salesListStartNum;
		}

	}
	if (Input::GetButtonDown(VK_LBUTTON) && PtInRect(&(shopImage.cancelRect), GetMousePoint()))
	{	// 취소버튼
		isActive = false;
	}




	return true;
}

void ShopManager::Render(HDC hdc)
{
	if (isActive == false) return;
	shopImage.main->Render(hdc, shopImage.mainPos.x, shopImage.mainPos.y, 0, 0);
	shopImage.up->Render(hdc, shopImage.upPos.x, shopImage.upPos.y, 0, 0);
	shopImage.down->Render(hdc, shopImage.downPos.x, shopImage.downPos.y, 0, 0);
	shopImage.cancel->Render(hdc, shopImage.cancelPos.x, shopImage.cancelPos.y, 0, 0);

	blackSmith.portrait->Render(hdc, blackSmith.portraitPos.x, blackSmith.portraitPos.y,0,0);

	int money = GAMEDATA_MANAGER->GetPlayerMoney();
	if (money != 0)
	{
		for (int i = 0; money > 0; ++i)
		{
			int number = (int)(money % 10);
			money = (int)(money / 10);
			char num_char[1 + sizeof(char)];
			sprintf_s(num_char, "%d", number);
			PrintText(hdc, num_char, 169 - (i * 6), 150);
		}
	}
	else
	{
		char num_char[1 + sizeof(char)];
		sprintf_s(num_char, "%d", 0);
		PrintText(hdc, num_char, 169 , 150);
	}
	for (int i = 0; i < 4; ++i)
	{
		// 아이템 출력
		ITEM_MANAGER->ItemRender(hdc, blackSmith.salesList[i + salesListStartNum], 138, 49 + (26 * i));

		// 아이템 이름 출력
		const ResourceItemInfo* item = ITEM_MANAGER->GetResourceItem(blackSmith.salesList[i + salesListStartNum]);
		char num_char[256];
		strcpy(num_char, item->name.c_str());
		PrintText(hdc, num_char, 150, 41 + (26.5f * i), 16);


		// 아이템 가격 출력
		
		int money = item->gold;
		for (int j = 0; money > 0; ++j)
		{
			int number = (int)(money % 10);
			money = (int)(money / 10);
			char num_char[1 + sizeof(char)];
			sprintf_s(num_char, "%d", number);
			PrintText(hdc, num_char, 350 - (j * 10), 41+ (27 * i),13);
		}
		
		// 코인 출력
		coinImage->Render(hdc, 365, 43 + (26 * i));
	}


	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 12; ++x)
		{
			int itemCode = INVEN_MANAGER->GetInventoryItemCode(x, y);
			INVEN_MANAGER->RenderItem(hdc, POINT{ x,y }, POINT{ 196 + (x * 16), 161 + y + (y * 16) });
		}
	}
}

void ShopManager::Release()
{
	delete[] blackSmith.salesList;
	blackSmith.salesList = nullptr;
	ReleaseSingleton();
}
