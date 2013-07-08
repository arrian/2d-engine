package util;

import java.nio.file.FileSystems;
import java.nio.file.Files;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Arrian
 */
public class Settings{

    public static final String DEFAULT_RESOURCE_LOCATIONS[] = {"..\\..\\res\\", "..\\res\\", ".\\res\\", ".\\"};
    
    public static String DEFAULT_RESOURCE_LOCATION = "";
    public static final String DEFAULT_WORLD_FOLDER = "world\\";
    public static final String DEFAULT_DATA_FOLDER = "data\\";
    public static final String DEFAULT_IMAGES_FOLDER = "images\\";
    public static final String DEFAULT_DATA_FILE = "game.dat";
    
    public static final float DEFAULT_WORLD_SCALE = 30.0f;
    public static final float DEFAULT_IMAGE_SCALE = 1 / 30.0f;
    public static final double CELL_SIZE = 600;
    public static final int DEBUG_GRID_SIZE_METRES = 10;
    public static final int DEBUG_GRID_CROSSHAIR_SIZE = 3;
    
    static
    {
        for(String path : DEFAULT_RESOURCE_LOCATIONS)
        {
            if(Files.exists(FileSystems.getDefault().getPath(path))) 
            {
                DEFAULT_RESOURCE_LOCATION = path;
                break;
            }
        }
    }
}
