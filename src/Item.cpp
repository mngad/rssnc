#include "Item.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream> 
#include <string>


std::string Item::GetTitle(){
	return _title;
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
void Item::SetTitle(std::string title){
	_title=title;
}
void Item::SetDescr(std::string descr){
	_descr=descr;
}
void Item::SetUrl(std::string url){
	_url=url;
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
	if(_dst = true){hour = hour +1;}
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