package Application;

import Graphics.Controller;
import javafx.application.Application;
import javafx.stage.Stage;


public class Main extends Application {

    private Controller controller;

    @Override
    public void start(Stage primaryStage) {

        controller = new Controller(primaryStage);

        controller.menu.setupStage(primaryStage);

        primaryStage.setScene(controller.menu.makeScene());

        primaryStage.show();
    }
}
