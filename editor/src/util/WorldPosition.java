package util;

import world.Cell;



/**
 *
 * @author Arrian
 */
public class WorldPosition extends Position
{
    private CellIndex cell;

    public WorldPosition(int xCell, int yCell, double x, double y) {
    	super(x, y);
        this.cell = new CellIndex(xCell, yCell);
    }

    public WorldPosition(CellIndex index, double x, double y) {
        super(x, y);
    	this.cell = index;
    }

    public void localise()
    {
        if(x > Cell.CELL_SIZE)
        {
            cell.setX(cell.getX() + (int) Math.round((x / Cell.CELL_SIZE)));
            x = x % Cell.CELL_SIZE;
        }
        else if(x < 0)
        {
            cell.setX(-(1 + cell.getX() - (int) Math.round((x / Cell.CELL_SIZE))));
            x = x % Cell.CELL_SIZE + Cell.CELL_SIZE;
        }

        if(y > Cell.CELL_SIZE)
        {
            cell.setY(cell.getY() + (int) Math.round((y / Cell.CELL_SIZE)));
            y = y % Cell.CELL_SIZE;
        }
        else if(y < 0)
        {
            cell.setY(-(1 + cell.getY() - (int) Math.round((y / Cell.CELL_SIZE))));
            y = y % Cell.CELL_SIZE + Cell.CELL_SIZE;
        }
    }

    public CellIndex getCellIndex() {
        return cell;
    }

    public int getXCell()
    {
        return cell.getX();
    }

    public int getYCell()
    {
        return cell.getY();
    }

    public static WorldPosition getTopLeft(WorldPosition p1, WorldPosition p2)
    {
    	double yMax = Math.max(p1.getY(), p2.getY());
    	double xMin = Math.min(p1.getX(), p2.getX());
    	int yCellMax = Math.max(p1.getYCell(), p2.getYCell());
    	int xCellMin = Math.min(p1.getXCell(), p2.getXCell());
    	return new WorldPosition(xCellMin, yCellMax, xMin, yMax);
    }

    public static double getXDistance(WorldPosition p1, WorldPosition p2)
    {
        return Math.abs(p2.getX() - p1.getX());
    }

    public static double getYDistance(WorldPosition p1, WorldPosition p2)
    {
    	return Math.abs(p2.getY() - p1.getY());
    }

}