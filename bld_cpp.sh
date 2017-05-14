export LD_LIBRARY_PATH=/usr/lib/x86_64-linux-gnu:$LD_LIBRARY_PATH
#sudo ln -s libperl.so.5.22 libperl.so
g++ -o  interp interp.cpp -L`pwd` `perl -MExtUtils::Embed -e ccopts -e ldopts`
# g++ -std=c++11 -o  interp interp.cpp -L`pwd` `perl -MExtUtils::Embed -e ccopts -e ldopts`
