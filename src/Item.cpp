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
void Item::SetTitle(std::string title){
	_title=title;
}
void Item::SetDescr(std::string descr){
	_descr=descr;
}
void Item::SetUrl(std::string url){
	_url=url;
}
void Item::SetDate(std::string date){
	_date=date;
}
