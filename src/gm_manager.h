#pragma once

#include "base_factory.h"
#include <nlohmann/json.hpp>

namespace http::utility
{
	using json = nlohmann::json;
	class gm_worker
	{
		friend class gm_manager;
	protected:
		bool m_suc;
		json m_reply_info;
		json m_request_info;
		std::uint32_t m_id;
		gm_worker(std::uint32_t id, const json& request_info)
		{
			m_id = id;
			m_request_info = request_info;
		}

	public:
		virtual bool handle_request()// true for complete false for async request
		{
			m_reply_info = "unknown handler for this command";
			return true;
		}
		virtual void handle_async_result(const json& async_result)
		{
			m_reply_info = async_result;
		}
		bool suc() const
		{
			return m_suc;
		}
		const json& reply_info() const
		{
			return m_reply_info;
		}
		std::uint32_t id() const
		{
			return m_id;
		}
	};
	using gm_factory = utility::basic_poly_factory<utility::raw_ptr_t, gm_worker, std::uint32_t, const json&>;
	using gm_callback_t = std::function<void(bool, const json&)>;
	class gm_manager
	{
	protected:
		std::unordered_map<std::uint32_t, std::pair<std::unique_ptr<gm_worker>, gm_callback_t>> async_workers;
		std::uint32_t idx = 0;
		gm_manager()
		{

		}
	public:
		gm_manager(const gm_manager& other) = delete;
		gm_manager& operator=(const gm_manager& other) = delete;
		static gm_manager& instance()
		{
			static gm_manager the_one;
			return the_one;
		}
		void handle_request(const std::string& method, const json& input, gm_callback_t callback)
		{
			auto cur_worker = gm_factory::make_by_name(method, idx++, input);
			if (!cur_worker)
			{
				callback(false, "cant find handler for " + method);
				return;
			}
			if (cur_worker->handle_request())
			{
				callback(cur_worker->suc(), cur_worker->reply_info());
				return;
			}
			async_workers[cur_worker->id()] = std::make_pair(std::unique_ptr<gm_worker>(cur_worker), callback);
		}
		void handle_async_result(std::uint32_t worker_id, const json& data)
		{
			auto cur_iter = async_workers.find(worker_id);
			if (cur_iter == async_workers.end())
			{
				return;
			}
			else
			{
				cur_iter->second.first->handle_async_result(data);
				auto& cur_worker = cur_iter->second.first;
				cur_iter->second.second(cur_worker->suc(), cur_worker->reply_info());
				async_workers.erase(cur_iter);
				return;
			}

		}
	};

}