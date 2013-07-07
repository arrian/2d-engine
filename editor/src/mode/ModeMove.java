package mode;

import editor.Editor;
import java.awt.Graphics2D;
import java.awt.event.MouseEvent;
import java.util.ArrayList;
import shape.Shape;
import shape.ShapePoint;
import util.ScreenPosition;
import util.WorldPosition;

public class ModeMove extends Mode
{
    Mode parent = null;
    ArrayList<Shape> selection = new ArrayList<Shape>();
    
    ScreenPosition previous = null;
    
    public ModeMove(Editor editor)
    {
        super(editor);
    }

    public ModeMove(Editor editor, Mode parent, ArrayList<Shape> selection)
    {
        super(editor);
        this.parent = parent;
        this.selection = selection;
    }

    @Override
    public void mousePressed(MouseEvent e) {
        
        previous = new ScreenPosition(e.getPoint());
        WorldPosition startWorld = editor.getWorldPosition(previous);
        
        if(parent != null) 
        {
            boolean startMove = false;
            for(Shape shape : selection)
            {
                if(shape.contains(new ShapePoint(-1, startWorld))) 
                {
                    startMove = true;
                    break;
                } 
            }
            if(!startMove) 
            {
                previous = null;
                if(parent != null) 
                {
                    parent.mousePressed(e);
                    editor.setMode(parent);
                }

            }
        }
        else
        {
            ArrayList<Shape> selectionStack = editor.getWorld().query(new ShapePoint(-1, startWorld));
            if(selectionStack.isEmpty()) previous = null;
            else 
            {
                selection.clear();
                selection.add(selectionStack.get(0));
            }
        }
    }

    @Override
    public void mouseReleased(MouseEvent e) 
    {   
        previous = null;
    }

    @Override
    public void mouseDragged(MouseEvent e) 
    {
        if(selection == null || selection.isEmpty() || previous == null) return;
        
        double dx = previous.getX() - e.getPoint().getX();
        double dy = previous.getY() - e.getPoint().getY();
        
        for(Shape shape : selection)
        {
            WorldPosition pos = shape.getPosition();
            shape.setPosition(new WorldPosition(pos.getCellIndex(), pos.getX() - dx / editor.getWorldScale(), pos.getY() + dy / editor.getWorldScale()));
        }
        
        previous = new ScreenPosition(e.getPoint());
    }

    @Override
    public void draw(Graphics2D g2d) {
        if(parent != null) parent.draw(g2d);
    }

    
}
