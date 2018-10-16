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
import java.util.Arrays;
import java.nio.file.StandardOpenOption;
import java.io.IOException;


public class AskRemote{

    public static void read(IfaceRemoteClass remote, String localPath, String remotePath){
        try {
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

    public static void write(IfaceRemoteClass remote, String localPath, String remotePath){
        try {
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

    public static void list(IfaceRemoteClass remote, String path){
        
         try {   
            String listReturn = remote.list(path);
            System.out.printf("%s\n", listReturn);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }


    public static void main(String[] args)
    {
        /* Look for hostname and msg length in the command line */
        if (args.length < 2) {
            System.out.printf("Usage: AskRemote\n"
            + "\t- <host> write <local> <remote>: Add a file from <local> to <remote> \n"
            + "\t- <host> add <local> <remote>: Add a file from <local> to <remote>\n"
            + "\t- <host> read <local> <remote>: Store a file from <local> to <remote>\n"
            + "\t- <host> get <local> <remote>: Store a file from <local> to <remote>\n"
            + "\t- <host> list <remote directory>: List files from <remote directory>\n"
            + "\t- <host> ls <remote directory>: List files from <remote directory>\n"
            );
            System.exit(1);
        }

        try {
            String rname = "//" + args[0] + ":" + Registry.REGISTRY_PORT + "/remote";
            IfaceRemoteClass remote = (IfaceRemoteClass) Naming.lookup(rname);

            switch (args[1]) {
                    case "read":
                    case "get":
                            if (args.length != 4)
                            {
                                System.out.println("4 argument needed: (remote) hostname, command , local directory and remote directory");
                                System.exit(1);
                            }
                            else
                                read(remote,args[2],args[3]);
                            break;
                    case "write":
                    case "add":
                            if (args.length != 4)
                            {
                                System.out.println("4 argument needed: (remote) hostname, command , local directory and remote directory");
                                System.exit(1);
                            }
                            else
                                write(remote,args[2],args[3]);
                            break;
                    case "list":
                    case "ls":
                            if (args.length != 3)
                            {
                                System.out.println("3 argument needed: (remote) hostname, command and directory");
                                System.exit(1);
                            }
                            else
                                list(remote,args[2]);
                            break;
                    case "time":
                            long startTime = System.nanoTime();
                            remote.time();
                            long stopTime = System.nanoTime();
                            System.out.println(stopTime - startTime);
                            break;
                    case "timeout":
                            Boolean ret = remote.timeout();
                            System.out.println(ret);
                            break;    
                    default: System.out.println("Command unavailable");
                            break;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }    
    }
}