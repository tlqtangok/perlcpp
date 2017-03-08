# perlcpp
Embed perl into cpp file ,and build into executed files. 

# demo 1 
 - use "./interp.cpp" as template, notice one only need change the code in "TODO AREA".

```c++

INIT_PERL_INTERP ;

// -------- TODO ----------
// ------------------------

char *id_cmd = " $a=qq/ABC_/;$a=$a x 10; $a =~ s/.$//;@arr=split m/_/,$a;  ";
P_eval( id_cmd );	// run the perl statement in C++ 
P_arr_print( "arr" );

// ------------------------
// ------------------------
DESTROY_PERL_INTERP ;
return 0;
```

to build that, please run :  sh bld_cpp.sh , remember on Windows, I recommend Strawberry Perl. 
use the g++ or gcc under Strawberry. (if one see error msg, please comment the first line and 
uncomment 2nd line to use C++11.)

if lucky enough, check you GCC version, >=4.8 is recommend. 

if everything is ok, a file "interp" will be generated. run it. this will get following output:

$ ./interp

```text
0 : ABC
1 : ABC
2 : ABC
3 : ABC
4 : ABC
5 : ABC
6 : ABC
7 : ABC
8 : ABC
9 : ABC
```

# demo 2

 - also based on ./interp.cpp, edit the TODO.
 
```c++
// -------- TODO ----------
// ------------------------

char *id_cmd = " @arr=(0..99); $float_num=1.234; $str=qq(STRINGS); ";
P_eval( id_cmd );

int num_idx_3 = P_arr_Int_i("arr", 3);   // => 3 
char *str = Str("str"); 	// => "STRINGS"
float *float_num = Float("float_num") ; // => 1.234 

// ------------------------
// ------------------------
```


# demo 3

 - also based on ./interp.cpp, edit the TODO.
 
 
```c++
// -------- TODO ----------
// ------------------------

int m_ok = m("abc", "m/b/");  // m_or_not => 1 
int m_not_ok = m("abc", "m/b/");  // m_or_not => 0
char *ss = s("abc", "s/b/_B_/"); // ss => a_B_c   ,this is perl $a =~ s/xx/XX/g

// ------------------------
// ------------------------
	
```



good enough? or wanna add more subroutines? Then Please give me 5 stars ! 


--By Jidor Tang at 20170307  : tlqtangok@126.com


# todo next
- add t folder for testcases
