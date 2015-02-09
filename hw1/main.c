/* Dictionary implementation */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "defs.h"

extern boolean isKeyExpected;
extern boolean isValExpected;
extern boolean isId;
extern boolean isInt;
extern boolean isStrConst;
extern int lineNumber;
extern FILE *yyin;
extern FILE *yyout;

char *key_str;

main( int argc, char **argv ){

    ++argv, --argc;    /* skip over program name */
    if ( argc > 0 )
	yyin = fopen( argv[0], "r" );
    else
	yyin = stdin;

    init_dict();
    yylex();

}


processDefine(char *text) {

    if( isKeyExpected ){
	if( isId ){
	    printf("Key: '%s'\n", text);

	    /* copy key value into temp char pointer */
	    key_str = (char *) malloc(strlen(text)+1);
	    strcpy(key_str, text);

	    isKeyExpected = FALSE;
	    isValExpected = TRUE;
	    isId = FALSE;
	} else {
	    fprintf(stderr, "Invalid ID received at 1. %d\n", lineNumber);
	    isKeyExpected = FALSE;
	    isValExpected = TRUE;
	}
    } else {
	if(isValExpected){
	    if(isId){
		printf("Value: '%s' of type ID\n", text);
		add_id_to_dict(key_str, text);
		isId = FALSE;
	    }

	    if(isInt){
		printf("Value: '%s' of type INT\n", text);
		add_int_to_dict(key_str, atol(text));
		isInt = FALSE;
	    }

	    if(isStrConst){
		printf("Value: '%s' of type STR_CONST\n", text);
		add_str_to_dict(key_str, text);
		isStrConst = FALSE;
	    }

	    isValExpected = FALSE;
	}
    }

}/* END processDefine() */
