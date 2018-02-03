
public class MinMax {
    private String name;
    private int value;
    private int index;

    MinMax() {    };

    MinMax(String name, int value, int index) {
        this.name = name;
        this.value = value;
        this.index = index;
    }

    public void setValue(int value) {
        this.value = value;
    }

    public void setIndex(int index) {
        this.index = index;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getValue() {
        return this.value;
    }

    public int getIndex() {
        return this.index;
    }

    public String getName() {
        return this.name;
    }
}
