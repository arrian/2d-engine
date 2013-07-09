package mode;

import editor.Editor;
import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.event.MouseEvent;
import java.util.ArrayList;
import shape.Shape;
import shape.ShapePoint;
import util.ScreenPosition;
import util.WorldPosition;

public class ModeRotate extends Mode
{
    Shape selection = null;
    ScreenPosition previous = null;
    
    public ModeRotate(Editor editor)
    {
        super(editor);
    }

    @Override
    public void mousePressed(MouseEvent e) {
        previous = new ScreenPosition(e.getPoint());
        WorldPosition startWorld = editor.getWorldPosition(previous);
        
        ArrayList<Shape> selectionStack = editor.query(new ShapePoint(-1, startWorld));
        if(selectionStack.isEmpty()) previous = null;
        else selection = selectionStack.get(0);
    }

    @Override
    public void mouseReleased(MouseEvent e) 
    {   
        previous = null;
        selection = null;
    }
    
        @Override
    public void mouseDragged(MouseEvent e) 
    {
        if(selection == null || previous == null) return;
        
        WorldPosition point1 = editor.getWorldPosition(new ScreenPosition(e.getPoint()));
        WorldPosition point2 = editor.getWorldPosition(previous);
       
        selection.setRotation(selection.getRotation() + WorldPosition.getAngle(selection.getPosition(), point1, point2));
        
        previous = new ScreenPosition(e.getPoint());
    }

    @Override
    public void draw(Graphics2D g2d) {
        if(selection != null) 
        {
            g2d.setColor(Color.pink);
            selection.drawDebug(editor, g2d);
        }
    }

}
