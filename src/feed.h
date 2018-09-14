#ifndef FEED_H
#define FEED_H
#include <string>
#include <vector>
#include "Item.h"

class Feed{
	
	private:
		std::string _name;
		std::string _url;
		std::vector<Item> _itemArr;
		
	public:
		Feed(std::vector<Item> itemArr);
		Feed(std::string name, std::vector<Item> itemArr);
		std::string GetName();
		std::string GetUrl();
		Item  GetItem(int entry);
		std::vector<Item>  GetItemArray();

		void SetItem(int entry, Item item);
		void SetItemArray(std::vector<Item> item);
		void SetName(std::string name);
		void SetUrl(std::string url);
		bool exists(std::string name);


};

#endif