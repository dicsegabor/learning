package Controls;

import Enums.UnitType;

import java.io.Serializable;

/**
 * Ebbol epul fel a jatektabla. Taolja a poziciojat, valamint a tartalmat.
 */
public class Field  implements Serializable {

    private final Coordinate position;
    public UnitType content;

    public Field( Coordinate position,  UnitType content) {

        this.position = position;
        setContent(content);
    }

    void setContent( UnitType content){

        this.content = content;
    }

    public Coordinate getPosition(){

        return position;
    }

    public int getValue() {

        return content.getValue();
    }

    public UnitType getContent() {

        return content;
    }

    @Override
    public boolean equals( Object o){

        return getValue() == ((Field)o).getValue() && content.equals(((Field)o).content);
    }
}