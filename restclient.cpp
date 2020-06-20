#include "pch.h"
#include "main.h"

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams
using namespace web::json;

int GetTemperature();

int GetTemperature() {

	http_client client(U("http://api.weatherunlocked.com/"));

	uri_builder builder(U("api/current/uk.s38br?app_id=5036d233&app_key=f30c86d947e8980722c6c385ec86021e"));

	http_request request(methods::GET);
	request.headers().set_content_type(L"application/json");
	request.set_request_uri(builder.to_string());

	pplx::task<int> requestTask =
		client.request(request)
		.then([](http_response response) -> pplx::task<json::value>
	{
		return response.extract_json();
	})
		.then([](pplx::task<json::value> previousTask)
	{
		json::value const& value = previousTask.get();

		return value.as_object().at(L"temp_c").as_number().to_int32();
	});

	try
	{
		return requestTask.get();
	}
	catch (http_exception const& e)
	{

	}
}


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