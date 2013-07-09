/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package util;

import editor.Editor;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;

/**
 *
 * @author Arrian
 */
public class Marker {
    
    
    private static BufferedImage image = null;
    
    static 
    {
        try {
            image = ImageIO.read(new File(Settings.DEFAULT_RESOURCE_LOCATION + Settings.DEFAULT_IMAGES_FOLDER + Settings.IMAGE_MARKER));
        } catch (IOException e) {
        } catch (NullPointerException e) {
        }
    }
    
    
    private String name = null;
    private WorldPosition position = null;

    public Marker(String name, WorldPosition position) {
        this.name = name;
        this.position = position;
    }

    public String getName() {
        return name;
    }

    public WorldPosition getPosition() {
        return position;
    }
    
    public void draw(Editor editor, Graphics2D g2d)
    {
        ScreenPosition sPos = editor.getScreenPosition(position);
        if(image != null && position != null)
        {
            g2d.drawImage(image, null, (int) sPos.getX() + - image.getWidth() / 2, (int) sPos.getY() - image.getHeight());
            g2d.drawString(name == null ? "" : name, (int) sPos.getX() + 5, (int) sPos.getY());
        }
    }

}
