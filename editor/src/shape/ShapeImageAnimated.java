package shape;

import java.awt.Graphics2D;
import java.util.ArrayList;

import util.ScreenPosition;
import util.WorldPosition;

public class ShapeImageAnimated extends Shape
{
    private transient String resourcePath;

    public ShapeImageAnimated(int id, WorldPosition position,
                    String resourcePath, ArrayList<String> resources)
    {
        super(id, position);
        this.resourcePath = resourcePath;
        this.resources.addAll(resources);
    }

    @Override
    protected void draw(Graphics2D g2d, ScreenPosition position, double scale)
    {
            g2d.fillOval((int) position.getX() - 5, (int) position.getY() - 5, 10, 10);
            g2d.drawString(name == null ? Integer.toString(id) : name, (int) position.getX() + 5, (int) position.getY() - 5);
    }

    @Override
    public boolean contains(ShapePoint point) {
        return ShapeIntersect.intersects(point, getImageOutline());
    }

    @Override
    public boolean intersects(ShapeRectangle rectangle) {
        return ShapeIntersect.intersects(rectangle, getImageOutline());
    }
    
    public ShapeRectangle getImageOutline()
    {
        return null;
        //return new ShapeRectangle(id, position, image.getWidth(), image.getHeight());
    }

}
