#include <asio2/udp/udp_server.hpp>

int main()
{
	std::string_view host = "0.0.0.0";
	std::string_view port = "8035";

	asio2::udp_server server;

	server.bind_recv([](std::shared_ptr<asio2::udp_session> & session_ptr, std::string_view data)
	{
		printf("recv : %zu %.*s\n", data.size(), (int)data.size(), data.data());

		session_ptr->async_send(data);

	}).bind_connect([](auto & session_ptr)
	{
		printf("client enter : %s %u %s %u\n",
			session_ptr->remote_address().c_str(), session_ptr->remote_port(),
			session_ptr->local_address().c_str(), session_ptr->local_port());
	}).bind_start([&]()
	{
		if (asio2::get_last_error())
			printf("start udp server failure : %d %s\n",
				asio2::last_error_val(), asio2::last_error_msg().c_str());
		else
			printf("start udp server success : %s %u\n",
				server.listen_address().c_str(), server.listen_port());
	}).bind_stop([&]()
	{
		printf("stop udp server : %d %s\n",
			asio2::last_error_val(), asio2::last_error_msg().c_str());
	}).bind_init([&]()
	{
		//// Join the multicast group. you can set this option in the on_init(_fire_init) function.
		//server.acceptor().set_option(
		//	// for ipv6, the host must be a ipv6 address like 0::0
		//	asio::ip::multicast::join_group(asio::ip::make_address("ff31::8000:1234")));
		//	// for ipv4, the host must be a ipv4 address like 0.0.0.0
		//	//asio::ip::multicast::join_group(asio::ip::make_address("239.255.0.1")));
	});

	server.start(host, port);

	while (std::getchar() != '\n');

	return 0;
}
