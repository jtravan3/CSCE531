/* Main pre-processor implementation*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "defs.h"

extern boolean isDefineLine;
extern boolean isNewLine;
extern boolean isKeyExpected;
extern boolean isValExpected;
extern boolean isId;
extern boolean isInt;
extern boolean isStrConst;
extern int line_num;
extern FILE *yyin;

char *key_str;

boolean isFirstIdRedefine = TRUE;

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
//		printf("Key: %s\n", key_str);
//		printf("Value: ");
//		output_substitution(key_str);
//		printf("\n");
		isId = FALSE;
	    }

	    if(isInt){
		logical_add_int_to_dict(key_str, atol(text));
		isInt = FALSE;
	    }

	    if(isStrConst){
		char* tmp = (char *) malloc(strlen(text)+1);
		strcpy(tmp, text);
		char* str = strtok(tmp, "\"");
		
		DR p = (DR) get_item(tmp);
		if(p == NULL){
		    logical_add_str_to_dict(key_str, text);
		} else {
		    logical_add_id_to_dict(key_str, str);
		}
		
		isStrConst = FALSE;
	    }

	    isValExpected = FALSE;
	} else {
	    if(!isDefineLine){
		if(isId){
		    output_substitution(text);
		} else {
		   printf("%s", text);
		}
	    } 
	    if(isNewLine){
		isNewLine = FALSE;
	    }
	}
	
    } 

}/* END processDefine() */

logical_add_str_to_dict(const char *key, const char *val) {

    DR p = (DR) get_item(key);
    if(p == NULL){
	add_str_to_dict(key, val);
    } else {
	if(p->tag != ID){
	    add_str_to_dict(key, val);
	} else {
	    if(p->in_cycle == TRUE){
	        unmark_cycle(p);
   	        add_str_to_dict(key, val);
	    } else {
	        add_str_to_dict(key, val);
	    }
	}
    }
    p == NULL;

}/* END logical_add_str_to_dict(*char, *char) */

logical_add_int_to_dict(const char *key, long val) {
    
    DR p = (DR) get_item(key);
    if(p == NULL){
	add_int_to_dict(key, val);
    } else {
	if(p->tag != ID){
	    add_int_to_dict(key, val);
	} else {
   	    if(p->in_cycle == TRUE){
	   	unmark_cycle(p);
		add_int_to_dict(key, val);
   	    } else {
		add_int_to_dict(key, val);
	    }
	}
    }
   

}/* END logical_add_int_to_dict(*char, *char) */

logical_add_id_to_dict(const char *key, const char *val){

    DR p = (DR) get_item(key);
    DR val_p = (DR) get_item(val);
    if(p == NULL){	
	loop_logic(p, val_p, key, val);
    } else {
	if(p->in_cycle == TRUE) {
//	    printf("umnmark: %s\n", p->key);
	    unmark_cycle(p);
	    loop_logic(p, val_p, key, val);
	} else {
	    loop_logic(p, val_p, key, val);
	}
    }

}/* END logical_add_id_to_dict */

loop_logic(DR p, DR val_p, const char *key, const char *val){

    boolean breakLoop = FALSE;
    while(!breakLoop){
	if(val_p == NULL){
	    add_id_to_dict(key, val);
	    breakLoop = TRUE;
	} else {
	    if(val_p->tag == STR_CONST || val_p->tag == INT_CONST || val_p->in_cycle == TRUE){
	        add_id_to_dict(key, val);
	        breakLoop = TRUE;
	    } else {
//		printf("Vals to check: %s to %s\n", key, val_p->u.idval);
	        if(strstr(key, val_p->u.idval) && strstr(val_p->u.idval, key)){
		    add_id_to_dict(key, val);
//		    printf("mark: %s\n", val_p->key);
		    mark_cycle(val_p);
		    breakLoop = TRUE;
	        } else {
		    val_p = (DR) get_item(val_p->u.idval);
	        }
	    }
	}
    }

}/* END loop_logic */
