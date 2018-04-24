Monitor sequencing_machine
{
    cond use_queue[100];
    int cant = 0;
    queue people;

    procedure use_in(int id)
    {
        if (cant) {
            cant++;
        } else {
            encolar_ordenado(people, id);
            wait(use_queue[id]);
        }
    }

    procedure use_out()
    {
        if (!cant) {
            cant--;
        } else {
            int person = desencolar(people);
            signal(use_queue[person]);
        }
    }
}

Procedure person[i: 1..100]
{
    sequencing_machine.use_in(i);
    // Use machine
    sequencing_machine.use_out(i);
}
