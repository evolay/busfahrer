#include "HTTP.h"

using namespace TrudyTheCrawler;

bool HTTP::get(std::string url) {
	CURL *curl;
	CURLcode res;

	curl = curl_easy_init();
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &HTTP::function_pt);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &output);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
		res = curl_easy_perform(curl);

		/* always cleanup */
		curl_easy_cleanup(curl);
	}

	return true;
}

void HTTP::function_pt(void *ptr, size_t size, size_t nmemb, void *stream){
	((std::string*)stream)->append((char *)ptr);
}

std::string HTTP::getOutput() {
	return output;
}
