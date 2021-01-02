# SilentDragonLite 

SilentDragonLite is a lightwallet for HUSH ($HUSH) runs on Linux and Windows which does not require you to download the full blockchain. This is experimental software under active development!


<img src="hushchat-screenshot.png">

## PRIVACY NOTICE

SilentDragonLite contacts a few different external websites to get various bits of data. 
The first two are option features, to get real-time price data feeds and if you want
to look at explorer details. Price feed can be turned off in Settings and you can set
a custom block explorer URL as well.

* coingecko.com for price data API  (optional)
* explorer.hush.is for explorer links (optional) 
* various community-run lite wallet servers to provide basic functionality (required)

This means your IP address is known to these servers. Enable Tor setting in SilentDragon to prevent this, or better yet, use TAILS: https://tails.boum.org/
or https://qubes-os.org

## Installation

Go to the releases page and grab the latest installers or binary. https://git.hush.is/hush/SilentDragonLite/releases

## Install Torsocks (or any other Socks service for TOR) on Ubuntu 18.04
```
sudo apt update
sudo apt install torsocks
```
## Connection to our TOR onion service Server
```
* Open SDL  Edit->Settings->LightwalletServer->6onaaujm4ozaokzu.onion:80
* Open the folder of SDL in a Terminal -> Enter: TORSOCKS_LOG_LEVEL=1 torsocks -i ./SilentDragonLite
```
## Note Management
SilentDragonLite does automatic note and utxo management, which means it doesn't allow you to manually select which address to send outgoing transactions from. It follows these principles:

* Defaults to sending shielded transactions, which are now enforced via consensus rules
* Sapling funds need at least 2 confirmations before they can be spent (150 seconds on average for HUSH mainnet)
* Can select funds from multiple shielded addresses in the same transaction (via raw transactions)
* Will automatically shield your transparent funds at the first opportunity
* When sending an outgoing transaction to a shielded address, SilentDragonLite can decide to use the transaction to additionally shield your transparent funds (i.e., send your transparent funds to your own shielded address in the same transaction)

## Compiling from source
* SilentDragonLite is written in C++ 14, and can be compiled with g++/clang++/visual c++. 
* It also depends on Qt5, which you can get from [here](https://www.qt.io/download). 
* You'll need Rust v1.41 +

## Building on Linux

```
git clone https://github.com/MyHush/SilenDragonLite.git
cd SilentDragonLite
# the next step will take potentially a long time for slower systems
# Be Patient and please report compiler problems!
./build.sh
./SilentDragonLite
```
