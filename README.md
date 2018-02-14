# Feader Library

This repo houses the library behind Feader. The idea behind the project is to separate the logic for retrieving, parsing, and storing RSS feed elements from the display, so that interface used to access the data can be independent from the logic, therefore allowing much easier cross-platform development. 

## Configuring the Environment

On Ubuntu, run the following:

```
sudo apt install cmake libcurl3-openssl-dev libxml2-dev libsqlite3-dev
```

## Building

Clone the repo, then run the following:

```
mkdir build
cd build
cmake ..
make
./Feader https://wbrawner.com/feed.xml
```

## Todo:

[ ] Write tests
[ ] Write Android client
[ ] Write Windows 10 client OR Java client
[ ] Write GTK client (if not Java client)
[ ] Write Mac client (if not Java client)