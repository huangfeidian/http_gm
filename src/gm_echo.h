#pragma once
#include "gm_manager.h"
namespace spiritsaway::http_gm
{
    class gm_echo final : public gm_factory::sub_class<gm_echo>
    {
    public:
        gm_echo(std::uint32_t id, const json& data)
            : gm_factory::sub_class<gm_echo>(id, data)
        {
        }
        static const std::string_view class_name()
        {
            static std::string name = "echo";
            return name;
        }
        bool handle_request() override
        {
            m_reply_info = m_request_info;
            return true;
        }
    };
}