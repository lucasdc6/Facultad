Monitor db
{
    cond read;
    int cant = 0;

    procedure read_in(int id)
    {
        if (cant > 5) {
            wait(read);
        }
        cant++;
    }

    procedure read_out(int id)
    {
        cant--;
        signal(read);
    }
}

Process readers[i: 1..N]
{
    db.read_in(i);
    // do something with db
    db.read_out(i);
}
