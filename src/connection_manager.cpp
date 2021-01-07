//
// connection_manager.cpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "connection_manager.hpp"

namespace http {
	namespace server {

		connection_manager::connection_manager()
		{
		}

		void connection_manager::start(connection_ptr c)
		{
			{
				std::lock_guard<std::mutex> guard(con_mutex_);
				connections_.insert(c);
			}
			c->start();
		}

		void connection_manager::stop(connection_ptr c)
		{
			{
				std::lock_guard<std::mutex> guard(con_mutex_);
				connections_.erase(c);
			}

			c->stop();
		}

		void connection_manager::stop_all()
		{
			std::vector<connection_ptr> con_copys;
			{
				std::lock_guard<std::mutex> guard(con_mutex_);
				con_copys.insert(con_copys.end(), connections_.begin(), connections_.end());
				connections_.clear();
			}
			for (auto c : con_copys)
			{
				c->stop();

			}
		}

	} // namespace server
} // namespace http
