// Copyright 2019-2021 The Hush developers
// Released under the GPLv3
#ifndef DATASTORE_H
#define DATASTORE_H

#include "SietchDataStore.h"
#include "ChatDataStore.h"
#include "ContactDataStore.h"

class DataStore
{
	public:
	    static SietchDataStore* getSietchDataStore();
	    static ChatDataStore* getChatDataStore();
		static ContactDataStore* getContactDataStore();
};

#endif
