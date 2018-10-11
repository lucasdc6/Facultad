/*
* AskRemote.java
* a) Looks up for the remote object
* b) "Makes" the RMI
*/
import java.rmi.Naming; /* lookup */
import java.rmi.registry.Registry; /* REGISTRY_PORT */
import java.util.Map;
import java.nio.file.Files;
import java.nio.file.Paths;


public class AskRemote
{
public static void main(String[] args)
{
    /* Look for hostname and msg length in the command line */
    if (args.length != 2)
    {
        System.out.println("2 argument needed: (remote) hostname and directory");
        System.exit(1);
    }
        try {
            String rname = "//" + args[0] + ":" + Registry.REGISTRY_PORT + "/remote";
            IfaceRemoteClass remote = (IfaceRemoteClass) Naming.lookup(rname);
            
            Files.read
            Boolean writeReturn = remote.write("/tmp/some", Files.readAllBytes(Paths.get(args[1])));
            System.out.printf("%s\n", writeReturn);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}