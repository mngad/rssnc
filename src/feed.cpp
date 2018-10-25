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

bool Feed::wayToSort(Item i, Item j) { 
	int datei = i.GetYear()*1000000 + i.GetMonth() *1000000 + i.GetDay()* 10000 +i.GetHour() *100 + i.GetMin();
	int datej = j.GetYear()*1000000 + j.GetMonth() *1000000 + j.GetDay()* 10000 +j.GetHour() *100 + j.GetMin();
	if(datei>datej){
		return true;
	} 
	else{return false;}
}

void Feed::SortDate(){

	std::sort(_itemArr.begin(), _itemArr.end(), wayToSort);

}
