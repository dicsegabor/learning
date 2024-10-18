package Graphics;

import Controls.Coordinate;
import Controls.Move;
import Enums.MoveType;
import Enums.UnitType;
import Exeptions.NoValidMoveException;
import javafx.geometry.Point2D;
import javafx.scene.Group;
import javafx.scene.Node;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.scene.text.Font;
import javafx.scene.text.FontPosture;
import javafx.scene.text.FontWeight;

/**
 * A gamet valositja meg.
 */
import java.util.ArrayList;

public class Game extends GUIBase {

    private Controller controller;
    private Group root = new Group();
    
    private ArrayList<Button> currentSelection = new ArrayList<>();
    private ArrayList<Node> currentState = new ArrayList<>();
    private ArrayList<Button> currentUnits = new ArrayList<>();
    private Coordinate from = null, to = null;

    /**
     * Letrehozaskor kesziti el a kinezetet. Hozzadja a hatteret valamint a gombokat, es beallitja a gombok viselkedeset.
     * @param controller A tartalmazo osztaly.
     */
    public Game(Controller controller) {

        this.controller = controller;

        //Making the background
        root.getChildren().add(loadBackGround("Game"));

        //Making the main buttons
        Button menuButton = makeButton("Menu Button", new Point2D(76, 967));
        menuButton.setOnAction(event -> {

            controller.gameBoard.reset();
            root.getChildren().removeAll(currentSelection);
            controller.primaryStage.getScene().setRoot(controller.menu.getRoot());
        });
        root.getChildren().add(menuButton);
    }

    /**
     * A tabla ertekei alapjan hozzadja az egysegeket jelkepezo gombokat, es beallitja viselkedesuket.
     */
    public void addUnits() {

        root.getChildren().removeAll(currentUnits);
        currentUnits.clear();

        for (Coordinate coordinate : controller.gameBoard.coordinates) {

            switch (controller.gameBoard.getField(coordinate).getContent()){

                case RED:
                    Button rbt = makeButton("Red", Coordinate.coordinateToPoint(coordinate));
                    if(controller.gameBoard.getPreviousPlayer().equals(UnitType.BLUE))
                        rbt.setOnAction(value -> { from = coordinate; displayPossibilities(coordinate); });
                    currentUnits.add(rbt);
                    break;

                case BLUE:
                    Button bbt = makeButton("Blue", Coordinate.coordinateToPoint(coordinate));
                    if(controller.gameBoard.getPreviousPlayer().equals(UnitType.RED))
                        bbt.setOnAction(value -> { from = coordinate; displayPossibilities(coordinate); });
                    currentUnits.add(bbt);
                    break;

                case HOLE:
                    currentUnits.add(makeButton("Hole", Coordinate.coordinateToPoint(coordinate)));
                    break;
            }
        }

        root.getChildren().addAll(currentUnits);
    }

    /**
     * Egy egysegre kattintva kijelzi a hozza kapcsolodo lepesi lehetosegeket.
     * @param center
     */
    private void displayPossibilities(Coordinate center) {

        root.getChildren().removeAll(currentSelection);
        currentSelection.clear();

        ArrayList<Button> buttons = new ArrayList<>();

        ArrayList<Coordinate> shortMoves = new ArrayList<>(controller.gameBoard.getSpecifiedFieldsInRange(center, MoveType.SHORT, UnitType.EMPTY));

        for(Coordinate c : shortMoves){

            Button bt = makeButton("Short Move", Coordinate.coordinateToPoint(c));
            bt.setOnAction(value -> { to = c; root.getChildren().removeAll(currentSelection); makeMove(new Move(from, to)); nextPlayer(); });
            buttons.add(bt);
        }

        ArrayList<Coordinate> longMoves = new ArrayList<>(controller.gameBoard.getSpecifiedFieldsInRange(center, MoveType.LONG, UnitType.EMPTY));

        for(Coordinate c : longMoves){

            Button bt = makeButton("Long Move", Coordinate.coordinateToPoint(c));
            bt.setOnAction(value -> { to = c; root.getChildren().removeAll(currentSelection); makeMove(new Move(from, to)); nextPlayer(); });
            buttons.add(bt);
        }

        Button bt = makeButton("Selected", Coordinate.coordinateToPoint(center));
        buttons.add(bt);

        currentSelection.addAll(buttons);

        root.getChildren().addAll(currentSelection);
    }

    /**
     * Elinditja a jatekot a jatekosok tipusa alapjan.
     */
    public void startGame(){

        if(controller.red == null || controller.blue == null){

            controller.primaryStage.getScene().setRoot(root);
            addUnits();
            drawState();
        }

        if(controller.red != null && controller.blue != null)
            AIvsAI();

        if(controller.red != null)
            nextPlayer();
    }

    /**
     * A kovetkezo jatekos lepese. Ha ember az illeto, akkor nem tortenik semmi.
     */
    private void nextPlayer(){

        try {

            if (controller.red != null)
                makeMove(controller.red.bestMove());

            else if (controller.blue != null)
                makeMove(controller.blue.bestMove());
        }

        catch (NoValidMoveException e) { controller.primaryStage.getScene().setRoot(controller.end.getRoot()); }

        addUnits();
    }

    /**
     * Specialis eset, amikor ket AI harcol egymas ellen.
     * Nincs kepi megjelenites.
     */
    private void AIvsAI(){

        try {

            while (true) {

                makeMove(controller.red.bestMove());
                makeMove(controller.blue.bestMove());
            }
        }

        catch (NoValidMoveException e ) { controller.primaryStage.getScene().setRoot(controller.end.getRoot()); }
    }

    /**
     * Vegrehajt egy lepest, kijelzi az azt koveto allapotot, valamint leellenorzi, hogy vege-e a jateknak.
     * @param move A lepes, amit vegrehajt.
     */
    private void makeMove(Move move){

        controller.gameBoard.makeMove(move);
        addUnits();
        drawState();
        if(controller.gameBoard.testForEnd()){

            controller.end = new End(controller);
            controller.primaryStage.getScene().setRoot(controller.end.getRoot());
        }
    }

    /**
     * Az eredmenyjezot rajzolja ki a bal also sarokban.
     */
    private void drawState(){

        root.getChildren().removeAll(currentState);
        currentState.clear();

        Label redText = new Label(Integer.toOctalString(controller.gameBoard.getRedCount()));
        redText.setFont(Font.font("verdana", FontWeight.BOLD, FontPosture.REGULAR, 30 * heightRatio));
        redText.setTextFill(Color.WHITE);
        placeNode(redText, new Point2D(1650, 955));

        Rectangle redState = new Rectangle();
        redState.setFill(Color.RED);
        redState.setWidth(controller.gameBoard.getRedCount() * 3 * widthRatio);
        redState.setHeight(50 * heightRatio);
        placeNode(redState, new Point2D(1700 - redState.getWidth() , 950));
        currentState.add(redState);
        currentState.add(redText);

        Label blueText = new Label(Integer.toOctalString(controller.gameBoard.getBlueCount()));
        blueText.setFont(Font.font("verdana", FontWeight.BOLD, FontPosture.REGULAR, 30 * heightRatio));
        blueText.setTextFill(Color.WHITE);
        placeNode(blueText, new Point2D(1650, 1015));

        Rectangle blueState = new Rectangle();
        blueState.setFill(Color.BLUE);
        blueState.setWidth(controller.gameBoard.getBlueCount() * 3 * widthRatio);
        blueState.setHeight(50 * heightRatio);
        placeNode(blueState, new Point2D(1700 - blueState.getWidth() , 1010));
        currentState.add(blueState);
        currentState.add(blueText);

        root.getChildren().addAll(currentState);
    }
}
