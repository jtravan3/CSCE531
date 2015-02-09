/* Dictionary implementation */

#include "defs.h"

extern boolean isKeyExpected;
extern boolean isValExpected;
extern boolean isId;
extern boolean isInt;
extern boolean isStrConst;
extern int lineNumber;
extern FILE *yyin;
extern FILE *yyout;

main( int argc, char **argv ){

    ++argv, --argc;    /* skip over program name */
    if ( argc > 0 )
	yyin = fopen( argv[0], "r" );
    else
	yyin = stdin;

    yylex();

}


processDefine(char *text) {

    if( isKeyExpected ){
	if( isId ){
	    printf("Key: '%s'\n", text);
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
		isId = FALSE;
	    }

	    if(isInt){
		printf("Value: '%s' of type INT\n", text);
		isInt = FALSE;
	    }

	    if(isStrConst){
		printf("Value: '%s' of type STR_CONST\n", text);
		isStrConst = FALSE;
	    }

	    isValExpected = FALSE;
	}
    }

}/* END processDefine() */
