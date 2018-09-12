#include <stdio.h>
#include <stdlib.h>
#include <iostream> 
#include <curl/curl.h>
#include "tinyxml.h"
#include "Item.h"

void printTitles(Item items){
	std::cout<<items.GetTitle()<<std::endl;
	std::cout<<items.GetUrl()<<std::endl;
	std::cout<<items.GetDate()<<std::endl;
}
bool checkExists(TiXmlElement *elem){

	if(elem != NULL){
		return true;
	}
	else{
		return false;
	}
}
void openXMLAtom(TiXmlDocument *doc)
{
	TiXmlElement *rootElem = doc->RootElement();
	TiXmlElement *entryC = rootElem->FirstChildElement( "entry" );
	TiXmlElement *entry = rootElem->FirstChildElement( "entry" );
	int numItems = 0;
	while(NULL != entryC){
		numItems++;
		entryC = entryC->NextSiblingElement("entry");

	}
	std::cout <<numItems<<std::endl;
	Item itemArr[numItems];	
	int count = 0;
	while(count<numItems){
		TiXmlElement *title = entry->FirstChildElement( "title" );
		TiXmlElement *content = entry->FirstChildElement( "content" );
		TiXmlElement *link = entry->FirstChildElement( "id" );
		TiXmlElement *date = entry->FirstChildElement( "updated" );
		if(checkExists(title)){
			itemArr[count].SetTitle(title->GetText());
		}
		if(checkExists(content)){
			itemArr[count].SetDescr(content->GetText());
		}
		if(checkExists(link)){
			itemArr[count].SetUrl(link->GetText());
		}
		if(checkExists(date)){
			itemArr[count].SetDate(date->GetText());
		}

		count++;
		entry = entry->NextSiblingElement("entry");
	
	}

	for(int a =0; a<numItems; a++)
	{
		printTitles(itemArr[a]);
	}
	std::cout<<"done"<<std::endl;
}
void openXML(TiXmlDocument *doc)
{
	TiXmlElement *rootElem = doc->RootElement();
	TiXmlElement *channel = rootElem->FirstChildElement( "channel" );
	TiXmlElement *itemC = channel->FirstChildElement( "item" );
	TiXmlElement *item = channel->FirstChildElement( "item" );
	int numItems = 0;
	while(NULL != itemC){
		numItems++;
		itemC = itemC->NextSiblingElement("item");
	}
	std::cout <<numItems<<std::endl;
	Item itemArr[numItems];	
	int count = 0;
	while(count<numItems){
		//std::cout<<item->FirstChildElement( "title" )->GetText()<<std::endl;
		itemArr[count].SetTitle(item->FirstChildElement( "title" )->GetText());
		itemArr[count].SetDescr(item->FirstChildElement( "description" )->GetText());
		itemArr[count].SetUrl(item->FirstChildElement( "link" )->GetText());
		itemArr[count].SetDate(item->FirstChildElement( "pubDate" )->GetText());
		count++;
		item = item->NextSiblingElement("item");
	
	}

	for(int a =0; a<numItems; a++)
	{
		printTitles(itemArr[a]);
	}
	std::cout<<"done"<<std::endl;
}
void openXML(const char* pFilename)
{
	TiXmlDocument doc(pFilename);
	bool loadOkay = doc.LoadFile();
	if (loadOkay)
	{
		printf("\n%s:\n", pFilename);
		openXMLAtom( &doc ); // defined later in the tutorial
	}
	else
	{
		printf("Failed to load file \"%s\"\n", pFilename);
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
		  /* write the page body to this file handle */
		  curl_easy_setopt(curl, CURLOPT_WRITEDATA, pagefile);

		  /* get it! */
		  curl_easy_perform(curl);

		  /* close the header file */
		  fclose(pagefile);
	  }
	  curl_easy_cleanup(curl);
	}

}

int main()
{
	char const *pagename = "url.txt";	
	//char const *link = "http://feeds.bbci.co.uk/news/uk/rss.xml";
	char const *link = "https://www.theverge.com/rss/index.xml";
	saveRssXml(pagename, link);
	openXML(pagename);
	return 0;
}
