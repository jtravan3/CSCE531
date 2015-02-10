%{
FILE *f;
%}

%%
.	print_stuff(yytext);
\r\n 	print_char();	
%%

int main(int argc, char **argv)
{
   ++argv, --argc;
   if(argv>0){
	yyin = fopen(argv[0], "ar+");
   } else {
	yyin = stdin;
   }

   f = fopen("NEW_OUTPUT.i", "w");

   yylex();
   fclose(f);
   return 0;
}

print_stuff(const char *text){
    fprintf(f,"%s",text);
}

print_char(){
    fprintf(f,"\n");
}
