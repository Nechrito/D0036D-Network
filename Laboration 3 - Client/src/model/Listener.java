package model;

import java.io.IOException;
import java.net.*;

public class Listener implements Runnable
{
    private DatagramSocket socket;
    private InetAddress address;
    private byte[] buffer;

    private Game game;

    public Listener(Game game)
    {
        this.game = game;

        try
        {
            buffer = new byte[512];
            address = InetAddress.getByName("localhost");
            socket = new DatagramSocket(7421);
        }
        catch (UnknownHostException | SocketException e)
        {
            e.printStackTrace();
        }
    }

    public void run()
    {
        while (true)
        {
            try
            {
                DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
                socket.receive(packet);
                String messageReceived = new String(packet.getData(), 0, packet.getLength());
                game.RecieveMsg(messageReceived);
            }
            catch (IOException e)
            {
                e.printStackTrace();
                return;
            }
        }
    }
}
