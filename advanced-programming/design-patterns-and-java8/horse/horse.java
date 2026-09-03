public class horse implements aliveCreature {
    private final String color;


    public horse(String color) {
        this.color = color;
    }

    public String getColor() {
        return color;
    }
    @Override
    public String worship() {
        return "sit down";
    }
}
