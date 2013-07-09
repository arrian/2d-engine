package mode;

import shape.Shape;
import editor.Editor;
import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;
import java.util.ArrayList;
import shape.ShapePoint;
import shape.ShapeRectangle;
import util.ScreenPosition;

public class ModeSelect extends Mode
{
    ArrayList<Shape> selectionStack = null;
    ArrayList<Shape> selection = new ArrayList<Shape>();

    ScreenPosition start = null;
    ShapeRectangle selectionBox = null;

    public ModeSelect(Editor editor)
    {
        super(editor);
    }

    @Override
    public void mousePressed(MouseEvent e) {
        start = new ScreenPosition(e.getPoint());
        selectionBox = ShapeRectangle.ShapeRectangleStart(-1, editor.getWorldPosition(start));
    }

    @Override
    public void mouseReleased(MouseEvent e) {
        if(start != null && e.getPoint().getX() == start.getX() && e.getPoint().getY() == start.getY())//point click
        {
            selectionStack = editor.query(new ShapePoint(-1, editor.getWorldPosition(new ScreenPosition(e.getPoint()))));
            if(!e.isShiftDown()) selection.clear();
            if(selectionStack.size() > 0) selection.add(selectionStack.get(0));
            
            editor.setMode(new ModeMove(editor, this, selection));
        }
        else if(selectionBox != null)//box select
        {
            selectionBox.setEnd(editor.getWorldPosition(new ScreenPosition(e.getPoint())));
            selectionStack = editor.query(selectionBox);
            if(!e.isShiftDown()) selection.clear();
            selection.addAll(selectionStack);
            
            editor.setMode(new ModeMove(editor, this, selection));
        }
        selectionBox = null;
    }

    @Override
    public void mouseDragged(MouseEvent e) {
        if(selectionBox != null) selectionBox.setEnd(editor.getWorldPosition(new ScreenPosition(e.getPoint())));
    }

    @Override
    public void keyTyped(KeyEvent e) {
        super.keyTyped(e);
        if(e.getKeyCode() == KeyEvent.VK_DELETE) editor.removeShapes(selection);
    }
    
    

    @Override
    public void draw(Graphics2D g2d) {
        super.draw(g2d);
        if(selectionBox != null && selectionBox.isComplete()) selectionBox.draw(editor, g2d);
        
        g2d.setColor(Color.pink);
        if(selection != null)
        {
            for(Shape shape : selection)
            {
                shape.drawDebug(editor, g2d);
            }
        }
    }
    
    
}
