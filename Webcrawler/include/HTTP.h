#pragma once
#include <string>
#include <iostream>
#include <curl/curl.h>

namespace TrudyTheCrawler
{

	class HTTP
	{
		public:
			bool get(std::string url);
			std::string getOutput(); 
		private:
			std::string output;
			static void function_pt(void *ptr, size_t size, size_t nmemb, void *stream);
	};

};
