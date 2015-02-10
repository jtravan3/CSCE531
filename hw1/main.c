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
extern int line_num;
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


processDefine(const char *text) {

    if(isKeyExpected){
	if(isId){

	    /* copy key value into temp char pointer */
	    key_str = (char *) malloc(strlen(text)+1);
	    strcpy(key_str, text);

	    isKeyExpected = FALSE;
	    isValExpected = TRUE;
	    isId = FALSE;
	} else {
	    fprintf(stderr, "Invalid ID received at 1. %d\n", line_num);
	    isKeyExpected = FALSE;
	    isValExpected = TRUE;
	}
    } else {
	if(isValExpected){
	    if(isId){
		logical_add_id_to_dict(key_str, text);
//		output_substitution(stdout, key_str);
		isId = FALSE;
	    }

	    if(isInt){
		logical_add_int_to_dict(key_str, atol(text));
//		output_substitution(stdout, key_str);
		isInt = FALSE;
	    }

	    if(isStrConst){
		logical_add_str_to_dict(key_str, text);
//		output_substitution(stdout, key_str);
		isStrConst = FALSE;
	    }

	    isValExpected = FALSE;
	}
    }

}/* END processDefine() */

logical_add_str_to_dict(const char *key, const char *val) {

    DR p = (DR) get_item(key);
    if(p == NULL){
	add_str_to_dict(key, val);
    } else {
	if(p->in_cycle == TRUE){
	    while(p->in_cycle == TRUE){
		unmark_cycle(p);
		p = (DR) get_item(p->u.idval);
	    }
   	    add_str_to_dict(key, val);
	    fprintf(stderr, "Warning: redefinition of %s to %s\n", key, val);
	} else {
	    add_str_to_dict(key, val);
	}
    }

}/* END logical_add_str_to_dict(*char, *char) */

logical_add_int_to_dict(const char *key, long val) {

    DR p = (DR) get_item(key);
    if(p == NULL){
	add_int_to_dict(key, val);
    } else {
	if(p->in_cycle == TRUE){
	    while(p->in_cycle == TRUE){
		unmark_cycle(p);
		p = (DR) get_item(p->u.idval);
	    }
	    add_int_to_dict(key, val);
	    fprintf(stderr, "Warning: redefinition of %s to %lu\n", key, val);
	} else {
	    add_int_to_dict(key, val);
	}
    }

}/* END logical_add_int_to_dict(*char, *char) */

logical_add_id_to_dict(const char *key, const char *val){

    DR p = (DR) get_item(key);
    if(p == NULL){
	add_id_to_dict(key, val);
    } else {
	if(p->in_cycle == TRUE){
	    while(p->in_cycle == TRUE){
		unmark_cycle(p);
		p = (DR) get_item(p->u.idval);
	    }
	    add_id_to_dict(key, val);
	    fprintf(stderr, "Warning: redefinition of %s to %s\n", key, val);
	} else {
	    DR val_p = (DR) get_item(val);
	    if(val_p == NULL){
		add_id_to_dict(key, val);
	    } else {
		boolean needsMarking = FALSE;
		while(val_p != NULL){
		    if(((DR) get_item(val_p->u.idval)) == p) {
			needsMarking = TRUE;
			val_p == NULL;
		    } else {
			val_p = (DR) get_item(val_p->u.idval);
		    }
		}

		if(needsMarking == TRUE){
		    while(val_p->in_cycle == FALSE){
			mark_cycle(val_p);
			val_p = (DR) get_item(val_p->u.idval);
		    }
		    add_id_to_dict(key, val);
		} else {
		    add_id_to_dict(key, val);
		}
		fprintf(stderr, "Warning: redefinition of %s to %s\n", key, val);
	    }
	}
    }

}/* END logical_add_id_to_dict(*char, *char) */
