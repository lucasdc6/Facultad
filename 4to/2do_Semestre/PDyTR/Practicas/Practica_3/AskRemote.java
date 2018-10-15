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
import java.util.Arrays;
import java.nio.file.StandardOpenOption;
import java.io.IOException;


public class AskRemote{

    public static void read(String host, String localPath, String remotePath){
        try {
            String rname = "//" + host + ":" + Registry.REGISTRY_PORT + "/remote";
            IfaceRemoteClass remote = (IfaceRemoteClass) Naming.lookup(rname);  
            byte endFile=0;
            int position=0;
            while (endFile != 1){
                byte[] fileContent = remote.read(remotePath,position);
                endFile=fileContent[fileContent.length-1];
                fileContent=Arrays.copyOf(fileContent,fileContent.length-1);
                position+=fileContent.length;
                try{
                    Files.write(Paths.get(localPath), fileContent,StandardOpenOption.APPEND);
                }
                catch (IOException e) {
                    Files.createFile(Paths.get(localPath));
                    Files.write(Paths.get(localPath), fileContent,StandardOpenOption.APPEND);
                }
            }
            System.out.printf("%s\n","El archivo se leyo correctamente");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void write(String host, String localPath, String remotePath){
        try {
            String rname = "//" + host + ":" + Registry.REGISTRY_PORT + "/remote";
            IfaceRemoteClass remote = (IfaceRemoteClass) Naming.lookup(rname);     
            byte[] fileContent=Files.readAllBytes(Paths.get(localPath));
            byte[] partialContent;
            int fileSize=fileContent.length;    
            int bytesReaded=0;

            while (bytesReaded<fileSize){
                partialContent= Arrays.copyOfRange(fileContent,bytesReaded,fileSize);
                int writeReturn = remote.write(remotePath,partialContent);
                bytesReaded+=writeReturn;
            }
            System.out.printf("%s\n", "The file was correctly written");

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void list(String host, String path){
        
         try {
            String rname = "//" + host + ":" + Registry.REGISTRY_PORT + "/remote";
            IfaceRemoteClass remote = (IfaceRemoteClass) Naming.lookup(rname);     
            String listReturn = remote.list(path);
            System.out.printf("%s\n", listReturn);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }


    public static void main(String[] args)
    {
        /* Look for hostname and msg length in the command line */
        if (args.length < 3)
        {
            System.out.println("Wrong number of arguments, at least 3: hostname, command and directory");
            System.exit(1);
        }

        switch (args[1]) {
                case "read":
                        if (args.length != 4)
                        {
                            System.out.println("4 argument needed: (remote) hostname, command , local directory and remote directory");
                            System.exit(1);
                        }
                        else
                            read(args[0],args[2],args[3]);
                        break;
                case "write":  
                        if (args.length != 4)
                        {
                            System.out.println("4 argument needed: (remote) hostname, command , local directory and remote directory");
                            System.exit(1);
                        }
                        else
                            write(args[0],args[2],args[3]);
                        break;
                case "list":
                        if (args.length != 3)
                        {
                            System.out.println("3 argument needed: (remote) hostname, command and directory");
                            System.exit(1);
                        }
                        else
                            list(args[0],args[2]);
                        break;
                default: System.out.println("Command unavailable");
                         break;
        }
            
    }
}