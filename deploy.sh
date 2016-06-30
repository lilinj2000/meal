#! /bin/sh

home_app=~/app

home_meal=${home_app}/meal

./configure --prefix=${home_meal}

if test -d ${home_meal}; then
    rm -rf ${home_meal}
fi

make install

make distclean
