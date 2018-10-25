#include "feed.h"
#include "Item.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream> 
#include <string>
#include <algorithm>

Feed::Feed(std::vector<Item> itemArr){
	_itemArr=itemArr;
}
Feed::Feed(std::string name, std::vector<Item> itemArr){
	_name=name;
	_itemArr=itemArr;
}
std::string Feed::GetName(){
	return _name;
}
std::string Feed::GetUrl(){
	return _url;
}
void Feed::SetName(std::string name){
	_name = name;
}
void Feed::SetUrl(std::string url){
	_url = url;
}
Item Feed::GetItem(int entry){
	return _itemArr[entry];
}
std::vector<Item> Feed::GetItemArray(){
	return _itemArr;
}
void Feed::SetItem(int entry, Item item){
	_itemArr[entry]=item;
}
void Feed::SetItemArray(std::vector<Item> itemVec){
	_itemArr = itemVec;
}
bool Feed::exists(std::string name){
	if(_name==name){ return true;}
	else{return false;}

}
bool Feed::wayToSortH(Item i, Item j) { return i.GetHour() > j.GetHour(); }
bool Feed::wayToSortM(Item i, Item j) { return i.GetMin() > j.GetMin(); }
bool Feed::wayToSortD(Item i, Item j) { return i.GetDay() > j.GetDay(); }
bool Feed::wayToSortMo(Item i, Item j) { return i.GetMonth() > j.GetMonth(); }
bool Feed::wayToSortY(Item i, Item j) { return i.GetYear() > j.GetYear(); }

void Feed::SortDate(){

	std::sort(_itemArr.begin(), _itemArr.end(), wayToSortY);
	std::sort(_itemArr.begin(), _itemArr.end(), wayToSortMo);
	std::sort(_itemArr.begin(), _itemArr.end(), wayToSortD);
	std::sort(_itemArr.begin(), _itemArr.end(), wayToSortH);
	std::sort(_itemArr.begin(), _itemArr.end(), wayToSortM);
}
