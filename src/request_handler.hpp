//
// request_handler.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HTTP_REQUEST_HANDLER_HPP
#define HTTP_REQUEST_HANDLER_HPP

#include <string>
#include "request.hpp"
#include "reply.hpp"

namespace http {
namespace server {


/// The common handler for all incoming requests.
using reply_handler = std::function<void(const reply& rep)>;
using request_handler = std::function<void(const request& req, reply_handler cb)>;

} // namespace server
} // namespace http

#endif // HTTP_REQUEST_HANDLER_HPP
