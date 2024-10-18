package Controls;

import Enums.MoveType;
import javafx.geometry.Point2D;

import java.io.Serializable;

public class Coordinate implements Serializable {

    public int x;
    public int y;

    public Coordinate(int x, int y){

        this.x = x;
        this.y = y;
    }

    /**
     * Viszater a kapott koordinata es sajat maganak a tavolsagaval.
     * Mivel a tablankban nem siman hasznaljuk a 2d-s tombot, ezert kicsit furak a szabalyok.
     * @param c A koordinata, amitol szaitja a taolsagot.
     * @return MoveType
     */
    public MoveType getDistance(Coordinate c){

        int xDist = Math.abs(this.x - c.x);
        int yDist = Math.abs(this.y - c.y);

        if(c.equals(this))
            return MoveType.INVALID;

        else if (xDist == 1 && yDist == 1 || xDist == 0 && yDist == 2)
            return MoveType.SHORT;

        else if (xDist == 2 && yDist == 0 || xDist == 2 && yDist == 2 || xDist == 1 && yDist == 3 || xDist == 0 && yDist == 4)
            return MoveType.LONG;

        else
            return MoveType.INVALID;
    }

    /**
     * Megadja, hogy a koordinata a kapott koordinatak kozott talahato-e.
     * @param leftUpper Az intervallum bal felso sarka.
     * @param rightLover Az intervallum jobb also sarka.
     * @return Boolean
     */
    public Boolean isBetween(Coordinate leftUpper, Coordinate rightLover){

        return x >= leftUpper.x && y <= leftUpper.y && x <= rightLover.x && y >= rightLover.y;
    }

    /**
     * Kapott koordinatabol, az 1920x1080-as felbontasnak megfelelo pontot csinal.
     * @param c A koordinata, amit pontta alakit.
     * @return Point2D
     */
    public static Point2D coordinateToPoint(Coordinate c){

        double x = 49 + c.x * 178;
        double y = 16 + c.y * 59.5;

        return new Point2D(x, y);
    }

    @Override
    public String toString() {

        return "x = " + x + ", y = " + y;
    }

    @Override
    public boolean equals(Object o){

        return ((Coordinate)o).x == x && ((Coordinate)o).y == y;
    }
}