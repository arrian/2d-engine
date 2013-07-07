package mode;

import editor.Editor;
import java.awt.event.MouseEvent;
import util.ScreenPosition;

public class ModeHand extends Mode
{
    boolean mousePressed = false;
    ScreenPosition previous = null;

    public ModeHand(Editor editor)
    {
        super(editor);
    }

    @Override
    public void mousePressed(MouseEvent e) {
        mousePressed = true;
        previous = new ScreenPosition(e.getPoint());
    }
    
    public void mouseReleased() {
        mousePressed = false;
        previous = null;
    }

    @Override
    public void mouseDragged(MouseEvent e) {
        double dx = e.getPoint().getX() - previous.getX();
        double dy = e.getPoint().getY() - previous.getY();
        double xScreenPos = (editor.getWidth() / 2) - dx;
        double yScreenPos = (editor.getHeight() / 2) - dy;
        
        editor.setWorldPosition(editor.getWorldPosition(new ScreenPosition(xScreenPos, yScreenPos)));
        
        previous = new ScreenPosition(e.getPoint());
    }   
}
