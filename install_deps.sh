#! /bin/bash

if [[ $(uname) = "Darwin" ]]; then
    brew install -f libfmt-dev libmysqlcppconn-dev
fi

if [[ $(uname) = "Linux" ]]; then
    sudo apt install -y libfmt-dev libmysqlcppconn-dev
fi
