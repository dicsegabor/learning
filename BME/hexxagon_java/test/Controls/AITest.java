package Controls;

import Enums.UnitType;
import Exeptions.NoValidMoveException;
import IO.BoardIOHandler;
import org.junit.Test;
import org.junit.jupiter.api.BeforeEach;

import static org.junit.Assert.*;

public class AITest {

    Board testBoard;
    AI red, blue;

    @BeforeEach
    public void setup(){

        testBoard = BoardIOHandler.load("defaultBoard");
        red = new AI(UnitType.RED, testBoard, 1);
        blue = new AI(UnitType.BLUE, testBoard, 1);
    }

    @Test
    public void testAIBestMove() throws NoValidMoveException {

        testBoard.makeMove(red.bestMove());

        assertEquals(1, testBoard.getValue());
    }
}