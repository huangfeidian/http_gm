//
// request_parser.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HTTP_REQUEST_PARSER_HPP
#define HTTP_REQUEST_PARSER_HPP

#include <tuple>
#include "http_parser.h"
#include "request.hpp"

namespace http {
namespace server {


/// Parser for incoming requests.
class request_parser
{
public:
  /// Construct ready to parse the request method.
  request_parser();


  void move_req(request& dest);

  /// Result of parse.
  enum class result_type { good, bad, indeterminate };

  /// Parse some data. The enum return value is good when a complete request has
  /// been parsed, bad if the data is invalid, indeterminate when more data is
  /// required. The InputIterator return value indicates how much of the input
  /// has been consumed.
  /// 
  result_type parse(const char* input, std::size_t len);

private:


public:
    request req_;
    bool req_complete_ = false;

private:
    http_parser_settings parse_settings_;
    http_parser parser_;
};

} // namespace server
} // namespace http

#endif // HTTP_REQUEST_PARSER_HPP
