/*
* IfaceRemoteClass.java
* Interface defining only one method which can be invoked remotely
*
*/
/* Needed for defining remote method/s */
import java.rmi.Remote;
import java.rmi.RemoteException;
/* This interface will need an implementing class */
public interface IfaceRemoteClass extends Remote
{
    /* It will be possible to invoke this method from an application in other JVM */
    public byte[] read(String path, int position) throws RemoteException;
    public int write(String path,byte[] data) throws RemoteException;
    public String list(String data) throws RemoteException;
    public Boolean time() throws RemoteException;
    public Boolean timeout() throws RemoteException;
}