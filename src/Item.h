#ifndef ITEM_H
#define ITEM_H
#include <string>

class Item{
	
	private:
		std::string _title;
		std::string _descr;
		std::string _url;
		std::string _date;
	public:
		std::string GetTitle();
		std::string GetDescr();
		std::string GetUrl();
		std::string GetDate();
		void SetTitle(std::string title);
		void SetDescr(std::string descr);
		void SetUrl(std::string url);
		void SetDate(std::string date);
		bool exists(std::string title);
};

#endif