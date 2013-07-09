/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package shape;

import com.google.gson.annotations.SerializedName;
import java.awt.Graphics2D;
import java.awt.geom.Rectangle2D;

import util.ScreenPosition;
import util.WorldPosition;

/**
 *
 * @author Arrian
 */
public class ShapeRectangle extends Shape {

    @SerializedName("w") private double width;
    @SerializedName("h") private double height;

    private transient boolean complete = false;
    private transient WorldPosition startPosition = null;

    public ShapeRectangle(int id, WorldPosition position, double width, double height) {
        super(id, position);
        this.width = width;
        this.height = height;
        complete = true;
    }

    public ShapeRectangle(int id, WorldPosition start, WorldPosition end) {
    	super(id, start);
        startPosition = start;
    	setEnd(end);
    }

    /**
     * Partially constructed rectangle.
     * @param id
     * @param start
     * @return
     */
    public static ShapeRectangle ShapeRectangleStart(int id, WorldPosition start)
    {
    	return new ShapeRectangle(id, start, null);
    }

    public void setEnd(WorldPosition end)
    {
    	if(end == null) return;
    	WorldPosition nPos = WorldPosition.getTopLeft(startPosition, end);
        width = WorldPosition.getXDistance(startPosition, end);
        height = WorldPosition.getYDistance(startPosition, end);
        position = nPos;
    	complete = true;
    }

    public double getWidth() {
        return width;
    }

    public double getHeight() {
        return height;
    }
    
    @Override
    public String serialise() {
        return super.serialise() + "," + position.getX() + "," + position.getY() + "," + width + "," + height;
    }

    @Override
    protected void draw(Graphics2D g2d, ScreenPosition position, double scale)
    {
    	if(complete) g2d.draw(new Rectangle2D.Double(position.getX(), position.getY(), width * scale, height * scale));
    }

    public boolean isComplete()
    {
        return complete;
    }

    @Override
    public boolean contains(ShapePoint point) {
        return ShapeIntersect.intersects(point, this);
    }

    @Override
    public boolean intersects(ShapeRectangle rectangle) {
        return ShapeIntersect.intersects(rectangle, this);
    }
}
