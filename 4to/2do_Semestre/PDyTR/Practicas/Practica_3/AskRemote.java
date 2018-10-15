/*
* AskRemote.java
* a) Looks up for the remote object
* b) "Makes" the RMI
*/
import java.rmi.Naming; /* lookup */
import java.rmi.registry.Registry; /* REGISTRY_PORT */
import java.util.HashMap;
import java.util.Map;
import java.io.File;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.lang.reflect.*;


public class AskRemote
{
public static void main(String[] args)
{
    /* Look for hostname and msg length in the command line */
    if (args.length < 2) {
        System.out.printf("Usage: AskRemote\n"
        + "\t- write: Add a file from \n"
        + "\t- add: Add a file from --src to --dest\n"
        + "\t- read: Store a file from --src to --dest\n"
        + "\t- get: Store a file from --src to --dest\n"
        + "\t- list: List files from --src\n"
        + "\t- ls: List files from --src\n"
        );
        System.exit(1);
    }
        try {
            String rname = "//" + args[0] + ":" + Registry.REGISTRY_PORT + "/remote";
            IfaceRemoteClass remote = (IfaceRemoteClass) Naming.lookup(rname);


            switch (args[1]) {
                case "list":
                case "ls":
                    System.out.println("Listing files");
                    System.out.print(remote.list(args[2]));
                    break;
                case "read":
                case "get":
                    System.out.println("Reading file");
                    Files.write(Paths.get(args[3]), remote.read(args[2]));
                    break;
                case "write":
                case "put":
                    System.out.println("Writing file");

                    remote.write(args[3], Files.readAllBytes(Paths.get(args[2])));
                    break;
                default:
                    System.out.printf("Unsupported option %s\n", args[0]);
                    System.exit(1);
                    break;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}