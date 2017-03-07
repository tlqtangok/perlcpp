
/*
   

a wrapped library for perl interprater.
please refer to this:
  http://perldoc.perl.org/perlembed.html
for more info.
--By Jidor Tang @ 20170307

------------

how to build and run (both Windows and Linux platform is OK)
   perl_interp_get_var_from_perl_to_c
   need to locate libperl.so or libperl.a  , something like this
   if on windows,
   first redirect the embed pm opts to a bat file, then put them in one line.
   and use straberryperl 's gcc : Strawberry\c\bin\gcc.exe
   to build , and may need use g++ -std=c++11   , or g++ is also ok.

   on Windows:  use :           g++ -std=c++11 -o interp interp.cpp  -s -L"C:\jd_p\sw\pro\STRAWB~1\perl\lib\CORE" -L ...
   and dep on at least these 4 DLLs:

   copy c:\jd_p\sw\pro\strawberry\c\bin\LIBWINPTHREAD-1.DLL .\
   copy c:\jd_p\sw\pro\strawberry\c\bin\LIBGCC_S_SJLJ-1.DLL .\
   copy "c:\jd_p\sw\pro\strawberry\c\bin\LIBSTDC++-6.DLL" .\
   copy c:\jd_p\sw\pro\strawberry\perl\bin\PERL522.DLL .\


### shell ###
export LD_LIBRARY_PATH=/usr/lib/x86_64-linux-gnu:$LD_LIBRARY_PATH
g++ -o -DWINDIR interp interp.cpp -L`pwd` `perl -MExtUtils::Embed -e ccopts -e ldopts`
# g++ -o  interp interp.cpp -L`pwd` `perl -MExtUtils::Embed -e ccopts -e ldopts`
./interp
### end shell ###

*/

#include <iostream>
#include<stdlib.h>
using namespace std;


/* perl: static my_perl interp  */
#include "perl_lib.hpp"



/*** function readme ***
  INIT_PERL_INTERP;                             init perl and perl interp :my_perl
...
  P_eval("$_=111");                                     run perl statement
  Int("a");                                             get $a from eval()
  Float("a");                                           dotto
  Str("a");                                                     dotto
  P_arr_len("arr");                             get @arr length
  P_arr_Str_i("arr", 3);                        get @arr[3] as Str;
  P_arr_Int_i("arr", 3);                        get @arr[3] as Int;
  P_arr_Float_i("arr", 3);                      get @arr[3] as Float;
  P_arr_print("arr");                           print out @arr and its index,very slowly...
  int xx = m("abc", "m/b./");           perl match
  char *ss = s("abc", "s/b/B/g");       perl substitute
...
  DESTROY_PERL_INTERP;                          Destroy my_perl
 ***********************/


int  main (int argc, char **argv, char **env){

        INIT_PERL_INTERP ;

        // -------- TODO ----------
        // ------------------------

        char *id_cmd = " $a=qq/ABC_/;$a=$a x 10; $a =~ s/.$//;@arr=split m/_/,$a;  ";
        P_eval( id_cmd );

        P_arr_print( "arr" );

        // ------------------------
        // ------------------------
        DESTROY_PERL_INTERP ;
        return 0;
}


