#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream> 
#include <curl/curl.h>
#include "tinyxml.h"
#define TIXML_USE_STL

void openXML(TiXmlDocument doc)
{
	TiXmlElement *rootElem = doc.RootElement();
	TiXmlElement *channel = rootElem->FirstChildElement( "channel" );
	TiXmlElement *item = channel->FirstChildElement( "item" );

	if(NULL != item){
		while(item){
			
			TiXmlElement *title = item->FirstChildElement( "title" );
			std::cout<<title->GetText()<<std::endl;
			item = item->NextSiblingElement("item");
		}
	}
}
void openXML(const char* pFilename)
{
	TiXmlDocument doc(pFilename);
	bool loadOkay = doc.LoadFile();
	if (loadOkay)
	{
		printf("\n%s:\n", pFilename);
		openXML( doc ); // defined later in the tutorial
	}
	else
	{
		printf("Failed to load file \"%s\"\n", pFilename);
	}
}

int main(int argc, char *argv[])
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
}
