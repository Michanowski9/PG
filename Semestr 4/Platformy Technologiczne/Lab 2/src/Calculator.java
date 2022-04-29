public class Calculator implements Runnable{
    private final Resource resource;

    public Calculator(Resource resource) {
        this.resource = resource;
    }

    @Override
    public void run() {
        while(!Thread.interrupted()) {
            try {
                Task currentTask = resource.takeTask();
                System.out.println("    Getting id:" + currentTask.getJobId());

                DoneTask calculatedPi = calculatePi(currentTask);
                System.out.println("        Putting Calculated " +
                        " id:" + calculatedPi.getJobId() +
                        " PI:" + calculatedPi.getPiValue() +
                        " iter:" + calculatedPi.getIterations() +
                        " error:" + calculatedPi.getErrorValue());

                resource.putResult(calculatedPi);
            } catch (InterruptedException ex) {
                System.out.println(ex);
                break;
            }
        }
    }

    private DoneTask calculatePi(Task task) throws InterruptedException {
        DoneTask result = new DoneTask(task.getJobId(), task.getPrecision());
        double tempPi = 0;
        int n = 1;

        while ((Math.abs(tempPi - Math.PI) > Math.pow(10, -result.getPrecision()))){
            if (Thread.interrupted()) {
                throw new InterruptedException();
            }
            tempPi += 4 * (n % 2 == 0 ? -1.0 : 1.0) / (2 * n - 1);
            n++;
        }

        result.setPiValue(tempPi);
        result.setIterations(n);
        return result;
    }
}
