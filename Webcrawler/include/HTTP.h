#pragma once
#define CURL_STATICLIB

#include <string>
#include <iostream>
#include <curl/curl.h>

namespace RudyTheCrawler
{

	class HTTP
	{	
	
		public:
			bool get(std::string url);
			std::string getOutput(); 
		private:
			std::string output;
			static size_t function_pt(void *ptr, size_t size, size_t nmemb, void *stream);
	};

};
