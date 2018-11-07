import jade.core.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.nio.file.DirectoryStream;
import java.util.Arrays;
import java.util.concurrent.TimeUnit;
import java.nio.file.StandardOpenOption;
import java.io.IOException;

public class AgentePunto3 extends Agent
{
    public void setup()
    {
        Location origen = here();
        System.out.println("\n\nHola, agente con nombre local " + getLocalName());
        System.out.println("Y nombre completo... " + getName());
        System.out.println("Y en location " + origen.getID() + "\n\n");
    try {
        ContainerID destino = new ContainerID("Main-Container", null);
        System.out.println("Migrando el agente a " + destino.getID());
        doMove(destino);
    } catch (Exception e) {
        System.out.println("\n\n\nNo fue posible migrar el agente\n\n\n");}
    }

    protected void afterMove()
    {
        Location origen = here();
        System.out.println("\n\nHola, agente migrado con nombre local " + getLocalName());
        System.out.println("Y nombre completo... " + getName());
        System.out.println("Y en location " + origen.getID() + "\n\n");
    }

    private byte[] read(String path, int position) throws RemoteException
    {
        try {
            byte[] contents = Files.readAllBytes(Paths.get(path));
            int fileSize=contents.length;
            contents=Arrays.copyOfRange(contents,position,fileSize);
            byte fileEnd=1;
            if (contents.length>1024){
                contents=Arrays.copyOf(contents,1024);
                fileEnd=0;
            }
            byte[] sizeAndContent=Arrays.copyOf(contents,contents.length+1);   
            sizeAndContent[contents.length]=fileEnd;    
            return sizeAndContent;
        } catch(Exception e) {
            System.out.println(e);
            return new byte[0];
        }
    }

    private int write(String path,byte[] data) throws RemoteException
    {
        try {
            if (data.length>1024)
                data=Arrays.copyOf(data,1024);
            try{
                Files.write(Paths.get(path), data,StandardOpenOption.APPEND);
            }
            catch (IOException e) {
                Files.createFile(Paths.get(path));
                Files.write(Paths.get(path), data,StandardOpenOption.APPEND);
            }
            System.out.println(data.length);
            return data.length;            
        } catch (Exception e) {
            System.out.println(e.toString());
            return -1;
        }
    }

    private String list(String path) throws RemoteException
    {
        try (DirectoryStream<Path> paths = Files.newDirectoryStream(Paths.get(path))) {
            String directoryPaths = "";
            System.out.printf("Listing files in %s\n", path);
            for (Path p : paths) {
                directoryPaths += p.toString();
                directoryPaths += "\n"; 
            }
            return directoryPaths;
        } catch(Exception e) {
            System.out.println(e);
            return e.toString();
        }
    }
}
