//
// main.cpp
// ~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <string>
#include <asio.hpp>
#include "server.hpp"

int main(int argc, char* argv[])
{
  try
  {
    // Check command line arguments.
    //if (argc != 2)
    //{
    //  std::cerr << "Usage: http_server <port>\n";
    //  return 1;
    //}

    // Initialise the server.
    http::server::request_handler echo_handler;
    std::string address = "0.0.0.0";
    std::string port = "8080";
    http::server::server s(address, port, &echo_handler);

    // Run the server until stopped.
    s.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "exception: " << e.what() << "\n";
  }

  return 0;
}
