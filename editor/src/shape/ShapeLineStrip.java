/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package shape;

import com.google.gson.annotations.SerializedName;
import java.awt.Graphics2D;
import java.awt.geom.Line2D;
import java.util.ArrayList;
import util.Position;

import util.ScreenPosition;
import util.WorldPosition;

/**
 *
 * @author Arrian
 */
public class ShapeLineStrip extends Shape {

    @SerializedName("ps") private ArrayList<Position> points = new ArrayList<Position>();

    public ShapeLineStrip(int id, WorldPosition position, ArrayList<Position> points) {
        super(id, position);
        this.points = points;
    }

    @Override
    public String serialise() {
        return super.serialise() + "," + this.toString();
    }

    @Override
    protected void draw(Graphics2D g2d, ScreenPosition position, double scale)
    {
        ScreenPosition previous = position;
        for(Position point : points) {
            ScreenPosition current = new ScreenPosition(point.getX() * scale + previous.getX(), -point.getY() * scale + previous.getY());
            g2d.draw(new Line2D.Double(previous.getX(), previous.getY(), current.getX(), current.getY()));
            previous = current;
        }
    }

    @Override
    public boolean contains(ShapePoint point) 
    {
        WorldPosition previous = getPosition();
        for(Position p : points) 
        {
            WorldPosition current = new WorldPosition(position.getCellIndex(), p.getX() + previous.getX(), p.getY() + previous.getY());
            if(ShapeIntersect.intersects(new ShapeLine(id, previous, current), point)) return true;
            previous = current;
        }
        return false;
    }

    @Override
    public boolean intersects(ShapeRectangle rectangle) {
        WorldPosition previous = getPosition();
        for(Position p : points) 
        {
            WorldPosition current = new WorldPosition(position.getCellIndex(), p.getX() + previous.getX(), p.getY() + previous.getY());
            if(ShapeIntersect.intersects(new ShapeLine(id, previous, current), rectangle)) return true;
            previous = current;
        }
        return false;
    }

}
