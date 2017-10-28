chan request_c(int*);
chan response_c[1..N](char*);

chan request_n(int*);
chan response_c[1..N](char*);

chan request_a(int*);
chan response_a[1..N](char*);

chan return_pencil(char);

Process nana
{
    int cant_c = 10;
    int cant_n = 15;
    int children;
    while(true){
        if (!empty(request_c) && cant_c){
            recive request_c(&children);
            send response_c[children]("C");
        } [](!empty(request_n) && cant_n)-> {
            recive request_n(&children);
            send response_c[children]("N");
        } [](!empty(request_a) && (cant_n + cant_c))-> {
            char pencil = get_any_pencil();
            recive request_a(&children);
            send response_a[children](&pencil);
        }
    }
}

Process children_c[i = 1..n]
{
    char pencil;
    while(true){
        send request_c(i);
        recive response_c[i](&pencil);
        delay(10 * 60);
        return_pencil(pencil);
    }
}

Process children_n[i = 1..n]
{
    char pencil;
    while(true){
        send request_n(i);
        recive response_n[i](&pencil);
        delay(10 * 60);
        return_pencil(pencil);
    }
}

Process children_a[i = 1..n]
{
    char pencil;
    while(true){
        send request_a(i);
        recive response_a[i](&pencil);
        delay(10 * 60);
        return_pencil(pencil);
    }
}
