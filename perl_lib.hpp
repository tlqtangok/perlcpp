/*
this file is the wrapped library for perl interprater.
please refer to this:
  http://perldoc.perl.org/perlembed.html
for more info.
--By Jidor Tang @ 20170307
*/

#pragma GCC diagnostic ignored "-Wwrite-strings"
 #include <EXTERN.h>
 #include <perl.h>

/***** global perl interp ******/
static PerlInterpreter *my_perl;
/*******************************/
#ifdef WINDIR
        #include <windows.h>
#else
        #include <unistd.h>
#endif

#define Int(str)                ((int)SvIV(get_sv(str,0)))
#define Float(str)              ((float)SvNV(get_sv(str,0)))
#define Str(str)                ((char*)SvPV_nolen(get_sv(str,0)))
#define P_eval(cmd)                     eval_pv(cmd,0)
#define P_arr_len(str)  (av_top_index(get_av(str, 0))+1)



#define P_arr_Str_i(str,i)      (SvPV_nolen( *av_fetch( get_av(str, 0) , i, 0 ) ))
#define P_arr_Int_i(str,i)      ((int)SvIV( *av_fetch( get_av(str, 0) , i, 0 ) ))
#define P_arr_Float_i(str,i) ((int)SvNV( *av_fetch( get_av(str, 0) , i, 0 ) ))


#define P_arr_print(str)	for(int i=0;i<av_top_index(get_av(str, 0)) + 1;i++){ \
					char *s = SvPV_nolen( *av_fetch( get_av(str, 0) , i, 0 ) ); \
					printf( "%d : %s\n", i,s ); \
				}

#define INIT_PERL_INTERP        char *embedding[] = { "", "-e", "0" }; \
                                                        PERL_SYS_INIT3(&argc,&argv,&env); \
                                                        my_perl = perl_alloc(); \
                                                        perl_construct( my_perl ); \
                                                        perl_parse(my_perl, NULL, 3, (char**)embedding, NULL); \
                                                        PL_exit_flags |= PERL_EXIT_DESTRUCT_END; \
                                                        perl_run(my_perl)

#define DESTROY_PERL_INTERP     perl_destruct(my_perl); \
                                                        perl_free(my_perl); \
                                                        PERL_SYS_TERM()

SV* my_eval_sv(SV *sv, I32 croak_on_error);
I32 match(SV *string, char *pattern) ;
int m( char *text, char*pattern);
I32 substitute(SV **string, char *pattern);
char * s( char *text, char *pattern);
SSize_t matches(SV *string, char *pattern, AV **match_list);

SV* my_eval_sv(SV *sv, I32 croak_on_error)
 {
     dSP;
     SV* retval;


     PUSHMARK(SP);
     eval_sv(sv, G_SCALAR);

     SPAGAIN;
     retval = POPs;
     PUTBACK;

     if (croak_on_error && SvTRUE(ERRSV))
        croak(SvPVx_nolen(ERRSV));

     return retval;
 }

 /** match(string, pattern)
  **
  ** Used for matches in a scalar context.
  **
  ** Returns 1 if the match was successful; 0 otherwise.
  **/

 I32 match(SV *string, char *pattern)
 {
     SV *command = newSV(0), *retval;

     sv_setpvf(command, "my $string = '%s'; $string =~ %s",
              SvPV_nolen(string), pattern);

     retval = my_eval_sv(command, TRUE);
     SvREFCNT_dec(command);

     return SvIV(retval);
 }

 int m( char *text, char *pattern){
         const int LEN_M=256;
         char *cmd = new char[strlen(text)+LEN_M];   // need delete []

         sprintf(cmd, "$_=qq/%s/;  $m=0; if (%s){ $m=1;} else{ $m =0;} " , text, pattern );

         //printf("cmd = %s", cmd );
         P_eval( cmd );
         int ret_int = 0;
         ret_int = Int("m");

         delete [] cmd ;
         return ret_int;
 }

  char * s( char *text, char *pattern){
         const int LEN_S=512;
         char *cmd = new char[strlen(text)+LEN_S];   // need delete []

         sprintf(cmd, "$_=qq/%s/;  $s=0; %s ; $s=$_; " , text, pattern );

         //printf("cmd = %s", cmd );
         P_eval( cmd );
         char *str = NULL;
         str = Str("s");

         delete [] cmd ;
         return str;
 }


 /** substitute(string, pattern)
  **
  ** Used for =~ operations that
  ** modify their left-hand side (s/// and tr///)
 **
 ** Returns the number of successful matches, and
 ** modifies the input string if there were any.
 **/

 I32 substitute(SV **string, char *pattern)
 {
     SV *command = newSV(0), *retval;

     sv_setpvf(command, "$string = '%s'; ($string =~ %s)",
              SvPV_nolen(*string), pattern);

     retval = my_eval_sv(command, TRUE);
     SvREFCNT_dec(command);

     *string = get_sv("string", 0);
     return SvIV(retval);
 }

 /** matches(string, pattern, matches)
  **
  ** Used for matches in a list context.
  **
  ** Returns the number of matches,
  ** and fills in **matches with the matching substrings
  **/

 SSize_t matches(SV *string, char *pattern, AV **match_list)
 {
     SV *command = newSV(0);
     SSize_t num_matches;

     sv_setpvf(command, "my $string = '%s'; @array = ($string =~ %s)",
              SvPV_nolen(string), pattern);

     my_eval_sv(command, TRUE);
     SvREFCNT_dec(command);

     *match_list = get_av("array", 0);
     num_matches = av_top_index(*match_list) + 1;

     return num_matches;
 }






