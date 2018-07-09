typedef int sem;

sem mutex = 1;
sem barrier = 0;
int cant_employee = 0;
int cant = 0;
int cant_build[E] = ([E] 0);
int employee_id = -1;

procedure employee[int id = 1..E]()
{
  P(mutex);
  cant_employee++;
  if (cant_employee == E) {
    for (int i = 0; i < E; i++) {
      V(barrier);
    }
  }
  V(mutex);
  P(barrier);
  P(mutex);
  while( cant != V) {
    cant++;
    V(mutex);
    //trabajar haciendo
    P(mutex);
  }
  if (employee_id == -1) {
    employee_id = get_max(cant_build);
    printf("El empleado %d es el que construyo más\n", employee_id);
  }
  V(mutex);
}
