# CPP2InfluxDB
C++ Implementation of database interface for an influx-database

[![Build Status](https://travis-ci.org/open-pete/CPP2InfluxDB.svg?branch=master)](https://travis-ci.org/open-pete/CPP2InfluxDB) [![Coverage Status](https://coveralls.io/repos/github/open-pete/CPP2InfluxDB/badge.svg?branch=master)](https://coveralls.io/github/open-pete/CPP2InfluxDB?branch=master)

## Requirements 

 1. Installation of qt
 2. Installation of python3-pip and gitpython

## Setup / Clone & Compile 

```bash
# set variables
repoName="CPP2InfluxDB"
repoURL="https://github.com/mezorian/CPP2InfluxDB.git"
branch="master"
manifest="default.xml"

# clone this repository
git clone ${repoURL}
cd ${repoName}

# download all depency repos
git clone https://github.com/mezorian/EasyDepend.git
cp EasyDepend/*.py .
python3 example.py

# build
source /opt/qt55/bin/qt55-env.sh
/opt/qt55/bin/qmake
make clean
make

# run
./untitled

```

