#include "gm_manager.h"
#include <http_server/http_packet.hpp>

namespace spiritsaway::http_gm
{
	class gm_handler
	{
	public:
		std::string check_request(const std::string& req_body, std::string& method, json& param_body)
		{
            if (!json::accept(req_body))
            {
                return "body must be json" ;
            }
            auto json_body = json::parse(req_body);
            if (!json_body.is_object())
            {
                return "body must be json object";

            }
            auto method_iter = json_body.find("method");
            if (method_iter == json_body.end() || !method_iter->is_string())
            {
                return "expect string value for key method";
            }
            method = method_iter->get<std::string>();
            auto params_iter = json_body.find("params");
            if (params_iter == json_body.end() || !params_iter->is_object())
            {
                return "expect object value for key params";
            }
            param_body = *params_iter;
            return "";
		}
		void operator()(const spiritsaway::http_server::request& req, spiritsaway::http_server::reply_handler cb)
		{
            std::string method;
            json param_body;
            auto error_info = check_request(req.body, method, param_body);

            auto finish_lambda = [=](bool suc, const json& reply_json)
            {
                json final_reply;
                final_reply["suc"] = suc;
                final_reply["reply"] = reply_json;
                spiritsaway::http_server::reply  cur_reply;
                cur_reply.status = spiritsaway::http_server::reply::status_type::ok;
                cur_reply.content = final_reply.dump();
                cb(cur_reply);
            };
            if (!error_info.empty())
            {
                finish_lambda(false, error_info + " cur body is " + req.body);
                return;
            }
            gm_manager::instance().handle_request(method, param_body, finish_lambda);
		}
	};
}