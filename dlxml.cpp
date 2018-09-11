#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream> 
#include <curl/curl.h>
 
static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
	size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
	return written;
}
 
int main(int argc, char *argv[])
{
	CURL *curl = curl_easy_init();
	if(curl) {
	  CURLcode res;
	  curl_easy_setopt(curl, CURLOPT_URL, "http://feeds.bbci.co.uk/news/uk/rss.xml");
	  res = curl_easy_perform(curl);
	  std::cout<<res<<std::endl;
	  curl_easy_cleanup(curl);
	}

}
