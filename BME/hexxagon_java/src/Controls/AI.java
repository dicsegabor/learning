package Controls;

import Enums.MoveType;
import Enums.UnitType;
import Exeptions.NoValidMoveException;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;

/**
 * A szamitasokat vegzo osztaly.
 * Tarolja a sajat szinet, a tablat, amin szamol, valamint a lepesek szamat, amennyivel elore szamol.
 */
public class AI {

    private final UnitType team;
    private Board calculatorBoard;
    private final int level;

    public AI(UnitType team, Board board, int level) {

        this.team = team;
        calculatorBoard = board;
        this.level = level;
    }

    /**
     * Visszater az altala kiszamitott legjobb lepessel. Ha nincs vegrehajthato lepes, akkor Exception-t dob.
     * @return Move
     * @throws NoValidMoveException Nincs lehetseges lepes.
     */
    public Move bestMove() throws NoValidMoveException {

        ArrayList<Move> moves;

        try{ moves = getPossibleMoves(); }
        catch (NoValidMoveException e) { throw new NoValidMoveException(""); }

        calculateMoveValues(moves);

        return getRandomMove(getBestMoves(moves));
    }

    /**
     * A tabla alapjan visszater az osszes lehetseges lepessel.
     * @return ArrayList
     * @throws NoValidMoveException Nincs lehetseges lepes.
     */
    private ArrayList<Move> getPossibleMoves() throws NoValidMoveException {

        ArrayList<Coordinate> sources = getPossibleSources();
        ArrayList<Move> moves = new ArrayList<>();

        if(sources.isEmpty())
            throw new NoValidMoveException("");

        for(Coordinate source : sources) {

            ArrayList<Coordinate> possibleFields = calculatorBoard.getSpecifiedFieldsInRange(source, MoveType.SHORT, UnitType.EMPTY);
            possibleFields.addAll(calculatorBoard.getSpecifiedFieldsInRange(source, MoveType.LONG, UnitType.EMPTY));

            for (Coordinate target : possibleFields) {

                    Move move = new Move(source, target);

                    if (move.isValid())
                        moves.add(move);
            }
        }

        if(moves.isEmpty())
            throw new NoValidMoveException("");

        return moves;
    }

    /**
     * A tabla alapjan visszater az osszer lehetseges forrassal.
     * Amilyen szinu az AI, az olyan tartalmu mezok koordinatajaval.
     * @return ArrayList
     */
    private ArrayList<Coordinate> getPossibleSources() {

        ArrayList<Coordinate> sources = new ArrayList<>();

        for(Coordinate c : calculatorBoard.usefulCoordinates)
            if (calculatorBoard.getField(c).getContent().equals(team))
                sources.add(calculatorBoard.getField(c).getPosition());

        return sources;
    }

    /**
     * Egy kapott listabol random kivalaszt egy elemt.
     * @param moves Kapott lepesek listaja.
     * @return Move
     */
    private Move getRandomMove(ArrayList<Move> moves){

        Random rand = new Random();
        int chosen = Math.abs(rand.nextInt()) % moves.size();
        return moves.get(chosen);
    }

    /**
     * A kapott listabol kivalsztja a legjobb lepest.
     * Ha piros az AI, akkor a legnagyobb ertekuvel, ha kek, akkor a legkisebbel.
     * @param moves Kapott lepesek listaja.
     * @return ArrayList
     */
    private ArrayList<Move> getBestMoves(ArrayList<Move> moves){

        int bestScore;

        if(team.equals(UnitType.RED))
            bestScore = Collections.max(moves, new MoveValueComparator()).value;

        else
            bestScore = Collections.min(moves, new MoveValueComparator()).value;

        ArrayList<Move> bestMoves = new ArrayList<Move>();

        for(Move move : moves)
            if(move.value == bestScore)
                bestMoves.add(move);

        return bestMoves;
    }

    /**
     * A tabla alapjan kiszamolja, hogy egy lepes vegrehajtasa utan mennyi a tabla erteke, es azt hozzarendeli a lepeshez.
     * Tobb lepesnel annyiszor hiv meg eg egyes szintut, mint amennyi az AI szintje, es az osszes lepes utan vizsgalja a tabla erteket.
     * @param moves Kapott lepesek listaja.
     */
    private void calculateMoveValues(ArrayList<Move> moves){

        Board temp = new Board(calculatorBoard);

        for(Move move : moves) {

            temp.makeMove(move);

            if(level > 1){

                int i = level;
                UnitType actualTeam = team.getOpposite();
                while (i-- > 1){

                    AI nextLevel = new AI(actualTeam, temp, 1);
                    try {  temp.makeMove(nextLevel.bestMove()); } catch (NoValidMoveException e) { break; }
                    actualTeam = actualTeam.getOpposite();
                }
            }

            move.value = temp.getValue();
            temp.reset();
        }
    }
}