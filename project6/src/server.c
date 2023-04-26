#include "../include/interface.h"
#include "../include/structures.h"
#include <stdlib.h>
#include <string.h>

static int callback(void *data, int argc, char **argv, char **azColName){
	int i;
    fprintf (stderr, "%s:\n", (const char *)data);
    for (i = 0; i < argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void select_int(char *query, char *buffer, int what_to_select){
    printf("Enter %s: ", buffer);
    int num;
    scanf("%d", &num);
    strcat(query, col[what_to_select]);
    strcat(query, " = ");
    int length = snprintf(NULL, 0, "%d", num);
    char *str = malloc(length + 1);
    snprintf(str, length + 1, "%d", num);
    strcat(query, str);
    free(str);
}

void select_char(char *query, char *buffer, int what_to_select){
    printf("Enter %s: ", buffer);
    char *str = malloc(20 * sizeof(char));
    scanf("%s", str);
    strcat(query, col[what_to_select]);
    strcat(query, " = '");
    strcat(query, str);
    strcat(query, "'");
    free(str);
}

void select_where(char *query){
    int field;
    strcat(query, commands[WHERE]);
    while(1){
        printf("Choose the field:\n"
               "1 - ID\n"
               "2 - NAME\n"
               "3 - AMOUNT\n"
               "4 - NETPRICE\n"
               "5 - GROSSPRICE\n"
               "6 - PRODUCTIONDATE\n"
               "7 - MANUFACTURER\n"
               "8 - PHONENUMBER\n"
               "9 - ADDRESS\n"
               "10 - SHOP_ID\n"
               "Enter: ");
        scanf("%d", &field);
        switch(field){
            case(1):
                select_int(query, "ID", ID);
                break;
            case(2):
                select_char(query, "NAME", NAME);
                break;
            case(3):
                select_int(query, "AMOUNT", AMOUNT);
                break;
            case(4):
                select_int(query, "NETPRICE", NETPRICE);
                break;
            case(5):
                select_int(query, "GROSSPRICE", GROSSPRICE);
                break;
            case(6):
                select_char(query, "PRODUCTIONDATE", PRODUCTIONDATE);
                break;
            case(7):
                select_char(query, "MANUFACTURER", MANUFACTURER);
                break;
            case(8):
                select_int(query, "PHONENUMBER", PHONENUMBER);
                break;
            case(9):
                select_char(query, "ADDRESS", ADDRESS);
                break;
            case(10):
                select_int(query, "SHOP_ID", SHOP_ID);
                break;
            default:
                printf("Wrong input!\n");
                continue;
        }
        break;
    }
}

void create_select_query(char *query){
    int global;
    strcat(query, commands[SELECT]);
    while(1){
        printf("Choose condition type:\n"
               "1 - no condition\n"
               "2 - with condition\n"
               "Enter: ");
        scanf("%d", &global );
        switch(global){
            case(1):
                return;
            case(2):
                select_where(query);
                return;
            default:
                printf("Wrong input!\n");
                continue;
        }
    }
}

void input_str_field(char *query, char *buffer, int what_to_enter){
    char *str_buffer = malloc(sizeof(char) * 80);
    printf("%s: ", col[what_to_enter]);
    scanf("%s", str_buffer);
    strcat(query, "'");
    strcat(query, str_buffer);
    strcat(query, "'");
    free(str_buffer);
}

void input_int_field(char *query, int what_to_enter){
    int buffer = 0;
    printf("%s: ", col[what_to_enter]);
    scanf("%d", &buffer);
    int length = snprintf(NULL, 0, "%d", buffer);
    char *str = malloc(length + 1);
    snprintf(str, length + 1, "%d", buffer);
    strcat(query, str);
    free(str);
}

void create_insert_query(char *query) {    
    strcat(query, commands[INSERT]);    
    printf("Enter the insert values:\n");
    input_int_field(query, ID);
    strcat(query, ", ");
    input_str_field(query, "NAME", NAME);
    strcat(query, ", ");
    input_int_field(query, AMOUNT);
    strcat(query, ", ");
    input_int_field(query, NETPRICE);
    strcat(query, ", ");
    input_int_field(query, GROSSPRICE);
    strcat(query, ", ");
    input_str_field(query, "PRODUCTIONDATE", PRODUCTIONDATE);
    strcat(query, ", ");
    input_str_field(query, "MANUFACTURER", MANUFACTURER);
    strcat(query, ", ");
    input_int_field(query, PHONENUMBER);
    strcat(query, ", ");
    input_str_field(query, "ADDRESS", ADDRESS);
    strcat(query, ", ");
    input_int_field(query, SHOP_ID);
    strcat(query, "); ");
}

void create_delete_query(char *query){
    strcat(query, commands[DELETE]);
    strcat(query, commands[WHERE]);
    select_int(query, "ID", ID);
}

int process_menu_actions(sqlite3 *db) {
    char *zErrMsg = 0;
    int rc;
    const char *data = "Callback function called";    
    int mode = 0;
    char *query = malloc(sizeof(char) * 800);
    int input;
    while(1){
        printf("Choose mode:\n"
               "\t1 - AUTOCOMMIT MODE\n"
               "\t2 - TRANSACTION MODE\n"
               "\t3 - EXIT\n"
               "Enter: ");
        scanf("%d", &mode);
        switch(mode){
            case(1):
                break;
            case(2):
                strcat(query, commands[BEGIN]);
                break;
            case(3):
                printf("Exit\n");
                free(query);
                return 1;
            default:
                printf("Wrong input! Try again\n");
                continue;
        }
        break;
    }
  
    while(1){
        printf("Menu:\n"
               "\t1 - SELECT\n"
               "\t2 - INSERT\n"
               "\t3 - DELETE\n"
               "\t4 - exit\n"
               "ENTER: ");
        
        scanf("%d", &input);
        switch(input){
            case(1):
                create_select_query(query);
                break;
            case(2):
                create_insert_query(query);
                break;
            case(3):
                create_delete_query(query);
                break;
            case(4):
                printf("exit\n");
                free(query);
                return 1;
            default:
                printf("Wrong input!\n");
                continue;
        }
        break;
    }

    if (mode == 2 && input != 4)
        strcat(query, commands[COMMIT]);    
   
    rc = sqlite3_exec(db, query, callback, (void *)data, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Operation done successfully\n");
    }
    free(query);
    return 0;
}
