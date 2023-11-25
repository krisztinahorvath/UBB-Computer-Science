public class KthThread implements Runnable{
    private int[][] result;
    private int k;
    private int stepSize;

    KthThread(int[][] _result, int _k, int _stepSize){
        result = _result;
        k = _k;
        stepSize = _stepSize;
    }

    @Override
    public void run(){
        int nrLines = Main.productNrLines;
        int nrColumns = Main.productNrColumns;

        int i = 0;
        int j = k;

        while(true){
            int columnOverflow = j / nrColumns;
            i += columnOverflow;
            j -= columnOverflow * nrColumns;

            if(i >= nrLines)
                break;

            result[i][j] = Matrix.computeElement(Main.matrix1, Main.matrix2, i, j);
            j += stepSize;
        }
    }
}
