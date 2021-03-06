// Copyright 2019-2021 The Hush developers
// Released under the GPLv3
#ifndef CONTACTITEM_H
#define CONTACTITEM_H

#include <vector>
#include <QString>
#include "mainwindow.h"
using json = nlohmann::json;

// This represents one HushContact in your ContactList of HushChat, which end users
// see as an avatar and name. This data structure holds all the other data to make things work
class ContactItem
{
private:
    QString _myAddress;
    QString _partnerAddress;
    QString _name;
    QString _cid;
    QString _avatar;
    QString _pubkey;
    
public:
    ContactItem();
    ContactItem(QString name, QString partnerAddress);
    ContactItem(QString name, QString partnerAddress, QString myAddress, QString cid);
    ContactItem(QString name, QString partnerAddress, QString myAddress, QString cid, QString avatar);
    QString getName() const;
    QString getMyAddress() const;
    QString getPartnerAddress() const;
    QString getCid() const;
    QString getAvatar() const;
    void setName(QString name);
    void setMyAddress(QString myAddress);
    void setPartnerAddress(QString partnerAddress);
    void setcid(QString cid);
    void setAvatar(QString avatar);
    QString toQTString();
    json toJson();
};

#endif
