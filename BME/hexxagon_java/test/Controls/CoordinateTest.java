package Controls;

import Enums.MoveType;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class CoordinateTest {

    @Test
    public void DistanceCalculatorTest(){

        Coordinate middle = new Coordinate(4, 8);

        assertEquals(MoveType.SHORT, middle.getDistance(new Coordinate(3, 9)));
        assertEquals(MoveType.SHORT, middle.getDistance(new Coordinate(3, 7)));
        assertEquals(MoveType.SHORT, middle.getDistance(new Coordinate(4, 6)));
        assertEquals(MoveType.LONG, middle.getDistance(new Coordinate(2, 8)));
        assertEquals(MoveType.LONG, middle.getDistance(new Coordinate(2, 6)));
        assertEquals(MoveType.LONG, middle.getDistance(new Coordinate(3, 5)));
        assertEquals(MoveType.LONG, middle.getDistance(new Coordinate(4, 4)));
        assertEquals(MoveType.INVALID, middle.getDistance(new Coordinate(4, 0)));
    }
}
