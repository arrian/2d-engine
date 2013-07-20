package editor;


import data.Data;
import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.event.MouseWheelEvent;
import java.awt.event.MouseWheelListener;
import java.io.File;

import javax.swing.JPanel;

import mode.Mode;
import mode.ModeAdd;
import mode.ModeSelect;
import util.CellIndex;
import util.ScreenPosition;
import util.Settings;
import util.WorldPosition;
import world.Cell;
import world.World;
import data.DataItem;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Stack;
import shape.Shape;
import shape.ShapePoint;
import shape.ShapeRectangle;
import util.*;
import util.ActionItem.MoveShapeAction;

public class Editor extends JPanel implements MouseListener, MouseMotionListener, KeyListener, MouseWheelListener {

    private World world;
    private String imagePath = null;
    private Mode mode;
    private WorldPosition worldPosition = new WorldPosition(0, 0, Cell.CELL_SIZE / 2, Cell.CELL_SIZE / 2);
    private double worldScale = Settings.DEFAULT_WORLD_SCALE;
    private WorldPosition mousePosition = null;
    private DataItem selectedDataItem = null;
    private boolean debug = true;
    
    private File workingFile = null;
    
    private Stack<ActionItem> undoStack = new Stack<ActionItem>();
    private Stack<ActionItem> redoStack = new Stack<ActionItem>();
    
    public Editor()
    {
        super();
        addMouseListener(this);
        addMouseMotionListener(this);
        this.imagePath = Settings.DEFAULT_RESOURCE_LOCATION + Settings.DEFAULT_IMAGES_FOLDER;
        clear();
    }

    /**
     * Generates a new world.
     */
    public final void clear()
    {
        world = new World();
        world.loadCell(new CellIndex(0,0));
        mode = new ModeSelect(this);
        repaint();
    }
    
    public void undo()
    {
        if(undoStack.isEmpty()) return;
        ActionItem action = undoStack.pop();
        action.undo();
        redoStack.add(action);
        repaint();
    }
    
    public void redo()
    {
        if(redoStack.isEmpty()) return;
        ActionItem action = redoStack.pop();
        action.redo();
        undoStack.add(action);
        repaint();
    }

    /**
     * Saves the world to the given file.
     * @param file
     */
    public void save(File file) 
    {
        try {
            World.save(world, file);
            workingFile = file;
        } catch (IOException ex) {
            System.err.println(ex.getMessage());
        }
    }
    
    public void save()
    {
        save(workingFile);
    }
    
    public void load(File file, Data data) 
    {
        try {
            world = World.load(file, this, data);
            workingFile = file;
        } catch (IOException ex) {
            System.err.println(ex.getMessage());
        }
    }

    public File getWorkingFile() {
        return workingFile;
    }

    @Override
    public void paint(Graphics g) {
        super.paint(g);

        Graphics2D g2d = (Graphics2D) g;

        //Normal world
        g2d.setStroke(new BasicStroke(1));
        g2d.setColor(Color.black);
        world.draw(this, g2d);

        if(debug)
        {
            g2d.setStroke(new BasicStroke(1));
            g2d.setColor(Color.red);
            world.drawDebug(this, g2d);
            
            //Position text
            if(mousePosition != null) {
        	g2d.drawString("cell(" + mousePosition.getXCell() + ", " + mousePosition.getYCell() + ") " + String.format("coords(%1$,.2f, %2$,.2f)", mousePosition.getX(), mousePosition.getY()) , 0, getHeight());
            }
        }

        //Edit mode components
        g2d.setColor(Color.gray);
        mode.draw(g2d);
    }

    @Override
    public void mouseClicked(MouseEvent e) {
    	mode.mouseClicked(e);
    	repaint();
    }

    @Override
    public void mousePressed(MouseEvent e) {
    	mode.mousePressed(e);
    	repaint();
    }

    @Override
    public void mouseReleased(MouseEvent e) {
    	mode.mouseReleased(e);
        repaint();
    }

    @Override
    public void mouseEntered(MouseEvent e) {
    	mode.mouseEntered(e);
    	repaint();
    }

    @Override
    public void mouseExited(MouseEvent e) {
    	mode.mouseEntered(e);
    	repaint();
    }

    @Override
    public void mouseDragged(MouseEvent e) {
    	mode.mouseDragged(e);
    	setMousePosition(e.getPoint());
        repaint();
    }

    @Override
    public void mouseMoved(MouseEvent e) {
    	mode.mouseMoved(e);
    	setMousePosition(e.getPoint());
        repaint();
    }

    @Override
    public void keyTyped(KeyEvent e) {
    	mode.keyTyped(e);
    	repaint();
    }

    @Override
    public void keyPressed(KeyEvent e) {
        System.out.println("key pressed");
    	mode.keyPressed(e);
        repaint();
    }

    @Override
    public void keyReleased(KeyEvent e) {
    	mode.keyReleased(e);
        
        /*
        if(e.getKeyCode() == KeyEvent.VK_EQUALS) 
        {
            
            worldScale += 1;
            System.out.println("equals pressed");
        }
        System.out.println(e.getKeyCode());
        */
        repaint();
    }

    @Override
    public void mouseWheelMoved(MouseWheelEvent e) {
        mode.mouseWheelMoved(e);
        
        repaint();
    }

    public void setSelectedDataItem(DataItem item) {
        selectedDataItem = item;
        setMode(new ModeAdd(this, item));
    }

    public void setWorldPosition(WorldPosition worldPosition) {
        this.worldPosition = worldPosition;
    }

    private void setMousePosition(Point point)
    {
    	mousePosition = getWorldPosition(new ScreenPosition(point));
    }

    public void setMode(Mode mode)
    {
    	this.mode = mode;
    }

    public DataItem getSelectedDataItem()
	{
		return selectedDataItem;
	}

    public String getImageResourceLocation()
    {
        return imagePath;
    }

    public Double getWorldScale()
    {
        return worldScale;
    }

    public WorldPosition getWorldPosition(ScreenPosition position)
    {
        double xWorldSpace = (position.getX() - getWidth() / 2) / worldScale;
        double yWorldSpace = (position.getY() - getHeight() / 2) / worldScale;
        yWorldSpace = -yWorldSpace;//need to invert due to coordinate systems
        WorldPosition wPosition = new WorldPosition(worldPosition.getXCell(), worldPosition.getYCell(), worldPosition.getX() + xWorldSpace, worldPosition.getY() + yWorldSpace);
        wPosition.localise();
        return wPosition;
    }

    public ScreenPosition getScreenPosition(WorldPosition position)
    {
        float xDiff = (float) (position.getX() - worldPosition.getX());//delta from x centre
        float yDiff = (float) (position.getY() - worldPosition.getY());//delta from y centre

        int xCellDiff = position.getXCell() - worldPosition.getXCell();//cell x diff
        int yCellDiff = position.getYCell() - worldPosition.getYCell();//cell y diff

        xDiff += (xCellDiff * Cell.CELL_SIZE);
        yDiff += (yCellDiff * Cell.CELL_SIZE);

        xDiff *= worldScale;
        yDiff *= worldScale;

        yDiff = -yDiff;//invert y axis

        return new ScreenPosition(xDiff + getWidth() / 2, yDiff + getHeight() / 2);
    }
    
    public void paste() {
    }

    public void copy() {
    }

    public void duplicate() {
    }

    public void delete() {
        
    }

    public void setShowDebug(boolean selected) {
        this.debug = selected;
        repaint();
    }
    
    ScreenPosition getScreenCentre()
    {
        return new ScreenPosition((float) getWidth() / 2f, (float) getHeight() / 2f);
    }
    
    public ArrayList<Shape> query(ShapePoint point)
    {
        return world.query(point);
    }
    
    public ArrayList<Shape> query(ShapeRectangle rectangle)
    {
        return world.query(rectangle);
    }
    
    public void addMarker(String name)
    {
        execute(new ActionItem.AddMarkerAction(world, ActionItem.ActionType.DO, new Marker(name, worldPosition)));
    }
    
    public void addShape(Shape shape)
    {
        execute(new ActionItem.AddShapeAction(world, ActionItem.ActionType.DO, shape));
    }
    
    public void removeShapes(ArrayList<Shape> shapes)
    {
        execute(new ActionItem.AddShapeArrayAction(world, ActionItem.ActionType.UNDO, shapes));
    }
    
    public void moveShape(Shape shape, WorldPosition position)
    {
        ActionItem action = undoStack.lastElement();
        if(action != null && action instanceof MoveShapeAction && action.getObject() == shape) ((MoveShapeAction) action).setNewPosition(position);
        else action = new ActionItem.MoveShapeAction(world, ActionItem.ActionType.DO, shape, position);
        execute(action);
    }
    
    public void execute(ActionItem action)
    {
        redoStack.clear();
        action.initialise();
        undoStack.push(action);
        if(undoStack.size() > Settings.MAX_UNDOS) undoStack.remove(0);
        repaint();        
    }
    
    public void zoom(double factor)
    {
        worldScale += factor;
        if(worldScale <= 0) worldScale = 0.1;
        repaint();
    }
    

}
