#include <stdio.h>
#include </usr/include/mysql/mysql.h>
#include <header.h>

#define DATABASE_NAME "widget_corp"
#define DATABASE_USERNAME "widget_cms"
#define DATABASE_PASSWORD "secretpassword"
MYSQL* mysql1;
MYSQL_RES *res;
MYSQL_ROW row;

void mysql_connect (void){
	mysql1 = mysql_init(NULL);
	
	if(mysql1 == NULL){
		fprintf(stderr, "%s\n", mysql_error(mysql1));
		return;
	}

	if(mysql_real_connect(mysql1, "localhost", DATABASE_USERNAME, DATABASE_PASSWORD,DATABASE_NAME, 0, NULL, 0)==NULL){
		fprintf(stderr, "%s\n", mysql_error(mysql1));
	}else{
		printf("database connected\n");
	}
}

void access_database(char* query, char* buffer){
	mysql_connect();

	if (query[0] == 'I'){
		printf("Going to android\n");
		mysql_query(mysql1, query);
		res = mysql_use_result(mysql1);
	}

	if (query[0] == 'S'){
		printf("Going to esp\n");
		mysql_query(mysql1, query);
		res = mysql_use_result(mysql1);

		printf("this is the data in you database\n");
		while((row = mysql_fetch_row(res)) != NULL){
			printf("%s \n", row[1]);
			printf("%s \n", row[3]);
		}
	}
    memmove(buffer, row[1],8);
    
	mysql_free_result(res);
	mysql_close(mysql1);

}

/*
int main(){
	char buffer[] = "show tables";
	access_database(buffer);
}
*/
