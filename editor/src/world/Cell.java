package world;


import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.geom.Rectangle2D;
import java.util.ArrayList;

import shape.Shape;
import util.CellIndex;
import util.ScreenPosition;
import util.Settings;
import util.WorldPosition;
import editor.Editor;
import shape.ShapePoint;
import shape.ShapeRectangle;

/*
 * To change this template, choose Tools | Templates and open the template in
 * the editor.
 */
/**
 *
 * @author Arrian
 */
public class Cell {
    
    CellIndex index;
    public static final double CELL_SIZE = Settings.CELL_SIZE;

    ArrayList<Shape> shapes = new ArrayList<Shape>();

    public Cell(CellIndex index) {
        this.index = index;
    }

    public ArrayList<Shape> getPlaceables() {
        return shapes;
    }

    public void addPlaceable(Shape placeable) {
        shapes.add(placeable);
    }

    public void removePlaceable(Shape placeable) {
        shapes.remove(placeable);
    }
    
    public ArrayList<Shape> query(ShapePoint point)
    {
        ArrayList<Shape> query = new ArrayList<Shape>();
        for(Shape placeable : shapes) {
            if(placeable.contains(point)) query.add(placeable);
        }
        return query;
    }
    
    public ArrayList<Shape> query(ShapeRectangle rectangle)
    {
        ArrayList<Shape> query = new ArrayList<Shape>();
        for(Shape placeable : shapes) {
            if(placeable.intersects(rectangle)) query.add(placeable);
        }
        return query;
    }

    public void drawDebug(Editor editor, Graphics2D g2d)
    {
    	//draw cell bounds
        ScreenPosition sPos = editor.getScreenPosition(new WorldPosition(index, 0, CELL_SIZE));
        g2d.draw(new Rectangle2D.Double(sPos.getX(), sPos.getY(), CELL_SIZE * editor.getWorldScale(), CELL_SIZE * editor.getWorldScale()));

        //draw id at bottom left of cell
        sPos = editor.getScreenPosition(new WorldPosition(index, 0, 0));
        g2d.drawString("Cell (" + index.getX() + ", " + index.getY() + ")", (float) sPos.getX(), (float) sPos.getY());

        //draw id at centre of cell
        sPos = editor.getScreenPosition(new WorldPosition(index, CELL_SIZE / 2, CELL_SIZE / 2));
        g2d.drawString("Cell (" + index.getX() + ", " + index.getY() + ")", (float) sPos.getX(), (float) sPos.getY());

        WorldPosition topLeftCorner = editor.getWorldPosition(new ScreenPosition(0,0));
        WorldPosition bottomRightCorner = editor.getWorldPosition(new ScreenPosition(editor.getWidth(),editor.getHeight()));
        
        for(long i = (long) ((long) Math.round(topLeftCorner.getX() / Settings.DEBUG_GRID_SIZE_METRES) * Settings.DEBUG_GRID_SIZE_METRES); i <= bottomRightCorner.getX(); i += Settings.DEBUG_GRID_SIZE_METRES)
        {
            for(long j = (long) ((long) Math.round(topLeftCorner.getY() / Settings.DEBUG_GRID_SIZE_METRES) * Settings.DEBUG_GRID_SIZE_METRES); j >= bottomRightCorner.getY(); j -= Settings.DEBUG_GRID_SIZE_METRES)
            {
                ScreenPosition drawPosition = editor.getScreenPosition(new WorldPosition(topLeftCorner.getCellIndex(), i, j));
                g2d.drawLine((int) drawPosition.getX() - Settings.DEBUG_GRID_CROSSHAIR_SIZE, (int) drawPosition.getY(), (int) drawPosition.getX() + Settings.DEBUG_GRID_CROSSHAIR_SIZE, (int) drawPosition.getY());
                g2d.drawLine((int) drawPosition.getX(), (int) drawPosition.getY() - Settings.DEBUG_GRID_CROSSHAIR_SIZE, (int) drawPosition.getX(), (int) drawPosition.getY() + Settings.DEBUG_GRID_CROSSHAIR_SIZE);
            }
        }

    }

    public void draw(Editor editor, Graphics2D g2d)
    {
        g2d.setColor(Color.black);
        for (Shape placeable : shapes) {
            placeable.draw(editor, g2d);
        }
    }

    CellIndex getIndex() {
        return index;
    }
}
