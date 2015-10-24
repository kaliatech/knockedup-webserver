/* Copyright (c) 2015 Joshua Sanderson
 * Copyright (c) 2015 JGS Technical LLC
 * License http://opensource.org/licenses/mit-license.php MIT License
 */

#include "CivetServer.h"

#include <chrono>
#include <fstream>
#include <string>
#include <thread>

#include "KnockedUpWebHandler.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define DOCUMENT_ROOT "/dev/null"
#define PORT "12080"
#define KNOCK_URI "/knock*"
#define EXIT_URI "/exit"
bool exitNow = false;


class ExitHandler : public CivetHandler
{
  public:
	bool
	handleGet(CivetServer *server, struct mg_connection *conn)
	{
		mg_printf(conn, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
		mg_printf(conn, "Bye!\n");
		exitNow = true;
		return true;
	}
};


int main(int argc, char *argv[])
{

	const char *options[] = {
	    "document_root", DOCUMENT_ROOT, "listening_ports", PORT, 0};

	CivetServer server(options);

	KnockedUpWebHandler kuwHandler(std::string("/etc/nginx/knocks.conf"), 50);
	server.addHandler(KNOCK_URI, kuwHandler);

	ExitHandler h_exit;
	server.addHandler(EXIT_URI, h_exit);

	printf("Knock at http://localhost:%s%s\n", PORT, KNOCK_URI);
	printf("Exit at http://localhost:%s%s\n", PORT, EXIT_URI);

	while (!exitNow) {
//#ifdef _WIN32
//		Sleep(1000);
//#else
//		sleep(1);
//#endif

      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

	printf("Bye!\n");

	return 0;
}
