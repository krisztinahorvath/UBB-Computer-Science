import java.util.HashMap;
import java.util.Map;

public class Colors {
    private int noOfColors;
    private Map<Integer,String> colors;

    public Colors(int n){
        noOfColors = n;

        colors = new HashMap<>();
        for (int code = 0; code < n ; code++)
            colors.put(code, "");
    }

    public void addColor(int code, String color) {
        colors.put(code, color);
    }

    public Map<Integer, String> getColorNamesForCodes(int[] codes) {
        Map<Integer,String> result = new HashMap<>();

        for(int i = 0; i < codes.length; i++) {
            String color = colors.get(codes[i]);
            result.put(i, color);
        }

        return result;
    }

    public int getNoOfColors() { return noOfColors; }
}