#ifndef KNOCKEDUPWEBCONFIG_H
#define KNOCKEDUPWEBCONFIG_H

#include <string>

class KnockedUpWebConfig
{
    public:
        KnockedUpWebConfig();
        virtual ~KnockedUpWebConfig();
        bool parseConfig();
        std::string getKnocksFilePath() { return mKnocksFilePath; }
        void setKnocksFilePath(std::string val) { mKnocksFilePath = val; }
        std::string getFormat() { return mFormat; }
        void setFormat(std::string val) { mFormat = val; }
        int32_t getMaxAllowedIps() { return mMaxAllowedIps; }
        void setMaxAllowedIps(int32_t val) { mMaxAllowedIps = val; }
        uint32_t getPort() { return mPort; }
        void setPort(uint32_t port) { mPort = port; }
    protected:
    private:
        std::string mKnocksFilePath;
        std::string mFormat;
        int32_t mMaxAllowedIps;
        uint32_t mPort;
};

#endif // KNOCKEDUPWEBCONFIG_H
