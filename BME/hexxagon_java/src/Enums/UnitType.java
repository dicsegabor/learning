package Enums;

/**
 * Tarolja a tablan elofordulo egysegek tipusat.
 * SPACE = helykitotlto mezo a hatszog alaku mezok miatt.
 */
public enum UnitType {

    BLUE, RED, EMPTY, HOLE, SPACE;

    /**
     * A ket ellentetes szin miatt kell.
     * @return UnitType
     */
    public UnitType getOpposite(){

        if(this.isEmpty())
            return EMPTY;

        return this.equals(RED) ? BLUE : RED;
    }

    /**
     *Ebbol hatarozzuk meg a mezo erteket, es ez a szamolas alapja.
     * RED = 1
     * BLUE = -1
     * EMPTY = 0
     * @return int
     */
    public int getValue(){ return (this.isEmpty() ? 0 : (this.equals(RED) ? 1 : -1)); }

    public Boolean isEmpty(){

        return this.equals(EMPTY);
    }

    /**
     * Igazzal ter vissza, ha nem HOLE, vagy SPACE
     * @return Boolean
     */
    public Boolean isUsable() { return !(this.equals(HOLE) || this.equals(SPACE)); }

    /**
     * Stringbol sajat tipusra alakitja. Korabbi beolvasashoz kellet, illetve a szerializalas hibainak kikuszobolesere.
     * @param s A string, amit atalakit.
     * @return UnitType
     */
    public static UnitType parseUnitType(String s){

        switch (s) {

            case "RED": return UnitType.RED;
            case "BLUE": return UnitType.BLUE;
            case "EMPTY": return UnitType.EMPTY;
            case "HOLE": return UnitType.HOLE;
            default: return UnitType.SPACE;
        }
    }
}
