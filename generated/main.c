/* Processed by ecpg (18.1) */
/* These include files are added by the preprocessor */
#include <ecpglib.h>
#include <ecpgerrno.h>
#include <sqlca.h>
/* End of automatic include section */

#line 1 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>


#line 1 "c:\\Program Files\\PostgreSQL\\18\\include/sqlca.h"
#ifndef POSTGRES_SQLCA_H
#define POSTGRES_SQLCA_H

#ifndef PGDLLIMPORT
#if  defined(WIN32) || defined(__CYGWIN__)
#define PGDLLIMPORT __declspec (dllimport)
#else
#define PGDLLIMPORT
#endif							/* __CYGWIN__ */
#endif							/* PGDLLIMPORT */

#define SQLERRMC_LEN	150

#ifdef __cplusplus
extern "C"
{
#endif

struct sqlca_t
{
	char		sqlcaid[8];
	long		sqlabc;
	long		sqlcode;
	struct
	{
		int			sqlerrml;
		char		sqlerrmc[SQLERRMC_LEN];
	}			sqlerrm;
	char		sqlerrp[8];
	long		sqlerrd[6];
	/* Element 0: empty						*/
	/* 1: OID of processed tuple if applicable			*/
	/* 2: number of rows processed				*/
	/* after an INSERT, UPDATE or				*/
	/* DELETE statement					*/
	/* 3: empty						*/
	/* 4: empty						*/
	/* 5: empty						*/
	char		sqlwarn[8];
	/* Element 0: set to 'W' if at least one other is 'W'	*/
	/* 1: if 'W' at least one character string		*/
	/* value was truncated when it was			*/
	/* stored into a host variable.             */

	/*
	 * 2: if 'W' a (hopefully) non-fatal notice occurred
	 */	/* 3: empty */
	/* 4: empty						*/
	/* 5: empty						*/
	/* 6: empty						*/
	/* 7: empty						*/

	char		sqlstate[5];
};

struct sqlca_t *ECPGget_sqlca(void);

#ifndef POSTGRES_ECPG_INTERNAL
#define sqlca (*ECPGget_sqlca())
#endif

#ifdef __cplusplus
}
#endif

#endif

#line 8 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"


/* exec sql begin declare section */
     
     
     
     
     
     
     
     
     
     
       
     
     
     
     
     
     
     
     
     

     
     
     
     
     

#line 11 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"
 char conn_str [ 128 ] ;
 
#line 12 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"
 char username [ 64 ] ;
 
#line 13 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"
 char password [ 64 ] ;
 
#line 14 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"
 char title [ 256 ] ;
 
#line 15 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"
 char author [ 256 ] ;
 
#line 16 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"
 char genre [ 256 ] ;
 
#line 17 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"
 int book_year ;
 
#line 18 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"
 int book_id ;
 
#line 19 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"
 int search_choice ;
 
#line 20 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"
 char search_value [ 256 ] ;
 
#line 21 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"
 int is_admin = 0 ;
 
#line 22 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"
 char new_username [ 64 ] ;
 
#line 23 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"
 char new_password [ 64 ] ;
 
#line 24 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"
 char new_role [ 32 ] ;
 
#line 25 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"
 char current_schema [ 128 ] ;
 
#line 26 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"
 char db_host [ 64 ] ;
 
#line 27 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"
 char db_port [ 16 ] ;
 
#line 28 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"
 char db_name [ 64 ] ;
 
#line 29 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"
 char db_admin_user [ 64 ] ;
 
#line 30 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"
 char db_admin_pass [ 64 ] ;
 
#line 32 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"
 int out_id ;
 
#line 33 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"
  struct varchar_1  { int len; char arr[ 256 ]; }  out_title ;
 
#line 34 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"
  struct varchar_2  { int len; char arr[ 256 ]; }  out_author ;
 
#line 35 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"
  struct varchar_3  { int len; char arr[ 256 ]; }  out_genre ;
 
#line 36 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"
 int out_year ;
/* exec sql end declare section */
#line 37 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"


void log_message(const char* message) {
    FILE* log_file = fopen("app.log", "a");
    if (log_file) {
        time_t now;
        time(&now);
        char* timestamp = ctime(&now);
        timestamp[strlen(timestamp) - 1] = '\0';
        
        fprintf(log_file, "[%s] %s\n", timestamp, message);
        fclose(log_file);
    }
}

void log_action(const char* action, const char* details) {
    char log_entry[512];
    sprintf_s(log_entry, sizeof(log_entry), "%s: %s", action, details);
    log_message(log_entry);
}

void print_sql_error() {
    if (sqlca.sqlcode < 0) {
        printf("\n=== SQL ERROR ===\n");
        printf("Code: %ld\n", sqlca.sqlcode);
        printf("Message: %s\n", sqlca.sqlerrm.sqlerrmc);
        printf("SQLSTATE: %s\n", sqlca.sqlstate);
        printf("=================\n\n");
        
        char error_log[512];
        sprintf_s(error_log, sizeof(error_log), 
                  "SQL ERROR - Code: %ld, Message: %s, SQLSTATE: %s",
                  sqlca.sqlcode, sqlca.sqlerrm.sqlerrmc, sqlca.sqlstate);
        log_message(error_log);
    }
}

void clear_screen() {
    system("cls");
}

void print_book_row() {
    printf("| %5d | %-40s | %-30s | %-20s | %4d |\n",
           out_id,
           out_title.arr,
           out_author.arr,
           out_genre.arr,
           out_year);
}

void show_all_books() {
    log_action("Action", "Show all books started");
    /* declare books_cur cursor for select * from sp_get_all_books ( ) */
#line 89 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare books_cur cursor for select * from sp_get_all_books ( )", ECPGt_EOIT, ECPGt_EORT);}
#line 91 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

    if (sqlca.sqlcode != 0) { 
        print_sql_error(); 
        log_action("Error", "Failed to show all books");
        return; 
    }

    printf("\n=== All Books ===\n");
    printf("|  ID   | Title                                    | Author                         | Genre                | Year |\n");
    printf("|-------|------------------------------------------|--------------------------------|----------------------|------|\n");

    int book_count = 0;
    for (;;) {
        { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch next from books_cur", ECPGt_EOIT, 
	ECPGt_int,&(out_id),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_varchar,&(out_title),(long)256,(long)1,sizeof(struct varchar_1), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_varchar,&(out_author),(long)256,(long)1,sizeof(struct varchar_2), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_varchar,&(out_genre),(long)256,(long)1,sizeof(struct varchar_3), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_int,&(out_year),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 105 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"


        if (sqlca.sqlcode != 0) break;

        print_book_row();
        book_count++;
    }

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close books_cur", ECPGt_EOIT, ECPGt_EORT);}
#line 113 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

    printf("\nTotal books: %d\n", book_count);
    
    char log_detail[256];
    sprintf_s(log_detail, sizeof(log_detail), "Displayed %d books", book_count);
    log_action("Show all books completed", log_detail);
}

void search_books() {
    printf("\nSearch by:\n");
    printf("1 - Title\n");
    printf("2 - Author\n");
    printf("3 - Genre\n");
    printf("Choice: ");
    scanf_s("%d", &search_choice);
    getchar();

    printf("Enter search value: ");
    fgets(search_value, sizeof(search_value), stdin);
    search_value[strcspn(search_value, "\n")] = 0;

    char search_log[256];
    sprintf_s(search_log, sizeof(search_log), "Search by choice %d, value: '%s'", 
              search_choice, search_value);
    log_action("Search started", search_log);

    if (search_choice == 1) {
        /* declare search_cur_title cursor for select * from sp_find_by_title ( $1  ) */
#line 140 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

        { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare search_cur_title cursor for select * from sp_find_by_title ( $1  )", 
	ECPGt_char,(search_value),(long)256,(long)1,(256)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);}
#line 141 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

        if (sqlca.sqlcode != 0) { 
            print_sql_error(); 
            log_action("Error", "Search by title failed");
            return; 
        }
        
        printf("\n=== Search Results ===\n");
        printf("|  ID   | Title                                    | Author                         | Genre                | Year |\n");
        printf("|-------|------------------------------------------|--------------------------------|----------------------|------|\n");

        int count = 0;
        for (;;) {
            { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch next from search_cur_title", ECPGt_EOIT, 
	ECPGt_int,&(out_id),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_varchar,&(out_title),(long)256,(long)1,sizeof(struct varchar_1), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_varchar,&(out_author),(long)256,(long)1,sizeof(struct varchar_2), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_varchar,&(out_genre),(long)256,(long)1,sizeof(struct varchar_3), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_int,&(out_year),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 154 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

            if (sqlca.sqlcode != 0) break;
            print_book_row();
            count++;
        }
        
        { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close search_cur_title", ECPGt_EOIT, ECPGt_EORT);}
#line 160 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

        printf("\nFound records: %d\n", count);
        
        sprintf_s(search_log, sizeof(search_log), "Found %d books by title '%s'", count, search_value);
        log_action("Search completed", search_log);
        
    } else if (search_choice == 2) {
        /* declare search_cur_author cursor for select * from sp_find_by_author ( $1  ) */
#line 167 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

        { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare search_cur_author cursor for select * from sp_find_by_author ( $1  )", 
	ECPGt_char,(search_value),(long)256,(long)1,(256)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);}
#line 168 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

        if (sqlca.sqlcode != 0) { 
            print_sql_error(); 
            log_action("Error", "Search by author failed");
            return; 
        }
        
        printf("\n=== Search Results ===\n");
        printf("|  ID   | Title                                    | Author                         | Genre                | Year |\n");
        printf("|-------|------------------------------------------|--------------------------------|----------------------|------|\n");

        int count = 0;
        for (;;) {
            { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch next from search_cur_author", ECPGt_EOIT, 
	ECPGt_int,&(out_id),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_varchar,&(out_title),(long)256,(long)1,sizeof(struct varchar_1), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_varchar,&(out_author),(long)256,(long)1,sizeof(struct varchar_2), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_varchar,&(out_genre),(long)256,(long)1,sizeof(struct varchar_3), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_int,&(out_year),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 181 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

            if (sqlca.sqlcode != 0) break;
            print_book_row();
            count++;
        }
        
        { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close search_cur_author", ECPGt_EOIT, ECPGt_EORT);}
#line 187 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

        printf("\nFound records: %d\n", count);
        
        sprintf_s(search_log, sizeof(search_log), "Found %d books by author '%s'", count, search_value);
        log_action("Search completed", search_log);
        
    } else if (search_choice == 3) {
        /* declare search_cur_genre cursor for select * from sp_find_by_genre ( $1  ) */
#line 194 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

        { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare search_cur_genre cursor for select * from sp_find_by_genre ( $1  )", 
	ECPGt_char,(search_value),(long)256,(long)1,(256)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);}
#line 195 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

        if (sqlca.sqlcode != 0) { 
            print_sql_error(); 
            log_action("Error", "Search by genre failed");
            return; 
        }
        
        printf("\n=== Search Results ===\n");
        printf("|  ID   | Title                                    | Author                         | Genre                | Year |\n");
        printf("|-------|------------------------------------------|--------------------------------|----------------------|------|\n");

        int count = 0;
        for (;;) {
            { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch next from search_cur_genre", ECPGt_EOIT, 
	ECPGt_int,&(out_id),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_varchar,&(out_title),(long)256,(long)1,sizeof(struct varchar_1), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_varchar,&(out_author),(long)256,(long)1,sizeof(struct varchar_2), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_varchar,&(out_genre),(long)256,(long)1,sizeof(struct varchar_3), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_int,&(out_year),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 208 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

            if (sqlca.sqlcode != 0) break;
            print_book_row();
            count++;
        }
        
        { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close search_cur_genre", ECPGt_EOIT, ECPGt_EORT);}
#line 214 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

        printf("\nFound records: %d\n", count);
        
        sprintf_s(search_log, sizeof(search_log), "Found %d books by genre '%s'", count, search_value);
        log_action("Search completed", search_log);
        
    } else {
        printf("Invalid choice!\n");
        log_action("Warning", "Invalid search choice");
        return;
    }
}

void add_book() {
    if (!is_admin) { 
        printf("Access denied!\n");
        log_action("Warning", "Non-admin tried to add book");
        return; 
    }

    printf("Title: ");   fgets(title,   sizeof(title),   stdin); title[strcspn(title, "\n")] = 0;
    printf("Author: ");  fgets(author,  sizeof(author),  stdin); author[strcspn(author, "\n")] = 0;
    printf("Genre: ");   fgets(genre,   sizeof(genre),   stdin); genre[strcspn(genre, "\n")] = 0;
    printf("Year: ");    scanf_s("%d", &book_year); getchar();

    char book_log[512];
    sprintf_s(book_log, sizeof(book_log), "Adding book: '%s' by %s, genre %s, year %d", 
              title, author, genre, book_year);
    log_action("Add book started", book_log);

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "call sp_add_book ( $1  , $2  , $3  , $4  )", 
	ECPGt_char,(title),(long)256,(long)1,(256)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(author),(long)256,(long)1,(256)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(genre),(long)256,(long)1,(256)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_int,&(book_year),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);}
#line 244 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

    if (sqlca.sqlcode == 0) {
        printf("Book added successfully!\n");
        log_action("Add book completed", book_log);
    } else {
        print_sql_error();
        log_action("Add book failed", book_log);
    }
}

void update_book() {
    if (!is_admin) { 
        printf("Access denied!\n");
        log_action("Warning", "Non-admin tried to update book");
        return; 
    }

    printf("Book ID to update: ");
    scanf_s("%d", &book_id); getchar();

    printf("New title: ");  fgets(title,   sizeof(title),   stdin); title[strcspn(title, "\n")] = 0;
    printf("New author: "); fgets(author,  sizeof(author),  stdin); author[strcspn(author, "\n")] = 0;
    printf("New genre: ");  fgets(genre,   sizeof(genre),   stdin); genre[strcspn(genre, "\n")] = 0;
    printf("New year: ");   scanf_s("%d", &book_year); getchar();

    char update_log[512];
    sprintf_s(update_log, sizeof(update_log), 
              "Updating book ID %d: title='%s', author='%s', genre='%s', year=%d", 
              book_id, title, author, genre, book_year);
    log_action("Update book started", update_log);

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "call sp_update_book ( $1  , $2  , $3  , $4  , $5  )", 
	ECPGt_int,&(book_id),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(title),(long)256,(long)1,(256)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(author),(long)256,(long)1,(256)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(genre),(long)256,(long)1,(256)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_int,&(book_year),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);}
#line 275 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

    if (sqlca.sqlcode == 0) {
        printf("Book updated successfully!\n");
        log_action("Update book completed", update_log);
    } else {
        print_sql_error();
        log_action("Update book failed", update_log);
    }
}

void delete_by_id() {
    if (!is_admin) { 
        printf("Access denied!\n");
        log_action("Warning", "Non-admin tried to delete book");
        return; 
    }

    printf("Book ID to delete: ");
    scanf_s("%d", &book_id); getchar();

    char delete_log[128];
    sprintf_s(delete_log, sizeof(delete_log), "Deleting book ID %d", book_id);
    log_action("Delete book started", delete_log);

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "call sp_delete_by_id ( $1  )", 
	ECPGt_int,&(book_id),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);}
#line 299 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

    if (sqlca.sqlcode == 0) {
        printf("Book deleted successfully!\n");
        log_action("Delete book completed", delete_log);
    } else {
        print_sql_error();
        log_action("Delete book failed", delete_log);
    }
}

void clear_table() {
    if (!is_admin) { 
        printf("Access denied!\n");
        log_action("Warning", "Non-admin tried to clear table");
        return; 
    }

    char confirm[10];
    printf("Clear entire table? (yes/no): ");
    fgets(confirm, sizeof(confirm), stdin);
    if (strncmp(confirm, "yes", 3) != 0) {
        log_action("Clear table", "Cancelled by user");
        return;
    }

    log_action("Clear table started", "Clearing all books");
    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "call sp_clear_table ( )", ECPGt_EOIT, ECPGt_EORT);}
#line 325 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

    if (sqlca.sqlcode == 0) {
        printf("Table cleared successfully!\n");
        log_action("Clear table completed", "All books removed");
    } else {
        print_sql_error();
        log_action("Clear table failed", "SQL error occurred");
    }
}

void create_user() {
    if (!is_admin) {
        printf("Access denied!\n");
        log_action("Warning", "Non-admin tried to create user");
        return;
    }

    printf("New username: ");
    fgets(new_username, sizeof(new_username), stdin);
    new_username[strcspn(new_username, "\n")] = 0;

    printf("New password: ");
    fgets(new_password, sizeof(new_password), stdin);
    new_password[strcspn(new_password, "\n")] = 0;

    printf("Role (admin_role / guest_role): ");
    fgets(new_role, sizeof(new_role), stdin);
    new_role[strcspn(new_role, "\n")] = 0;

    char user_log[256];
    sprintf_s(user_log, sizeof(user_log), "Creating user: %s, role: %s", new_username, new_role);
    log_action("Create user started", user_log);

    printf("[DEBUG] Creating user:\n");
    printf("Username: '%s'\n", new_username);
    printf("Password: '%s'\n", new_password);
    printf("Role: '%s'\n", new_role);

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "call sp_create_db_user ( $1  , $2  , $3  )", 
	ECPGt_char,(new_username),(long)64,(long)1,(64)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(new_password),(long)64,(long)1,(64)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(new_role),(long)32,(long)1,(32)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);}
#line 363 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"


    if (sqlca.sqlcode == 0) {
        printf("User created successfully!\n");
        printf("[LOG] Create user %s role=%s\n", new_username, new_role);
        log_action("Create user completed", user_log);
    } else {
        print_sql_error();
        log_action("Create user failed", user_log);
    }
}

int database_exists(const char* host, const char* port, const char* dbname) {
    char temp_conn_str[128];
    sprintf_s(temp_conn_str, sizeof(temp_conn_str), "postgres@%s:%s", host, port);
    
    /* exec sql begin declare section */
         
         
           
    
#line 380 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"
 char check_conn_str [ 128 ] ;
 
#line 381 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"
 char check_dbname [ 64 ] ;
 
#line 382 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"
 int exists = 0 ;
/* exec sql end declare section */
#line 383 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

    
    strcpy_s(check_conn_str, sizeof(check_conn_str), temp_conn_str);
    strcpy_s(check_dbname, sizeof(check_dbname), dbname);
    
    { ECPGconnect(__LINE__, 0, check_conn_str , "postgres" , "admin" , NULL, 0); }
#line 388 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

    
    if (sqlca.sqlcode != 0) {
        printf("Cannot connect to postgres database for checking.\n");
        log_action("Database check", "Failed to connect to postgres database");
        return 0;
    }
    
    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select count ( * ) from pg_database where datname = $1 ", 
	ECPGt_char,(check_dbname),(long)64,(long)1,(64)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, 
	ECPGt_int,&(exists),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 396 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

    
    { ECPGdisconnect(__LINE__, "CURRENT");}
#line 398 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

    
    return exists;
}

int create_database(const char* host, const char* port, const char* dbname) {
    char temp_conn_str[128];
    sprintf_s(temp_conn_str, sizeof(temp_conn_str), "postgres@%s:%s", host, port);
    
    /* exec sql begin declare section */
         
         
    
#line 408 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"
 char create_conn_str [ 128 ] ;
 
#line 409 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"
 char new_dbname [ 64 ] ;
/* exec sql end declare section */
#line 410 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

    
    strcpy_s(create_conn_str, sizeof(create_conn_str), temp_conn_str);
    strcpy_s(new_dbname, sizeof(new_dbname), dbname);
    
    char db_log[256];
    sprintf_s(db_log, sizeof(db_log), "Attempting to create database '%s'", dbname);
    log_action("Database creation started", db_log);
    
    { ECPGconnect(__LINE__, 0, create_conn_str , "postgres" , "admin" , NULL, 0); }
#line 419 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

    
    if (sqlca.sqlcode != 0) {
        printf("Cannot connect to postgres database for creation.\n");
        log_action("Database creation failed", "Cannot connect to postgres");
        return 0;
    }
    
    /* exec sql begin declare section */
         
    
#line 428 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"
 char create_sql [ 256 ] ;
/* exec sql end declare section */
#line 429 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

    
    sprintf_s(create_sql, sizeof(create_sql), "CREATE DATABASE %s", dbname);
    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_exec_immediate, create_sql, ECPGt_EOIT, ECPGt_EORT);}
#line 432 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

    
    if (sqlca.sqlcode != 0) {
        print_sql_error();
        { ECPGdisconnect(__LINE__, "CURRENT");}
#line 436 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

        sprintf_s(db_log, sizeof(db_log), "Database '%s' creation failed", dbname);
        log_action("Database creation failed", db_log);
        return 0;
    }
    
    printf("Database '%s' created successfully.\n", dbname);
    sprintf_s(db_log, sizeof(db_log), "Database '%s' created successfully", dbname);
    log_action("Database creation completed", db_log);
    
    { ECPGdisconnect(__LINE__, "CURRENT");}
#line 446 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

    return 1;
}

int setup_database() {
    printf("\n=== Database Setup ===\n");
    
    printf("Host [localhost]: ");
    fgets(db_host, sizeof(db_host), stdin);
    db_host[strcspn(db_host, "\n")] = 0;
    if (strlen(db_host) == 0) strcpy_s(db_host, sizeof(db_host), "localhost");
    
    printf("Port [5433]: ");
    fgets(db_port, sizeof(db_port), stdin);
    db_port[strcspn(db_port, "\n")] = 0;
    if (strlen(db_port) == 0) strcpy_s(db_port, sizeof(db_port), "5433");
    
    printf("Database name [library]: ");
    fgets(db_name, sizeof(db_name), stdin);
    db_name[strcspn(db_name, "\n")] = 0;
    if (strlen(db_name) == 0) strcpy_s(db_name, sizeof(db_name), "library");
    
    printf("\nOptions:\n");
    printf("1. Connect to existing database\n");
    printf("2. Create new database\n");
    printf("Choice: ");
    
    int choice;
    scanf_s("%d", &choice);
    getchar();
    
    if (choice == 2) {
        if (database_exists(db_host, db_port, db_name)) {
            printf("Database '%s' already exists.\n", db_name);
            char exists_log[256];
            sprintf_s(exists_log, sizeof(exists_log), "Database '%s' already exists", db_name);
            log_action("Database setup", exists_log);
            printf("Connect to it? (y/n): ");
            char confirm = getchar();
            getchar();
            if (confirm == 'y' || confirm == 'Y') {
                return 1;
            } else {
                return 0;
            }
        } else {
            if (!create_database(db_host, db_port, db_name)) {
                printf("Failed to create database.\n");
                return 0;
            }
            printf("Database created. Please initialize it with the Java application first.\n");
            printf("Press Enter to continue with connection...");
            getchar();
        }
    }
    
    return 1;
}

int main() {
    SetConsoleOutputCP(1251);
    system("chcp 1251 > nul");

    log_message("=== Application Started ===");
    log_action("Version", "ECPG Library Management System");

    int action;
    int back_to_start = 0;
    
    do {
        back_to_start = 0;
        clear_screen();
        
        printf("=== Main Menu ===\n");
        printf("1. Connect to existing database\n");
        printf("2. Create new database\n");
        printf("0. Exit\n");
        printf("Choice: ");
        
        scanf_s("%d", &action);
        getchar();

        if (action == 0) {
            log_message("=== Application Ended ===");
            printf("Ending of work...\n");
            return 0;
        }

        if (action != 1 && action != 2) {
            printf("Invalid choice. Please try again.\n");
            printf("\nPress Enter to continue...");
            getchar();
            continue;
        }

        char menu_log[128];
        sprintf_s(menu_log, sizeof(menu_log), "Selected option: %s", 
                  action == 1 ? "Connect to existing" : "Create new");
        log_action("Main Menu", menu_log);

        printf("\n=== PostgreSQL Server Connection (enter 0 to go back) ===\n");
        
        printf("Host [localhost]: ");
        fgets(db_host, sizeof(db_host), stdin);
        db_host[strcspn(db_host, "\n")] = 0;
        if (strlen(db_host) == 1 && db_host[0] == '0') { 
            log_action("Setup", "Returned to main menu");
            back_to_start = 1; 
            continue; 
        }
        if (strlen(db_host) == 0) strcpy_s(db_host, sizeof(db_host), "localhost");
        
        printf("Port [5433]: ");
        fgets(db_port, sizeof(db_port), stdin);
        db_port[strcspn(db_port, "\n")] = 0;
        if (strlen(db_port) == 1 && db_port[0] == '0') { 
            log_action("Setup", "Returned to main menu");
            back_to_start = 1; 
            continue; 
        }
        if (strlen(db_port) == 0) strcpy_s(db_port, sizeof(db_port), "5433");
        
        printf("Superuser [postgres]: ");
        fgets(db_admin_user, sizeof(db_admin_user), stdin);
        db_admin_user[strcspn(db_admin_user, "\n")] = 0;
        if (strlen(db_admin_user) == 1 && db_admin_user[0] == '0') { 
            log_action("Setup", "Returned to main menu");
            back_to_start = 1; 
            continue; 
        }
        if (strlen(db_admin_user) == 0) strcpy_s(db_admin_user, sizeof(db_admin_user), "postgres");
        
        printf("Superuser password (enter 0 to go back): ");
        fgets(db_admin_pass, sizeof(db_admin_pass), stdin);
        db_admin_pass[strcspn(db_admin_pass, "\n")] = 0;
        if (strlen(db_admin_pass) == 1 && db_admin_pass[0] == '0') { 
            log_action("Setup", "Returned to main menu");
            back_to_start = 1; 
            continue; 
        }

        char temp_conn_str[128];
        sprintf_s(temp_conn_str, sizeof(temp_conn_str), "%s@%s:%s", "postgres", db_host, db_port);
        
        /* exec sql begin declare section */
             
             
               
        
#line 591 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"
 char check_conn_str [ 128 ] ;
 
#line 592 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"
 char check_dbname [ 64 ] ;
 
#line 593 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"
 int exists = 0 ;
/* exec sql end declare section */
#line 594 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

        
        strcpy_s(check_conn_str, sizeof(check_conn_str), temp_conn_str);
        
        printf("Connecting to PostgreSQL server...\n");
        log_action("Connection", "Attempting to connect to PostgreSQL server");
        { ECPGconnect(__LINE__, 0, check_conn_str , db_admin_user , db_admin_pass , NULL, 0); }
#line 600 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

        
        if (sqlca.sqlcode != 0) {
            print_sql_error();
            printf("Failed to connect to PostgreSQL server.\n");
            printf("Press Enter to try again or 0 to go back: ");
            char choice = getchar();
            getchar();
            if (choice == '0') { 
                log_action("Connection", "Connection failed, returning to main menu");
                back_to_start = 1; 
                continue; 
            }
            else continue;
        }
        log_action("Connection", "Successfully connected to PostgreSQL server");

        if (action == 2) {
            printf("\n=== Create New Database (enter 0 to go back) ===\n");
            printf("New database name: ");
            fgets(db_name, sizeof(db_name), stdin);
            db_name[strcspn(db_name, "\n")] = 0;
            
            if (strlen(db_name) == 1 && db_name[0] == '0') { 
                { ECPGdisconnect(__LINE__, "CURRENT");}
#line 624 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

                log_action("Setup", "Database creation cancelled, returning to main menu");
                back_to_start = 1; 
                continue; 
            }
            
            if (strlen(db_name) == 0) {
                printf("Database name cannot be empty.\n");
                { ECPGdisconnect(__LINE__, "CURRENT");}
#line 632 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

                continue;
            }

            strcpy_s(check_dbname, sizeof(check_dbname), db_name);
            
            { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select count ( * ) from pg_database where datname = $1 ", 
	ECPGt_char,(check_dbname),(long)64,(long)1,(64)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, 
	ECPGt_int,&(exists),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 638 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

            
            if (exists) {
                printf("Database '%s' already exists.\n", db_name);
                char exists_log[256];
                sprintf_s(exists_log, sizeof(exists_log), "Database '%s' already exists", db_name);
                log_action("Database creation", exists_log);

                printf("1. Connect to it\n");
                printf("2. Choose another name\n");
                printf("0. Go back\n");
                printf("Choice: ");
                
                int subchoice;
                scanf_s("%d", &subchoice);
                getchar();
                
                if (subchoice == 0) {
                    { ECPGdisconnect(__LINE__, "CURRENT");}
#line 656 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

                    log_action("Setup", "Database already exists, returning to main menu");
                    back_to_start = 1;
                    continue;
                } else if (subchoice == 1) {
                    action = 1;
                    log_action("Setup", "Will connect to existing database instead");
                } else {
                    { ECPGdisconnect(__LINE__, "CURRENT");}
#line 664 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

                    continue;
                }
            } else {
                printf("Creating database '%s'...\n", db_name);
                log_action("Database creation", db_name);
                
                /* exec sql begin declare section */
                     
                
#line 672 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"
 char create_sql [ 256 ] ;
/* exec sql end declare section */
#line 673 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

                
                sprintf_s(create_sql, sizeof(create_sql), "CREATE DATABASE %s", db_name);
                { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_exec_immediate, create_sql, ECPGt_EOIT, ECPGt_EORT);}
#line 676 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

                
                if (sqlca.sqlcode != 0) {
                    print_sql_error();
                    printf("Failed to create database.\n");
                    char fail_log[256];
                    sprintf_s(fail_log, sizeof(fail_log), "Database '%s' creation failed", db_name);
                    log_action("Database creation failed", fail_log);
                    printf("Press Enter to continue...");
                    getchar();
                    { ECPGdisconnect(__LINE__, "CURRENT");}
#line 686 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

                    continue;
                }
                
                printf("Database '%s' created successfully.\n", db_name);
                char db_log[128];
                sprintf_s(db_log, sizeof(db_log), "Database '%s' created successfully", db_name);
                log_action("Database creation", db_log);
            }
        }

        if (action == 1) {
            printf("\n=== Connect to Existing Database (enter 0 to go back) ===\n");
            printf("Database name: ");
            fgets(db_name, sizeof(db_name), stdin);
            db_name[strcspn(db_name, "\n")] = 0;
            
            if (strlen(db_name) == 1 && db_name[0] == '0') {
                { ECPGdisconnect(__LINE__, "CURRENT");}
#line 704 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

                log_action("Setup", "Connection cancelled, returning to main menu");
                back_to_start = 1; 
                continue; 
            }
            
            if (strlen(db_name) == 0) {
                printf("Database name cannot be empty.\n");
                { ECPGdisconnect(__LINE__, "CURRENT");}
#line 712 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

                continue;
            }
            
            strcpy_s(check_dbname, sizeof(check_dbname), db_name);
            { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select count ( * ) from pg_database where datname = $1 ", 
	ECPGt_char,(check_dbname),(long)64,(long)1,(64)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, 
	ECPGt_int,&(exists),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 717 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

            
            if (!exists) {
                printf("Database '%s' does not exist.\n", db_name);
                char not_exists_log[256];
                sprintf_s(not_exists_log, sizeof(not_exists_log), "Database '%s' does not exist", db_name);
                log_action("Database check", not_exists_log);

                printf("1. Try another name\n");
                printf("2. Create it\n");
                printf("0. Go back\n");
                printf("Choice: ");
                
                int subchoice;
                scanf_s("%d", &subchoice);
                getchar();
                
                if (subchoice == 0) {
                    { ECPGdisconnect(__LINE__, "CURRENT");}
#line 735 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

                    log_action("Setup", "Database not found, returning to main menu");
                    back_to_start = 1;
                    continue;
                } else if (subchoice == 2) {
                    action = 2;
                    { ECPGdisconnect(__LINE__, "CURRENT");}
#line 741 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

                    log_action("Setup", "Will create database instead");
                    continue;
                } else {
                    { ECPGdisconnect(__LINE__, "CURRENT");}
#line 745 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

                    continue;
                }
            }
        }

        { ECPGdisconnect(__LINE__, "CURRENT");}
#line 751 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"


        printf("\n=== User Login (enter 0 to go back) ===\n");
        printf("Username: ");
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = 0;
        if (strlen(username) == 1 && username[0] == '0') { 
            log_action("Login", "Login cancelled, returning to main menu");
            back_to_start = 1; 
            continue; 
        }
        
        printf("Password: ");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = 0;
        if (strlen(password) == 1 && password[0] == '0') { 
            log_action("Login", "Login cancelled, returning to main menu");
            back_to_start = 1; 
            continue; 
        }

        sprintf_s(conn_str, sizeof(conn_str), "%s@%s:%s", db_name, db_host, db_port);
        
        printf("\nConnecting to %s...\n", conn_str);
        printf("Username: %s\n", username);
        
        char login_log[256];
        sprintf_s(login_log, sizeof(login_log), "User '%s' attempting to connect to %s", 
                  username, conn_str);
        log_action("Login", login_log);
        
        { ECPGconnect(__LINE__, 0, conn_str , username , password , NULL, 0); }
#line 782 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"


        if (sqlca.sqlcode != 0) {
            print_sql_error();
            printf("Connection failed.\n");
            log_action("Login failed", "Could not connect to database");
            printf("Press Enter to try again or 0 to go back: ");
            char choice = getchar();
            getchar();
            if (choice == '0') { 
                log_action("Login", "Login failed, returning to main menu");
                back_to_start = 1; 
                continue; 
            }
            else continue;
        }

        printf("Connected successfully!\n");
        log_action("Login", "User successfully connected");

        { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select case when pg_has_role ( session_user , 'admin_role' , 'member' ) then 1 else 0 end", ECPGt_EOIT, 
	ECPGt_int,&(is_admin),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 807 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"


        printf("Mode: %s\n\n", is_admin ? "ADMINISTRATOR" : "GUEST");
        char mode_log[64];
        sprintf_s(mode_log, sizeof(mode_log), "User mode: %s", 
                  is_admin ? "ADMINISTRATOR" : "GUEST");
        log_action("Access", mode_log);
        
        printf("Press Enter to continue...");
        getchar();

        int choice;
        while (1) {
            clear_screen();
            printf("=== Menu ===\n");
            printf("1. Show all books\n");
            printf("2. Search books\n");

            if (is_admin) {
                printf("3. Add new book\n");
                printf("4. Update book\n");
                printf("5. Delete book by ID\n");
                printf("6. Clear table\n");
                printf("7. Create new user\n");
            }

            printf("8. Disconnect and go back to start\n");
            printf("0. Exit\n");
            printf("\nChoice: ");
            scanf_s("%d", &choice);
            getchar();

            if (choice == 0) {
                { ECPGdisconnect(__LINE__, "ALL");}
#line 840 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

                log_message("User logged out normally");
                log_message("=== Application Ended ===");
                printf("Ending of work...\n");
                return 0;
            }
            
            if (choice == 8) {
                { ECPGdisconnect(__LINE__, "ALL");}
#line 848 "C:\\Users\\xxeeg\\source\\repos\\ECPG\\main.pgc"

                printf("Disconnected. Returning to start...\n");
                log_action("Session", "User disconnected, returning to main menu");
                back_to_start = 1;
                break;
            }

            switch (choice) {
                case 1: show_all_books();    break;
                case 2: search_books();      break;
                case 3: if (is_admin) add_book();     else printf("Access denied\n"); break;
                case 4: if (is_admin) update_book();  else printf("Access denied\n"); break;
                case 5: if (is_admin) delete_by_id(); else printf("Access denied\n"); break;
                case 6: if (is_admin) clear_table();  else printf("Access denied\n"); break;
                case 7: if (is_admin) create_user();  else printf("Access denied\n"); break;
                default: printf("Invalid choice\n");
            }

            if (choice != 8) {
                printf("\nPress Enter to continue...");
                getchar();
            }
        }
        
    } while (back_to_start);

    return 0;
}