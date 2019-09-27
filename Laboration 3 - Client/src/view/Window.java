package view;

import model.Game;
import model.Listener;
import org.lwjgl.glfw.GLFWErrorCallback;
import org.lwjgl.glfw.GLFWVidMode;
import org.lwjgl.opengl.GL;
import org.lwjgl.system.MemoryStack;

import java.nio.IntBuffer;

import static org.lwjgl.glfw.GLFW.*;
import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.system.MemoryStack.stackPush;
import static org.lwjgl.system.MemoryUtil.NULL;

public class Window
{
    private long window;

    private int width = 960;
    private int height = 960;

    private Game game;
    private Listener listener;

    public Window()
    {
        initWindow();

        game = new Game();

        listener = new Listener(game);
        Thread thread = new Thread(listener);
        thread.start();

        mainLoop();
    }

    private void initWindow()
    {
        // In-built error callback
        GLFWErrorCallback.createPrint(System.err).set();

        glfwInit();

        window = glfwCreateWindow(width, height, "Client - Philip Lindh", NULL, NULL);

        // Setup a key callback. It will be called every time a key is pressed, repeated or released.
        glfwSetKeyCallback(window, (window, key, scancode, action, mods) ->
        {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
                glfwSetWindowShouldClose(window, true);
        });

        // Get the thread stack and push a new frame
        try (MemoryStack stack = stackPush())
        {
            IntBuffer widthBuffer = stack.mallocInt(1);
            IntBuffer heightBuffer = stack.mallocInt(1);

            // Get the window size
            glfwGetWindowSize(window, widthBuffer, heightBuffer);

            // Get the resolution of the primary monitor
            GLFWVidMode vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());

            // Center the window
            glfwSetWindowPos(window, (vidmode.width() - widthBuffer.get(0)) / 2, (vidmode.height() - heightBuffer.get(0)) / 2);
        } // the stack frame is popped automatically

        glfwMakeContextCurrent(window);

        // Enable v-sync
        glfwSwapInterval(1);

        // Make the window visible
        glfwShowWindow(window);
    }

    private void mainLoop()
    {
        // Allows OpenGL bindings
        GL.createCapabilities();

        glClearColor(0.5f, 0.5f, 0.5f, 0.5f);

        while (!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT);

            game.Update();
            //listener.Update();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
}
