# perlcpp
perl embed into cpp , and build into executed files

# demo 1 
 - use ./interp.cpp as template, notice:

`

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
`

to build that, please run :  sh bld_cpp.sh 
(if one see error msg, please use c++11)

if OK, file "interp" will be generated. run it.
this will get following output:

$ ./interp
`
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
`

# demo 2

 - also based on ./interp.cpp, edit the TODO.
 
 `
        // -------- TODO ----------
        // ------------------------

        char *id_cmd = " @arr=(0..99); $float_num=1.234; $str=qq(STRINGS); ";
        P_eval( id_cmd );

        int num_idx_3 = P_arr_Int_i("arr", 3);   // => 3 
	char *str = Str("str"); 	// => "STRINGS"
	float *float_num = Float("float_num") ; // => 1.234 

        // ------------------------
        // ------------------------
`

# demo 3

 - also based on ./interp.cpp, edit the TODO.
 
 `
        // -------- TODO ----------
        // ------------------------

	int m_or_not = m("abc", "m/b/");  // m_or_not => 1 
	char *ss = s("abc", "s/b/_B_/"); // ss => a_B_c   ,this is perl $a =~ s/xx/XX/g

        // ------------------------
        // ------------------------
`


good enough? or wanna add more subroutines?
then Please give me 5 stars ! 

--By Jidor Tang @ 20170307  : tlqtangok@126.com

