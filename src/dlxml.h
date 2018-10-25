#include <stdio.h>
#ifndef DLXML_H
#define DLXML_H
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
#include <map>

class Dlxml{


	public:
		std::vector<Feed> fe;
		int get_month_index( std::string name );
		void feedToXml(Feed feed);
		inline bool fileExists (const std::string& name);
		void printTitles(Item items);
		bool checkExists(TiXmlElement *elem);
		std::string openFirstType(TiXmlElement *rootElem);
		bool itemexists(std::vector<Item> itemarr, std::string feedTitle, Item item);
		void openXml(TiXmlDocument *doc);
		TiXmlDocument * openXMLSafe(const char* pFilename);
		void saveRssXml(char const *pagename, char const *link);
		void getRSS(std::string fname);

		void openFeedStoreXML(std::string titlefull);
		void feedListToXML(std::string feedListFname);
		void populateFeedVec(std::string feedStoreName);
		std::vector<Feed> init();
		std::vector<Feed> update();
		std::vector<Feed> getFeedVec();

};

#endif