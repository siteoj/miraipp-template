#include <mirai/mirai.h>

int main()
{
    const char* auth_key = "somerandomauthkeyformybot";
    const int64_t qq = 3378448768;

    mirai::Session sess(auth_key, qq);
    sess.config({}, true);
    sess.start_websocket_client();
    sess.subscribe_all_events([&](const mirai::Event& event)
    {
        event.dispatch([&](const mirai::GroupRecallEvent& e) // anti-recall test
        {
            sess.send_group_message(e.group.id, u8"不许撤回", e.message_id);
        });
        event.dispatch([&](const mirai::GroupMessage& e) // ping pong test
        {
            const auto& msg = e.message.content;
            if (msg.string() == "!ping")
                sess.send_group_message(e.sender.group.id, "pong!", e.message.source.id);
        });
    }, mirai::error_logger);
    std::cin.get();
    return 0;
}
