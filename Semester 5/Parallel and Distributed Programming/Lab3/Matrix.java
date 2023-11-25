import java.util.Random;

public class Matrix {
    private int[][] matrix;
    private int nrLines;
    private int nrColumns;

    Matrix(int _nrLines, int _nrColumns){
        matrix = new int[_nrLines][_nrColumns];
        nrLines = _nrLines;
        nrColumns = _nrColumns;

        Random random = new Random();
        for(int i = 0; i < nrLines; i++)
            for(int j = 0; j < nrColumns; j++)
                matrix[i][j] = random.nextInt(10);
    }

    Matrix(int[][] _matrix){
        matrix = _matrix;
        nrLines = _matrix.length;
        nrColumns = _matrix[0].length;
    }

    public int getNrLines(){
        return nrLines;
    }

    public int getNrColumns(){
        return nrColumns;
    }

    public int getElement(int line, int column){
        return matrix[line][column];
    }

    public static int computeElement(Matrix matrix1, Matrix matrix2, int line, int column){
        int result = 0;
        for(int i = 0; i < matrix1.getNrColumns(); i++)
            result += matrix1.getElement(line, i) * matrix2.getElement(i,column);

        return result;
    }

    public static Matrix computeSequentialProduct(Matrix matrix1, Matrix matrix2){
        int[][] product = new int[matrix1.getNrLines()][matrix2.getNrColumns()];
        for(int i = 0; i < matrix1.getNrLines(); i++)
            for(int j = 0; j < matrix2.getNrColumns(); j++)
                product[i][j] = computeElement(matrix1, matrix2, i, j);

        return new Matrix(product);
    }

    @Override
    public String toString(){
        StringBuilder stringBuilder = new StringBuilder();

        for(int i = 0; i < nrLines; i++){
            for(int j = 0; j < nrColumns; j++)
                stringBuilder.append(matrix[i][j]).append(" ");
            stringBuilder.append("\n");
        }
        stringBuilder.append("\n");

        return stringBuilder.toString();
    }

    @Override
    public boolean equals(Object obj){
        if (!(obj instanceof Matrix))
            return false;

        if(nrLines != ((Matrix) obj).nrLines || nrColumns != ((Matrix) obj).nrColumns)
            return false;

        for(int i = 0; i < nrLines; i++)
            for(int j = 0; j < nrColumns; j++)
                if(matrix[i][j] != ((Matrix) obj).getElement(i, j))
                    return false;

        return true;
    }
}
