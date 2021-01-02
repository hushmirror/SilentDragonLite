// Copyright 2019-2020 The Hush developers
// Released under the GPLv3
#ifndef FIRSTTIMEWIZARD_H
#define FIRSTTIMEWIZARD_H

#include "precompiled.h"
#include "ui_newseed.h"
#include "ui_restoreseed.h"
#include "ui_newwallet.h"
#include "mainwindow.h"

class FirstTimeWizard: public QWizard
{


    
public:
    FirstTimeWizard(bool dangerous, QString server);

    QString getSeed();
    QString getBirthday();   
    QString _birthday;
    QString _seed;
    void setSeed(QString Seed); 
    void setBirthday(QString Birthday);   
    void cancelEvent();

public slots: 
    void slot_change_theme(const QString& themeName);
    

protected:
    int nextId() const;

private:
    enum {
        Page_NewOrRestore,
        Page_New,
        Page_Restore
    };

    bool dangerous;
    QString server;

    friend class NewOrRestorePage;
    friend class NewSeedPage;
    friend class RestoreSeedPage;
    
     
    
};

class NewOrRestorePage: public QWizardPage {
public:
 
    NewOrRestorePage(FirstTimeWizard* parent);

};


class NewSeedPage: public QWizardPage {
public:
    NewSeedPage(FirstTimeWizard* parent);
 

protected:
    virtual void initializePage();
    virtual bool validatePage();    

private:
    FirstTimeWizard* parent;
    Ui_NewSeedForm form;    
};


class RestoreSeedPage: public QWizardPage {
public:
    RestoreSeedPage(FirstTimeWizard* parent);

protected:
    bool validatePage();

private:
    FirstTimeWizard* parent;
    Ui_RestoreSeedForm form;
};



#endif // FIRSTTIMEWIZARD_H
