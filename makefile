test: test2.c server.c
	gcc -o test $(mysql_config --cflags) test2.c server.c $(mysql_config --libs) -I.
