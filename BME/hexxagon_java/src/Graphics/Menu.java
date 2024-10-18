package Graphics;

import Controls.AI;
import Enums.UnitType;
import javafx.geometry.Point2D;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.paint.Color;
import javafx.stage.Stage;

import java.util.ArrayList;

/**
 * A menut valositja meg.
 */
public class Menu extends GUIBase {

    private Controller controller;
    private Group root = new Group();

    /**
     * Letrehozaskor kesziti el a kinezetet. Hozzadja a hatteret valamint a gombokat, es beallitja a gombok viselkedeset.
     * @param controller A tartalmazo osztaly.
     */
    public Menu(Controller controller) {

        this.controller = controller;

        //Making the background
        root.getChildren().add(loadBackGround("Menu"));

        //Making the main buttons
        Button startGameButton = makeButton("Start Game Button", new Point2D(200, 896));
        startGameButton.setOnAction(event -> {

            controller.game.startGame();
        });
        root.getChildren().add(startGameButton);

        root.getChildren().add(makeButton("Return To Demo Button", new Point2D(200, 966)));

        Button configureBoardButton = makeButton("Configure Board Button", new Point2D(999, 896));
        configureBoardButton.setOnAction(event -> {

            controller.primaryStage.getScene().setRoot(controller.editor.getRoot());
        });
        root.getChildren().add(configureBoardButton);

        Button quitToDosButton = makeButton("Quit To Dos Button", new Point2D(999, 966));
        quitToDosButton.setOnAction(event -> {

            controller.primaryStage.close();
        });
        root.getChildren().add(quitToDosButton);

        //Making the red player type chooser buttons
        Button redLevelHuman = makeButton("Active Button", new Point2D(184, 205));
        root.getChildren().add(redLevelHuman);

        Button redLevelAI1 = makeButton("Inactive Button", new Point2D(184, 270));
        root.getChildren().add(redLevelAI1);

        Button redLevelAI2 = makeButton("Inactive Button", new Point2D(184, 335));
        root.getChildren().add(redLevelAI2);

        Button redLevelAI3 = makeButton("Inactive Button", new Point2D(184, 400));
        root.getChildren().add(redLevelAI3);

        //Making the blue player type chooser buttons
        Button blueLevelHuman = makeButton("Active Button", new Point2D(983, 205));
        root.getChildren().add(blueLevelHuman);

        Button blueLevelAI1 = makeButton("Inactive Button", new Point2D(983, 270));
        root.getChildren().add(blueLevelAI1);

        Button blueLevelAI2 = makeButton("Inactive Button", new Point2D(983, 335));
        root.getChildren().add(blueLevelAI2);

        Button blueLevelAI3 = makeButton("Inactive Button", new Point2D(983, 400));
        root.getChildren().add(blueLevelAI3);

        //Setting up all the chooser buttons
        ArrayList<Button> playerChooseButtons = new ArrayList<>();

        for (int i = 5; i < 13; i++)
            playerChooseButtons.add((Button)root.getChildren().get(i));

        setupMenuPlayerButtons(playerChooseButtons);

        //Making some worthless shiny buttons
        root.getChildren().add(makeButton("Active Button", new Point2D(184 , 637)));
        root.getChildren().add(makeButton("Inactive Button", new Point2D(184 , 702)));
        root.getChildren().add(makeButton("Inactive Button", new Point2D(184 , 767)));
        root.getChildren().add(makeButton("Active Button", new Point2D(983 , 637)));
        root.getChildren().add(makeButton("Inactive Button", new Point2D(983 , 702)));
        root.getChildren().add(makeButton("Inactive Button", new Point2D(983 , 767)));
    }

    /**
     * Beallitja a nehezseg valasztasahoz szukseges gombokat.
     * @param toggleButtons
     */
    private void setupMenuPlayerButtons(ArrayList<Button> toggleButtons){

        for(int i = 0; i < 4; i++){

            final int fi = i;

            toggleButtons.get(i).setOnAction(value -> {

                if(fi == 0)
                    controller.red = null;

                else
                    controller.red = new AI(UnitType.RED, controller.gameBoard, fi);

                setButtonBackground(toggleButtons.get(fi), "Active Button");
                setButtonBackgrounds(toggleButtons, 0, 4, fi); });
        }

        for(int i = 4; i < 8; i++){

            final int fi = i;

            toggleButtons.get(i).setOnAction(value -> {

                if(fi == 4)
                    controller.blue = null;

                else
                    controller.blue = new AI(UnitType.BLUE, controller.gameBoard, fi - 4);

                setButtonBackground(toggleButtons.get(fi), "Active Button");
                setButtonBackgrounds(toggleButtons, 4, 8, fi); });
        }
    }

    private void setButtonBackgrounds(ArrayList<Button> buttons, int from, int to, int without){

        for(int i = from; i < to; i++)
            if(i != without)
                setButtonBackground(buttons.get(i), "Inactive Button");
    }

    /**
     * Teljes kepernyosre allitja a kapott ablakot.
     * @param stage Az ablak, amit beallit.
     */
    public void setupStage(Stage stage){

        stage.setFullScreen(true);
        setExitKey(stage, KeyCode.ESCAPE);
        stage.setFullScreenExitHint("");
    }

    /**
     * Az ESCAPE billentyut beallitja, hogy zarja be az ablakot.
     * @param stage Az ablak, amit beallit.
     * @param key A billentyu, amit beallit.
     */
    private void setExitKey(Stage stage, KeyCode key){

        stage.addEventHandler(KeyEvent.KEY_PRESSED, (KeyEvent event) -> {

            if (key == event.getCode())
                stage.close();
        });
    }

    /**
     * Keszit egy Scene-t, ugy hogy megfelejen az aktualis felbontasnak.
     * @return Scene
     */
    public Scene makeScene(){

        return new Scene(root, primaryScreenBounds.getWidth(), primaryScreenBounds.getHeight(), Color.BLACK);
    }

    public Group getRoot(){

        return root;
    }
}
