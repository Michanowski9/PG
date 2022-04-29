public class DoneTask {
    private final int jobId;
    private final int precision;
    private double piValue;
    private double errorValue;
    private int iterations;

    public DoneTask(int jobId, int precision) {
        this.jobId = jobId;
        this.precision = precision;
    }

    public double getPiValue() {
        return piValue;
    }


    public int getJobId() {
        return jobId;
    }

    public int getPrecision() {
        return precision;
    }

    public void setPiValue(double piValue) {
        this.piValue = piValue;
        this.errorValue = Math.abs(this.piValue - Math.PI);
    }

    public void setIterations(int iterations) {
        this.iterations = iterations;
    }

    public double getErrorValue() {
        return errorValue;
    }

    public int getIterations() {
        return iterations;
    }
}
