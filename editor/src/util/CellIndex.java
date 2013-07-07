package util;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Arrian
 */
public class CellIndex
{
    private int x;
    private int y;

    public CellIndex(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    public void setX(int x) {
        this.x = x;
    }

    public void setY(int y) {
        this.y = y;
    }

    @Override
    public boolean equals(Object obj) {
        if(obj == null || !(obj instanceof CellIndex)) return false;
        return (((CellIndex) obj).x == x && ((CellIndex) obj).y == y);
    }

    @Override
    public String toString() {
        return x + "," + y;
    }
    
    
}
