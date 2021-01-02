// Copyright 2019-2021 The Hush developers
// Released under the GPLv3
#include "DataStore.h"

SietchDataStore* DataStore::getSietchDataStore()
{
    return SietchDataStore::getInstance();
}

ChatDataStore* DataStore::getChatDataStore()
{
    return ChatDataStore::getInstance();
}

ContactDataStore* DataStore::getContactDataStore()
{
    return ContactDataStore::getInstance();
}
