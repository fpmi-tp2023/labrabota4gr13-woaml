#include "../include/interface.h"
#include <stdio.h>

int main() {
    sqlite3 *db;
    
    if (sqlite3_open("db/NewTask2.db", &db) != 0) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    
	while(1){
		if (process_menu_actions(db) == -1){
			break;
		}
	}
    sqlite3_close(db);
    return 0;
}
