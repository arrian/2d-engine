/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package shape;

import java.awt.geom.Line2D;
import java.awt.geom.Rectangle2D;

/**
 *
 * @author Arrian
 */
public class ShapeIntersect {
    
    protected static final float HIT_EPSILON = 1.0f;
    
    protected static boolean intersects(ShapeLine line, ShapePoint point) {
        return lineToLine2D(line).intersects(pointToRectangle2D(point));
    }
    
    protected static boolean intersects(ShapeLine line, ShapeRectangle rectangle)
    {
        return lineToLine2D(line).intersects(rectangleToRectangle2D(rectangle));
    }
    
    protected static boolean intersects(ShapePoint point, ShapeRectangle rectangle)
    {
        return rectangleToRectangle2D(rectangle).contains(point.getPosition().getX(), point.getPosition().getY());
    }
    
    protected static boolean intersects(ShapePoint point1, ShapePoint point2)
    {
        return pointToRectangle2D(point1).contains(pointToRectangle2D(point2));
    }
    
    protected static boolean intersects(ShapeRectangle rectangle1, ShapeRectangle rectangle2)
    {
        return rectangleToRectangle2D(rectangle1).intersects(rectangleToRectangle2D(rectangle2));
    }
    
    private static Rectangle2D.Double pointToRectangle2D(ShapePoint point)
    {
        double boxX = (point.getPosition().getX() - HIT_EPSILON / 2.0);
        double boxY = (point.getPosition().getY() - HIT_EPSILON / 2.0);

        double width = HIT_EPSILON;
        double height = HIT_EPSILON;
        
        return new Rectangle2D.Double(boxX, boxY, width, height);
    }
    
    private static Rectangle2D.Double rectangleToRectangle2D(ShapeRectangle rectangle)
    {
        return new Rectangle2D.Double(rectangle.getPosition().getX(), rectangle.getPosition().getY() - rectangle.getHeight(), rectangle.getWidth(), rectangle.getHeight());
    }
    
    private static Line2D.Double lineToLine2D(ShapeLine line)
    {
        return new Line2D.Double(line.getPosition().getX(), line.getPosition().getY(), line.getEnd().getX(), line.getEnd().getY());
    }
}
