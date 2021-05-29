# SilentDragonLite 

<p align="left">
    <a href="https://twitter.com/MyHushTeam">
        <img src="https://img.shields.io/twitter/url?style=social&url=https%3A%2F%2Ftwitter.com%2Fmyhushteam"
            alt="MyHushTeam's Twitter"></a>
    <a href="https://twitter.com/intent/follow?screen_name=MyHushTeam">
        <img src="https://img.shields.io/twitter/follow/MyHushTeam?style=social&logo=twitter"
            alt="follow on Twitter"></a>
    <a href="https://fosstodon.org/@myhushteam">
        <img src="https://img.shields.io/badge/Mastodon-MyHushTeam-blue"
            alt="follow on Mastodon"></a>
    <a href="https://www.reddit.com/r/Myhush/">
        <img src="https://img.shields.io/reddit/subreddit-subscribers/Myhush?style=social"
            alt="MyHushTeam's Reddit"></a>
</p>

SilentDragonLite is a lightwallet for HUSH ($HUSH) runs on Linux and Windows which does not require you to download the full blockchain. This is experimental software under active development!

![HushChat screenshot](hushchat-screenshot.png)

## PRIVACY NOTICE

SilentDragonLite contacts a few different external websites to get various bits of data. 
The first two are option features, to get real-time price data feeds and if you want
to look at explorer details. Price feed can be turned off in Settings and you can set
a custom block explorer URL as well.

    * coingecko.com for price data API  (optional)
    * explorer.hush.is for explorer links (optional) 
    * various community-run lite wallet servers to provide basic functionality (required)

This means your IP address is known to these servers. Enable Tor setting in your wallet to prevent this, or better yet, use TAILS: https://tails.boum.org/
or https://qubes-os.org

## Installation

Choose to install a binary release or compile it yourself.
For Arch Linux users, we have a silentdragonlite package on [AUR](https://aur.archlinux.org/).

### Option 1: Binary Release
Go to the [releases page](https://git.hush.is/hush/SilentDragonLite/releases) and grab the latest binary.

### Option 2: Compile Release Yourself

* SilentDragonLite is written in C++ 14, and can be compiled with g++/clang++/visual c++. 
* It also depends on Qt5, which you can get from [here](https://www.qt.io/download) or install using your Linux version's package manager.
* You'll need Rust v1.49

#### Building on Linux

##### Ubuntu 18.04 and 20.04:
```shell script
sudo apt-get -y install qt5-default qt5-qmake libqt5websockets5-dev qtcreator
git clone https://git.hush.is/hush/SilentDragonLite
cd SilentDragonLite
# sometimes have to build the translations before building the binary
./build.sh linguist
# the next step will take potentially a long time for slower systems
# Be Patient and please report compiler problems!
./build.sh
./SilentDragonLite
```

### Other notes

#### Install Torsocks (or any other Socks service for TOR) on Ubuntu 18.04
```shell script
sudo apt update
sudo apt install torsocks
```
#### Connection to our TOR onion service Server

NOTE: Tor server is currently under maintenance.

```
* Open SDL  Edit->Settings->LightwalletServer->nope.onion:80
* Open the folder of SDL in a Terminal -> Enter: TORSOCKS_LOG_LEVEL=1 torsocks -i ./SilentDragonLite
```
### Note Management
SilentDragonLite does automatic note and utxo management, which means it doesn't allow you to manually select which address to send outgoing transactions from. It follows these principles:

* Defaults to sending shielded transactions, which are now enforced via consensus rules
* Sapling funds need at least 2 confirmations before they can be spent (150 seconds on average for HUSH mainnet)
* Can select funds from multiple shielded addresses in the same transaction (via raw transactions)
* Will automatically shield your transparent funds at the first opportunity
* When sending an outgoing transaction to a shielded address, SilentDragonLite can decide to use the transaction to additionally shield your transparent funds (i.e., send your transparent funds to your own shielded address in the same transaction)

## Support

```
git clone https://git.hush.is/hush/SilenDragonLite
cd SilentDragonLite
# the next step will take potentially a long time for slower systems
# Be Patient and please report compiler problems!
./build.sh
./SilentDragonLite
```

## Support

For support join us on [Telegram Support](https://hush.is/telegram_support), or our [Main Telegram](https://hush.is/telegram) or tweet at [@MyHushTeam](https://twitter.com/MyHushTeam), or toot at our [Mastodon](https://fosstodon.org/@myhushteam), or [file an issue](https://git.hush.is/hush/SilentDragonLite/issues).

You can also subscribe to our channel on [YouTube](https://hush.is/yt)

## License

GPLv3 or later
