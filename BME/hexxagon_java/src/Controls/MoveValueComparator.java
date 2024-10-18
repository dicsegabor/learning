package Controls;

import java.util.Comparator;

public class MoveValueComparator implements Comparator<Move>{

    public int compare(Move move1, Move move2) {

        return Integer.compare(move1.value, move2.value);
    }
}
