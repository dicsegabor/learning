package Controls;

import Enums.MoveType;

import java.io.Serializable;

/**
 * Egy lepest reprezental, ketto koordinatabol all, valamint a lepes tipusabol es ertekebol.
 */
public class Move  implements Serializable {

    public final Coordinate from;
    public final Coordinate to;
    public final MoveType type;
    public int value;

    public Move( Coordinate from,  Coordinate to){

        this.from = from;
        this.to = to;
        type = from.getDistance(to);
    }

    public Boolean isValid(){

        return !type.equals(MoveType.INVALID);
    }

    @Override
    public String toString(){

        return "From: " + from + " | To: " + to;
    }
}