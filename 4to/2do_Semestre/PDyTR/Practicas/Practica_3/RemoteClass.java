/*
* RemoteClass.java
* Just implements the RemoteMethod interface as an extension to
* UnicastRemoteObject
*
*/
/* Needed for implementing remote method/s */
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

/* This class implements the interface with remote methods */
public class RemoteClass extends UnicastRemoteObject implements IfaceRemoteClass
{
    static final long serialVersionUID = 1;

    protected RemoteClass() throws RemoteException
    {
        super();
    }
    /* Remote method implementation */
    public byte[] read(String path, int position) throws RemoteException
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

    public int write(String path,byte[] data) throws RemoteException
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

    public String list(String path) throws RemoteException
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

    public Boolean time() throws RemoteException
    {
        return true;
    }

    public Boolean timeout() throws RemoteException
    {
        try {
            TimeUnit.MINUTES.sleep(6);
        } catch(InterruptedException e) {
            return false;
        }
        return true;
    }
}