EQEmuDBI
===

[![Build Status](https://travis-ci.org/KimLS/EQEmuDBI.svg?branch=master)](https://travis-ci.org/KimLS/EQEmuDBI)

Overview
---

Provides a common C++ interface to MySQL/SQLite3/PostgreSQL database connectors for use in EQEmu/Server and associated products.

Usage
---

Please check the following for a pretty exhaustive usage set:

- test-mysql/main.cpp
- test-postgresql/main.cpp
- test-sqlite/main.cpp

Dependencies
---

Both dependencies are optional, if either are missing the respective components will simply not build by CMake.

For Windows:

- The MySQL C Connector (MariaDB may also work but I've not tested it)
- PostgreSQL's libpq (Packaged with PostgreSQL server binary distributions).

For Debian based distros (adjust to your local flavor):

- libmysqlclient-dev
- libpq-dev

Building
---

Uses CMake for building, Finding PostgreSQL doesn't work the best even on linux systems so if you want to use it you may need to
pass -DPostgreSQL_INCLUDE_DIR -DPostgreSQL_LIBRARY -DPostgreSQL_TYPE_INCLUDE_DIR or -DPostgreSQL_ADDITIONAL_VERSIONS="YourVersionHere" to CMake.

Successfully tested as building on both Windows under MSVC and Debian under GCC.

Bug reports
---

Please use the [issue tracker](https://github.com/KimLS/EQEmuDBI/issues) provided by GitHub to send bug reports or feature requests.

Contributions
---

The preferred way to contribute is to fork the repo and submit a pull request on GitHub.