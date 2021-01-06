//
// request_handler.cpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "request_handler.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include "mime_types.hpp"
#include "reply.hpp"
#include "request.hpp"

namespace http {
namespace server {

request_handler::request_handler()
{
}

void request_handler::handle_request(const request& req, reply& rep) const
{


  // Fill out the reply to be sent to the client.
  rep.status = reply::ok;
  rep.content = "echo request uri: " + req.uri + " body: " + req.body;
  rep.headers.resize(2);
  rep.headers[0].name = "Content-Length";
  rep.headers[0].value = std::to_string(rep.content.size());
  rep.headers[1].name = "Content-Type";
  rep.headers[1].value = "text";
}


} // namespace server
} // namespace http
