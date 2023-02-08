#include "Stdafx.h"
#include "ItemSkill.h"

HRESULT ItemSkill::init(void)
{
	Json::Value root = JSONDATAMANAGER->loadJsonFile("Item.json");

	for (auto it = root["Item"].begin(); it != root["Item"].end(); it++)
	{
		if ((*it).isObject())
		{
			_itemSkill.push_back({ (*it)["Price"].asInt() });
		}
	}
	return S_OK;
}