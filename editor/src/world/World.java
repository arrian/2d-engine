package world;


import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import data.Data;
import java.awt.Graphics2D;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.HashMap;

import shape.Shape;
import util.CellIndex;
import editor.Editor;
import java.io.*;
import java.util.ArrayList;
import shape.ShapePoint;
import shape.ShapeRectangle;
import util.Marker;
import util.WorldPosition;

/*
 * To change this template, choose Tools | Templates and open the template in
 * the editor.
 */
/**
 *
 * @author Arrian
 */
public class World {
    
    private String name = "Test World";
    private HashMap<String, Cell> cells = new HashMap<String, Cell>();
    private ArrayList<Marker> markers = new ArrayList<Marker>();

    public World() 
    {
    }

    public void loadCell(CellIndex index)
    {
        cells.put(index.toString(), new Cell(index));
    }
    
    private void addCell(Cell cell)
    {
        cells.put(cell.getIndex().toString(), cell);
    }

    public Cell getCell(CellIndex index) 
    {
        return cells.get(index.toString());
    }

    public void draw(Editor editor, Graphics2D g2d)
    {
        for (Cell cell : cells.values()) {
            cell.draw(editor, g2d);
        }
    }

    public void addShape(Shape shape)
    {
    	Cell cell = getCell(shape.getPosition().getCellIndex());
    	if(cell == null)
    	{
    		System.err.println("Could not add shape to cell.");
    		return;
    	}
    	cell.addPlaceable(shape);
    }

    public static void save(World world, File file) throws IOException
    {
        if (!file.exists()) file.createNewFile();

        FileWriter fw = new FileWriter(file);
        BufferedWriter bw = new BufferedWriter(fw);

        Gson gson = new Gson();
        bw.write(gson.toJson(world));
        
        bw.close();
        fw.close();
    }
    
    public static World load(File file, Editor editor, Data data) throws IOException
    {
        FileReader fr = new FileReader(file);
        BufferedReader br = new BufferedReader(fr);
        Gson gson = new GsonBuilder().registerTypeAdapter(Shape.class, new Shape.ShapeAdapter(editor, data)).create();
        World world = gson.fromJson(br, World.class);

        br.close();
        fr.close();
        
        return world;
    }

    public void drawDebug(Editor editor, Graphics2D g2d)
    {
        for (Cell cell : cells.values()) cell.drawDebug(editor, g2d);
        for (Marker marker : markers) marker.draw(editor, g2d);
    }

    public ArrayList<Shape> query(ShapeRectangle rectangle) 
    {
        Cell cell = getCell(rectangle.getPosition().getCellIndex());
        if(cell == null) return new ArrayList<Shape>();
        
        return cell.query(rectangle);
    }

    public ArrayList<Shape> query(ShapePoint point) 
    {
        Cell cell = getCell(point.getPosition().getCellIndex());
        if(cell == null) return new ArrayList<Shape>();
        
        return cell.query(point);
    }

    public String getName() {
        return name;
    }
    
    public void addMarker(Marker marker)
    {
        markers.add(marker);
    }

    public ArrayList<Marker> getMarkers() {
        return markers;
    }
    
}
