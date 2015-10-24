#ifndef KNOCKEDUPWEBHANDLER_H
#define KNOCKEDUPWEBHANDLER_H

#include "CivetServer.h"
#include <fstream>
#include <string>

class KnockedUpWebHandler : public CivetHandler
{
    public:
        KnockedUpWebHandler(const std::string& dataFilePath, const unsigned int maxNumlines);

        bool handleGet(CivetServer *server, struct mg_connection *conn);

        virtual ~KnockedUpWebHandler();

    private:
        std::string exec(std::string cmd);

    protected:
    private:
        std::string   mDataFilePath;
        unsigned int  mMaxNumLines;
};

#endif // KNOCKEDUPWEBHANDLER_H
