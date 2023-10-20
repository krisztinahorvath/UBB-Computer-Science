import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.TimeUnit;

class Operation{
    public int serialNo;
    public int srcAccountId;
    public int destAccountId;
    public int amount;

    @Override
    public  String toString(){
        return "SerialNo: " + serialNo + ", srcAccountId: " + srcAccountId + ", destAccountId: " + destAccountId
                + ", Amount: " + amount;
    }
}

class Account {
    public int accountId;
    public int currentBalance;
    public int initialBalance;
    public List<Operation> logs = new ArrayList<>(); // all the operations of this bank account

    @Override
    public String toString(){
        return "Account: " + accountId + ", currentBalance: " + currentBalance +
                ", initialBalance: " + initialBalance;
    }
}

public class BankAccounts{
    private int nextSerialNo = 0;
    private final Object mutexSerialNo = new Object();
    private List<Account> accountList = new ArrayList<>();

    private int generateRandomNoInRange(int min, int max){
        return ThreadLocalRandom.current().nextInt(min, max + 1); // [min, max) for this function
    }

    private void createBankAccounts(int n){
        for (int i = 0; i < n; i++){
            Account account = new Account();
            account.accountId = i;
            account.initialBalance = generateRandomNoInRange(0, 1000);
            account.currentBalance = account.initialBalance;

            accountList.add(account);
        }
    }

    private void createTransaction(){
        Operation operation = new Operation(); // to be added to the logs

        // select random source and destination accounts
        int srcAccountId = generateRandomNoInRange(0, accountList.size() - 1);
        int destAccountId = generateRandomNoInRange(0, accountList.size() - 1);

        // make sure the source and destination accounts are different
        while(srcAccountId == destAccountId){
            destAccountId = generateRandomNoInRange(0, accountList.size() - 1);
        }

        operation.srcAccountId = srcAccountId;
        operation.destAccountId = destAccountId;

        // mutex for source account
        synchronized (accountList.get(srcAccountId)){
            // mutex for destination account
            synchronized (accountList.get(destAccountId)){
                operation.amount = generateRandomNoInRange(0, accountList.get(srcAccountId).currentBalance);

                synchronized (mutexSerialNo){
                    operation.serialNo = nextSerialNo++;
                }

                accountList.get(srcAccountId).currentBalance -= operation.amount;
                accountList.get(srcAccountId).logs.add(operation);

                accountList.get(destAccountId).currentBalance += operation.amount;
                accountList.get(destAccountId).logs.add(operation);
            } // end mutex destAccount
        } // end mutex srcAccount

        System.out.println(getCurrentTimestamp() + " " + operation);
    }

    private boolean checkIfOperationFromSrcIsInDestAccount(Operation operation){
        Account destAccount = accountList.get(operation.destAccountId);

        for(Operation op: destAccount.logs){
            if (op.serialNo == operation.serialNo)
                return true;
        }

        return false;
    }

    private boolean checkIfOperationFromDestIsInSrcAccount(Operation operation){
        Account srcAccount = accountList.get(operation.srcAccountId);

        for(Operation op: srcAccount.logs){
            if (op.serialNo == operation.serialNo)
                return true;
        }

        return false;
    }

    private void checkConsistency()  {
        boolean consistent = true;

        for (int i = 0; i < accountList.size() - 1 && consistent; i++){
            synchronized (accountList.get(i)){ // protect the account from any modifications while we are checking for consistency
                Account account = accountList.get(i);
                int currentBalance = account.currentBalance;
                for(Operation operation: account.logs){
                    if(operation.srcAccountId == account.accountId){ // money was withdrawn from the account
                        currentBalance += operation.amount;
                        if(!checkIfOperationFromSrcIsInDestAccount(operation))
                        {
                            consistent = false;
                            break;
                        }
                    }
                    else if(operation.destAccountId == account.accountId){ // money was added to the account
                        currentBalance -= operation.amount;
                        if(!checkIfOperationFromDestIsInSrcAccount(operation)){
                            consistent =  false;
                            break;
                        }
                    }
                }

                if (currentBalance != account.initialBalance){
                    consistent = false;
                    break;
                }
            }
        }

        if(consistent)
            System.out.println("\nConsistency check passed at: " + getCurrentTimestamp() + "\n");
        else
            System.out.println("\nConsistency check failed at: " + getCurrentTimestamp() + "\n");

    }

    public void printAccountWithLogs(){
        for (Account account: accountList){
            System.out.println("\n" + account);
            for(Operation operation: account.logs)
                System.out.println(operation);
        }
    }

    public static String getCurrentTimestamp() {
        SimpleDateFormat sdf = new SimpleDateFormat("HH:mm:ss.SSS");
        return sdf.format(new Date(System.currentTimeMillis()));
    }

    public static void main(String[] args) throws InterruptedException {
        final int NO_BANK_ACCOUNTS = 1000;
        final int NO_THREADS = 10000;
        final int CHECK_INTERVAL_MS = 10;

        BankAccounts bankAccounts = new BankAccounts();
        bankAccounts.createBankAccounts(NO_BANK_ACCOUNTS);

        Thread[] threads = new Thread[NO_THREADS];

        ScheduledExecutorService scheduler = Executors.newScheduledThreadPool(1);
        scheduler.scheduleAtFixedRate(bankAccounts::checkConsistency, 10, CHECK_INTERVAL_MS, TimeUnit.MILLISECONDS);

        long startTime = System.nanoTime();
        for (int i = 0; i < NO_THREADS; i++) {
            threads[i] = new Thread(bankAccounts::createTransaction);
            threads[i].start();
        }

        for (int i = 0; i < NO_THREADS; i++) {
            threads[i].join(); // join them to make sure all finished
        }

        scheduler.shutdown();

        System.out.println("\nFINAL CONSISTENCY CHECK STARTING: " + getCurrentTimestamp());
        bankAccounts.checkConsistency();

        long endTime = System.nanoTime();
        long duration = endTime - startTime;

        long seconds = duration / 1_000_000_000; // 1 second = 1,000,000,000 nanoseconds
        long milliseconds = (duration / 1_000_000) % 1000; // 1 millisecond = 1,000,000 nanoseconds

        System.out.println("DURATION: " + seconds + " seconds " + milliseconds + " milliseconds");

//        bankAccounts.printAccountWithLogs();
    }
}