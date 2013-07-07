package util;

public class Position
{
    double x;
    double y;

    public Position(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public Position()
    {
    }

    public double getX()
    {
        return x;
    }

    public double getY()
    {
        return y;
    }

    public void setX(double x)
	{
		this.x = x;
	}

    public void setY(double y)
	{
		this.y = y;
	}
}
