#include <stdio.h>
#include <stdlib.h>
#include <iostream> 
#include <fstream>
#include <curl/curl.h>
#include "tinyxml.h"
#include "Item.h"
#include "feed.h"


std::vector<Feed> fe;
void feedToXml(Feed feed);

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
	std::string feedTitle;
	std::string firstType = openFirstType(rootElem);
	if(firstType == "entry"){
		entryC = rootElem->FirstChildElement( firstType.c_str() );
		entry = rootElem->FirstChildElement( firstType.c_str() );
		feedTitle = rootElem->FirstChildElement( "title")->GetText();

	}
	if(firstType == "item"){
		TiXmlElement *channel = rootElem->FirstChildElement( "channel" );
		entryC = channel->FirstChildElement( firstType.c_str() );
		entry = channel->FirstChildElement( firstType.c_str() );
		feedTitle = channel->FirstChildElement( "title" )->GetText();

	}

	
	std::vector<Item> itemArr;
	
	
	int count = 0;
	while(NULL != entry){
		Item item;
		TiXmlElement *title = entry->FirstChildElement( "title" );
		TiXmlElement *content = entry->FirstChildElement( "content" );
		TiXmlElement *id = entry->FirstChildElement( "id" );
		TiXmlElement *date = entry->FirstChildElement( "updated" );
		TiXmlElement *descr = entry->FirstChildElement( "description" );
		TiXmlElement *link = entry->FirstChildElement( "link" );
		TiXmlElement *pubdate = entry->FirstChildElement( "pubDate" );

		if(checkExists(title)){
			item.SetTitle(title->GetText());
		}
		if(checkExists(content)){
			item.SetDescr(content->GetText());
		}
		else if(checkExists(descr)){
			item.SetDescr(descr->GetText());
		}
		if(checkExists(id)){
			item.SetUrl(id->GetText());
		}
		else if(checkExists(link)){
			item.SetUrl(link->GetText());
		}
		if(checkExists(date)){
			item.SetDate(date->GetText());
		}
		else if(checkExists(pubdate)){
			item.SetDate(pubdate->GetText());
		}

		
		entry = entry->NextSiblingElement(firstType.c_str());
		itemArr.push_back(item);
	}


	Feed feed(feedTitle, itemArr);
	return feed;

}

TiXmlDocument * openXMLSafe(const char* pFilename)
{
	TiXmlDocument *doc = new TiXmlDocument(pFilename);
	bool loadOkay = doc->LoadFile();
	if (loadOkay)
	{
		printf("\n%s:\n", pFilename);
		return doc;
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

 	
	std::ifstream file(fname);
	std::string content;
	int id =0;
	while(file >> content) {
		saveRssXml(std::to_string(id).c_str(), content.c_str());
		TiXmlDocument *doc =  openXMLSafe(std::to_string(id).c_str());
		fe.push_back(openXml( doc));
		id++;
		remove(std::to_string(id).c_str());
	}

	for(Feed i:fe){
		feedToXml(i);
		std::vector<Item> itemarr = i.GetItemArray();
		for(Item item : itemarr){
			printTitles(item);
		}
	}
}

void feedToXml(Feed feed){

	TiXmlDocument doc;  
	TiXmlElement* entry;
 	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );  
	doc.LinkEndChild( decl );  
 
	TiXmlElement * root = new TiXmlElement( feed.GetName().c_str() );  
	doc.LinkEndChild( root );  

	TiXmlElement * entrys = new TiXmlElement( "Entrys" );  
	root->LinkEndChild( entrys );  
	std::vector<Item> itemarr = feed.GetItemArray();

	TiXmlElement * title;
	TiXmlElement * descr;
	TiXmlElement * url;
	TiXmlElement * date;

	for(Item item : itemarr){

		entry = new TiXmlElement( "Entry" );  
		entrys->LinkEndChild( entry );

		title = new TiXmlElement( "Title" );
		entry->LinkEndChild(title);
		title->LinkEndChild(new TiXmlText(item.GetTitle()));

		descr = new TiXmlElement( "Description" );
		entry->LinkEndChild(descr);
		descr->LinkEndChild(new TiXmlText(item.GetDescr().c_str()));

		url = new TiXmlElement( "URL" );
		entry->LinkEndChild(url);
		url->LinkEndChild(new TiXmlText(item.GetUrl().c_str()));

		date = new TiXmlElement( "Date" );
		entry->LinkEndChild(date);
		date->LinkEndChild(new TiXmlText(item.GetDate().c_str()));

	}
	doc.SaveFile( feed.GetName() + ".xml" );  
}

void openFeedStoreXML(std::string title){

	title = title + ".xml";
	TiXmlDocument *doc = openXMLSafe(title.c_str());

	TiXmlElement *entryC;
	TiXmlElement *entry;

	TiXmlElement *rootElem = doc->RootElement();
	TiXmlElement *entrys = rootElem->FirstChildElement("Entrys");

	entryC = entrys->FirstChildElement( "Entry" );
	entry = entrys->FirstChildElement( "Entry" );

	int numItems = 0;
	while(NULL != entryC){
		numItems++;
		entryC = entryC->NextSiblingElement("Entry");

	}
	std::vector<Item> itemArr(numItems);
	
	
	int count = 0;
	while(count<numItems){
		TiXmlElement *title = entry->FirstChildElement( "Title" );
		TiXmlElement *descr = entry->FirstChildElement( "Description" );
		TiXmlElement *link = entry->FirstChildElement( "URL" );
		TiXmlElement *pubdate = entry->FirstChildElement( "Date" );

		itemArr[count].SetTitle(title->GetText());

		itemArr[count].SetDescr(descr->GetText());
	
		itemArr[count].SetUrl(link->GetText());

		itemArr[count].SetDate(pubdate->GetText());

		count++;
		entry = entry->NextSiblingElement("Entry");
	
	}

	Feed feed(title, itemArr);
	fe.push_back(feed);

}

void feedListToXML(std::string feedListFname){

	TiXmlDocument doc;  
	TiXmlElement* entry;
 	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );  
	doc.LinkEndChild( decl );  
 
	TiXmlElement * root = new TiXmlElement( feedListFname);  
	doc.LinkEndChild( root );  

	TiXmlElement * entrys = new TiXmlElement( "Entrys" );  
	root->LinkEndChild( entrys );  

	TiXmlElement * filename;

	for(Feed feed : fe){

		entry = new TiXmlElement( "Entry" );  
		entrys->LinkEndChild( entry );

		filename = new TiXmlElement( "FileName" );
		entry->LinkEndChild(filename);
		filename->LinkEndChild(new TiXmlText(feed.GetName() + ".xml"));

	}
	doc.SaveFile(feedListFname );  
}


void populateFeedVec(std::string urllist){

	std::ifstream file(urllist);
	std::string content;
	int id =0;
	while(file >> content) {
		saveRssXml(std::to_string(id).c_str(), content.c_str());
		TiXmlDocument *doc =  openXMLSafe(std::to_string(id).c_str());
		fe.push_back(openXml( doc));
		id++;
		remove(std::to_string(id).c_str());
	}

}

int main()
{
	getRSS("urllist.txt");
	feedListToXML("feedStore.xml");
	
	return 0;
}
