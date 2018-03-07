# Feader Library

This repo houses the library behind Feader. The idea behind the project is to separate the logic for retrieving, parsing, and storing RSS feed elements from the display, so that interface used to access the data can be independent from the logic, therefore allowing much easier cross-platform development. 

## External dependencies

The external dependencies are included in the `src/` directory, to allow for compilation anywhere. They were acquired from the following sources:

- SQLite3: http://www.sqlite.org/download.html
- Yxml: https://g.blicky.net/yxml.git


## Building

Clone the repo, then run the following:

```
mkdir build
cd build
cmake ..
make
```

## Todo:

[ ] Write tests
[ ] Write Android client
[ ] Write Windows 10 client OR Java client
[ ] Write GTK client (if not Java client)
[ ] Write Mac client (if not Java client)
