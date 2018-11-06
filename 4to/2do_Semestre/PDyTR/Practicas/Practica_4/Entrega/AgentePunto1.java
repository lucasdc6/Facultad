import jade.core.*;
import java.util.ArrayList;
public class AgentePunto1	 extends Agent
{

	private Location origen;
	private long startTime;
	private ArrayList<String> containers;
	// Ejecutado por unica vez en la creacion
	public void setup()
	{
		this.origen = here();
		System.out.println("\n\nHola, agente con nombre local " + getLocalName());
		System.out.println("Y nombre completo... " + getName());
		System.out.println("Y en location " + this.origen.getID() + "\n\n");
		// Para migrar el agente

		for (int i=0; i<10;i++){
			String containerName="Contenedor-"+i;
			createContainer(containerName);
			containers.add(containerName);
		}
		containers.add(this.origen.getName());
		try {
			ContainerID destino = new ContainerID(containers.next(), null);
			System.out.println("Migrando el agente a " + destino.getID());
			startTime = System.currentTimeMillis();    
			doMove(destino);
		} catch (Exception e) {
			System.out.println("\n\n\nNo fue posible migrar el agente\n\n\n");}
	}

	// Ejecutado al llegar a un contenedor como resultado de una migracion
	protected void afterMove()
	{
		Location actual = here();
		if (actual.getName().equals(origen.getName())){
			long finishTime=System.currentTimeMillis() - startTime;
			System.out.println("Termine la vuelta, tiempo: "+ finishTime +" milisegundos");
		}
		else{
			System.out.println("\n\nHola, agente migrado con nombre local " + getLocalName());
			System.out.println("Y nombre completo... " + getName());
			System.out.println("Free memory (bytes): " + 
  			java.lang.Runtime.getRuntime().freeMemory());
			System.out.println("Y en location " + actual.getID() + "\n\n");
			try {
				ContainerID destino = new ContainerID(origen.getName(), null);
				System.out.println("Migrando el agente a " + destino.getID());
				doMove(destino);
			} catch (Exception e) {
				System.out.println("\n\n\nNo fue posible migrar el agente\n\n\n");
			}
		}
	}

	protected ContainerController createContainer(String name){
		//Get the JADE runtime interface (singleton)
		jade.core.Runtime runtime = jade.core.Runtime.instance();
		//Create a Profile, where the launch arguments are stored
		Profile profile = new ProfileImpl();
		profile.setParameter(Profile.CONTAINER_NAME, name);
		profile.setParameter(Profile.MAIN_HOST, "localhost");
		//create a non-main agent container
		return runtime.createAgentContainer(profile);
	}
}
