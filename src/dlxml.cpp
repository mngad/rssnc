#include <stdio.h>
#include <stdlib.h>
#include <iostream> 
#include <fstream>
#include <curl/curl.h>
#include "tinyxml.h"
#include "Item.h"
#include "feed.h"

void printTitles(Item items){
	std::cout<<items.GetTitle()<<std::endl;
	std::cout<<items.GetUrl()<<"\n"<<std::endl;

	// std::cout<<items.GetDate()<<std::endl;

}
bool checkExists(TiXmlElement *elem){

	if(elem != NULL){
		return true;
	}
	else{
		return false;
	}
}

std::string openFirstType(TiXmlElement *rootElem){
	
	if(NULL != rootElem->FirstChildElement( "entry" )){
		return "entry";
	}
	else{
		return "item";
	}
}
Feed openXml(TiXmlDocument *doc)
{
	TiXmlElement *entryC;
	TiXmlElement *entry;
	TiXmlElement *rootElem = doc->RootElement();
	std::string firstType = openFirstType(rootElem);
	if(firstType == "entry"){
		entryC = rootElem->FirstChildElement( firstType.c_str() );
		entry = rootElem->FirstChildElement( firstType.c_str() );
	}
	if(firstType == "item"){
		TiXmlElement *channel = rootElem->FirstChildElement( "channel" );
		entryC = channel->FirstChildElement( firstType.c_str() );
		entry = channel->FirstChildElement( firstType.c_str() );
	}

	int numItems = 0;
	while(NULL != entryC){
		numItems++;
		entryC = entryC->NextSiblingElement(firstType.c_str());

	}
	std::vector<Item> itemArr(numItems);
	
	
	int count = 0;
	while(count<numItems){
		TiXmlElement *title = entry->FirstChildElement( "title" );
		TiXmlElement *content = entry->FirstChildElement( "content" );
		TiXmlElement *id = entry->FirstChildElement( "id" );
		TiXmlElement *date = entry->FirstChildElement( "updated" );
		TiXmlElement *descr = entry->FirstChildElement( "description" );
		TiXmlElement *link = entry->FirstChildElement( "link" );
		TiXmlElement *pubdate = entry->FirstChildElement( "pubDate" );

		if(checkExists(title)){
			itemArr[count].SetTitle(title->GetText());
		}
		if(checkExists(content)){
			itemArr[count].SetDescr(content->GetText());
		}
		else if(checkExists(descr)){
			itemArr[count].SetDescr(descr->GetText());
		}
		if(checkExists(id)){
			itemArr[count].SetUrl(id->GetText());
		}
		else if(checkExists(link)){
			itemArr[count].SetUrl(link->GetText());
		}
		if(checkExists(date)){
			itemArr[count].SetDate(date->GetText());
		}
		else if(checkExists(pubdate)){
			itemArr[count].SetDate(pubdate->GetText());
		}

		count++;
		entry = entry->NextSiblingElement(firstType.c_str());
	
	}


	Feed feed(itemArr);
	return feed;

}

TiXmlDocument openXMLSafe(const char* pFilename)
{
	TiXmlDocument doc(pFilename);
	bool loadOkay = doc.LoadFile();
	if (loadOkay)
	{
		printf("\n%s:\n", pFilename);
		return doc;
		//doc.Clear();
	}
	else
	{
		printf("Failed to load file \"%s\"\n", pFilename);
		exit (EXIT_FAILURE);
	}


}

void saveRssXml(char const *pagename, char const *link)
{

	CURL *curl = curl_easy_init();
	
	FILE *pagefile;
	if(curl) {
	  curl_easy_setopt(curl, CURLOPT_URL, link);
	  curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
	  pagefile = fopen(pagename, "wb");
	  if(pagefile) {
		  curl_easy_setopt(curl, CURLOPT_WRITEDATA, pagefile);

		  curl_easy_perform(curl);

		  fclose(pagefile);
	  }
	  curl_easy_cleanup(curl);
	}

}

void getRSS(std::string fname){

 	std::vector<Feed> fe;
	std::ifstream file(fname);
	std::string content;
	int id =0;
	while(file >> content) {
		saveRssXml(std::to_string(id).c_str(), content.c_str());
		TiXmlDocument doc =  openXMLSafe(std::to_string(id).c_str());
		fe.push_back(openXml( &doc));
		id++;
	}

	for(Feed i:fe){
		std::vector<Item> itemarr = i.GetItemArray();
		for(Item item : itemarr){
			printTitles(item);
		}
	}
}

int main()
{
	getRSS("urllist.txt");
	
	return 0;
}
