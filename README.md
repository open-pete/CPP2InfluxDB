# DBInterface
C++ Implementation of database interface for an influx-database

[![Build Status](https://travis-ci.org/open-pete/DBInterface.svg?branch=master)](https://travis-ci.org/open-pete/DBInterface) [![Coverage Status](https://coveralls.io/repos/github/open-pete/DBInterface/badge.svg?branch=master)](https://coveralls.io/github/open-pete/DBInterface?branch=master)

## Requirements 

 1. Installation of qt
 2. Installation of python3-pip and gitpython

## Setup / Clone & Compile 

```bash
# set variables
repoName="DBInterface"
repoURL="https://github.com/mezorian/DBInterface.git"
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
