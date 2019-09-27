package model;

import java.io.IOException;
import java.net.*;

public class Server extends Thread
{
    private DatagramSocket socket;
    private byte[] buffer;
    private InetAddress address;
    private int port = 7421;

    public Server()
    {
        try
        {
            // ports greater than 1024 are typically used by system services or require admin privilege
            socket = new DatagramSocket();
            address = InetAddress.getByName("localhost");
            buffer = new byte[512];
        } catch (SocketException | UnknownHostException e)
        {
            e.printStackTrace();
        }
    }

    public void SendMessage(String msg)
    {
        buffer = msg.getBytes();
        DatagramPacket packet = new DatagramPacket(buffer, buffer.length, address, port);
        try
        {
            socket.send(packet);
        } catch (IOException e)
        {
            e.printStackTrace();
        }
    }

    public void run()
    {
        // todo
    }
}
