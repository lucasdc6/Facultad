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
import java.util.ArrayList;
import java.util.stream.Stream;
import java.nio.file.DirectoryStream;

/* This class implements the interface with remote methods */
public class RemoteClass extends UnicastRemoteObject implements IfaceRemoteClass
{
    static final long serialVersionUID = 1;

    protected RemoteClass() throws RemoteException
    {
        super();
    }
    /* Remote method implementation */
    public String read(String path) throws RemoteException
    {
        try {
            String contents = new String(Files.readAllBytes(Paths.get(path)));
            System.out.println(contents);
            return contents;
        } catch(Exception e) {
            System.out.println(e);
            return e.toString();
        }
    }

    public Boolean write(String path, byte[] data) throws RemoteException
    {
        try {
            Files.write(Paths.get(path), data);
            return true;            
        } catch (Exception e) {
            System.out.println(e.toString());
            return false;
        }
    }

    public String list(String path) throws RemoteException
    {
        try (DirectoryStream<Path> paths = Files.newDirectoryStream(Paths.get(path))) {
            String directoryPaths = "";
            System.out.printf("Listing files in %s\n", path);
            for (Path p : paths) {
                System.out.println(p);
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