#include "HTTP.h"
#include <sstream>

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
		std::cout << "ERRORCODE: "<<res<<std::endl;
		long http_code = 0;
		curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);

		/* always cleanup */
		curl_easy_cleanup(curl);

		if(http_code/100 == 2)
			return true;
	}

	return false;
}


size_t HTTP::function_pt(void *ptr, size_t size, size_t nmemb, void *stream)
{
	std::ostringstream oss;
	oss << (char*)ptr;

	((std::string*)stream)->append(oss.str());

	return size*nmemb;
}

std::string HTTP::getOutput() {
	return output;
}

