// Copyright 2019-2021 The Hush developers
// Released under the GPLv3
#ifndef SIETCHDATASTORE_H
#define SIETCHDATASTORE_H

using json = nlohmann::json;

class SietchDataStore
{
    private:
        static bool instanced;
        static SietchDataStore* instance;
        std::map<QString, QString> data;
        SietchDataStore()
        {

        }

    public:
        static SietchDataStore* getInstance();
        void clear();
        void setData(QString key, QString value);
        QString getData(QString key);
        QString dump();

        ~SietchDataStore()
        {
            SietchDataStore::instanced = false;
            SietchDataStore::instance = nullptr;
        }
};

#endif
