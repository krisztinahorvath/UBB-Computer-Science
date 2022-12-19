package view;

public class ExitCommand extends Command{
    public ExitCommand(int k, String d) {
        super(k, d);
    }

    @Override
    public void execute() {
        System.exit(0);
    }
}
