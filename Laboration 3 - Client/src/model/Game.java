package model;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.opengles.GLES32.GL_QUADS;

class Vector2
{
    public float X;
    public float Y;

    public Vector2(float x, float y)
    {
        this.X = x;
        this.Y = y;
    }
}

class Color
{
    float R;
    float G;
    float B;

    public Color(float r, float g, float b)
    {
        this.R = r;
        this.G = g;
        this.B = b;
    }
}

class Grid
{
    public Color Color;
    public Vector2 Spot;

    public Grid(Color color, Vector2 spot)
    {
        this.Color = color;
        this.Spot = spot;
    }
}

public class Game
{
    private List<Grid> layout;
    private Random random;
    private int quadCount;
    private float quadSize;
    private boolean isRefreshing;

    public Game()
    {
        this.quadCount = 50;
        this.quadSize = 2.0f / quadCount;

        random = new Random();
        layout = new ArrayList<>();

        init();
    }

    private void init()
    {
        List<Vector2> spots = new ArrayList<>();
        layout.clear();

        for (int x = 0; x < quadCount; x ++)
        {
            for (int y = 0; y < quadCount; y++)
            {
                Vector2 spot = new Vector2(-1.0f + x * quadSize, -1.0f + y * quadSize);
                spots.add(spot);
            }
        }

        System.out.println("Grid Size: " + spots.size());

        for (Vector2 v2 : spots)
        {
            Color color = GenerateColor(random.nextInt(8));

            layout.add(new Grid(color, v2));
        }
        this.isRefreshing = false;
    }

    private Color GenerateColor(int index)
    {
        switch (index)
        {
            case 0: return new Color(0, 0, 0);
            case 1: return new Color(1, 1, 1);
            case 2: return new Color(1, 0, 1);
            case 3: return new Color(0, 1, 0);
            case 4: return new Color(0, 1, 1);
            case 5: return new Color(0.25f, 0.75f, 0.2f);
            case 6: return new Color(0.15f, 0.69f, 0.5f);
            case 7: return new Color(0, 0.25f, 0.79f);
            case 8: return new Color(0.52f, 0, 0.92f);
        }
        return new Color(1, 1, 1);
    }

    public void RecieveMsg(String msg)
    {
        if (msg.equals("SET_ALL_RANDOM"))
        {
            for (Grid g : layout)
                g.Color = GenerateColor(random.nextInt(8));
        }

        if (msg.equals("SET_ALL_WHITE"))
        {
            for (Grid g : layout)
                g.Color = new Color(1, 1, 1);
        }

        if (msg.toUpperCase().equals("SET_ALL_BLACK"))
        {
            for (Grid g : layout)
                g.Color = new Color(0, 0, 0);
        }

        if (msg.toUpperCase().equals("SET_ALL_BLUE"))
        {
            for (Grid g : layout)
                g.Color = new Color(0, 0, 1);
        }

        try
        {
            var quads = Double.parseDouble(msg);
            this.quadCount = (int) quads;
            this.quadSize = 2.0f / quadCount;
            this.isRefreshing = true;
            init();
        }
        catch (NumberFormatException | NullPointerException e)
        {
            return;
        }
    }

    public void Update()
    {
        if (isRefreshing)
            return;

        for (Grid g : layout)
        {
            Color color = g.Color;
            Vector2 pos = g.Spot;

            // Draw
            glBegin(GL_QUADS);

            glColor3f(color.R, color.G, color.B);

            glVertex2f(pos.X, pos.Y);
            glVertex2f(pos.X + quadSize, pos.Y);
            glVertex2f(pos.X + quadSize, pos.Y + quadSize);
            glVertex2f(pos.X, pos.Y + quadSize);

            glEnd();
        }
    }
}
