/* Copyright (c) 2015 Joshua Sanderson
 * Copyright (c) 2015 JGS Technical LLC
 * License http://opensource.org/licenses/mit-license.php MIT License
 */

#include "CivetServer.h"

#include <chrono>
#include <fstream>
#include <string>
#include <thread>

#include "KnockedUpWebConfig.h"
#include "KnockedUpWebHandler.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define DOCUMENT_ROOT "/dev/null"
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
    KnockedUpWebConfig config;
    bool result = config.parseConfig();
    if (!result) {
        printf("Unable to parse config file.");
        return -1;
    }

    printf("Settings\n");
    printf("  Knock File : %s\n", config.getKnocksFilePath().c_str());
    printf("  Max IPs    : %d\n", config.getMaxAllowedIps());
    printf("  Format     : %s\n", config.getFormat().c_str());


    std::string port(std::to_string(config.getPort()));
    const char *options[] = {
        "document_root", DOCUMENT_ROOT, "listening_ports", port.c_str(), 0
    };

    CivetServer server(options);

    KnockedUpWebHandler kuwHandler(std::string("/etc/nginx/knocks.conf"), config.getMaxAllowedIps());
    server.addHandler(KNOCK_URI, kuwHandler);

    ExitHandler h_exit;
    server.addHandler(EXIT_URI, h_exit);

    printf("Knock at http://localhost:%d%s\n", config.getPort(), KNOCK_URI);
    printf("Exit at http://localhost:%d%s\n", config.getPort(), EXIT_URI);

    //TODO: Is there a better way to keep the process open?
    while (!exitNow) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return 0;
}
