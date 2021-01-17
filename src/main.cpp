

#include <iostream>
#include <string>
#include <asio.hpp>
#include <http_server/http_server.hpp>
#include "gm_echo.h"
#include "gm_handler.h"

using namespace spiritsaway::http_server;
using namespace spiritsaway::http_gm;

int main(int argc, char* argv[])
{

	asio::io_context cur_context;
	std::size_t n_thread = 2;
	try
	{
		// Check command line arguments.
		//if (argc != 2)
		//{
		//  std::cerr << "Usage: http_server <port>\n";
		//  return 1;
		//}

		// Initialise the server.
		std::string address = "0.0.0.0";
		std::string port = "8080";
		server s(cur_context, address, port, gm_handler());

		// Run the server until stopped.
		s.run();
		std::vector<std::thread> v;
		v.reserve(n_thread - 1);
		for (auto i = n_thread - 1; i > 0; --i)
			v.emplace_back(
				[&cur_context]
				{
					cur_context.run();
				});
		cur_context.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "exception: " << e.what() << "\n";
	}

	return 0;
}
