package Exeptions;

public class NoValidMoveException extends Exception {

    public NoValidMoveException(String errorMessage) {

        super(errorMessage);
    }
}
