#include <stdio.h>
#include <stdlib.h>
#include <iostream> 
#include <curl/curl.h>
#include "tinyxml.h"
#include "Item.h"

void printTitles(Item items){
	std::cout<<items.GetUrl()<<std::endl;
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
		std::cout<<a<<std::endl;
		printTitles(itemArr[a]);
		std::cout<<a<<std::endl;
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
		openXML( &doc ); // defined later in the tutorial
	}
	else
	{
		printf("Failed to load file \"%s\"\n", pFilename);
	}


}


int main()
{
	CURL *curl = curl_easy_init();
	char const *pagename = "url.xml";
	FILE *pagefile;
	if(curl) {
	  curl_easy_setopt(curl, CURLOPT_URL, "http://feeds.bbci.co.uk/news/uk/rss.xml");
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
	
	openXML(pagename);
	return 0;
}
