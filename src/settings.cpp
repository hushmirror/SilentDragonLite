// Copyright 2019-2021 The Hush developers
// Released under the GPLv3
#include "mainwindow.h"
#include "settings.h"
#include "camount.h"
#include "../lib/silentdragonlitelib.h"

Settings* Settings::instance = nullptr;

Settings* Settings::init() {    
    if (instance == nullptr) 
        instance = new Settings();

    return instance;
}

Settings* Settings::getInstance() {
    return instance;
}

Config Settings::getSettings() {
    qDebug() << __func__;
    // Load from the QT Settings. 
    QSettings s;
    
    // this domain is stolen and malicious!
    // More info: https://git.hush.is/hush/fraud/#gilardh
    auto malicious     = "https://lite.myhush.org";
    auto server        = s.value("connection/server").toString();
    bool sticky        = s.value("connection/stickyServer").toBool();
    bool torOnly       = s.value("connection/torOnly").toBool();

    // Users that have old configs generated from old SDLs will have this hostname
    if(server == malicious) {
        qDebug() << "Replacing malicious SDL server with " << server;
        server = "https://lite.hush.is";
        s.setValue("connection/server", server);
    }

    // default behavior : no server listed in conf, randomly choose from server list, unless sticky
    if (server.trimmed().isEmpty()) {
        server = Settings::getRandomServer();

        // make sure existing server in conf is alive, otherwise choose random one
        char* resp = litelib_initialize_existing(false, server.toStdString().c_str());
        QString response = litelib_process_response(resp);

        if (response.toUpper().trimmed() != "OK") {
            qDebug() << "Lite server in conf " << server << " is down, getting a random one";
            server = Settings::getRandomServer();
            s.setValue("connection/server", server);
        }
    } else {
        if (sticky) {
            qDebug() << server << " is sticky";
        }
        // if it's down, oh well
    }

    s.sync();
    // re-init to load correct settings
    init();

    return Config{server, torOnly, sticky};
}

void Settings::saveSettings(const QString& server) {
    QSettings s;

    s.setValue("connection/server", server);
    s.sync();

    // re-init to load correct settings
    init();
}

bool Settings::isTestnet() {
    return _isTestnet;
}

void Settings::setTestnet(bool isTestnet) {
    this->_isTestnet = isTestnet;
}

bool Settings::isSaplingAddress(QString addr) {
    if (!isValidAddress(addr))
        return false;

    return ( isTestnet() && addr.startsWith("ztestsapling")) ||
           (!isTestnet() && addr.startsWith("zs1"));
}

bool Settings::isSproutAddress(QString addr) {
    if (!isValidAddress(addr))
        return false;
        
    return isZAddress(addr) && !isSaplingAddress(addr);
}

bool Settings::isZAddress(QString addr) {
    if (!isValidAddress(addr))
        return false;
        
    return addr.startsWith("zs");
}

bool Settings::isTAddress(QString addr) {
    if (!isValidAddress(addr))
        return false;
        
    return addr.startsWith("R");
}

QString Settings::gethushdVersion() {
    return _hushdVersion;
}

void Settings::sethushdVersion(QString version) {
    _hushdVersion = version;
}

bool Settings::isSyncing() {
    return _isSyncing;
}

void Settings::setSyncing(bool syncing) {
    this->_isSyncing = syncing;
}

int Settings::getBlockNumber() {
    return this->_blockNumber;
}

void Settings::setBlockNumber(int number) {
    this->_blockNumber = number;
}

bool Settings::isSaplingActive() {
    return  (isTestnet() && getBlockNumber() > 0) || (!isTestnet() && getBlockNumber() > 0);
}

double Settings::getZECPrice() { 
    return ZECPrice; 
}
double Settings::getEURPrice() { 
    return EURPrice; 
}
double Settings::getBTCPrice() { 
    return BTCPrice; 
}
double Settings::getCNYPrice() { 
    return CNYPrice; 
}
double Settings::getRUBPrice() { 
    return RUBPrice; 
}
double Settings::getCADPrice() { 
    return CADPrice; 
}
double Settings::getSGDPrice() { 
    return SGDPrice; 
}
double Settings::getCHFPrice() { 
    return CHFPrice; 
}
double Settings::getINRPrice() { 
    return INRPrice; 
}
double Settings::getGBPPrice() { 
    return GBPPrice; 
}
double Settings::getAUDPrice() { 
    return AUDPrice; 
}
double Settings::getUSDVolume() { 
    return USDVolume; 
}
double Settings::getEURVolume() { 
    return EURVolume; 
}
double Settings::getBTCVolume() { 
    return BTCVolume; 
}
double Settings::getCNYVolume() { 
    return CNYVolume; 
}
double Settings::getRUBVolume() { 
    return RUBVolume; 
}
double Settings::getCADVolume() { 
    return CADVolume; 
}
double Settings::getSGDVolume() { 
    return SGDVolume; 
}
double Settings::getCHFVolume() { 
    return CHFVolume; 
}
double Settings::getINRVolume() { 
    return INRVolume; 
}
double Settings::getGBPVolume() { 
    return GBPVolume; 
}
double Settings::getAUDVolume() { 
    return AUDVolume; 
}
double Settings::getUSDCAP() { 
    return USDCAP; 
}
double Settings::getEURCAP() { 
    return EURCAP; 
}
double Settings::getBTCCAP() { 
    return BTCCAP; 
}
double Settings::getCNYCAP() { 
    return CNYCAP; 
}
double Settings::getRUBCAP() { 
    return RUBCAP; 
}
double Settings::getCADCAP() { 
    return CADCAP; 
}
double Settings::getSGDCAP() { 
    return SGDCAP; 
}
double Settings::getCHFCAP() { 
    return CHFCAP; 
}
double Settings::getINRCAP() { 
    return INRCAP; 
}
double Settings::getGBPCAP() { 
    return GBPCAP; 
}
double Settings::getAUDCAP() { 
    return AUDCAP; 
}


bool Settings::getCheckForUpdates() {
    return QSettings().value("options/allowcheckupdates", true).toBool();
}

void Settings::setCheckForUpdates(bool allow) {
     QSettings().setValue("options/allowcheckupdates", allow);
}

bool Settings::getAllowFetchPrices() {
    return QSettings().value("options/allowfetchprices", true).toBool();
}

void Settings::setAllowFetchPrices(bool allow) {
     QSettings().setValue("options/allowfetchprices", allow);
}

QString Settings::get_currency_name() {
    // Load from the QT Settings.
    return QSettings().value("options/currency_name", false).toString();
}

void Settings::set_currency_name(QString currency_name) {
    QSettings().setValue("options/currency_name", currency_name);  
}

QString Settings::get_theme_name() {
    // Load from the QT Settings.
    return QSettings().value("options/theme_name", "Dark").toString();
}

void Settings::set_theme_name(QString theme_name) {
    QSettings().setValue("options/theme_name", theme_name);
}

// Static Stuff
void Settings::saveRestore(QDialog* d) {
    d->restoreGeometry(QSettings().value(d->objectName() % "geometry").toByteArray());

    QObject::connect(d, &QDialog::finished, [=](auto) {
        QSettings().setValue(d->objectName() % "geometry", d->saveGeometry());
    });
}

void Settings::saveRestoreTableHeader(QTableView* table, QDialog* d, QString tablename) {
    table->horizontalHeader()->restoreState(QSettings().value(tablename).toByteArray());
    table->horizontalHeader()->setStretchLastSection(true);

    QObject::connect(d, &QDialog::finished, [=](auto) {
        QSettings().setValue(tablename, table->horizontalHeader()->saveState());
    });
}

QString Settings::getRandomServer() {
    qDebug() << __func__;
    // we don't need cryptographic random-ness, but we want
    // clients to never get "stuck" with the same server, which
    // prevents various attacks
    QList<QString> servers;
    //TODO: This should be a much larger list which we randomly choose from
    servers[0] = "https://lite.hush.is";
    servers[1] = "https://devo.crabdance.com";
    servers[2] = "https://lite.hush.community";
    //servers[3] = "https://hush.leto.net";
    //servers[4] = "https://milktoast.attackingzcash.com";

    // start at a random place in the list
    int x       = rand() % servers.size();
    auto server = servers[x];
    int tries = 0;

    // We try every server,in order, starting from a random place in the list
    while (tries <= servers.size() ) {
        qDebug() << "Checking if lite server " << server << " is a alive, try=" << tries;
        char* resp = litelib_initialize_existing(false, server.toStdString().c_str());
        QString response = litelib_process_response(resp);

        // if we see a valid connection, return this server
        if (response.toUpper().trimmed() == "OK") {
            qDebug() << "Choosing lite server " << server;
            return server;
        }
        server = servers[++x % servers.size()];

        tries++;
    }
    return server;
}

QString Settings::getDefaultServer() {
    qDebug() << __func__;
    return "https://lite.hush.is";
}

void Settings::openAddressInExplorer(QString address) {
    QString url = "https://explorer.hush.is/address/" + address;
    QDesktopServices::openUrl(QUrl(url));
}

void Settings::openTxInExplorer(QString txid) {
    QString url = "https://explorer.hush.is/tx/" + txid;
    QDesktopServices::openUrl(QUrl(url));
}


const QString Settings::txidStatusMessage = QString(QObject::tr("Tx submitted (right click to copy) txid:"));

QString Settings::getTokenName() {
    if (Settings::getInstance()->isTestnet()) {
        return "TUSH";
    } else {
        return "HUSH";
    }
}

QString Settings::getDonationAddr() {
    if (Settings::getInstance()->isTestnet()) 
            return "ztestsaplingXXX";
    else 
            return "zs1fq9f7vg797qaeac9lyx0njyjmjg4w7m60hwq6lhyhvdcqltl5hdkm8vwx9cxy60ehuuz2x49jxt";

}

CAmount Settings::getMinerFee() {
    return CAmount::fromqint64(10000);
}

bool Settings::isValidSaplingPrivateKey(QString pk) {
    if (isTestnet()) {
        QRegExp zspkey("^secret-extended-key-test[0-9a-z]{278}$", Qt::CaseInsensitive);
        return zspkey.exactMatch(pk);
    } else {
        QRegExp zspkey("^secret-extended-key-main[0-9a-z]{278}$", Qt::CaseInsensitive);
        return zspkey.exactMatch(pk);
    }
}

bool Settings::isValidAddress(QString addr) {
    QRegExp zsexp("^zs1[a-z0-9]{75}$",  Qt::CaseInsensitive);
    QRegExp ztsexp("^ztestsapling[a-z0-9]{76}", Qt::CaseInsensitive);
    QRegExp texp("^R[a-z0-9]{33}$", Qt::CaseInsensitive);

    return  texp.exactMatch(addr) || ztsexp.exactMatch(addr) || zsexp.exactMatch(addr);
}

// Get a pretty string representation of this Payment URI
QString Settings::paymentURIPretty(PaymentURI uri) {
    CAmount amount = CAmount::fromDecimalString(uri.amt);
    return QString() + "Payment Request\n" + "Pay: " + uri.addr + "\nAmount: " + amount.toDecimalhushString() 
        + "\nMemo:" + QUrl::fromPercentEncoding(uri.memo.toUtf8());
}

// Parse a payment URI string into its components
PaymentURI Settings::parseURI(QString uri) {
    PaymentURI ans;

    if (!uri.startsWith("hush:")) {
        ans.error = "Not a HUSH payment URI";
        return ans;
    }

    uri = uri.right(uri.length() - QString("hush:").length());
    
    QRegExp re("([a-zA-Z0-9]+)");
    int pos;
    if ( (pos = re.indexIn(uri)) == -1 ) {
        ans.error = "Couldn't find an address";
        return ans;
    }

    ans.addr = re.cap(1);
    if (!Settings::isValidAddress(ans.addr)) {
        ans.error = "Could not understand address";
        return ans;
    }
  uri = uri.right(uri.length() - ans.addr.length()-1);  // swallow '?'
    QUrlQuery query(uri);

    // parse out amt / amount
    if (query.hasQueryItem("amt")) {
        ans.amt  = query.queryItemValue("amt");
    } else if (query.hasQueryItem("amount")) {
        ans.amt  = query.queryItemValue("amount");
    }

    // parse out memo / msg / message
    if (query.hasQueryItem("memo")) {
        ans.memo  = query.queryItemValue("memo");
    } else if (query.hasQueryItem("msg")) {
        ans.memo  = query.queryItemValue("msg");
    } else if  (query.hasQueryItem("message")) {
        ans.memo  = query.queryItemValue("message");
    }

    return ans;
}

const QString Settings::labelRegExp("[a-zA-Z0-9\\-_]{0,40}");
