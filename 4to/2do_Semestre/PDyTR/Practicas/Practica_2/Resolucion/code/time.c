x = atoi(argv[2]);
y = atoi(argv[3]);

double time = dwalltime();
printf("%d + %d = %d\n",x,y,
       add(clnt,x,y));

printf("%g\n", dwalltime() - time);

return(0);
