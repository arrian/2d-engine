package mode;

import java.awt.AlphaComposite;
import java.awt.Composite;
import java.awt.Graphics2D;
import java.awt.event.MouseEvent;

import shape.Shape;
import shape.ShapeImage;
import shape.ShapeImageAnimated;
import shape.ShapeLine;
import shape.ShapeRectangle;
import util.ScreenPosition;
import util.WorldPosition;
import data.DataItem;
import editor.Editor;
import shape.*;

public class ModeAdd extends Mode
{
	DataItem item = null;
	Shape ghost = null;

	ScreenPosition position = null;

	public ModeAdd(Editor editor, DataItem item)
	{
		super(editor);
		this.item = item;
	}

	@Override
	public void mouseMoved(MouseEvent e)
	{
                if(item == null) return;
		position = new ScreenPosition(e.getPoint());

		if(ghost != null)
		{
			updateGhost();
		}
		else
		{
			switch(item.getType())
			{
				case IMAGE: createGhost(); break;
				case IMAGE_ANIMATED: createGhost(); break;
				case POINT: createGhost(); break;
				default: break;
			}
		}
	}

	@Override
	public void mouseDragged(MouseEvent e)
	{
		mouseMoved(e);
	}
        
	@Override
	public void draw(Graphics2D g2d)
	{
            super.draw(g2d);
            if(item == null || ghost == null) return;
		
            Composite oldComp = g2d.getComposite();
            g2d.setComposite(AlphaComposite.getInstance(AlphaComposite.SrcOver.getRule(), 0.5f));
            ghost.draw(editor, g2d);
            g2d.setComposite(oldComp);
	}

	@Override
	public void mouseReleased(MouseEvent e)
	{
            if(item == null) return;
		if(e.getPoint() == null) return;
		position = new ScreenPosition(e.getPoint());
		if(ghost != null)
		{
			updateGhost();
			addGhost();
		}
		else
		{
			createGhost();
		}
		super.mouseReleased(e);
	}

	private void createGhost()
	{
            if(item == null) return;
		WorldPosition worldPosition = editor.getWorldPosition(position);
		switch(item.getType())
		{
			case LINE: ghost = ShapeLine.ShapeLineStart(item.getId(), worldPosition); break;
			case IMAGE: ghost = new ShapeImage(item.getId(), worldPosition, editor.getImageResourceLocation() + item.getResource(0)); break;
			case IMAGE_ANIMATED: ghost = new ShapeImageAnimated(item.getId(), worldPosition, editor.getImageResourceLocation(), item.getResources()); break;
			case RECTANGLE: ghost = ShapeRectangle.ShapeRectangleStart(item.getId(), worldPosition); break;
                        case POINT: ghost = new ShapePoint(item.getId(), worldPosition); break;
			default: break;
		}
                if(ghost != null) ghost.setName(item.getName());
	}

	private void updateGhost()
	{
            if(item == null) return;
		if(ghost == null) return;

		if(ghost instanceof ShapeLine) ((ShapeLine) ghost).setEnd(editor.getWorldPosition(position));
		else if(ghost instanceof ShapeRectangle) ((ShapeRectangle) ghost).setEnd(editor.getWorldPosition(position));
		else ghost.setPosition(editor.getWorldPosition(position));
	}

	private void addGhost()
	{
            if(item == null) return;
		if(ghost instanceof ShapeLine)
		{
			if(!((ShapeLine)ghost).isComplete()) ((ShapeLine) ghost).setEnd(editor.getWorldPosition(position));
			editor.getWorld().addShape(ghost);
			ghost = null;
		}
		else if(ghost instanceof ShapeRectangle)
		{
			if(!((ShapeRectangle)ghost).isComplete()) ((ShapeRectangle) ghost).setEnd(editor.getWorldPosition(position));
			editor.getWorld().addShape(ghost);
			ghost = null;
		}
		else if(ghost instanceof ShapeImage || ghost instanceof ShapePoint)
		{
			editor.getWorld().addShape(ghost);
			createGhost();
		}
                
                
	}
}
