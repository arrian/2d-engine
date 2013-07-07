package shape;

import java.awt.Graphics2D;

import util.ScreenPosition;
import util.WorldPosition;

public class ShapePoint extends Shape
{

    public ShapePoint(int id, WorldPosition position)
    {
        super(id, position);
    }

    @Override
    protected void draw(Graphics2D g2d, ScreenPosition position, double scale)
    {
        g2d.fillOval((int) position.getX() - 5, (int) position.getY() - 5, 10, 10);
        g2d.drawString(name == null ? Integer.toString(id) : name, (int) position.getX() + 5, (int) position.getY() - 5);
    }

    @Override
    public boolean contains(ShapePoint point) {
        return ShapeIntersect.intersects(point, this);
    }

    @Override
    public boolean intersects(ShapeRectangle rectangle) {
        return ShapeIntersect.intersects(this, rectangle);
    }

}
