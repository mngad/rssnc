#include "Item.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream> 
#include <string>
#include <curl/curl.h>


std::string Item::GetTitle(){
	return _title;
}
std::string Item::GetFeedTitle(){
	return _feedtitle;
}
std::string Item::GetDescr(){
	return _descr;
}
std::string Item::GetUrl(){
	return _url;
}
std::string Item::GetDate(){
	return _date;
}
int Item::GetHour(){return _hour;}
int Item::GetMin(){return _min;}
int Item::GetDay(){return _day;}
int Item::GetMonth(){return _month;}
int Item::GetYear(){return _year;}
void Item::SetFeedTitle(std::string feedtitle){
	_feedtitle=feedtitle;
	//std::cout<<"hey"<<_feedtitle<<std::endl;
}
void Item::SetTitle(std::string title){
	_title=title;
}
void Item::SetDescr(std::string descr){
	_descr=descr;
}
void Item::SetUrl(std::string url){
	// if(url.length()>50){
	// 	_url=UrlShort(url);
	// }
	// else{
		_url = url;
	// }
}
int Item::count_numbers ( int num) {
   int count =0;
   if(num==0){return 1;}
   while (num !=0) {   
      count++;  
      num/=10;
   } 
   return count;
}
void Item::SetDate(int min, int hour, int day, int month, int year){

	_day=day;
	_month=month;
	_year=year;
	_min=min;
	_hour=hour;

	std::string mins;
	if(count_numbers(min)==1){
		mins = "0"+std::to_string(min);
	}
	else{
		mins = std::to_string(min);
	}
	std::string hours;
	if(count_numbers(hour)==1){
		hours = "0"+std::to_string(hour);
	}
	else{
		hours = std::to_string(hour);
	}
	_date=hours+":"+
		mins+" "+
		std::to_string(day)+"/"+
		std::to_string(month)+"/"+
		std::to_string(year);
}
bool Item::exists(std::string title){
	if(_title == title){return true;}
	else{return false;}
}

std::string Item::UrlShort(std::string url){

	curl_global_init(CURL_GLOBAL_ALL);

    CURL* easyhandle = curl_easy_init();
    std::string readBuffer;

    curl_easy_setopt(easyhandle, CURLOPT_URL, "https://is.gd/create.php\\?format\\=simple\\&url\\=" + url);
    //curl_easy_setopt(easyhandle, CURLOPT_VERBOSE, 1L);

    curl_easy_setopt(easyhandle, CURLOPT_WRITEDATA, &readBuffer);

    curl_easy_perform(easyhandle);

    std::cout << readBuffer << std::endl;

    return readBuffer;
}