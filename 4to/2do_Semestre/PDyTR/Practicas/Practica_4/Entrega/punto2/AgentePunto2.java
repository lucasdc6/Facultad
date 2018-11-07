import java.nio.charset.Charset;
import java.nio.file.Files;

import jade.core.*;
import java.io.IOException;
import java.util.List;
import java.nio.file.Paths;

public class AgentePunto2 extends Agent
{
    private final String machine = "Main-Container";
    private Location origen = null; 
    public void setup()
    {
        this.origen = here();
        System.out.println("\n\nHola, agente con nombre local " + getLocalName());
        System.out.println("Y nombre completo... " + getName());
        System.out.println("Y en location " + origen.getID() + "\n\n");
    try {
        ContainerID destino = new ContainerID(this.machine, null);
        System.out.println("Migrando el agente a " + destino.getID());
        doMove(destino);
    } catch (Exception e) {
        System.out.println("\n\n\nNo fue posible migrar el agente\n\n\n");}
    }

    protected void afterMove()
    {
        Location actual = here();

        if (!actual.getName().equals(this.origen.getName())) {
            try {
                List<String> numbers = Files.readAllLines(Paths.get("/tmp/file"), Charset.forName("utf8"));
                int result = 0;
                for (String number: numbers) {
                    result += Integer.parseInt(number);
                }
                System.out.printf("La suma es: %d\n", result);
            } catch(NumberFormatException e) {
                System.out.println("Solo se admiten numeros");
            } catch(IOException e) {
                System.out.println("El archivo no existe");
            } catch(Exception e) {
                System.out.printf("Algo salio mal\n\n%s", e.getMessage());
            }
    
            ContainerID destino = new ContainerID(this.origen.getName(), null);
            doMove(destino);
        }
    }
}
