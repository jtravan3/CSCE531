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
		    logical_add_str_to_dict(key_str, str);
		} else {
		    logical_add_id_to_dict(key_str, str);
		}
		
		isStrConst = FALSE;
	    }

	    isValExpected = FALSE;
	} else {
	    if(!isDefineLine){
		    // output the goods
	    } else{
		printf("%s", text);
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
	if(p->in_cycle == TRUE){
	    while(p->in_cycle == TRUE){
		unmark_cycle(p);
		p = (DR) get_item(p->u.idval);
	    }
   	    add_str_to_dict(key, val);
	    fprintf(stderr, "Warning: redefinition of %s to %s at line %d", key, val, line_num);
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
	    fprintf(stderr, "Warning: redefinition of %s to %lu at line %d", key, val, line_num);
	} else {
	    add_int_to_dict(key, val);
	}
    }

}/* END logical_add_int_to_dict(*char, *char) */

logical_add_id_to_dict(const char *key, const char *val){

    DR p = (DR) get_item(key);
    if(p == NULL){
	boolean breakLoop = FALSE;
	DR val_p = (DR) get_item(val);
	while(!breakLoop){
	    if(val_p == NULL){
		add_id_to_dict(key, val);
		printf("Key not in Dictionary. Added. Break loop called.\n");
		breakLoop = TRUE;
	    } else { 
		if(val_p->in_cycle == TRUE){
		    add_id_to_dict(key, val);
		    printf("Traced to a marked value. Added. Break loop called\n");
		    breakLoop = TRUE;
		} else {
		    if(val_p->tag == INT_CONST || val_p->tag == STR_CONST){
			add_id_to_dict(key, val);
			printf("Traced to a non-ID entry. Added. Break loop called\n");
			breakLoop = TRUE;
		    } else {
			if(strstr(key, val_p->u.idval) && strstr(val_p->u.idval, key)){	
			    printf("LOOP DETECTED. HANDLE IT.\n");
			    breakLoop = TRUE;
			} else {
			    val_p = (DR) get_item(val_p->u.idval);			    
			    printf("Did not break. Continue looping\n");
			}
		    }
		}
	    }
	}
    } else {
	// key is already in dictionary
    }

}

//logical_add_id_to_dict(const char *key, const char *val){
//
//    DR p = (DR) get_item(key);
//    if(p == NULL){
//	add_id_to_dict(key, val);
//    } else {
//	if(p->in_cycle == TRUE){
//	    while(p->in_cycle == TRUE){
//		unmark_cycle(p);
//		p = (DR) get_item(p->u.idval);
//	    }
//	    add_id_to_dict(key, val);
//	    if(isFirstIdRedefine){
//		fprintf(stderr, "Warning: redefinition of %s to %s at line %d", key, val, line_num);
//		isFirstIdRedefine = FALSE;
//	    } else {
//	    	fprintf(stderr, "\nWarning: redefinition of %s to %s at line %d", key, val, line_num);
//	    }
//	} else {
//	    DR val_p = (DR) get_item(val);
//	    if(val_p == NULL){
//		add_id_to_dict(key, val);
//	    } else {
//		boolean needsMarking = FALSE;
//		while(val_p != NULL){
//		    if(((DR) get_item(val_p->u.idval)) == p) {
//			needsMarking = TRUE;
//			val_p == NULL;
//		    } else {
//			val_p = (DR) get_item(val_p->u.idval);
//		    }
//		}
//
//		if(needsMarking == TRUE){
//		    while(val_p->in_cycle == FALSE){
//			mark_cycle(val_p);
//			val_p = (DR) get_item(val_p->u.idval);
//		    }
//		    add_id_to_dict(key, val);
//		} else {
//		    add_id_to_dict(key, val);
//		}
//
//		if(isFirstIdRedefine){
//		    fprintf(stderr, "Warning: redefinition of %s to %s at line %d", key, val, line_num);
//		    isFirstIdRedefine = FALSE;
//		} else {
//		    fprintf(stderr, "\nWarning: redefinition of %s to %s at line %d", key, val, line_num);
//		}
//	    }
//	}
//    }
//
//}/* END logical_add_id_to_dict(*char, *char) */
