#include <stdio.h>
#include <stdlib.h>
#include <iostream> 
#include <fstream>
#include <curl/curl.h>
#include "tinyxml.h"
#include "Item.h"
#include "feed.h"
#include <sys/stat.h>
//#include <unistd.h>
#include <string>



std::vector<Feed> fe;
void feedToXml(Feed feed);

inline bool fileExists (const std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}

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

bool itemexists(std::vector<Item> itemarr, std::string feedTitle, Item item){

	for(Feed feed : fe){

		if(feed.exists(feedTitle)){

			for(Item it : itemarr){

				if(it.exists(item.GetTitle())){

					return true;
				}
			}
		}
	}
	return false;
}

void openXml(TiXmlDocument *doc)
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
	for(Feed feed : fe){

		if(feed.exists(feedTitle)){

			itemArr = feed.GetItemArray();
			std::cout<<feedTitle<<", itemArr.size() = "<<itemArr.size()<<std::endl;
			break;
		}
	}
	
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
		if(itemexists(itemArr, feedTitle, item) == false){

				itemArr.push_back(item);
			
		}
		
	}

	Feed feedcurr(feedTitle, itemArr);
	if(fe.size() > 0){
		int count = 0;
		bool added = false;
		for(Feed feed : fe){
			//std::cout<<"feedTitle = "<<feedTitle<<std::endl;
			//std::cout<<"feed.GetName() = "<<feed.GetName()<<std::endl;

			if(feed.exists(feedTitle)){
				
				added = true;
				fe[count] = feedcurr;
				break;
				
			}
			
			count++;
		}
		if(added==false){
				fe.push_back(feedcurr);
		}
	}
	if(fe.size()==0){
		

		fe.push_back(feedcurr);
	}

}

TiXmlDocument * openXMLSafe(const char* pFilename)
{
	TiXmlDocument *doc = new TiXmlDocument(pFilename);
	bool loadOkay = doc->LoadFile();
	if (loadOkay)
	{
		//printf("\n%s:\n", pFilename);
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
		
		openXml( doc);
		
		
		id++;
		remove(std::to_string(id).c_str());
	}

	for(Feed i:fe){
		feedToXml(i);
		std::vector<Item> itemarr = i.GetItemArray();
		for(Item item : itemarr){
			//printTitles(item);
		}
	}
}

void feedToXml(Feed feed){

	TiXmlDocument doc;  
	TiXmlElement* entry;
 	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );  
	doc.LinkEndChild( decl );  
 
	TiXmlElement * root = new TiXmlElement("root");  
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

void openFeedStoreXML(std::string titlefull){
	
	size_t lastindex = titlefull.find_last_of("."); 
	std::string title = titlefull.substr(0, lastindex); 
	

	TiXmlDocument *doc = openXMLSafe(titlefull.c_str());
	

	TiXmlElement *entryC;
	TiXmlElement *entry;

	TiXmlElement *rootElem = doc->RootElement();
	TiXmlElement *entrys = rootElem->FirstChildElement("Entrys");

	entryC = entrys->FirstChildElement( "Entry" );
	entry = entrys->FirstChildElement( "Entry" );

	
	std::vector<Item> itemArr;
	
	

	while(NULL != entry){
		
		TiXmlElement *title;
		TiXmlElement *descr;
		TiXmlElement *link;
		TiXmlElement *pubdate;
		Item item;
		if(entry->FirstChildElement( "Title" )->GetText()  != NULL){
			title = entry->FirstChildElement( "Title" );
		}
		if(entry->FirstChildElement( "Description" )->GetText() != NULL){
			descr = entry->FirstChildElement( "Description" );
		}
		if(entry->FirstChildElement( "Description" )->GetText() !=NULL){
			link = entry->FirstChildElement( "URL" );
		}
		if(entry->FirstChildElement( "Date" )->GetText()  != NULL){
			pubdate = entry->FirstChildElement( "Date" );
		}

		item.SetTitle(title->GetText());

		item.SetDescr(descr->GetText());
	
		item.SetUrl(link->GetText());

		item.SetDate(pubdate->GetText());


		entry = entry->NextSiblingElement("Entry");
		itemArr.push_back(item);
	
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
	doc.SaveFile(feedListFname);  
}


void populateFeedVec(std::string feedStoreName){
	
	TiXmlDocument *doc = openXMLSafe(feedStoreName.c_str());


	TiXmlElement *entry;

	TiXmlElement *rootElem = doc->RootElement();
	TiXmlElement *entrys = rootElem->FirstChildElement("Entrys");


	entry = entrys->FirstChildElement( "Entry" );

	

	while(NULL != entry){
		TiXmlElement *filename = entry->FirstChildElement( "FileName" );
		openFeedStoreXML(filename->GetText());


		entry = entry->NextSiblingElement("Entry");
	
	}

}

int main()
{


	if(fileExists("feedStore.xml")){


		populateFeedVec("feedStore.xml");
	}

	for(Feed i:fe){
		//std::cout<<i.GetName()<<std::endl;
		std::vector<Item> itemarr = i.GetItemArray();
		for(Item item : itemarr){
			//printTitles(item);

		}
	}

	getRSS("urllist.txt");
	feedListToXML("feedStore.xml");
	std::cout<<"fe.size() = "<<fe.size()<<std::endl;
	for(Feed i:fe){
		//std::cout<<i.GetName()<<std::endl;
	}
	return 0;
}
