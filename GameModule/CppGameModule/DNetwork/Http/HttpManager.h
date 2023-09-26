#include "HttpHeader.h"




namespace DHttp {

	typedef httplib::Request Request;
	typedef httplib::Response Response;
	//typedef std::function<void(const Request&, Response&)> HttpHandler;
	typedef DGeneric::Handler<void(const Request&, Response&)> HttpHandler;

	class HttpServer {
	public:
		HttpServer();

	public:
		void host() {
			// HTTP
			Route("/", &HttpServer::onAccept);
			Route("/index", &HttpServer::onAccept);
			Route("", &HttpServer::onAccept);
			listen("0.0.0.0", 8080);
		}

		void Route(const DGeneric::String& _pattern, HttpHandler _handler) {
			m_svr.Get(_pattern, _handler);
		}
		//void Route(const DGeneric::String& _pattern, std::function<void(const Request&, Response&)> _handler) {
		//	m_svr.Get(_pattern, _handler);
		//}

		void listen(const std::string &host, int port, int socket_flags = 0) { m_svr.listen(host, port, socket_flags); }

		static void onAccept(const Request&, Response& _res)
		{
			_res.set_content("Hello World!", "text/plain");
		}

	private:
		httplib::Server m_svr;
	};

	HttpServer::HttpServer()
	{

	}


}