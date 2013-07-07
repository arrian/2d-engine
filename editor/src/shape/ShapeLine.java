/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package shape;

import com.google.gson.annotations.SerializedName;
import java.awt.Graphics2D;
import java.awt.geom.Line2D;

import util.Position;
import util.ScreenPosition;
import util.WorldPosition;

/**
 *
 * @author Arrian
 */
public class ShapeLine extends Shape {

    @SerializedName("v") private Position vector;
    private transient boolean complete = true;//line finished?

    public ShapeLine(int id, WorldPosition start, WorldPosition end) {
    	super(id, start);
        complete = false;
    	setEnd(end);
    }

    /**
     * Constructs the first point in a line. Use setEnd() to complete.
     * @param id
     * @param start
     * @return
     */
    public static ShapeLine ShapeLineStart(int id, WorldPosition start)
    {
    	return new ShapeLine(id, start, null);
    }

    public void setEnd(WorldPosition end)
    {
        if(end == null) return;
        vector = new Position(end.getX() - position.getX(), end.getY() - position.getY());//TODO: vector does not take into account the world position cell index
        complete = true;
    }
    
    public void setComplete(boolean complete)
    {
        this.complete = complete;
    }

    @Override
    public String serialise() {
        if(!isComplete()) return super.serialise();
        return super.serialise() + "," + position.getX() + "," + position.getY() + "," + getEnd().getX() + "," + getEnd().getY();
    }
    
    public Position getEnd()
    {
        if(!isComplete()) return null;
        return new Position(vector.getX() + position.getX(), vector.getY() + position.getY());
    }

    @Override
    protected void draw(Graphics2D g2d, ScreenPosition position, double scale)
    {
        if(complete) g2d.draw(new Line2D.Double(position.getX(), position.getY(), vector.getX() * scale + position.getX(), -vector.getY() * scale + position.getY()));
    }

    public boolean isComplete()
    {
        return complete;
    }

    @Override
    public boolean contains(ShapePoint point) {
        return ShapeIntersect.intersects(this, point);
    }

    @Override
    public boolean intersects(ShapeRectangle rectangle) {
        return ShapeIntersect.intersects(this, rectangle);
    }
}
