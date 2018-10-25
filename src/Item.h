#ifndef ITEM_H
#define ITEM_H
#include <string>

class Item{
	
	private:
		std::string _title;
		std::string _descr;
		std::string _url;
		std::string _date;
		int _day;
		int _month;
		int _year;
		int _min;
		int _hour;
		bool _dst = true;
	public:
		std::string GetTitle();
		std::string GetDescr();
		std::string GetUrl();
		std::string GetDate();
		int GetHour();
		int GetMin();
		int GetDay();
		int GetMonth();
		int GetYear();
		void SetTitle(std::string title);
		void SetDescr(std::string descr);
		void SetUrl(std::string url);
		void SetDate(int day, int month, int year, int min, int hour);
		bool exists(std::string title);
		int count_numbers ( int num);

};

#endif