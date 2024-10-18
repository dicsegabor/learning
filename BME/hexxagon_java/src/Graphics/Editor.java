package Graphics;

import Controls.Coordinate;
import Enums.UnitType;
import IO.BoardIOHandler;
import javafx.geometry.Point2D;
import javafx.scene.Group;
import javafx.scene.control.Button;

import java.util.ArrayList;

/**
 * Az editort valositja meg.
 */
public class Editor extends GUIBase{

    private Controller controller;
    private Group root = new Group();

    private ArrayList<Button> currentUnits = new ArrayList<>();
    private UnitType currentlyPlacing = UnitType.HOLE;
    private int currentBoard = 1;

    /**
     * Letrehozaskor kesziti el a kinezetet. Hozzadja a hatteret valamint a gombokat, es beallitja a gombok viselkedeset.
     * @param controller A tartalmazo osztaly.
     */
    public Editor(Controller controller) {

        this.controller = controller;

        //Making the background
        root.getChildren().add(loadBackGround("Editor"));

        //Making the main buttons
        Button menuButton = makeButton("Menu Button", new Point2D(76, 967));
        menuButton.setOnAction(event -> {
            BoardIOHandler.save(controller.gameBoard, "Save " + currentBoard);
            controller.gameBoard = BoardIOHandler.load("Save " + currentBoard);
            controller.primaryStage.getScene().setRoot(controller.menu.getRoot());
        });
        root.getChildren().add(menuButton);

        Button save1Button = makeButton("Save 1 Button", new Point2D(1355, 50));
        Button save2Button = makeButton("Save 2 Button", new Point2D(1355, 50));
        save2Button.setVisible(false);
        Button save3Button = makeButton("Save 3 Button", new Point2D(1355, 50));
        save3Button.setVisible(false);
        Button save4Button = makeButton("Save 4 Button", new Point2D(1355, 50));
        save4Button.setVisible(false);
        Button save5Button = makeButton("Save 5 Button", new Point2D(1355, 50));
        save5Button.setVisible(false);

        save1Button.setOnAction(value -> { save1Button.setVisible(false); save2Button.setVisible(true);
            BoardIOHandler.save(controller.gameBoard, "Save 1");
            controller.gameBoard = BoardIOHandler.load("Save 2"); addUnits(); currentBoard = 1; });
        save2Button.setOnAction(value -> { save2Button.setVisible(false); save3Button.setVisible(true);
            BoardIOHandler.save(controller.gameBoard, "Save 2");
            controller.gameBoard = BoardIOHandler.load("Save 3"); addUnits(); currentBoard = 2; });
        save3Button.setOnAction(value -> { save3Button.setVisible(false); save4Button.setVisible(true);
            BoardIOHandler.save(controller.gameBoard, "Save 3");
            controller.gameBoard = BoardIOHandler.load("Save 4"); addUnits(); currentBoard = 3; });
        save4Button.setOnAction(value -> { save4Button.setVisible(false); save5Button.setVisible(true);
            BoardIOHandler.save(controller.gameBoard, "Save 4");
            controller.gameBoard = BoardIOHandler.load("Save 5"); addUnits(); currentBoard = 4; });
        save5Button.setOnAction(value -> { save5Button.setVisible(false); save1Button.setVisible(true);
            BoardIOHandler.save(controller.gameBoard, "Save 5");
            controller.gameBoard = BoardIOHandler.load("Save 1"); addUnits(); currentBoard = 5; });

        root.getChildren().add(save5Button);
        root.getChildren().add(save4Button);
        root.getChildren().add(save3Button);
        root.getChildren().add(save2Button);
        root.getChildren().add(save1Button);

        //Making the placing chooser buttons
        ArrayList<Button> placingTypeChooseButtons = new ArrayList<>();

        Button chooseHoleButton = makeButton("Active Button", new Point2D(81, 5));
        placingTypeChooseButtons.add(chooseHoleButton);

        Button chooseRedButton = makeButton("Inactive Button", new Point2D(81, 70));
        placingTypeChooseButtons.add(chooseRedButton);

        Button chooseBlueButton = makeButton("Inactive Button", new Point2D(81, 135));
        placingTypeChooseButtons.add(chooseBlueButton);

        setupPlaceButtons(placingTypeChooseButtons);

        root.getChildren().addAll(placingTypeChooseButtons);

        addUnits();
    }

    /**
     * A tabla ertekei alapjan hozzadja az egysegeket jelkepezo gombokat, es beallitja viselkedesuket.
     */
    private void addUnits() {

        root.getChildren().removeAll(currentUnits);
        currentUnits.clear();

        for (Coordinate coordinate : controller.gameBoard.coordinates) {

            switch (controller.gameBoard.getField(coordinate).getContent()) {

                case RED:
                    Button rbt = makeButton("Red", Coordinate.coordinateToPoint(coordinate));
                    rbt.setOnAction(value -> {

                        if(controller.gameBoard.getField(coordinate).content.equals(currentlyPlacing))
                            controller.gameBoard.getField(coordinate).content = UnitType.EMPTY;

                        else
                            controller.gameBoard.getField(coordinate).content = currentlyPlacing;

                        addUnits();
                    });
                    currentUnits.add(rbt);
                    break;

                case BLUE:
                    Button bbt = makeButton("Blue", Coordinate.coordinateToPoint(coordinate));
                    bbt.setOnAction(value -> {

                        if(controller.gameBoard.getField(coordinate).content.equals(currentlyPlacing))
                            controller.gameBoard.getField(coordinate).content = UnitType.EMPTY;

                        else
                            controller.gameBoard.getField(coordinate).content = currentlyPlacing;

                        addUnits();
                    });
                    currentUnits.add(bbt);
                    break;

                case EMPTY:
                    Button ebt = makeButton("Empty", Coordinate.coordinateToPoint(coordinate));
                    ebt.setOnAction(value -> {

                        if(controller.gameBoard.getField(coordinate).content.equals(currentlyPlacing))
                            controller.gameBoard.getField(coordinate).content = UnitType.EMPTY;

                        else
                            controller.gameBoard.getField(coordinate).content = currentlyPlacing;

                        addUnits();
                    });
                    currentUnits.add(ebt);
                    break;

                case HOLE:
                    Button hbt = makeButton("Hole", Coordinate.coordinateToPoint(coordinate));
                    hbt.setOnAction(value -> {

                        if(controller.gameBoard.getField(coordinate).content.equals(currentlyPlacing))
                            controller.gameBoard.getField(coordinate).content = UnitType.EMPTY;

                        else
                            controller.gameBoard.getField(coordinate).content = currentlyPlacing;

                        addUnits();
                    });
                    currentUnits.add(hbt);
                    break;
            }
        }

        root.getChildren().addAll(currentUnits);
    }

    /**
     * Beallitja a szerkesztogombok viselekedeset.
     * @param toggleButtons A gombok, amiket beallit.
     */
    private void setupPlaceButtons(ArrayList<Button> toggleButtons){

        for(int i = 0; i < 3; i++){

            final int fi = i;

            toggleButtons.get(i).setOnAction(value -> {

                if(fi == 0)
                    currentlyPlacing = UnitType.HOLE;

                else if(fi == 1)
                    currentlyPlacing = UnitType.RED;

                else
                    currentlyPlacing = UnitType.BLUE;

                setButtonBackground(toggleButtons.get(fi), "Active Button");
                setButtonBackgrounds(toggleButtons, 0, 3, fi); });
        }
    }

    private void setButtonBackgrounds(ArrayList<Button> buttons, int from, int to, int without){

        for(int i = from; i < to; i++)
            if(i != without)
                setButtonBackground(buttons.get(i), "Inactive Button");
    }

    public Group getRoot(){

        return root;
    }
}
