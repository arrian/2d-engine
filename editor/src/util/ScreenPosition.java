package util;

import java.awt.Point;


public class ScreenPosition extends Position
{
	public ScreenPosition()
	{
	}

	public ScreenPosition(double x, double y)
	{
		super(x,y);
	}

	public ScreenPosition(Point point)
	{
		super(point.x, point.y);
	}


}
