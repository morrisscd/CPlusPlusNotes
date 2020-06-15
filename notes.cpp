// CPlusPlusNotes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "winerror.h"
#include "notes.h"
#include "string"
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams
using namespace web::json;


#include "cpprest/containerstream.h"
#include "cpprest/filestream.h"
#include "cpprest/http_client.h"
#include "cpprest/json.h"
#include "cpprest/producerconsumerstream.h"
#include <iostream>
#include <sstream>

using namespace ::pplx;
using namespace utility;
using namespace concurrency::streams;

using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace web::json;


int main()
{
    //std::cout << "Hello World!\n";

    // Success codes
    // #define S_OK        ((HRESULT)0L)
    // #define S_FALSE     ((HRESULT)1L)
    // std::cout << ((HRESULT)0L) << std::endl; // equates to 0
    // std::cout << ((HRESULT)1L) << std::endl; // equates to 1
	GetURL();

	//json::value obj;
	//obj[L"key1"] = json::value::boolean(false);
	//obj[L"key2"] = json::value::number(44);
	//obj[L"key3"] = json::value::number(43.6);
	//obj[L"key4"] = json::value::string(U("str"));

	//
	//auto temp3 = obj.at(L"key2").as_number().to_int32();
	//auto temp4 = obj[L"key2"];
	//
	//// Note the "as_object()" method calls
	//for (auto iter = obj.as_object().cbegin(); iter != obj.as_object().cend(); ++iter)
	//{
	//	// This change lets you get the string straight up from "first"
	//	const utility::string_t& str = iter->first;
	//	const json::value& v = iter->second;
	//	auto temp = v.as_bool();

	//	const int temp2 = 1;
	//}
   
}



void GetURL() {

	//auto fileStream = std::make_shared<ostream>();
	// Open stream to output file.
	//pplx::task<void> requestTask = fstream::open_ostream(U("results.html")).then([=](ostream outFile)
	//{
		//*fileStream = outFile;

	http_client client(U("http://api.weatherunlocked.com/"));

	// Build request URI and start the request.
	// uri_builder builder(U("/search"));
	uri_builder builder(U("api/current/uk.s38br?app_id=5036d233&app_key=f30c86d947e8980722c6c385ec86021e"));
	// builder.append_query(U("q"), U("cpprestsdk github"));
	http_request request(methods::GET);
	request.headers().set_content_type(L"application/json");
	request.set_request_uri(builder.to_string());
	
	client.request(request)
		.then([](http_response response) -> pplx::task<json::value>
	{
		return response.extract_json();
	})
		.then([](pplx::task<json::value> previousTask)
	{
		try
		{
			json::value const & value = previousTask.get();
			//object test = value.as_object();

			auto temperature = value.as_object().at(L"temp_c").as_number().to_int32();

			int test1 = 1;
			
			//DisplayJSONValue(value);
		}
		catch (http_exception const& e)
		{
			std::wcout << e.what() << std::endl;
		}
	}).wait();
	
}

//void DisplayJSONValue(json::value v)
//{
//	if (!v.is_null())
//	{
//		// Loop over each element in the object
//		for (auto iter = v.as_object().cbegin(); iter != v.as_object().cend(); ++iter)
//		{
//			// It is necessary to make sure that you get the value as const reference
//			// in order to avoid copying the whole JSON value recursively (too expensive for nested objects)
//			/*const json::value& key = iter->first;
//			const json::value& value = iter->second;*/
//			const utility::string_t& str = iter->first;
//			const json::value& value = iter->second;
//
//			if (value.is_object() || value.is_array())
//			{
//				// We have an object with children or an array
//				if ((!str.is_null()) && (key.is_string()))
//				{
//					std::wcout << L"Parent: " << key.as_string() << std::endl;
//				}
//				// Loop over each element in the object by calling DisplayJSONValue
//				DisplayJSONValue(value);
//				if ((!key.is_null()) && (key.is_string()))
//				{
//					std::wcout << L"End of Parent: " << key.as_string() << std::endl;
//				}
//			}
//			else
//			{
//				// Always display the value as a string
//				std::wcout << L"Key: " << key.as_string() << L", Value: " << value.to_string() << std::endl;
//			}
//		}
//	}
//}


//int GetURL() {
//
//	auto fileStream = std::make_shared<ostream>();
//	// Open stream to output file.
//	pplx::task<void> requestTask = fstream::open_ostream(U("results.html")).then([=](ostream outFile)
//	{
//		*fileStream = outFile;
//
//		http_client client(U("http://api.weatherunlocked.com/"));
//
//		// Build request URI and start the request.
//		// uri_builder builder(U("/search"));
//		uri_builder builder(U("api/current/uk.s38br?app_id=5036d233&app_key=f30c86d947e8980722c6c385ec86021e"));
//		// builder.append_query(U("q"), U("cpprestsdk github"));
//
//		return client.request(methods::GET, builder.to_string());
//
//	})
//
//		.then([=](http_response response)
//	{
//		printf("Received response status code:%u\n", response.status_code());
//
//		// Write response body into the file.
//		 //return response.body().read_to_end(fileStream->streambuf());
//		// Write response to a variable
//		return response.extract_string();
//		//textString = L"hello";//response.extract_string();
//		// return textString;
//	})
//
//		// Close the file stream.
//		.then([=](size_t)
//	{
//		return fileStream->close();
//	});
//
//	// Wait for all the outstanding I/O to complete and handle any exceptions
//	try
//	{
//		requestTask.wait();
//	}
//	catch (const std::exception& e)
//	{
//		printf("Error exception:%s\n", e.what());
//	}
//
//	return 0;
//}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file


//int GetURL() {
//
//	auto fileStream = std::make_shared<ostream>();
//	// Open stream to output file.
//	pplx::task<void> requestTask = fstream::open_ostream(U("results.html")).then([=](ostream outFile)
//	{
//		*fileStream = outFile;
//
//		http_client client(U("http://api.weatherunlocked.com/"));
//
//		// Build request URI and start the request.
//		// uri_builder builder(U("/search"));
//		uri_builder builder(U("api/current/uk.s38br?app_id=5036d233&app_key=f30c86d947e8980722c6c385ec86021e"));
//		// builder.append_query(U("q"), U("cpprestsdk github"));
//
//		return client.request(methods::GET, builder.to_string());
//
//	})
//
//		.then([=](http_response response)
//	{
//		printf("Received response status code:%u\n", response.status_code());
//
//		// Write response body into the file.
//		 //return response.body().read_to_end(fileStream->streambuf());
//		// Write response to a variable
//		return response.extract_string();
//		//textString = L"hello";//response.extract_string();
//		// return textString;
//	})
//
//		// Close the file stream.
//		.then([=](size_t)
//	{
//		return fileStream->close();
//	});
//
//	// Wait for all the outstanding I/O to complete and handle any exceptions
//	try
//	{
//		requestTask.wait();
//	}
//	catch (const std::exception& e)
//	{
//		printf("Error exception:%s\n", e.what());
//	}
//
//	return 0;
//}
