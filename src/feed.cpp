#include "feed.h"
#include "Item.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream> 
#include <string>

Feed::Feed(std::string name, std::string url, std::vector<Item> itemArr){
	_name=name;
	_url=url;
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