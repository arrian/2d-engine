/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package shape;

import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

import util.ScreenPosition;
import util.Settings;
import util.WorldPosition;

/**
 *
 * @author Arrian
 */
public class ShapeImage extends Shape {

    private transient BufferedImage image = null;

    public ShapeImage(int id, WorldPosition position, String image) {
        super(id, position);
        setImage(image);
    }
    
    public void setImage(String image)
    {
        try {
            this.image = ImageIO.read(new File(image));
            this.resources.add(image);
        } catch (IOException e) {
        } catch (NullPointerException e) {
        }
    }

    @Override
    protected void draw(Graphics2D g2d, ScreenPosition position, double scale)
    {
        if(image != null)
        {
            g2d.drawImage(image, null, (int) position.getX() - image.getWidth() / 2, (int) position.getY() - image.getHeight());
        }
        else 
        {
            g2d.fillOval((int) position.getX() - 5, (int) position.getY() - 5, 10, 10);
            g2d.drawString(name == null ? Integer.toString(id) : name, (int) position.getX() + 5, (int) position.getY() - 5);
        }
    }
    
    @Override
    protected void drawDebug(Graphics2D g2d, ScreenPosition position, double scale) {
        g2d.drawOval((int) position.getX(), (int) position.getY(), 5, 5);
        if(image != null) 
        {
            ScreenPosition adjustedPosition = new ScreenPosition(position.getX() - image.getWidth() / 2, position.getY() - image.getHeight());
            getImageOutline().draw(g2d, adjustedPosition, scale);
        }
        else super.drawDebug(g2d, position, scale);
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
        double width = getWidth();
        double height = getHeight();
        
        return new ShapeRectangle(id, new WorldPosition(position.getCellIndex(),position.getX() - width / 2, position.getY()), width, height);
    }
    
    public double getWidth()
    {
        if(image == null) return ShapeIntersect.HIT_EPSILON;
        return image.getWidth() * Settings.DEFAULT_IMAGE_SCALE;
    }
    
    public double getHeight()
    {
        if(image == null) return ShapeIntersect.HIT_EPSILON;
        return image.getHeight() * Settings.DEFAULT_IMAGE_SCALE;
    }
}
