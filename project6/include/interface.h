#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include <sqlite3.h>

int process_menu_actions(sqlite3 *db);
static int callback(void *data, int argc, char **argv, char **azColName);
void select_int(char *query, char *buffer, int what_to_select);
void select_char(char *query, char *buffer, int what_to_select);
void select_where(char *query);
void create_select_query(char *query);
void input_str_field(char *query, char *buffer, int what_to_enter);
void input_int_field(char *query, int what_to_enter);
void create_insert_query(char *query);
void create_delete_query(char *query);

#endif
